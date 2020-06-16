#include "../inc/numerical.h"

#include <fstream>
#include <complex>
#include <iostream>

using namespace std::complex_literals;

/*
 * http://www.fisica.uniud.it/~giannozz/Didattica/MQ/Software/C/harmonic0.c
 * http://www.fisica.uniud.it/~giannozz/Didattica/MQ/Software/C/harmonic1.c
 *
 */

void loadPotenial(std::string filename, std::vector<Point>& potential)
{
	// load potential barrier from file
	// and save it to C++ vector
	std::ifstream file;

	file.open(filename);
	double xCoordinate, yCoordinate;
	while (file >> xCoordinate >> yCoordinate)
		potential.push_back({ xCoordinate, yCoordinate });
}

double g(double potential, double energy, double mass)
{
	return 2 * mass / hbar / hbar * (energy - potential);
}

double k(double mass, double energy, double potential)
{
	return 2 * mass * (energy - potential) / (hbar * hbar);
}

void numerovMethod(std::vector<Point>& pot, double energy, double mass, std::vector<std::complex<double>>& wf)
{
	double h = pot[1].x - pot[0].x;
	double h2 = h * h / 12.0;


//	wf.resize(pot.size() - 1);

	//wf.push_back(0);
	wf.push_back(exp(std::complex<double>(-1i * sqrt(2 * mass * energy) / hbar * pot[0].x)));
	wf.push_back(exp(std::complex<double>(-1i * sqrt(2 * mass * energy) / hbar * pot[1].x )));
	
	for (int n = 1; n < pot.size() - 1; ++n)
	{
		double coeff1 = 1. + h2 * k(mass, energy, pot[n+1].y);
		double coeff2 = 2. - 10.0 * h2 * k(mass, energy, pot[n].y);
		double coeff3 = 1. + h2 * k(mass, energy, pot[n-1].y);

		wf.push_back( (coeff2 * wf[n] - coeff3 * wf[n-1]) / coeff1);
	}
}

void saveWavefunctionToFile(std::vector<Point>& potential, std::vector<std::complex<double>>& wf, std::string filename)
{
	std::ofstream file;
	file.open(filename, std::ios_base::out | std::ios_base::trunc);

	file << "x,wf_double,wf_imag\n";
	for (int i = 0; i < wf.size(); ++i)
	{
		file << potential[i].x << "," << wf[i].real() << "," << wf[i].imag() << "\n";
	}
	
}


