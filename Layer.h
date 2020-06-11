#pragma once
#include<vector>
#include "Neuron.h"
#include <math.h>
#include <thread>

class Layer
{
private:
	int Prev_LayerSize;

public:
	Layer(int Size, int Prev_LayerSize);
	void ThinQ_All(std::vector<double> NeuronLayerPrev_Output);
	//set as inital layer ignores ...
	bool isInitial = false;
	int Size;
	std::vector<Neuron> NeuronLayer;
	std::vector<double> LOCAL_X_WEIGHT;
	void CALC_All_Local_X_Weight();
	double Error(std::vector<double> listOutpust_EXPECTED);
	void CalculateLocalGradients_Last(std::vector<double> listOutpust_EXPECTED , double LearningRate);
	void CalculateLocalGradients(std::vector<double> listOf_Prev_grads , double LearningRate);
	void printLayer();
	std::vector<double>GetOutput();
};

Layer::Layer(int Size , int Prev_LayerSize)
{
	this->Size = Size;
	this->Prev_LayerSize = Prev_LayerSize;
	NeuronLayer.clear();

	for (size_t i = 0; i < Size; i++)
	{
		Neuron N;
		N.Neuron_INIT(Prev_LayerSize);
		NeuronLayer.push_back(N);
	}
}
void ThinQ(Neuron n)
{
	n.ThinQ();
	
}
/*
std::vector<double> Clone (std::vector<double> NeuronLayerPrev_Outputs)
{
	std::vector<double> clone;
	for (size_t i = 0; i < NeuronLayerPrev_Outputs.size(); i++)
	{
		clone.push_back(NeuronLayerPrev_Outputs[i]);
	}
	return clone;
}*/

inline void Layer::ThinQ_All(std::vector<double> NeuronLayerPrev_Outputs)
{
	std::vector<std::thread> threads;
	if (isInitial)
	{
		for (size_t i = 0; i < NeuronLayer.size(); i++)
		{
			//preenche a primeira camada da rede
			NeuronLayer[i].setOutputValue(NeuronLayerPrev_Outputs[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < NeuronLayer.size(); i++)
		{
			NeuronLayer[i].setX(NeuronLayerPrev_Outputs);
			NeuronLayer[i].ThinQ();
			//if (NeuronLayer.size() - 1 == i)
			//{
			//	NeuronLayer[i].setX(NeuronLayerPrev_Outputs);
			//	NeuronLayer[i].ThinQ();
			//}
			//else
			//{

			//	NeuronLayer[i].setX(NeuronLayerPrev_Outputs);
			//	std::thread  thread(ThinQ, std::ref(NeuronLayer[i]));
			//	//thread.detach();
			//	threads.push_back(std::move(thread));
			//}
		}
		/*for (size_t i = 0; i < threads.size(); i++)
		{
			threads[i].join();
		}*/
	}

}



inline void Layer::printLayer()
{
	
	int n = 1;
	for (Neuron neuron : NeuronLayer) {
		std::cout << "Neuron #" << n << ":" << std::endl;
		std::cout << " BIAS: " << neuron.b << std::endl;
		std::cout << "Input Weights:" << std::endl;
		std::vector<double> weights = neuron.Weights;
		for (size_t i = 0; i < neuron.Weights.size(); i++)
		{
			std::cout << neuron.Weights[i] << " ";
		}
		n++;

	}
}

//outout y da camada
inline std::vector<double> Layer::GetOutput()
{
	std::vector<double> OutputLayer;
	for (auto n : NeuronLayer)
	{
		OutputLayer.push_back(n.Y);
	}
	return OutputLayer;
}


inline void Layer::CALC_All_Local_X_Weight()
{
	//isto vai dar um vetor com um tamanho igual ao da camada anterior 
	LOCAL_X_WEIGHT.clear();
	for (size_t j = 0; j < Prev_LayerSize; j++)
	{
		double sum = 0.0;
		for (size_t i = 0; i < NeuronLayer.size(); i++)
		{
			sum += NeuronLayer[i].LocalGradient * NeuronLayer[i].Weights[j];
		}
		LOCAL_X_WEIGHT.push_back(sum);
	}
}


inline double Layer::Error(std::vector<double> listOutpust_EXPECTED)
{
	auto outputs = this->GetOutput();
	double SumError = 0.0;
	for (size_t i = 0; i < outputs.size(); i++)
	{
		SumError += pow(outputs[i] - listOutpust_EXPECTED[i], 2);
	}
	return SumError;
}


//vai atualizar os pesos na ultima camada e calcular o gradiente local...
inline void Layer::CalculateLocalGradients_Last(std::vector<double> listOutpust_EXPECTED , double LearningRate)
{
	for (size_t i = 0; i < NeuronLayer.size(); i++)
	{
		NeuronLayer[i].calculateLocalGradientOutput(listOutpust_EXPECTED[i] , LearningRate);
	}
}


inline void Layer::CalculateLocalGradients(std::vector<double> SomaLastLocalGrad , double LearningRate)
{
	for (size_t i = 0; i < NeuronLayer.size(); i++)
	{
		NeuronLayer[i].calculateLocalGradient(SomaLastLocalGrad[i] , LearningRate);
	}
}