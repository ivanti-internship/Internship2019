#include "pch.h"
#include "TreeNode.h"
#include "TreeReaders.h"
#include "TreeReaders.cpp"


TreeNode::TreeNode(int id, string description)
	:Id(id),
	Description(description),
	Children()
{
	
}


TreeNode::~TreeNode()
{
}
