//
// Created by lxs on 17-3-25.
//

#include <fstream>
#include <map>
#include <iostream>
#include <array>
#include <string>
#include <regex>
#include "file_helper.h"

bool if_whitespace(const char &c){
    return (c == ' ' || c == '\t');
}

void parse_obj2polygon(std::vector<Polygon> &shape, const char *filename)
{
    std::ifstream if_file(filename);
    if(!if_file)
    {
        std::cout<<"Can not open file: "<<filename<<std::endl;
        return;
    }
    shape.clear();
    std::vector<Point3D> points;
    std::vector<std::vector<int>> faces;

    // 每一行最长为512个字节
    std::array<char, 512> input_buf;
    std::vector<float> xyz;
    std::vector<int> vertice_index;
    std::smatch str_match;
    std::regex coord_regex("[\\S]+");
    std::regex face_regex[4], face_regex_test[4];
    // 匹配 vertice
    face_regex[0] = std::regex("\\d+"), face_regex_test[0] = std::regex("\\s*\\d+\\s.*");
    // 匹配  vertice/texture
    face_regex[1] = std::regex("\\d+/\\d+"), face_regex_test[1] = std::regex("\\s*\\d+/\\d+\\s.*");
    // 匹配 vertice/texture/normal
    face_regex[2] = std::regex("\\d+/\\d+/\\d+"), face_regex_test[2] = std::regex("\\s*\\d+/\\d+/\\d+\\s.*");
    // 匹配 vertice//normal
    face_regex[3] = std::regex("\\d+//\\d+"), face_regex_test[3] = std::regex("\\s*\\d+//\\d+\\s.*");
    while(if_file.peek() != -1)
    {
        if(!if_file.getline(&input_buf[0], 512))
        {
            std::cout<<"Has a too long line in this file: "<<filename<<std::endl;
            return;
        }
        std::string line_buf(&input_buf[0]);
        // windows下的换行符\r\n,getline认为\n为换行符,因此需删除多余的\r标记
        if(line_buf.size() > 0)
            if(line_buf[line_buf.size() - 1] == '\r')
                line_buf.erase(line_buf.size() - 1);
        // 跳过空行和注释行
        if(line_buf.empty() || line_buf[0] == '#' || line_buf[0] == '\0')
            continue;
        if(line_buf[0] == 'v' && if_whitespace(line_buf[1]))
        {
            line_buf.erase(0, 2);
            xyz.clear();
            while(std::regex_search(line_buf, str_match, coord_regex))
            {
                xyz.push_back(std::stof(str_match.str()));
                line_buf = str_match.suffix().str();
            }
            // 有些obj文件点的坐标有四维
            if(xyz.size() >= 3)
                points.push_back(Point3D(xyz[0], xyz[1], xyz[2]));
            else
            {
                std::cout<<"Error point coordinate"<<std::endl;
                return;
            }
        }
        if(line_buf[0] == 'f' && if_whitespace(line_buf[1]))
        {
            line_buf.erase(0, 2);
            int i = 0;
            for(i = 0; i < 4; i++)
            {
                // 确认文件中对face的描述属于哪一种格式
                if(std::regex_match(line_buf, face_regex_test[i]))
                    break;
            }
            // i >= 4时没有一种模式与输入匹配,输入文件有误
            if(i >= 4)
            {
                std::cout<<"Error face syntax"<<std::endl;
                return;
            }
            vertice_index.clear();
            switch(i)
            {
                case 0:
                    while(std::regex_search(line_buf, str_match, face_regex[0]))
                    {
                        vertice_index.push_back(std::stoi(str_match.str()));
                        line_buf = str_match.suffix().str();
                    }
                    break;
                case 1:
                    while(std::regex_search(line_buf, str_match, face_regex[1]))
                    {
                        unsigned long index = str_match.str().find('/');
                        vertice_index.push_back(stoi(str_match.str().substr(0, index)));
                        line_buf = str_match.suffix().str();
                    }
                    break;
                case 2:
                    while(std::regex_search(line_buf, str_match, face_regex[2]))
                    {
                        unsigned long index = str_match.str().find('/');
                        vertice_index.push_back(stoi(str_match.str().substr(0, index)));
                        line_buf = str_match.suffix().str();
                    }
                    break;
                case 3:
                    while(std::regex_search(line_buf, str_match, face_regex[3]))
                    {
                        unsigned long index = str_match.str().find('/');
                        vertice_index.push_back(stoi(str_match.str().substr(0, index)));
                        line_buf = str_match.suffix().str();
                    }
                    break;
            }
            faces.push_back(vertice_index);
        }
    }
    std::vector<Point3D> polygon_vertics;
    for(std::vector<int> polygon_vertice_index : faces)
    {
        polygon_vertics.clear();
        for(int index : polygon_vertice_index)
        {
            polygon_vertics.push_back(points[index - 1]);
        }
        shape.push_back(Polygon(polygon_vertics));
    }

}

void write_png_file(int image_x, int image_y, float rgb[], std::string filename)
{

}

