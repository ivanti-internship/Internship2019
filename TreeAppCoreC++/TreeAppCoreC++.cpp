// TreeAppCoreC++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "TreeReaders.h"
#include "TreeWriters.h"
int main()
{

	std::cout << "Constructing tree...\n";
	auto tree = StaticNamesTreeReader().ConstructTree();

	DatabaseTreeWriter treeWriter ("treenodes.db");
	treeWriter.WriteTree(*tree.get());

	std::cout <<"Done.";
	
	
	//list the siblings of the node with the specified name (e.g. George)
	//TODO: uncomment line and implement method
	//var nodeGeorge = tree.ListNodeSiblings("George");

	
}

