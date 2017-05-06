//
// Created by lxs on 17-4-13.
//

#include "disk_sampler.h"
#include "../util/math_func.h"
#include <cmath>

bool DiskSampler::next_window() {
    if(not_init())
        return false;
    x_pos++;
    if(x_pos == x_end) {
        x_pos = x_start;
        y_pos++;
    }
    if(y_pos == y_end)
        return false;
    generate_samples();
    return true;
}

void DiskSampler::generate_samples() {
    image_samples.clear();
    len_samples.clear();
    image_sample_index = len_sample_index = 0;
    if(not_init())
        return;
    generate_poisson_sample(1, 1, min_dis, 30, image_samples);
    image_sp_pw = (int)(image_samples.size());
}

bool DiskSampler::get_sample(ComplexSample &sample) {
    if(not_init())
        return false;
    if(image_sample_index == image_sp_pw)
        return false;
    sample.cam.x = x_pos + image_samples[image_sample_index][0];
    sample.cam.y = y_pos + image_samples[image_sample_index][1];
//    sample->cam.len_u = len_samples[cur_sample_index][0];
//    sample->cam.len_v = len_samples[cur_sample_index][1];
    image_sample_index++;
    return true;
}

int DiskSampler::get_all_samples(std::vector<ComplexSample> &samples)
{
    if(not_init())
        return 0;
    int i = 0;
    for(auto &sample : image_samples)
    {
        samples[i].cam.x = x_pos + sample[0];
        samples[i].cam.y = y_pos + sample[1];
        i++;
    }
    image_sample_index = image_sp_pw;
    return i;
}

inline float sample_dis_square(const std::array<float, 2> &sample1, const std::array<float, 2> &sample2)
{
    return (sample1[0] - sample2[0])*(sample1[0] - sample2[0])
           + (sample1[1] - sample2[1])*(sample1[1] - sample2[1]);
}

class Grid
{
public:
    Grid(int nx, int ny, float size, float min_distance, SAMPLES &sample_points) {
        x_cell_n = nx, y_cell_n = ny, cell_size = size, min_dis_square = min_distance*min_distance;
        points = &sample_points;
        status = new bool*[y_cell_n];
        points_index = new int*[y_cell_n];
        bool *data = new bool[x_cell_n * y_cell_n];
        int *index_data = new int[x_cell_n * y_cell_n];
        for(int i = 0; i < y_cell_n; i++, data += x_cell_n, index_data += x_cell_n) {
            status[i] = data;
            points_index[i] = index_data;
        }
    }
    ~Grid() {
        delete []status[0];
        delete []status;
        delete []points_index[0];
        delete []points_index;
    }
    bool put_point_in_grid(const std::array<float, 2> &point) {
        int x_index = (int)(point[0] / cell_size), y_index = (int)(point[1] / cell_size);
        if(check_point_neighbourhood(x_index, y_index, point))
            return false;
        status[y_index][x_index] = true;
        points->push_back(point);
        points_index[y_index][x_index] = (int)points->size() - 1;
        return true;
    }
    bool check_point_neighbourhood(int x_index, int y_index, const std::array<float, 2> &new_point) {
        if(x_index >= x_cell_n || y_index >= y_cell_n)
            return true;
        int x_begin, x_end, y_begin, y_end;
        x_begin = Clamp(x_index - 2, 0, x_cell_n - 1);
        x_end = Clamp(x_index + 2, 0, x_cell_n - 1);
        y_begin = Clamp(y_index - 2, 0, y_cell_n -1);
        y_end = Clamp(y_index + 2, 0, y_cell_n - 1);
        for(int i = y_begin; i <= y_end; i++)
            for(int j = x_begin; j <= x_end; j++)
            {
                if(status[i][j] && sample_dis_square((*points)[points_index[i][j]], new_point) < min_dis_square)
                    return true;
            }
        return false;
    }
    int x_cell_n, y_cell_n;
    float min_dis_square;
    float cell_size;
    bool **status;
    // 相应grid中的点在points这个vector中的序号
    int **points_index;
    std::vector<std::array<float , 2>> *points;
};

std::array<float, 2> generate_random_point_around(const std::array<float, 2> &point, float min_dis)
{
    float radius = min_dis * RandomFloat(1.f, 2.f), angle = RandomFloat(0.f, 2 * PI);
    return {point[0] + radius * std::cos(angle), point[1] + radius * std::sin(angle)};
};

void generate_poisson_sample(int width, int height, float min_distance, int new_points_count,
                            SAMPLES &image_samples)
{
    float cell_size = min_distance / std::sqrt(min_distance);
    int x_cell_n = (int)(width/cell_size), y_cell_n = (int)(height/cell_size);
    Grid grid(x_cell_n, y_cell_n, cell_size, min_distance, image_samples);
    SAMPLES process_list;
    process_list.reserve((unsigned long)(x_cell_n * y_cell_n));
    std::array<float, 2> cur_point, new_point;
    // generate random point
    cur_point[0] = RandomFloat(0, width), cur_point[1] = RandomFloat(0, height);
    grid.put_point_in_grid(cur_point);
    process_list.push_back(cur_point);

    int random_point_index;
    update_random_seed();
    while(!process_list.empty())
    {
        // 从待处理队列中随机取出一个元素
        random_point_index = RandomInt(0, (int)process_list.size() - 1);
        cur_point = process_list[random_point_index];
        process_list[random_point_index] = process_list.back();
        process_list.pop_back();
        for(int i = 0; i < new_points_count; i++)
        {
            new_point = generate_random_point_around(cur_point, min_distance);
            if(new_point[0] > 0.f && new_point[0] < width
               && new_point[1] > 0.f && new_point[1] < height
               && grid.put_point_in_grid(new_point))
                process_list.push_back(new_point);
        }
    }
}
