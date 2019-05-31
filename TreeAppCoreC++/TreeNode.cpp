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
