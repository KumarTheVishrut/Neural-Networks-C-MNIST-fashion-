#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_


#include <iostream>
#include <math.h>
#include <vector>
#include <random>
using namespace std;

class Matrix

{
public:
	Matrix(int numRows , int numCols, bool isRandom);

    Matrix *transpose();
    inline void setValue(int r, int c, double v) { this->values.at(r).at(c) = v; }
    inline double getValue(int r , int c) const{return this->values.at(r).at(c); }
    void printToConsole();
    int getNumRows() {return this->numRows;}
    int getNumCols(){return this->numCols;}
private:
    int numRows;
    int numCols;
    //vector <vector<double>> values;
    std::vector<std::vector<double>> values;
    std::mt19937 gen; // Random number generator
    double generateRandomNumber();



};

#endif
