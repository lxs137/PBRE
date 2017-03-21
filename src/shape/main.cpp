#include <iostream>
#include <cmath>
int main(int argv, char** argc)
{
    float f = std::sqrt(-1.0f);
    std::cout<<std::isnan(f)<<std::endl<<f<<std::endl;
    return 0;
}
