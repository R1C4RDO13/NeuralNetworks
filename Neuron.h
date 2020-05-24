#pragma once
#include<vector>
#include <math.h>
#include "CONFIG.h"

class Neuron
{
private:
	std::vector<double> X;

public:
	void ThinQ(std::vector<double> Inputs);

	//inicia todo o neuronio com valores aleatorios
	void Neuron_INIT(int inputNUMBER);
	std::vector<double> Weights;
	double LocalGradient;
	double b;
	//incideValue
	double Z;
	double Y;
	void setOutputValue(double value);
	void CorrectWeights(double LearningRate);
	void calculateLocalGradientOutput(double ExpectedValue, double LearningRate);
	void calculateLocalGradient(double SomaLastLocalGrad , double LearningRate);

private:
	std::vector<double> listOfWeight_Correction;		//for momentum 

};


void Neuron::Neuron_INIT(int inputNUMBER)
{
	Weights.clear();
	for (size_t i = 0; i < inputNUMBER; i++)
	{
		Weights.push_back(0);// ((double)rand()) / RAND_MAX);
	}
	b = 0;// ((double)rand()) / RAND_MAX;
}

inline void Neuron::ThinQ(std::vector<double> Inputs)
{
	/*
	X1	---- w11-----> E() + b = Z ... O(Z) ---> Y
	               |
	X2 ----- w12---
	
	*/
	X = Inputs;
	double Value = b;
	for (size_t i = 0; i < Inputs.size(); i++)
	{
		Value = Value + Inputs[i] * Weights[i];
	}
	Z = Value;
	CONFIG tmp;
	Y = tmp.ActivationFunction(Value);
}

///for the initial layer
inline void Neuron::setOutputValue(double value)
{
	Y = value;
}

inline void Neuron::CorrectWeights(double LearningRate)
{
	CONFIG tmp;

	for (size_t i = 0; i < Weights.size(); i++)
	{
		Weights[i] = Weights[i] - LearningRate * LocalGradient * X[i];
	}
	b = b - LearningRate * LocalGradient;

}

//Para o calculo do gradiente na ultima camada //backprop
inline void Neuron::calculateLocalGradientOutput(double ExpectedValue , double LearningRate)
{
	CONFIG tmp;
	// Y * (1.0 - Y) * (ExpectedValue - Y);
	double tm_ = tmp.derivativeActivationFunction(Z);
	LocalGradient =   -2 * (ExpectedValue - Y) * tm_;
	CorrectWeights(LearningRate);
}


// SomaLastLocalGrad = E( o * w ) da camada seguinte
inline void Neuron::calculateLocalGradient(double SomaLastLocalGrad , double LearningRate)
{
	CONFIG tmp;
	LocalGradient = SomaLastLocalGrad * Y * (1 - Y); //tmp.derivativeActivationFunction(Z);
	CorrectWeights(LearningRate);
}

