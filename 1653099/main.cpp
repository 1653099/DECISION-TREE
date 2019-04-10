#include"Dataset.h"
#include"Tree.h"

void main()
{
	DATASET datas;
	datas.readDATASET("train.txt");
	//datas.OutputData();
	//cout<<ComputeAE(datas, "outlook");
	TREE * root = NULL;
	root->ID3("tree.txt",datas,root);
	//Test
	root->Prediction("test.txt", "prediction.txt", root);
	cout << "\n=>Write File is done" << endl;
	system("pause");
}