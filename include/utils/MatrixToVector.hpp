#indef __MATRIX__TO__VECTOR__HPP_
#define __MATRIX__TO__VECTOR__HPP_


#include <iostream>
#include <vector>
#include <assert.h>


#include "../Matrix.hpp"


using namespace std;

namespace utils 
{

	class MatrixToVector(Matrix *a){
	
	public:
		MatrixToVector(Matrix *a);
		vector <double> *execute();

	private:
		Matrix *a;


	};

}
