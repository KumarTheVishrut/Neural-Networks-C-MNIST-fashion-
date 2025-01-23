#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
using namespace std;
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
    vector<double> input = {1, 0, 1};  // Input for Layer 0
    vector<int> topology;
    topology.push_back(3);  // Input layer: 3 neurons
    topology.push_back(2);  // Hidden layer: 2 neurons
    topology.push_back(1);  // Output layer: 1 neuron

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->feedForward();
    nn->printToConsole();

    delete nn;  // Cleanup (ensure destructor is properly implemented)
    return 0;
}