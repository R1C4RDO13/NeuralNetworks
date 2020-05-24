// NeuralNetworks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Backpropagation.h"
#include "NeurolNet.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> read_csv(std::string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result [0] atributos [1] resultados
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
            
         //Extract each integer

        std::vector<double> lineNumber;
        while (std::getline(ss, colname, ';')) {

            // Initialize and add <colname, int vector> pairs to result
            lineNumber.push_back(std::stod(colname) / 4);
        }

        std::vector<double> classResult;
        classResult.push_back(lineNumber.back() * 4);
        lineNumber.pop_back();
        result.first.push_back(lineNumber);
        result.second.push_back(classResult);
    }

    // Close file
    myFile.close();

    return result;
}


double ConstFunction(std::vector<double> Outputs , std::vector<double> RealValues )		//Co
{
	double Cost = 0 ;
	for (size_t i = 0; i < Outputs.size(); i++)
	{
		Cost = Cost +  pow(Outputs[i] - RealValues[i] , 2);
	}
	return Cost;
}

double ActivatonValue(std::vector<double> Inputs, std::vector<double> InputsWeights , double bias = 0)	//Zj
{
	double Value = bias;
	for (size_t i = 0; i < Inputs.size(); i++)
	{
		Value = Value + Inputs[i] * InputsWeights[i];
	}

	return Value ;
}


int main()
{
    auto readCSV = read_csv("C:\\Users\\ricar\\Desktop\\divorce.csv");
    NeuralNet n =  NeuralNet(54, 1);
    Backpropagation B = Backpropagation();

    //mistura os dados de entrada de forma aleatoria
    while (readCSV.first.size() != 0)
    {

        double n = rand() % readCSV.first.size();

        B.TraningData.push_back(readCSV.first[n]);
        B.ExpectedOutputs.push_back(readCSV.second[n]);

        readCSV.first.erase(readCSV.first.begin() + n);
        readCSV.second.erase(readCSV.second.begin() + n);

    }

   
    B.train(n);

    std::cout << "Duvido que chegue aqui" ;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
