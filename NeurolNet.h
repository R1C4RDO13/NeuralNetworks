#pragma once
#include "Layer.h"
#include<vector>

class NeuralNet
{
private:


public:
	std::vector<Layer> Layers;
	NeuralNet(int InputSize, int OutputSize);
	void printAllLayers();
	NeuralNet(int InputSize, int OutputSize, int HidenLayers);
	int SizeLayers() { return Layers.size(); }
	std::vector<double> GETOutput(std::vector<double> entradas);
	double GetError(std::vector<double> expectedOutput);
};

NeuralNet::NeuralNet(int InputSize, int OutputSize)
{
	//defaul n neurons per layer = 2/3 n input + n output 3layer default
	//init Layer
	Layer INIT = Layer(InputSize, InputSize);
	INIT.isInitial = true;
	Layers.push_back(INIT);
	INIT.isInitial = true;
	int neuronsInHidden =( (2.0 / 3.0) * InputSize) + OutputSize;
	Layer Hidden = Layer(neuronsInHidden, InputSize);
	Layers.push_back(Hidden);
	/*Layer Hidden2 = Layer(neuronsInHidden, InputSize);
	Layers.push_back(Hidden2);
	Layer Hidden3 = Layer(neuronsInHidden, neuronsInHidden);
	Layers.push_back(Hidden3);*/
	Layer Output = Layer(OutputSize, neuronsInHidden);
	Layers.push_back(Output);

	

}

NeuralNet::NeuralNet(int InputSize, int OutputSize, int HidenLayers)
{

}

//foward
inline std::vector<double> NeuralNet::GETOutput(std::vector<double> entradas)
{
	Layers[0].ThinQ_All(entradas);
	
	for (size_t i = 1; i < Layers.size(); i++)
	{

		Layers[i].ThinQ_All(Layers[i - 1].GetOutput());
	}

	//resultad final da ultima camada
	return Layers[Layers.size() -1 ].GetOutput();
}

//error
inline double NeuralNet::GetError(std::vector<double> expectedOutput)
{
	return Layers[Layers.size() - 1].Error(expectedOutput);
}

inline void NeuralNet::printAllLayers()
{
	for (size_t i = 0; i < Layers.size(); i++)
	{
		std::cout << " \n Layer #" << i << ":" << std::endl;
		Layers[i].printLayer();
	}
}

