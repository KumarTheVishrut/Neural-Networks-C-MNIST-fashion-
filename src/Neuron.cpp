#include "../include/Neuron.hpp"
void Neuron::setVal(double val){
	this->val = val;
	activate();
	derive();
}
// Constructor
//
Neuron::Neuron(double val) {
	this->val = val;
	activate();
	derive();
}

// Fast sigmoid f(x) = x / (1 + |x|)
void Neuron::activate() {
	this->acti_val = this->val / (1 + abs(this->val));
	
}

// derivative for fast sigmoid f(x) 
void Neuron::derive() {
	this->der_val = this->acti_val * (1 - this->acti_val);
	
}
