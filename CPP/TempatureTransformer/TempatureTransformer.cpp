// Concept - take in arguments - string with numbers at the end with tempature
// symbol
//  and tempature symbol that's gonna be a output tempature - program will just
//  print out the converted tempature

#include <iostream>
#include <string>

double KelwinToCelcius(double degrees) = [](double deg) -> double {
  return deg - 273.15;
};
double KelwinToFahrenheit(double degrees) = [](double deg) -> double {
  return CelciusToFahrenheit(KelwinToCelcius(deg));
};
double CelciusToKelwin(double degrees) = [](double deg) -> double {
  return deg + 273.15;
};
}
;
double CelciusToFahrenheit(double degrees) = [](double deg) -> double {
  return (deg * 9.0 / 5.0) + 32.0
};
double FahrenheitToKelvin(double degrees) = [](double deg) -> double {
  return FahrenheitToCelcius(CelciusToKelwin(deg));
};
double FahrenheitToCelcius(double degrees) = [](double deg) -> double {
  return (deg - 32.0) * 5.0 / 9.0;
};

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
