#include "matlabFunctions.h"

/*
#include <Engine.h>
#include <string>
#include <iostream> //for cin/cout
#include <cmath> // for math stuff
*/



#pragma comment ( lib , "libmat.lib")
#pragma comment ( lib , "libmx.lib")
#pragma comment ( lib , "libmex.lib")
#pragma comment ( lib , "libeng.lib")









void funct(engine* m_pEngine)
{
	//Engine *m_pEngine; //name the engine variable
	//m_pEngine = engOpen("null");

	/*
	const int arraysize(1000); // number of rows, number of columns, size of the array
	const double degToRad(.0174);
	double SinArray[arraysize], degrees[arraysize]; //an array with sin values in it. Our data vector

	for (int i = 0; i < arraysize; ++i)
	{
		SinArray[i] = sin(i*degToRad);
		degrees[i] = i;
	}

	// this is how you pass stuff to matlab
	//Sends a matrix variable of your data to matlab and names it
	mxArray* SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	
	std::memcpy((void *)mxGetPr(SIN), (void *)SinArray, sizeof(double)*arraysize);

	engPutVariable(m_pEngine, "SinGraph", SIN); //creates a matlab variable called "SinGraph" which can be called later
	*/


	engEvalString(m_pEngine, "figure(1)"); // opens up matlab figure window
	engEvalString(m_pEngine, "plot(Degrees,Sine)");
	
}

