#include "../../include/utils/MatrixToVector.hpp"
namespace utils {

    // Constructor
    MatrixToVector::MatrixToVector(Matrix *matrix) {
        assert(matrix != nullptr);
        this->a = matrix;
    }

    //Destructor

        MatrixToVector::~MatrixToVector() {
        if (result != nullptr) {
            delete result;
            result = nullptr;
        }
    }

    // Execute method to convert matrix to vector
    vector<double>* MatrixToVector::execute() {
        int rows = a->getRows();
        int cols = a->getCols();
        
        // Create a new vector to store the matrix elements
        vector<double>* result = new vector<double>();
        
        // Reserve space for efficiency
        result->reserve(rows * cols);
        
        // Convert matrix to vector row by row
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result->push_back(a->get(i, j));
            }
        }
        
        return result;
    }
    
}
