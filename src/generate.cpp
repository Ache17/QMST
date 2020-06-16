#include "../inc/generate.h"

#include <iostream>
#include <string>

/*
 *  instruct user how to create simple test potential ( square, eckhart barrier )
 */
void handleGeneration(int argc, char** argv)
{
	if (std::string(argv[2]) == "square")
	{
		if (argc < 9)
		{
			std::cout << "not sufficient number of parameters\n";
			std::cout << "please use : main.exe generate square [minInf] [maxInf] [start of barrier] [end of barrier] [number of points] [value]\n";
			return;
		}
		generateSquareBarrier(std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]),
							 std::stod(argv[6]), std::stoi(argv[7]), std::stod((argv[8])));
	}
	
}

void generateSquareBarrier(double minInf, double plusInf, double startMin, double startMax, int points, double val)
{
	// always generated file will be in "square.inp"
	std::ofstream file;
	file.open("square.inp", std::ios_base::out | std::ios_base::trunc);

	
	const double delta = (plusInf - minInf) / double(points);
	for (double x = minInf; x <= plusInf; x += delta)
	{
		double y = 0;
		if (x >= startMin && x <= startMax)
			y = val;
		file << x << " " << y << "\n";
	}

	file.close();
}
