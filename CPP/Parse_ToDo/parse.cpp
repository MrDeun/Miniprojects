#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>

#include "task.hpp"
#include "states.hpp"

void clear_queue(std::queue<std::string>& queue_in)
{
    while (!queue_in.empty())
    {
        queue_in.pop();
    }
    return;
}

bool is_number(const std::string &s) 
{
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void new_task();
void show_tasks();

void change_title(std::vector<Task>& tasklist, std::queue<std::string>& words,const uint32_t& index)
{
    if(index > tasklist.size()) // Size Check
        {
            std::cout << "ERROR: Incorrect index - not enough elements in tasklist" << std::endl;
            while (!words.empty())  words.pop();
            return;
        }
    std::string title = {};
    while (!words.empty())
    {
        title += words.front() + " ";
        words.pop();
    }
    
    tasklist[index].modify_title(title);
    return;
}

void delete_task(std::vector<Task>& tasklist, uint32_t index)
{
    if(tasklist.size() < index)
        {
            std::cout << "Tasklist doesnt have this many tasks!" << std::endl;
            return;
        }

    tasklist.erase(tasklist.begin() + index);
    tasklist.shrink_to_fit();
    return;
}

void load_tasklist(std::vector<Task>& tasklist, std::string filename);
void save_tasklist(std::vector<Task>& tasklist, std::string filename);
void mark_off_task(std::vector<Task>& tasklist, uint32_t index);
void show_help();

bool process(std::string line, std::vector<Task>& tasklist)
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
            if (!is_number( words.front() )) 
                {std::cout << "ERROR:Second argument not number!\n";return 0;}
            uint32_t count = stoi(words.front());
            words.pop();
            change_title(tasklist,words,count);
            break;
        case DELETE:
            if( !is_number(words.front()) )
                {std::cout << "ERROR:Second argument not number!\n";return 0;}
            uint32_t index = stoi(words.front());
            clear_queue(words);
            delete_task(tasklist,count);
            break;
        case LOAD:
            std::string filename = words.front() + ".txt";
            clear_queue(words);
            load_tasklist(tasklist,filename);
            break;
        case SAVE:
            std::string filename = words.front() + ".txt";
            clear_queue(words);
            save_tasklist(tasklist,filename);
            break;
        case MARKED:
            if(!is_number(words.front()))
                {std::cout << "ERROR:Second argument not number!\n";return 0;}
            uint32_t index = stoi(words.front());
            break;
        case HELP:
            clear_queue(words);
            show_help();
            break;
        case EXIT:
            return true;
        default:
            std::cout << "ERROR: Unknown command" << std::endl;
            break;
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

    return -1;
}