#include"Tree.h"

TREE::TREE()
{
	Node = "";
	Branch = "";
}

TREE * TREE::buildTree(TREE * tree, DATASET dataS)
{
	if (tree == NULL)
		tree = new TREE();
	//Lay ket qua duy nhat
	vector<string> out;
	out = getUniOutput(dataS.getOutput());
	//case: gia tri output co 2 gia tri
	if (out.size() == 1) {
		tree->Node = out[0];
		return tree;
	}
	//case: dataset co so thuoc tinh la 1
	if (dataS.getSizeAtt() == 1) {
		string FreqOutput = getFreOutput(dataS.getOutput());
		tree->Node = FreqOutput;
		return tree;
	}
	//Tinh AE
	double max=0.0, tmp = 0.0;
	string max_att;
	int index = 0;
	for (int i = 0; i < dataS.attributes.size()-1; i++) {
		tmp = ComputeAE(dataS, dataS.attributes[i]);
		if (tmp - max > 1.e-8) {
			max = tmp;
			max_att = dataS.attributes[i];
			index = i;
		}
	}
	//Chon node dau tien(lon nhat)
	tree->Node = max_att;
	//Lay gia tri thuoc tinh cua max_att,tao datas moi
	vector<string> values = dataS.GetAttributesValues(index);
	DATASET newData;
	for (int i = 0; i < values.size(); i++) {
		newData = newData.doNewDATASET(dataS, max_att, values[i]);
		TREE * newT = new TREE();
		newT->Branch = values[i];
		if (newData.getSizeAtt() == 1)
			newT->Node = getFreOutput(newData.getOutput());
		else
			buildTree(newT, newData);
		tree->child.push_back(newT);
	}
	return tree;
}

void TREE::writeFile(ofstream & ofs, TREE * tree, int size_tree)
{
	for (int i = 0; i < size_tree; i++) {
		if (i == size_tree - 1) {
			cout<< "\t";
			ofs << "\t";
		}
		else {
			cout << "\t";
			ofs << "\t";
		}
	}
	if (tree->Branch.compare("") != 0) {
		cout << " - " << tree->Branch << endl;;
		ofs << " - " << tree->Branch << endl;;
		
		for (int i = 0; i < size_tree + 1; i++) {
			if (i == size_tree) {
				cout << "\t+";
				ofs << "\t+";
			}
			else {
				cout << " \t";
				ofs << " \t";
			}
		}
	}
	ofs << tree->Node << endl;
	cout << tree->Node << endl;
	for (int i = 0; i < tree->child.size(); i++)
		writeFile(ofs, tree->child[i], size_tree + 1);
}

void TREE::ID3(string fOutName,DATASET dataS,TREE *&root)
{
	root = root->buildTree(root, dataS);
	ofstream ofs(fOutName);
	writeFile(ofs, root, -1);
	ofs.close();
}

void TREE::Prediction(string fInTestName, string fOutTestName, TREE * tree)
{
	Data_Test data_t;
	TEST t;
	ifstream ifs(fInTestName);
	ofstream ofs(fOutTestName);
	vector <string> atts;
	string att,tmp;
	getline(ifs, tmp);
	istringstream iss(tmp);
	while (getline(iss,att,','))
		atts.push_back(att);
	TREE *cur = tree;
	while (!ifs.eof()){
		tree = cur;
		string line;
		getline(ifs, line);
		istringstream iss(line);
		int i = 0;
		while (getline(iss, tmp, ',')) {
			data_t.attribute = atts[i++];
			data_t.result = tmp;
			t.test.push_back(data_t);
		}
		while (tree->child.size() != 0) {
			string r = t.doFind(tree->Node);
			for (int i = 0; i < tree->child.size(); i++) {
				if (tree->child[i]->Branch == r)
					tree = tree->child[i];
			}
		}
		ofs << tree->Node << endl;
	}
	ifs.close();
	ofs.close();
}

string TEST::doFind(string cur)
{
	for (int i = 0; i < test.size(); i++) {
		if (test[i].attribute == cur)
			return test[i].result;
	}
}
