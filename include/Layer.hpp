#ifndef _LAYER_HPP_
#define _LAYER_HPP_


#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Layer

{
public:
	int size;
	Layer (int size);
	//	~Layer();
	void setVal(int i, double v);
	Matrix *matrixifyVals();
	Matrix *matrixifyActivatedVals();
	Matrix *matrixifyDerivedVals();
	vector <Neuron *>getNeurons() { return this->neurons;};

	void updateWeights(double learningRate);
    void saveWeights(std::ofstream& file) const;
    std::vector<double> getOutputValues() const;

	void updateWeights(double learningRate);
    const std::vector<double>& getWeights() const;

private:
	// setters
	vector <Neuron *> neurons;
};

#endif
