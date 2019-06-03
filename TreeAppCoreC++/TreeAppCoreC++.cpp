// TreeAppCoreC++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
using namespace std;

#include "TreeReaders.h"
#include "TreeWriters.h"

bool comp(unique_ptr<TreeNode> a, unique_ptr<TreeNode> b) {
	return a->Description < b->Description;
}

int main()
{

	std::cout << "Constructing tree...\n";
	auto tree = StaticNamesTreeReader().ConstructTree();

	DatabaseTreeWriter treeWriter ("treenodes.db");
	treeWriter.WriteTree(*tree.get());

	std::cout <<"Done.";
	
	
	//list the siblings of the node with the specified name (e.g. George)
	//TODO: uncomment line and implement method
	list<StaticNamesNode> nodeGeorge =  StaticNamesTreeReader().ListNodeSiblings("George");


	//5 

	list<unique_ptr<TreeNode>> lista;

	lista.push_back(tree);

	for (auto i : tree->Children) {
		StaticNamesNode aux = StaticNamesTreeReader().FindStaticNode(i->Id);
		unique_ptr<TreeNode> current;

		current->Children = i->Children;
		current->Id = i->Id;
		current->Id = i->Id;

		lista.push_back(current);
	}


	sort(lista.begin(), lista.end(), comp);

}

