#pragma once
#include<vector>
#include <math.h>
#include "CONFIG.h"

class Neuron
{
private:
	std::vector<double> X;

public:
	void ThinQ();

	//inicia todo o neuronio com valores aleatorios
	void Neuron_INIT(int inputNUMBER);
	std::vector<double> Weights;
	double LocalGradient;
	double b;
	//incideValue
	double Z;
	double Y;
	void setX(std::vector<double>& values) { X = values; }
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
		Weights.push_back(((rand()%100)/100.0));
	}
	b = (((rand() % 100) /100.0));// ((double)rand()) / RAND_MAX;
}

std::vector<double> Clone(std::vector<double>& NeuronLayerPrev_Outputs)
{
	std::vector<double> clone;
	for (size_t i = 0; i < NeuronLayerPrev_Outputs.size(); i++)
	{
		clone.push_back(NeuronLayerPrev_Outputs[i]);
	}
	return clone;
}



inline void Neuron::ThinQ()
{
	/*
	X1	---- w11-----> E() + b = Z ... O(Z) ---> Y
	               |
	X2 ----- w12---
	
	*/
	//X =  Clone(Inputs);
	//setX(Inputs);
	double Value = b;
	for (size_t i = 0; i < X.size(); i++)
	{
		Value = Value + X[i] * Weights[i];
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
	LocalGradient = SomaLastLocalGrad * tmp.derivativeActivationFunction(Z);
	CorrectWeights(LearningRate);
}

