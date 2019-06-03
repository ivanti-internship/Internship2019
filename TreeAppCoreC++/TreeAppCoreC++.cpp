// TreeAppCoreC++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>

#include "TreeReaders.h"
#include "TreeWriters.h"

int main()
{

	std::cout << "Constructing tree...\n";
	auto tree = StaticNamesTreeReader().ConstructTree();

	std::cout << "Done building tree\n";

	DatabaseTreeWriter treeWriter ("treenodes.db");
	
	std::cout << "Created tree writer\n";

	treeWriter.WriteTree(*tree.get());

	std::cout <<"Done.\n";
	
	string person_name = "Papuc";

	auto siblings = (*tree.get()).listSiblings(person_name);

	std::cout << "Siblings of " + person_name + " are : \n";
	for (auto x : siblings) {
		std::cout << x << '\n';
	}

	cout << "***************\n";
	cout << "Sorted in descending order by name";
	list<TreeNode> treeAsList = (*tree.get()).getTreeAsList();

	// std:sort(treeAsList.begin(), treeAsList.end());
	treeAsList.sort();

	for (auto x : treeAsList)
	{
		cout << x.Description << '\n';
	}




	//list the siblings of the node with the specified name (e.g. George)
	//TODO: uncomment line and implement method
	//var nodeGeorge = tree.ListNodeSiblings("George");
	
}

