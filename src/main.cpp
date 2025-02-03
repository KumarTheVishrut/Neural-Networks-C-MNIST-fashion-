#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
#include <chrono>
#include <memory>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"
#include "../include/NeuralNetwork.hpp"
#include "../include/utils/MultiplyMatrix.hpp"
#include "../include/utils/ImageProcessor.hpp"

// Namespace aliases
namespace fs = std::filesystem;
namespace chrono = std::chrono;
using namespace std;

// Forward declarations
struct TrainingSample;
vector<TrainingSample> loadDataset(const string& dir);
void shuffleDataset(vector<TrainingSample>& dataset);
void trainModel(NeuralNetwork& nn, const vector<TrainingSample>& trainData, 
               const vector<TrainingSample>& testData, int epochs, 
               double learningRate, int batchSize);
double calculateAccuracy(const NeuralNetwork& nn, 
                        const vector<TrainingSample>& dataset);

// Training sample structure
struct TrainingSample {
    vector<double> pixels;
    vector<double> label;
};

int main(int argc, char** argv) {
    // Argument validation
    if (argc < 3) {
        cerr << "Usage: " << argv[0] 
             << " <train_dir> <test_dir> [epochs=10] [learning_rate=0.01]\n";
        return 1;
    }

    try {
        // Configuration
        const vector<int> topology = {784, 128, 64, 10};
        const int epochs = (argc > 3) ? stoi(argv[3]) : 10;
        const double learningRate = (argc > 4) ? stod(argv[4]) : 0.01;
        const int batchSize = 64;

        // Load data
        cout << "Loading training data...\n";
        auto trainData = loadDataset(argv[1]);
        cout << "Loading test data...\n";
        auto testData = loadDataset(argv[2]);

        // Initialize network
        unique_ptr<NeuralNetwork> nn = make_unique<NeuralNetwork>(topology);
        
        // Training process
        trainModel(*nn, trainData, testData, epochs, learningRate, batchSize);

        // Save results
        cout << "\nSaving model weights...\n";
        nn->saveWeights("model_weights.bin");

    } catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// Function implementations
vector<TrainingSample> loadDataset(const string& dir) {
    vector<TrainingSample> dataset;
    
    for (int classIdx = 0; classIdx < 10; ++classIdx) {
        const string classDir = dir + "/" + to_string(classIdx);
        
        for (const auto& entry : fs::directory_iterator(classDir)) {
            const auto pixels = ImageProcessor::process(entry.path().string());
            vector<double> label(10, 0);
            label[classIdx] = 1;
            
            dataset.push_back({pixels, label});
        }
    }
    
    return dataset;
}

void shuffleDataset(vector<TrainingSample>& dataset) {
    static random_device rd;
    static mt19937 rng(rd());
    shuffle(dataset.begin(), dataset.end(), rng);
}

void trainModel(NeuralNetwork& nn, const vector<TrainingSample>& trainData,
               const vector<TrainingSample>& testData, int epochs,
               double learningRate, int batchSize) {
    auto trainDataCopy = trainData;  // Create modifiable copy
    const auto startTime = chrono::high_resolution_clock::now();

    for (int epoch = 0; epoch < epochs; ++epoch) {
        cout << "\nEpoch " << epoch + 1 << "/" << epochs << endl;
        
        shuffleDataset(trainDataCopy);
        double epochLoss = 0;
        int correctCount = 0;

        // Batch processing
        for (size_t i = 0; i < trainDataCopy.size(); i += batchSize) {
            const size_t endIdx = min(i + batchSize, trainDataCopy.size());
            const size_t actualBatchSize = endIdx - i;

            double batchLoss = 0;
            int batchCorrect = 0;

            // Process batch
            for (size_t j = i; j < endIdx; ++j) {
                const auto& sample = trainDataCopy[j];
                
                nn.setCurrentInput(sample.pixels);
                nn.setTarget(sample.label);
                
                // Forward + backward pass
                nn.feedForward();
                batchLoss += nn.getError();
                
                // Calculate accuracy
                const auto output = nn.getOutput();
                const int predicted = distance(output.begin(), 
                                             max_element(output.begin(), output.end()));
                const int actual = distance(sample.label.begin(), 
                                          max_element(sample.label.begin(), sample.label.end()));
                
                if (predicted == actual) batchCorrect++;
                
                nn.backPropagation();
            }

            // Update weights
            nn.updateWeights(learningRate / actualBatchSize);
            
            epochLoss += batchLoss / actualBatchSize;
            correctCount += batchCorrect;
        }

        // Epoch statistics
        const double accuracy = static_cast<double>(correctCount) / trainDataCopy.size();
        cout << "Loss: " << epochLoss / (trainDataCopy.size()/batchSize)
             << "  Accuracy: " << accuracy * 100 << "%";

        // Validation
        if (epoch % 2 == 0) {
            const double testAcc = calculateAccuracy(nn, testData);
            cout << "  Validation Accuracy: " << testAcc * 100 << "%";
        }
    }

    // Training duration
    const auto duration = chrono::duration_cast<chrono::minutes>(
        chrono::high_resolution_clock::now() - startTime
    );
    cout << "\n\nTraining completed in " << duration.count() << " minutes\n";
}

double calculateAccuracy(const NeuralNetwork& nn, 
                        const vector<TrainingSample>& dataset) {
    int correct = 0;
    
    for (const auto& sample : dataset) {
        nn.setCurrentInput(sample.pixels);
        nn.feedForward();
        
        const auto output = nn.getOutput();
        const int predicted = distance(output.begin(), 
                                     max_element(output.begin(), output.end()));
        const int actual = distance(sample.label.begin(), 
                                  max_element(sample.label.begin(), sample.label.end()));
        
        if (predicted == actual) correct++;
    }
    
    return static_cast<double>(correct) / dataset.size();
}