// Concept - take in arguments - string with numbers at the end with tempature
// symbol
//  and tempature symbol that's gonna be a output tempature - program will just
//  print out the converted tempature

#include <iostream>
#include <string>

auto KelwinToCelcius = [](double deg) {return deg - 273.15;};
auto CelciusToKelwin = [](double deg) {  return deg + 273.15;};
auto CelciusToFahrenheit = [](double deg){  return (deg * 9.0 / 5.0) + 32.0;};
auto FahrenheitToCelcius = [](double deg) { return (deg - 32.0) * 5.0 / 9.0; };
auto KelwinToFahrenheit = [](double deg) { return CelciusToFahrenheit(KelwinToCelcius(deg));};
auto FahrenheitToKelvin = [](double deg) { return CelciusToKelwin(FahrenheitToCelcius(deg));};

void decode_argument(std::string tempature_str, double &degrees,
                     char &tempature_symbol) {
  degrees = std::stod(tempature_str,nullptr);
  tempature_symbol = tempature_str.back();
  return;
}

double input_kelwin(double degrees, char tempature_output) {

  switch (tempature_output) {
  case 'k':
  case 'K':
    return degrees;
  case 'c':
  case 'C':
    return KelwinToCelcius(degrees);
  case 'f':
  case 'F':
    return KelwinToFahrenheit(degrees);
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}
double input_celcius(double degrees, char tempature_output) {

  switch (tempature_output) {
  case 'k':
  case 'K':
    return CelciusToKelwin(degrees);
  case 'c':
  case 'C':
    return degrees;
  case 'f':
  case 'F':
    return CelciusToFahrenheit(degrees);
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}
double input_fahrenheit(double degrees, char tempature_output) {

  switch (tempature_output) {
  case 'k':
  case 'K':
    return FahrenheitToKelvin(degrees);
  case 'c':
  case 'C':
    return FahrenheitToCelcius(degrees);
  case 'f':
  case 'F':
    return degrees;
  default:
    std::cout << "Incorrect symbol at first argument" << std::endl;
    return -1;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Wrong amount of arguments - "
              << "Number of degress ended with a tempature symbol and a symbol "
                 "of output tempature"
              << std::endl;

    return -1;
  }

  double degrees{};
  char tempature_input{}, tempature_output{*argv[2]};

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

  std::cout << degrees << tempature_output << "\n";

  return 0;
}
