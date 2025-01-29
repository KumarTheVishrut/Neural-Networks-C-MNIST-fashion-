#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
using namespace std;

std::ostream& operator<<(std::ostream& os, const std::vector<double>& vec) {
    os << "[ ";
    for (size_t i = 0; i < vec.size(); i++) {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    os << " ]";
    return os;
}

	//Neuron *n = new Neuron(1.5);
	//cout << "Val:" << n->getVal() << endl;
	//cout << "Activated Val:" << n->getActivatedVal() << endl;
	//cout << "Derived Val:" << n->getDerivatedVal() << endl;
	//Matrix* m = new Matrix(3, 2, true);
    //std::cout << "Original Matrix:" << std::endl;
    //m->printToConsole();

    //std::cout << "----------" << std::endl;

    // Transpose the matrix
    //Matrix* mT = m->transpose();
    //std::cout << "Transposed Matrix:" << std::endl;
    //mT->printToConsole();

    // Clean up memory
    //delete m;
    //delete mT;
int main(int argc, char **argv) {
    // Network topology: 3 input, 2 hidden, 3 output neurons
    vector<int> topology = {3, 2, 3};
    
    // Training data
    vector<double> input = {1, 0, 1};
    vector<double> target = {0.5, 0.5, 0.5};  // Matches output layer size
    
    NeuralNetwork *nn = new NeuralNetwork(topology);
    int epochs = 100;
    double learningRate = 0.1;  // Should be set in NeuralNetwork class
    // Forward pass
    nn->setCurrentInput(input);
    nn->setTarget(target);

    
    // Training loop
    for (int epoch = 0; epoch < epochs; epoch++) {
        cout << "EPOCH"<< epoch << endl;
        // Set target and calculate errors
        nn->feedForward();
        nn->setErrors();
        cout << "ERROR"<< nn->getError() << endl;

        // Backward pass
        nn->backPropagation();
        
        cout << "\n-------------------------" << endl;
        cout << "OUTPUT" << endl;
        nn->printOutPutToConsole();
        // Progress reporting
    }

    delete nn;  // Cleanup after loop
    return 0;
}