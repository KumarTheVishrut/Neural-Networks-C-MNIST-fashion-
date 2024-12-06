#ifndef _LAYER_HPP_
#define _LAYER_HPP_


#include <iostream>
#include "Neuron.hpp"
#include <math.h>
#include <vector>
using namespace std;

class Layer

{
public:
	Layer (int size);
private:
	int size;
	// setters
	vector <Neuron *> neurons;
};

#endif
