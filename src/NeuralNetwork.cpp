#include "../include/NeuralNetwork.hpp"

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
    this->layers[0]->setVal(i, input[i]);
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