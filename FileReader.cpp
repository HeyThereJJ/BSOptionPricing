#include "FileReader.h"
#include "OptionData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <vector>

OptionData FileRead(std::string filepath, bool mode)
{
	OptionData res;

	std::fstream file{filepath};
	std::vector<double> resvec;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			resvec.push_back(std::stod(line));
		}
	}
	res.t = resvec[0];
	res.s = resvec[1];
	res.k = resvec[2];
	res.r = resvec[3];
	if (mode == 0)
	{
		res.sigma = resvec[4];
		res.premium = 0;
	}
	else
	{
		res.sigma = 0;
		res.premium = resvec[4];
	}
	return res;
}