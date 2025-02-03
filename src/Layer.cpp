#include "../include/Layer.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"





Matrix *Layer::matrixifyVals(){
	Matrix *m = new Matrix(1, this->neurons.size(),false);
	for (int i = 0 ; i< neurons.size(); i++){
		m->setValue(0,
		i,
		this->neurons[i]->getVal());
	}
	return m;
}

Matrix *Layer::matrixifyActivatedVals(){
	Matrix *m = new Matrix(1, this->neurons.size(),false);
	for (int i = 0 ; i< neurons.size(); i++){
		m->setValue(0,
		i,
		this->neurons[i]->getActivatedVal());
	}
	return m;
}

Matrix *Layer::matrixifyDerivedVals(){
	Matrix *m = new Matrix(1, this->neurons.size(),false);
	for (int i = 0 ; i< neurons.size(); i++){
		m->setValue(0,
		i,
		this->neurons[i]->getDerivatedVal());
	}
	return m;
}


Layer::Layer(int size){
	//this->size = size;
	for (int i = 0 ; i < size ; i++){
	Neuron *n = new Neuron(0.00);
	this->neurons.push_back(n);

}
}

void Layer::setVal(int index, double value) {
    if (index < neurons.size()) {
        neurons[index]->setVal(value);  // Assuming Neuron has a setVal method
    }
}


// Get the output values of the layer
std::vector<double> Layer::getOutput() const {
    std::vector<double> output;
    for (const auto& neuron : neurons) {
        output.push_back(neuron->getActivatedVal());
    }
    return output;
}

// Update weights using gradient descent
void Layer::updateWeights(double learningRate) {
    for (auto& neuron : neurons) {
        neuron->updateWeights(learningRate);
    }
}

// Save weights to a file
void Layer::saveWeights(std::ofstream& file) const {
    for (const auto& neuron : neurons) {
        for (double weight : neuron->getWeights()) {
            file << std::fixed << std::setprecision(15) << weight << " ";
        }
        file << "\n";
    }
}