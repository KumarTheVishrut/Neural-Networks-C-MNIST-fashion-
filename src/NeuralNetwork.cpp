    #include "../include/NeuralNetwork.hpp"
    #include "../include/utils/MultiplyMatrix.hpp"


void::NeuralNetwork::setErrors(){
    //variables - double error;
    //vector <double> errors;
    //vector <double> historicalErrors;
    //methods
    //vector<double> getTotalErrors(){return this->errors;};
    //double getError(){return this->error; };  

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
        double err = pow(target.at(i) - pred,2);
        errors.push_back(err);
        tot_err += err; 
}
    tot_err /= out_lay_idx;
    //this->errors = tot_err;
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


    NeuralNetwork::~NeuralNetwork() {
        for (auto layer : layers) {
            delete layer;
        }
        for (auto matrix : weightMatrices) {
            delete matrix;
        }
    }