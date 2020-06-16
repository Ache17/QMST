#include <complex>
#include <iostream>
#include <vector>
#include "inc/generate.h"
#include "inc/help.h"
#include "inc/numerical.h"

using namespace std;

int main(int argc, char ** argv)
{
	if (argc < 3)
	{
		usage();
		return 1;
	}

	string command = string(argv[1]);
	if (command == "generate")
		handleGeneration(argc, argv);
	else if (command == "potential")
	{
		if (argc < 5)
		{
			cout << "usage : main.exe potential [path to potential] [energy] [mass]";
			return 1;
		}
		vector<Point> potential;
		std::vector<complex<double>> wf;
		loadPotenial(string(argv[2]), potential);
		numerovMethod(potential, stod(argv[3]), stod(argv[4]), wf);
		saveWavefunctionToFile(potential, wf, "wf1.csv");
	}
	return 0;
}