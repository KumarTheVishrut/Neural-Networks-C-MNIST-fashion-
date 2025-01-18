#ifndef _NEURAL_NETWORK_HPP
#define _NEURAL_NETWORK_HPP


#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include "Layer.hpp"
#include <math.h>
#include <vector>
using namespace std;

class NeuralNetwork

{
public:
	NeuralNetwork (vector<int> topology);
    ~NeuralNetwork();
    void setCurrentInput(vector<double> input);
    void printToConsole();
private:
    int     topologySize; 
    vector<int> topology;
    vector<Layer *> layers;
    vector<Matrix *> weightMatrices;
    vector <double> input;
};

#endif
