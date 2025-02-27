#ifndef _NEURON_HPP_
#define _NEURON_HPP_


#include <iostream>
#include <math.h>
using namespace std;

class Neuron

{
public:
	Neuron(double val);
	void setVal (double v);


	// Fast forward Sigmoid F(x)
	// f(x) = x / (1 + |x|)
	void activate();

	// Derivative
	// f'(x) = f(x) * (1 - f(x))
	void derive();

	// getter
	double getVal() const;
	double getActivatedVal() {return this->acti_val;}
	double getDerivatedVal() {return this->der_val;}

	void updateWeights(double learningRate);
    const std::vector<double>& getWeights() const;
private:
	// setters
	double val;
	double acti_val;
	double der_val;

};

#endif
