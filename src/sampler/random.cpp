//
// Created by lxs on 17-4-13.
//

#include "sampler/random.h"

bool RandomSampler::next_window()
{
    if(not_init())
        return false;
    x_pos++;
    if(x_pos == x_end) {
        x_pos = x_start;
        y_pos++;
    }
    if(y_pos == y_end)
        return false;
    image_samples.clear();
    len_samples.clear();
    cur_sample_index = 0;
    generate_samples();
    return true;
}

void RandomSampler::generate_samples()
{
    if(not_init())
        return;
    std::default_random_engine engine(device());
    // float x, y;
    for(int i = 0; i < sp_pw; i++) {
        image_samples[i][0] = distribution(engine);
        image_samples[i][1] = distribution(engine);
    }
}

bool RandomSampler::get_sample(ComplexSample &sample)
{
    if(not_init())
        return false;
    if(cur_sample_index == sp_pw)
        return false;
    sample.cam.x = x_pos + image_samples[cur_sample_index][0];
    sample.cam.y = y_pos + image_samples[cur_sample_index][1];
    sample.cam.len_u = len_samples[cur_sample_index][0];
    sample.cam.len_v = len_samples[cur_sample_index][1];
    cur_sample_index++;
    return true;
}

int RandomSampler::get_all_samples(std::vector<ComplexSample> &samples)
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
    cur_sample_index = sp_pw;
    return i;
}