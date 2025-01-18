#ifndef _LAYER_HPP_
#define _LAYER_HPP_


#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include <math.h>
#include <vector>
using namespace std;

class Layer

{
public:
	int size;
	Layer (int size);
	void setVal(int i, double v);
	Matrix *matrixifyVals();
	Matrix *matrixifyActivatedVals();
	Matrix *matrixifyDerivedVals();

private:
	// setters
	vector <Neuron *> neurons;
};

#endif
