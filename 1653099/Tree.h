#pragma once
#include"Dataset.h"

class TREE
{
public:
	string Node;
	string Branch;
	vector<TREE*> child;
	TREE();
	TREE* buildTree(TREE *tree, DATASET dataS);
	void writeFile(ofstream&ofs, TREE *tree, int size_tree);
	void ID3(string fOutName, DATASET dataS, TREE *&root);
	void Prediction(string fInTestName, string fOutTestName, TREE *tree);
};
struct Data_Test
{
	string attribute;
	string result;
};
class TEST 
{
public:
	vector<Data_Test> test;
	string doFind(string cur);
};