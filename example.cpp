#include "constants.h"

#include <iostream>

using namespace Plato;

int main() {

  // Version

  std::cout << "Welcome to Plato.Constant v" << Constant::version() << "!\n";
  std::cout << std::endl;

  // Compile time usage

  std::cout << "- Hello, light-year, who are you?\n";
  std::cout << "- Hi! I am " << Distance::LightYear::description << ".\n";
  std::cout << "  That is " << Distance::LightYear::si << " " << Distance::LightYear::si.unit << "\n";
  std::cout << "  or " << Distance::LightYear::cgs << " " << Distance::LightYear::cgs.unit << " if you prefer.\n";
  std::cout << std::endl;

  // With alias

  std::cout << "- Hello, Plank constant, or should I say... h?\n";
  std::cout << "- I am " << Fundamental::h::si << " " << Fundamental::h::si.unit << "\n";
  std::cout << "  id est " << Fundamental::Planck::cgs << " " << Fundamental::Planck::cgs.unit << "\n";
  std::cout << std::endl;

  // Run time usage

  std::cout << "Please enter the name of a constant you wish to learn about:\n";
  std::string tag;
  getline(std::cin, tag);
  Constant constant;
  try {
    constant = ConstantRegister::at(tag);
  } catch (std::runtime_error& e) {
    std::cout << e.what() << "\nTry again!\n";
    getline(std::cin, tag);
    constant = ConstantRegister::at(tag);
  }
  std::cout << constant.description << " is " << constant.si << " " << constant.si.unit << ".\n";
  std::cout << std::endl;
}
