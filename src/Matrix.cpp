#include "../include/Matrix.hpp"

// Deconstructor added



Matrix *Matrix::transpose(){
    Matrix *m = new Matrix(this->numCols,this->numRows,false);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) { 
            m->setValue(j,i,this->getValue(i,j));
        }
}
    return m;

}



double Matrix::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); // Define the range
    return dis(gen); // Use the class member generator
}

void Matrix::printToConsole() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) { 
            std::cout << values[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


Matrix::Matrix(int numRows, int numCols, bool isRandom) {
    this->numRows = numRows;
    this->numCols = numCols;
    for (int i = 0; i < numRows; i++) {
        std::vector<double> row;
        for (int j = 0; j < numCols; j++) {
            double r = isRandom ? this->generateRandomNumber() : 0.0;
            row.push_back(r);
        }
        values.push_back(row);
    }}
