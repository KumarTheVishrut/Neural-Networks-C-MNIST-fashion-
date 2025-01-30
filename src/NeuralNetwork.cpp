    #include "../include/NeuralNetwork.hpp"
    #include "../include/utils/MultiplyMatrix.hpp"

void NeuralNetwork::backPropagation() {
    vector<Matrix*> newWeights;
    double learningRate = this->learningRate; // Ensure learningRate is a member variable

    int outputLayerIdx = layers.size() - 1;
    Layer *outputLayer = layers.at(outputLayerIdx);
    Matrix *derivedOutput = outputLayer->matrixifyDerivedVals();
    Matrix *gradient = new Matrix(1, outputLayer->getNeurons().size(), false);
    for (int i = 0; i < errors.size(); i++) {
    double derivedVal = derivedOutput->getValue(0, i);
    double error = errors.at(i);
    gradient->setValue(0, i, derivedVal * error);
}

    // Process each weight matrix in reverse order
    for (int w_idx = weightMatrices.size() - 1; w_idx >= 0; w_idx--) {
        Layer *currentLayer = layers.at(w_idx + 1); // Layer after the weight matrix
        Layer *prevLayer = layers.at(w_idx); // Layer before the weight matrix

        // Compute delta for the current weight matrix
        Matrix *activatedPrev = prevLayer->matrixifyActivatedVals();
        Matrix *deltaWeights = (new utils::MultiplyMatrix(gradient->transpose(), activatedPrev))->execute()->transpose();

        // Update weights with learning rate
        Matrix *currentWeights = weightMatrices.at(w_idx);
        Matrix *newWeightMatrix = new Matrix(currentWeights->getNumRows(), currentWeights->getNumCols(), false);
        for (int r = 0; r < newWeightMatrix->getNumRows(); r++) {
            for (int c = 0; c < newWeightMatrix->getNumCols(); c++) {
                double original = currentWeights->getValue(r, c);
                double delta = deltaWeights->getValue(r, c);
                newWeightMatrix->setValue(r, c, original - learningRate * delta);
            }
        }
        newWeights.push_back(newWeightMatrix);

        // Compute gradient for previous layer if not the first weight matrix
        if (w_idx > 0) {
            Matrix *weightsT = currentWeights->transpose();
            Matrix *gradientPrevUntrained = (new utils::MultiplyMatrix(gradient, weightsT))->execute();
            Matrix *derivedPrev = prevLayer->matrixifyDerivedVals();
            Matrix *gradientPrev = new Matrix(gradientPrevUntrained->getNumRows(), gradientPrevUntrained->getNumCols(), false);
            for (int r = 0; r < gradientPrev->getNumRows(); r++) {
                for (int c = 0; c < gradientPrev->getNumCols(); c++) {
                    gradientPrev->setValue(r, c, gradientPrevUntrained->getValue(r, c) * derivedPrev->getValue(r, c));
                }
            }
            // Update gradient for next iteration
            delete gradient;
            gradient = gradientPrev;

            // Cleanup temporary matrices
            delete weightsT;
            delete gradientPrevUntrained;
            delete derivedPrev;
        }

        // Cleanup
        delete activatedPrev;
        delete deltaWeights;
    }

    // Reverse newWeights to match original weight matrix order
    reverse(newWeights.begin(), newWeights.end());

    // Replace old weights with new weights
    for (Matrix *w : this->weightMatrices) {
        delete w;
    }
    this->weightMatrices.clear();
    for (Matrix *w : newWeights) {
        this->weightMatrices.push_back(w);
    }

    // Cleanup remaining matrices
    delete gradient;
    delete derivedOutput;
}

void NeuralNetwork::printInputToConsole() {
    for (int i = 0; i < this->target.size(); i++){
    cout << this->target.at(i) << "\t";

    } 
    cout << endl;

}


void NeuralNetwork::printTargetToConsole() {
  for (int i = 0; i < this->target.size(); i++)
  {
    cout << this->target.at(i) << "\t";

  }
  
  cout << endl;
}

void NeuralNetwork::printOutPutToConsole(){
  int idx_out_layer = this->layers.size() - 1;
  Matrix *outputVals = this->layers.at(idx_out_layer)->matrixifyActivatedVals();
  for (int c = 0 ; c < outputVals->getNumCols(); c++){
    cout << outputVals->getValue(0,c)<<"\t";
  }
  cout << endl;
}

void::NeuralNetwork::setErrors(){
    int out_lay_idx = this->layers.size() -1;
    Layer* outputLayer = this->layers.at(out_lay_idx);
    int out_layer_size = outputLayer->getNeurons().size();

    if (target.size() != out_layer_size) {
        cerr << "Target-Output layer mismatch! "
             << "Target size: " << target.size()
             << ", Output size: " << out_layer_size << endl;
        return; // Critical: Exit early to prevent crashes
    }

    errors.clear();
    vector<Neuron*> out_neurons = outputLayer->getNeurons();
    double tot_err = 0.0;
    for (int i =0 ; i < out_layer_size; i++){
        double pred = out_neurons.at(i)->getActivatedVal();
        double err = target.at(i) - pred;
        errors.push_back(err);
        tot_err += err; 
}
    tot_err /= out_lay_idx;
    this->error = tot_err;
    historicalErrors.push_back(tot_err); 
}

void::NeuralNetwork::setTarget(vector<double> target){
    this->target = target ;

}




void NeuralNetwork::feedForward() {
    // Iterate only for the number of weight matrices (layers.size() - 1)
    for (int i = 0; i < layers.size() - 1; i++) {  // FIXED: Stop at layers.size() - 1
        Matrix *a = this->getNeuronMatrix(i);

        if (i != 0) {
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix *b = this->getWeightMatrix(i);  // Now safe (i < weightMatrices.size())

        if (a != nullptr && b != nullptr) {
            Matrix *c = (new utils::MultiplyMatrix(a, b))->execute();

            for (int c_idx = 0; c_idx < c->getNumCols(); c_idx++) {
                // Set values for layer i+1 (guaranteed to exist)
                this->setNeuronValue(i + 1, c_idx, c->getValue(0, c_idx));
            }
            delete c;  // Clean up dynamically allocated matrix
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
    
            
            if (i == 0) {
                Matrix *m = this->layers.at(i)->matrixifyVals();
                m->printToConsole();
            } else {
                Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
                m->printToConsole();
            }
            cout << "===========================" << endl;

            if(i < this->layers.size()-1){
                cout << "Weight Matrix" << i << endl;
                this->getWeightMatrix(i)->printToConsole();
            }
            cout << "===========================" << endl;

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

    // Initialize layers
    for (int i = 0; i < topologySize; i++) {
        layers.push_back(new Layer(topology.at(i)));
    }

    // Initialize weight matrices (N-1 matrices for N layers)
    for (int i = 0; i < topologySize - 1; i++) {  // Correct: topologySize - 1
        weightMatrices.push_back(new Matrix(topology[i], topology[i + 1], true));
    }
}

//Deconstructor
    NeuralNetwork::~NeuralNetwork() {
        for (auto layer : layers) {
            delete layer;
        }
        for (auto matrix : weightMatrices) {
            delete matrix;
        }
    }
