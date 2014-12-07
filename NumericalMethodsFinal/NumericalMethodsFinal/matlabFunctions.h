#pragma once

#include <Engine.h>
#include <string>
#include <iostream> //for cin/cout
#include <cmath> // for math stuff
#include <vector>



void funct(engine* m_pEngine);

template <typename T, typename A>
void vecToMatlab(engine* ptrEngine, std::vector<T,A> vec, std::string varName)
{
	// this is how you pass stuff to matlab
	//Sends a matrix variable of your data to matlab and names it

	mxArray* VAR = mxCreateDoubleMatrix(vec.size(), 1, mxREAL);
	std::copy(vec.begin(), vec.end(), mxGetPr(VAR)); //copies data from the passed vector to the mxArray
	engPutVariable(ptrEngine, varName.c_str(), VAR); //creates a matlab variable using the passed string
	mxDestroyArray(VAR);

}