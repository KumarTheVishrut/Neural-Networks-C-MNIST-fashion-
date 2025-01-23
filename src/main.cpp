#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
using namespace std;


int main(int argc , char **argv){
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
    vector <double> input;
    input.push_back(1);
    input.push_back(0);
    input.push_back(1);

    vector <int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);




    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->feedForward();
    nn->printToConsole();
	
    
    
    return 0;
}
