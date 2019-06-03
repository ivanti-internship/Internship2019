// TreeAppCoreC++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <map>

#include "TreeReaders.h"
#include "TreeWriters.h"

#include "sqlite3.h"
using namespace std;

void writeTree() {
	cout << "Constructing tree...\n";
	auto tree = StaticNamesTreeReader().ConstructTree();

	DatabaseTreeWriter treeWriter ("treenodes.db");
	treeWriter.WriteTree(*tree.get());

	cout << "Done." << endl;
	cout << endl;

	//list the siblings of the node with the specified name (e.g. George)
	//TODO: uncomment line and implement method
	cout << "List siblings" << endl;
	vector<TreeNode*> nodes = tree->ListNodeSiblings("Piedone");
	for (const TreeNode* t: nodes) {
		cout << t->Id << ' ' << t->Description << endl;
	}
	cout << endl;

	cout << "List all" << endl;
	nodes = tree->ListAll();
	for (const TreeNode* t: nodes) {
		cout << t->Id << ' ' << t->Description << endl;
	}
	cout << endl;
}

int main()
{
	writeTree();
	
}

