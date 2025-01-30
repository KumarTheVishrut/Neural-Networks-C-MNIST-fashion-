#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
#include <chrono>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
#include "../include/utils/ImageProcessor.hpp"

namespace fs = std::filesystem;
using namespace std;

// Operator overload for vector printing
std::ostream& operator<<(std::ostream& os, const std::vector<double>& vec) {
    os << "[ ";
    for (size_t i = 0; i < vec.size(); i++) {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    os << " ]";
    return os;
}

// Structure to hold training samples
struct TrainingSample {
    vector<double> pixels;
    vector<double> label; // One-hot encoded
};

// Function to load dataset from directory
vector<TrainingSample> loadDataset(const string& dir) {
    vector<TrainingSample> dataset;
    for (int classIdx = 0; classIdx < 10; ++classIdx) {
        string classDir = dir + "/" + to_string(classIdx);
        for (const auto& entry : fs::directory_iterator(classDir)) {
            vector<double> pixels = ImageProcessor::process(entry.path());
            vector<double> label(10, 0);
            label[classIdx] = 1;
            dataset.push_back({pixels, label});
        }
    }
    return dataset;
}

// Function to shuffle dataset
void shuffleDataset(vector<TrainingSample>& dataset) {
    auto rng = default_random_engine {};
    shuffle(begin(dataset), end(dataset), rng);
}

int main(int argc, char **argv) {
    // Check for correct arguments
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <train_dir> <test_dir> [epochs] [learning_rate]" << endl;
        return 1;
    }

    // Network topology for Fashion MNIST
    vector<int> topology = {784, 128, 64, 10};
    
    // Training parameters
    int epochs = (argc > 3) ? stoi(argv[3]) : 10;
    double learningRate = (argc > 4) ? stod(argv[4]) : 0.01;
    int batchSize = 64;

    // Load datasets
    cout << "Loading training data..." << endl;
    auto trainData = loadDataset(argv[1]);
    cout << "Loading test data..." << endl;
    auto testData = loadDataset(argv[2]);

    // Create neural network
    NeuralNetwork *nn = new NeuralNetwork(topology);

    // Training loop
    cout << "Starting training..." << endl;
    auto startTime = chrono::high_resolution_clock::now();

    for (int epoch = 0; epoch < epochs; epoch++) {
        cout << "\nEpoch " << epoch + 1 << "/" << epochs << endl;
        
        shuffleDataset(trainData);
        double epochLoss = 0;
        int correctPredictions = 0;

        // Mini-batch training
        for (size_t i = 0; i < trainData.size(); i += batchSize) {
            double batchLoss = 0;
            int batchCorrect = 0;

            for (size_t j = 0; j < batchSize && (i + j) < trainData.size(); j++) {
                const auto& sample = trainData[i + j];
                
                // Forward pass
                nn->setCurrentInput(sample.pixels);
                nn->setTarget(sample.label);
                nn->feedForward();
                
                // Calculate loss and accuracy
                batchLoss += nn->getError();
                auto output = nn->getOutput();
                int predicted = distance(output.begin(), max_element(output.begin(), output.end()));
                int actual = distance(sample.label.begin(), max_element(sample.label.begin(), sample.label.end()));
                if (predicted == actual) batchCorrect++;
                
                // Backward pass
                nn->backPropagation();
            }

            // Update weights
            nn->updateWeights(learningRate / batchSize);
            
            epochLoss += batchLoss / batchSize;
            correctPredictions += batchCorrect;
        }

        // Calculate epoch statistics
        double accuracy = static_cast<double>(correctPredictions) / trainData.size();
        cout << "Loss: " << epochLoss / (trainData.size() / batchSize)
             << "  Accuracy: " << accuracy * 100 << "%" << endl;

        // Test set evaluation
        if (epoch % 5 == 0) {
            int testCorrect = 0;
            for (const auto& sample : testData) {
                nn->setCurrentInput(sample.pixels);
                nn->feedForward();
                auto output = nn->getOutput();
                int predicted = distance(output.begin(), max_element(output.begin(), output.end()));
                int actual = distance(sample.label.begin(), max_element(sample.label.begin(), sample.label.end()));
                if (predicted == actual) testCorrect++;
            }
            cout << "Test Accuracy: " << (static_cast<double>(testCorrect) / testData.size()) * 100 << "%" << endl;
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::minutes>(endTime - startTime);
    cout << "\nTraining completed in " << duration.count() << " minutes" << endl;

    // Save model weights
    cout << "Saving model weights..." << endl;
    nn->saveWeights("model_weights.bin");

    delete nn;
    return 0;
}