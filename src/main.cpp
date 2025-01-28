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
    vector<double> input = {1, 0, 1};  // Input for Layer 0
    vector<double> target = {0.5};
    vector<int> topology;
    topology.push_back(3);  // Input layer: 3 neurons
    topology.push_back(2);  // Hidden layer: 2 neurons
    topology.push_back(3);  // Output layer: 1 neuron

    NeuralNetwork *nn = new NeuralNetwork(topology);
    int epochs = 5;

    // Training loop
    for (int epoch = 0; epoch < epochs; epoch++) {
        cout << "Epoch " << epoch + 1 << ":" << endl;

        // Set the current input and target
        nn->setCurrentInput(input);
        nn->setTarget(input);

        // Perform forward propagation
        nn->feedForward();

        // Calculate errors
        nn->setErrors();

        // Perform backpropagation
        nn->backPropagation();

        // Get and print the total error for this epoch
        vector<double> totalErrors = nn->getTotalErrors();
        cout << "Total Error: ";
        for (double err : totalErrors) {
            cout << err << " ";
        }
        cout << endl << "-------------------------" << endl;
    }
    delete nn;  // Cleanup (ensure destructor is properly implemented)
    return 0;
}