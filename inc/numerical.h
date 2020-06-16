#pragma once

#include <complex>
#include <vector>

#include "utils.h"


void loadPotenial(std::string filename, std::vector<Point> &potential);
void numerovMethod(std::vector<Point>& potential, double energy, double mass, std::vector<std::complex<double>> & wavefunction);
void saveWavefunctionToFile(std::vector<Point>& potential, std::vector<std::complex<double>>& wf, std::string filename);