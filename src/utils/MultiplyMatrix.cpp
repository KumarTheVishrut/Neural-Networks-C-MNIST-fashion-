#include "../../include/utils/MultiplyMatrix.hpp"
#include <iostream>
#include <cassert>

namespace utils {
    MultiplyMatrix::MultiplyMatrix(Matrix* a, Matrix* b) {
        // Check for null pointers and log the error instead of asserting
        if (!a || !b) {
            std::cerr << "Error: Null matrix pointer passed!" << std::endl;
            std::cerr << "Matrix A: " << (a ? "Valid" : "Null") << std::endl;
            std::cerr << "Matrix B: " << (b ? "Valid" : "Null") << std::endl;
            return; // Gracefully exit without proceeding further
        }

        this->a = a;
        this->b = b;

        // Ensure dimensions are compatible for multiplication
        if (a->getNumCols() != b->getNumRows()) {
            std::cerr << "Matrix A columns: " << a->getNumCols()
                      << " do not match Matrix B rows: " << b->getNumRows() << std::endl;
            return; // Return early to prevent multiplication
        }

        // Initialize result matrix
        this->c = new Matrix(a->getNumRows(), b->getNumCols(), false);
        //std::cout << "Matrix initialized successfully!" << std::endl;
    }

Matrix* MultiplyMatrix::execute() {
    if (!this->a || !this->b) {
        std::cerr << "Error: Matrix multiplication cannot proceed due to invalid matrices!" << std::endl;
        return nullptr;
    }

    //std::cout << "Matrix A Size: " << a->getNumRows() << "x" << a->getNumCols() << std::endl;
    //std::cout << "Matrix B Size: " << b->getNumRows() << "x" << b->getNumCols() << std::endl;

    for (int i = 0; i < a->getNumRows(); ++i) {
        for (int j = 0; j < b->getNumCols(); ++j) {
            double sum = 0;
            for (int k = 0; k < a->getNumCols(); ++k) {
                sum += this->a->getValue(i, k) * this->b->getValue(k, j);
            }
            this->c->setValue(i, j, sum);
        }
    }

    return this->c;
}
}
