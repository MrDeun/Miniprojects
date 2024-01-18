
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "states.hpp"
#include "task.hpp"

using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

void save_file(const vector<Task> &tasklist, string path) {
  ofstream file(path);
  for (Task element : tasklist) {
    file << element.get_title() << " "<<  element.get_done();
  }
  file.close();
  return;
}

void load_file(vector<Task> &tasklist, string path) {
  tasklist.clear();
  tasklist.shrink_to_fit();

  ifstream file(path);
  if (!file.good()) {
    std::cout << "Savefile not found! Creating a new one!";
    return;
  }

  string task_title{};
  bool task_state{};

  while (file.good()) {
    file >> task_title;
    Task new_task{task_title};
    file >> task_state;
    new_task.set_done(task_state);
    tasklist.push_back(new_task);
    task_title.clear();
  }
}

void modify_task(vector<Task> &tasklist, size_t tasklist_index,
                 string new_title) {
  if (tasklist_index < tasklist.size() || tasklist_index > 0)
    tasklist[tasklist_index].modify_title(new_title);
  else {
    std::cout << "Incorrect index of a task list!";
  }
  return;
}

void new_task(vector<Task> &tasklist, string new_title) {
  Task new_task(new_title);
  tasklist.push_back(new_title);

  return;
}

void delete_task(vector<Task> &tasklist, size_t tasklist_index) {
  if (tasklist.size() < tasklist_index) {
    std::cout << "Incorrect index of task list!";
    return;
  }
  tasklist.erase(tasklist.begin() + tasklist_index);
  tasklist.shrink_to_fit();
  return;
}
void show_tasks(vector<Task> tasklist) {
  for (size_t i = 0; i < tasklist.size(); i++) {
    std::cout << i + 1 << ". " << tasklist[i].state() <<"\n";
  }

  return;
}

void help() {
  std::cout
      << "\n help - displays this image"
      << "\n save [FILE.EXTENSION] - saves current tasklist to specified file"
      << "\n load [FILE.EXTENSION] - load a takslist from specified file"
      << "\n modify [INDEX] [NEW_TITLE] - modifies a task with specified index "
         "with a new title"
      << "\n delete [INDEX] - deletes a specified task from the list"
      << "\n show - shows all currently loaded tasks"
      << "\n marked [INDEX] - marks your task as done"
      << "\n exit - exits the program WITHOUT SAVING!";
  return;
}

void mark_off(vector<Task> &tasklist, size_t tasklist_index) {
  if (tasklist.size() < tasklist_index) {
    std::cout << "\n Incorrect index of tasklist ";
    return;
  }

  tasklist[tasklist_index].set_done(true);
  return;
}

bool process(std::string line, vector<Task> &tasklist) {
  stringstream command_stream(line);
  string keyword{};
  while (command_stream >> keyword) {
    keyword = str_tolower(keyword);
    std::string path{};
    string index{};
    switch (string_to_command[keyword]) {
    case SAVE:
      command_stream >> path;
      save_file(tasklist, path);
      break;
    case LOAD:
      command_stream >> path;
      load_file(tasklist, path);
      break;
    case MODIFY:
      command_stream >> index;
      command_stream >> path;
      modify_task(tasklist, stoi(index) - 1, path);
      break;
    case DELETE:
      command_stream >> index;
      delete_task(tasklist, stoi(index) - 1);
      break;
    case SHOW:
      show_tasks(tasklist);
      break;
    case NEW:
      command_stream >> path;
      new_task(tasklist, path);
      break;
    case MARKED:
      command_stream >> index;
      mark_off(tasklist, stoi(index) - 1);
      break;
    case HELP:
      help();
      break;
    case EXIT:
      return true;
      break;
    default:
      break;
    }
    path.clear();
  }

  return false;
}

int main() {

  vector<Task> tasklist{};
  for (string line; cout << "\nTO DO LIST > " && getline(cin, line);) {
    if (!line.empty() && process(line, tasklist)) {
      line.clear();
      return 0;
    }
    line.clear();
  }
}
