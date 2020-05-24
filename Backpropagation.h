#pragma once
#include "NeurolNet.h"
#include <math.h>

class Backpropagation
{
public:
	double targetError = 0.01;
	int MaxEpoch = 50000;
	double currentError;
	std::vector<std::vector<double>> TraningData;
	std::vector <std::vector<double >> ExpectedOutputs;
	Backpropagation();

	NeuralNet& train(NeuralNet& n);

private:
	double ActualError;
	double LearningRate;
	void setLearningRate(double epoch);

protected:
	void forward(NeuralNet& n, size_t row);
	void backward(NeuralNet& n, size_t row);
};

inline Backpropagation::Backpropagation()
{

}


inline NeuralNet& Backpropagation::train(NeuralNet& n)
{
	//iteração atual
	int epoch = 1;
	ActualError = 1.0;
	size_t traningSetSize = TraningData.size();

	while (ActualError > targetError)
	{
		if (epoch >= MaxEpoch) break;
		double errors = 0.0;
		setLearningRate(epoch);
		for (size_t dt = 0; dt < traningSetSize; dt++)
		{

			forward(n, dt);
			std::vector<double> ExpectedOutput = ExpectedOutputs[dt];
			errors += n.GetError(ExpectedOutput);
			backward(n, dt);
		}
		ActualError = errors / traningSetSize;
		std::cout << "Errors: \t" << errors << "\n";
		std::cout << "Current Error: \t" << ActualError <<  "\n";
		std::cout << "Current Epoch: \t" << epoch  << "\n"; 
		std::cout << "Current learning rate: \t" << LearningRate << "\n";
		epoch++;
	}

	std::cout << "\n Resultado Final: \n" ;
	n.printAllLayers();
	std::cout << "\n TESTE: \n";
	double error = 0;
	double OutputN = 0;
	for (size_t dt = 0; dt < traningSetSize; dt++)
	{
		auto output = n.GETOutput(TraningData[dt]);
		std::vector<double> ExpectedOutput = ExpectedOutputs[dt];
		for (size_t i = 0; i < ExpectedOutput.size(); i++)
		{
			if (ExpectedOutput[i] != round(output[i]))
			{
				error++;
			}
			OutputN++;
		}
	}

	double Acuracy = 100 - (error / OutputN) * 100.0 ;
	std::cout << "Acuracy = " << Acuracy << "%"  << "\n";
	return n;
}

inline void Backpropagation::setLearningRate(double epoch)
{
	//y\:=\:0.5^{-2000/\left(x+2200\right)}\:-1.0
	LearningRate =  pow(0.5, (-2000 / (epoch + 2200))) - 1.0;
}

inline void Backpropagation::forward(NeuralNet& n, size_t row)
{
	//inicializar a primeira camada
	std::vector<double> dataSet = TraningData[row];
	n.GETOutput(dataSet);

}

//faz o backpropagation e correção dos pesos na rede...
inline void Backpropagation::backward(NeuralNet& n, size_t row)
{
	std::vector<double> ExpectedOutput = ExpectedOutputs[row];
	//calcula primeiro o gradiente local da ultima camada e corrige os seus pesos
	n.Layers[n.Layers.size() - 1].CalculateLocalGradients_Last(ExpectedOutput , LearningRate);
	n.Layers[n.Layers.size() - 1].CALC_All_Local_X_Weight();

	for (int i = n.Layers.size() - 2; i >= 1; i--)
	{
		n.Layers[i].CalculateLocalGradients(n.Layers[i + 1].LOCAL_X_WEIGHT ,  LearningRate);
		if (i != 1)
		{
			n.Layers[i].CALC_All_Local_X_Weight();
		}
	}
}