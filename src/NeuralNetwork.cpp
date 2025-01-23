#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
void NeuralNetwork::feedForward() {
    for (int i = 0; i < layers.size(); i++) {
        // Step 1: Get the neuron matrix for the current layer
        Matrix *a = this->getNeuronMatrix(i);

        // Step 2: Print matrix 'a' to debug
        if (a != nullptr) {
            std::cout << "LAYER " << i << " (Neuron Matrix):" << std::endl;
            a->printToConsole();
        } else {
            std::cerr << "Matrix a is null at layer " << i << std::endl;
        }

        // If we're not at the first layer, use the activated neuron matrix
        if (i != 0) {
            a = this->getActivatedNeuronMatrix(i);
        }

        // Step 3: Get the weight matrix for the current layer
        Matrix *b = this->getWeightMatrix(i);

        // Step 4: Print matrix 'b' to debug
        if (b != nullptr) {
            std::cout << "LAYER " << i << " (Weight Matrix):" << std::endl;
            b->printToConsole();
        } else {
            std::cerr << "Matrix b is null at layer " << i << std::endl;
        }

        // Step 5: Perform matrix multiplication if both 'a' and 'b' are valid
        if (a != nullptr && b != nullptr) {
            Matrix *c = (new utils::MultiplyMatrix(a, b))->execute();

            // Step 6: Process the result of matrix multiplication (Matrix c)
            std::vector<double> vals;
            for (int c_idx = 0; c_idx < c->getNumCols(); c_idx++) {
                vals.push_back(c->getValue(0, c_idx));
                
                // Ensure the index is within bounds for setting neuron values
                if (i + 1 < layers.size()) {
                    this->setNeuronValue(i + 1, c_idx, c->getValue(0, c_idx));
                } else {
                    std::cerr << "Error: Layer index out of bounds when setting neuron value for layer " << (i + 1) << std::endl;
                }
            }
        } else {
            std::cerr << "Error: Matrix a or Matrix b is null at layer " << i << std::endl;
        }
    }
}




void NeuralNetwork::printToConsole() {
    if (this->layers.empty()) {
        cout << "Error: No layers in the network!" << endl;
        return;
    }

    for (int i = 0; i < this->layers.size(); i++) {
        cout << "LAYER " << i << endl;
        Matrix *m = nullptr;
        
        if (i == 0) {
            m = this->layers.at(i)->matrixifyVals();
        } else {
            m = this->layers.at(i)->matrixifyActivatedVals();
        }

        if (m != nullptr) {
            m->printToConsole();
            delete m;  // Avoid memory leaks
        } else {
            cout << "Error: Matrix is null for layer " << i << endl;
        }
    }
}


void NeuralNetwork::setCurrentInput(vector<double> input){
    this->input = input;
    for (int i = 0 ; i < input.size(); i++){
    this->layers.at(0)->setVal(i, input[i]);
    }
}
    


NeuralNetwork::NeuralNetwork(vector<int> topology) {
    this->topology = topology;
    this->topologySize = topology.size();

    for (int i = 0; i < topologySize; i++) {
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    for (int i = 0; i < (topologySize - 1); i++) {
        Matrix *m = new Matrix(topology[i], topology[i + 1], true);
        this->weightMatrices.push_back(m);
    }
}




NeuralNetwork::~NeuralNetwork() {
    for (auto layer : layers) {
        delete layer;
    }
    for (auto matrix : weightMatrices) {
        delete matrix;
    }
}