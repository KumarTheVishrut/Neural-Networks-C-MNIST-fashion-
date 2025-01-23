#ifndef _NEURAL_NETWORK_HPP
#define _NEURAL_NETWORK_HPP


#include <iostream>
#include "Neuron.hpp"
#include "Matrix.hpp"
#include "Layer.hpp"
#include <math.h>
#include <vector>
#include "utils/MultiplyMatrix.hpp"

using namespace std;

class NeuralNetwork

{
public:
	NeuralNetwork (vector<int> topology);
    ~NeuralNetwork();
    void setCurrentInput(vector<double> input);
    void printToConsole();
    void feedForward();

    Matrix *getNeuronMatrix(int idx){ return this->layers.at(idx)->matrixifyVals();};
    Matrix *getActivatedNeuronMatrix(int idx){return this->layers.at(idx)->matrixifyActivatedVals();};
    Matrix *getDerivedNeuronMatrix(int idx){return this->layers.at(idx)->matrixifyDerivedVals();};
    Matrix *getWeightMatrix(int idx){return this->weightMatrices.at(idx);};

    void setNeuronValue(int indexLayer, int indexNeuron, double val){this->layers[indexLayer]->setVal(indexNeuron,val);};


private:
    int     topologySize; 
    vector<int> topology;
    vector<Layer *> layers;
    vector<Matrix *> weightMatrices;
    vector <double> input;
};

#endif
