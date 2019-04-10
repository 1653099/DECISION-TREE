#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
//#include <conio.h>
using namespace std;

class DATASET
{
public:
	vector<string> attributes;
	vector<vector<string>>example;
	void readDATASET(string fileName);
	void OutputData();
	vector<string> getOutput();//Lay toan bo gia tri output
	int getSizeAtt();
	int getSizeLineExp();

	vector<string> GetAttributesValues(int Index);
	vector< vector<string>> GetAttributeValuesScores(string The_Attribute);//Dem tan so gia tri cua thuoc tinh
	DATASET doNewDATASET(DATASET cur, string The_Attibute, string values);
};

string delDot(string& cur);
vector<string> getUniOutput(vector<string>out);//Lay gia tri output duy nhat
string getFreOutput(vector<string> Scores);//Lay tan so cua output

double ComputeEntropy(vector<string> Scores); // Tinh entropy
double ComputeAE(DATASET data, string The_Attribute);//Tinh AE
