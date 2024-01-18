#include <map>
#include <string>

enum Command {
  SHOW,
  NEW,
  DELETE,
  MODIFY,
  SAVE,
  LOAD,
  MARKED,
  HELP,
  EXIT,
};

std::map<std::string, Command> string_to_command{
    {"show", SHOW},     {"new", NEW},   {"delete", DELETE},
    {"modify", MODIFY}, {"save", SAVE}, {"load", LOAD},
    {"help", HELP},     {"exit", EXIT}, {"marked", MARKED}};
