#include<iostream>
#include<sstream>
#include<vector>
#include<queue>
#include<algorithm>

#include "task.hpp"
#include "states.hpp"

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

bool process(std::string line, std::vector<Task> tasklist)
{
    std::stringstream stream_line {line};
    std::string temp;
    std::queue<std::string> words;

    while (stream_line >> temp)
    {
        words.push(temp);
    }

    Command current_command = string_to_command[words.front()];
    words.pop();
    switch(current_command)
    {
        
        case NEW:
        case SHOW:
        case MODIFY:
            int count = stoi(words.front());
            words.pop();
        case DELETE:
        case LOAD:
        case SAVE:
        case MARKED:
        case HELP:
        case EXIT:


        default:
            std::cout << "ERROR: Unknown command" << std::endl;
    }
    


    

    return false;
}
int main()
{
    std::vector<Task> tasklist{};
    for (std::string line; std::cout << "TO DO LIST > " && std::getline(std::cin, line);) 
    {
        if (!line.empty() && process(line, tasklist)) 
        {
            line.clear();
            return 0;
        }
    line.clear();
    }
}