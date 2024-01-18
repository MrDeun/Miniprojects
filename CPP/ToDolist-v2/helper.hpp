#include <string>
#include <algorithm>

std::string str_tolower(std::string input)
{
    std::transform(input.begin(),input.end(),input.begin(),
                    [](unsigned char c){ return std::tolower(c); }
                    );
    return input;
}