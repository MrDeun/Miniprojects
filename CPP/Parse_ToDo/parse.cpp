#include <iostream>
#include <fstream>
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

std::string extract_words(std::queue<std::string> words)
{
    std::string whole;
    while(!words.empty())
    {
        whole.append(words.front());
        words.pop();
    }
    delete &words;
    return whole;
}

bool is_number(const std::string &s) 
{
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void change_title(std::vector<Task>& tasklist, std::queue<std::string>& words,const uint32_t& index)
{
    if(index > tasklist.size()) // Size Check
        {
            std::cout << "ERROR: Incorrect index - not enough elements in tasklist" << std::endl;
            while (!words.empty())  words.pop();
            delete &words;
            return;
        }
    std::string title = extract_words(words);
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

void new_task(std::vector<Task>& tasklist, std::queue<std::string> words)
{
    std::string task_name;
    while(!words.empty())
    {
        task_name.append(words.front());
        words.pop();
    }
    
    Task new_task{task_name};
    tasklist.push_back(task_name);
    return;
}

void show_tasks(std::vector<Task>& tasklist)
{
    uint32_t index = 0;
    for (auto task_i : tasklist)
    {
        std::cout << ++index <<". " << task_i.state() << std::endl; 
    }
    return;
}

void load_tasklist(std::vector<Task>& tasklist, std::string filename)
{
    if (!tasklist.empty())
    {
        std::cout << "WARNING! Tasklist was already fulfilled! Deleting the list!" << std::endl;
        tasklist.erase(tasklist.begin(),tasklist.end());
    }

    std::ifstream file(filename);
    while (file.good())
    {
        std::string word;
        std::string words;
        do
        {
            file >> word;
            if(!is_number(word))
                words += word + " ";   
            else
                break;
            word.clear();            
        } while (is_number(word));
        
    }
    
    return;
    
}
void save_tasklist(std::vector<Task>& tasklist, std::string filename);
void mark_task(std::vector<Task>& tasklist, uint32_t index)
{
    if(index > tasklist.size())
    {
        std::cout << "ERROR! Index bigger than size of tasklist!" << std::endl;
        return;
    }
    tasklist[index].set_done(true);

    return;
}
void show_help()
{
    std::cout << "show - shows all currently loaded tasks\n"
              << "new [TITLE] - adds new title to the list\n"
              << "delete [INDEX] - deletes task from the list\n"
              << "modify [INDEX] [TITLE] - changes the name of task to another one\n"
              << "save [FILENAME] - saves current tasklist to the file\n"
              << "load [FILENAME] - load a new current tasklist, deleting an already existing one in the process\n"
              << "marked [INDEX] - marks off a task\n"
              << "help - shows this text\n"
              << "exit - exits the program\n";

    return;

}

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
            new_task(tasklist,words);
            break;
        case SHOW:
            delete &words;
            show_tasks(tasklist);
            break;
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
            std::cout << "SAVE FILE NOT IMPLEMENTED YET!" << std::endl;
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