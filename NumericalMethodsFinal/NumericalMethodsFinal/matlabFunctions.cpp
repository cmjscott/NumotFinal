#include "matlabFunctions.h"



void funct()
{

	Engine *m_pEngine; //name the engine variable
	m_pEngine = engOpen("null");

	int rows, columns;
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
	std::memcpy((void *)mxGetPr(SIN), (void *)SinArray, sizeof ((double*)arraysize));
	engPutVariable(m_pEngine, "SinGraph", SIN); //creates a matlab variable called "SinGraph" which can be called later

	//Sends a matrix variable of your data to matlab and names it
	mxArray* DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	std::memcpy((void *)mxGetPr(DEG), (void *)degrees, sizeof ((double*)arraysize));
	engPutVariable(m_pEngine, "Degrees", DEG); //creates a matlab variable called "SinGraph" which can be called later


	engEvalString(m_pEngine, "figure(1)"); // opens up matlab figure window
	engEvalString(m_pEngine, "plot(Degrees,SinGraph)");



}