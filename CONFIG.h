#pragma once
#include <math.h>
#include <iostream>


class CONFIG
{
public:
	double ActivationFunction(double x);
	double derivativeActivationFunction(double x);
	double sigmoid(double x);
	const double Momentum = 0.01;	//como os valores passados continuam a afetar os valores atuais

	//defaul n neurons per layer = 2/3 n input + n output
	//defaul n of sub layers
};


//esta preparado apenas para a função sigmoid
double CONFIG::ActivationFunction(double x)
{
	return sigmoid(x);
}

inline double CONFIG::derivativeActivationFunction(double x)
{
	return sigmoid(x) * (1 - sigmoid(x));
}

inline double CONFIG::sigmoid(double x)
{
	return (1.0f / (1.0f + std::exp(-x)));
}

