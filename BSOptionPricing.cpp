// BSOptionPricing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BSFormula.h"
#include "FileReader.h"
#include "OptionData.h"

int main(int argc, char* argv[])
{
 std::cout << "---Black-scholes pricing application---\n";

 OptionData option_data;
 std::string filepath;
 bool mode;

 if (argc == 1)
 {
  std::cout << "Please, specify the path to the input file:\n";
  std::cin >> filepath;
  std::cout << "To calculate option premium, type 0; to calculate volatility, type 1:\n";
  std::cin >> mode;
 }
 else if (argc == 2)
 {
  filepath = argv[1];
  std::cout << "To calculate option premium, type 0; to calculate volatility, type 1:\n";
  std::cin >> mode;
 }
 else
 {
  filepath = argv[1];
  mode = bool(argv[2]);
 }

 option_data = FileRead(filepath, mode);

 if (mode == 0)
 {
  double result = BSFormulaCalc(option_data);
  std::cout << "Price of European call option would be: " << result << "\n";
 }
 else
 {
  double result = BSFormulaFindVolat(option_data);
  std::cout << "Estimated volatility in the market: " << result << "\n";
 }
}