#include "pch.h"
#include "TreeNode.h"


TreeNode::TreeNode(int id, string description)
	:Id(id),
	Description(description),
	Children()
{
	
}

TreeNode::~TreeNode()
{
}

void TreeNode::listSiblingsHelper(TreeNode node, string name, list<string>& siblings) {

	int is_present = 0;

	for (auto x : node.Children) {
		if (x->Description == name) {
			is_present = 1;
		}
	}

	if (is_present == 1) {
		
		for (auto x : node.Children) {
			if (x->Description != name) {
				siblings.push_back(x->Description);
			}
		}	
	}
	for (auto x : node.Children) {
		listSiblingsHelper(*x.get(), name, siblings);
	}
	
}

list<string> TreeNode::listSiblings(string name) {
	list<string> siblings;
	listSiblingsHelper(*this, name, siblings);
	return siblings;
}

list<TreeNode> TreeNode::getTreeAsList() {
	list<TreeNode> treeAsList;
	getTreeAsListHelper(*this,treeAsList);
	return treeAsList;
}

void TreeNode::getTreeAsListHelper(TreeNode node, list<TreeNode>& treeAsList) {
	for (auto x : node.Children) {
		treeAsList.push_back(*x);
		getTreeAsListHelper(*x, treeAsList);

	}
}
