// Concept - take in arguments - string with numbers at the end with tempature
// symbol
//  and tempature symbol that's gonna be a output tempature - program will just
//  print out the converted tempature

#include <iostream>
#include <string>

void decode_argument(std::string tempature_str, double &degrees,
                     char &tempature_symbol) {
  degrees = std::stod(degrees);
  tempature_symbol = tempature_str.back();
  return;
}

double input_kelwin(double degrees, char tempature_output) {

  switch (tempature_output) {
  case 'k':
  case 'K':
    break;
  case 'c':
  case 'C':
    break;
  case 'f':
  case 'F':
    break;
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}
double input_celcius(double degrees, char tempature_output) {

  switch (tempature_output) {
  case 'k':
  case 'K':
    break;
  case 'c':
  case 'C':
    break;
  case 'f':
  case 'F':
    break;
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}
double input_fahrenheit(double degrees, char tempature_output) {

  switch (tempature_input) {
  case 'k':
  case 'K':
    degrees = input_kelwin(degrees, tempature_output);
    break;
  case 'c':
  case 'C':
    degrees = input_celcius(degrees, tempature_output);
    break;
  case 'f':
  case 'F':
    degrees = input_fahrenheit(degrees, tempature_output);
    break;
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Wrong amount of arguments - "
              << "Number of degress ended with a tempature symbol and a symbol "
                 "of output tempature"
              << std::endl;

    return -1;
  }

  double degrees{};
  char tempature_input{}, tempature_output{};

  decode_argument(argv[1], degrees, tempature_input);

  switch (tempature_input) {
  case 'k':
  case 'K':
    degrees = input_kelwin(degrees, tempature_output);
    break;
  case 'c':
  case 'C':
    degrees = input_celcius(degrees, tempature_output);
    break;
  case 'f':
  case 'F':
    degrees = input_fahrenheit(degrees, tempature_output);
    break;
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }

  return 0;
}
