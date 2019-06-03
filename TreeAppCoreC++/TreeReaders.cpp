#include "pch.h"
#include "TreeReaders.h"

unique_ptr<TreeNode> StaticNamesTreeReader::ConstructTree()
{

	//find root node
	auto rootNodeIterator = find_if(Nodes.begin(), Nodes.end(), [](const StaticNamesNode& s) { return s.ParentId == TreeNode::ROOT_NODE_ID; });

	//construct tree starting from root
	auto rootNode = ConstructTreeNode(rootNodeIterator->Id);

	return rootNode;
}

	unique_ptr<TreeNode>StaticNamesTreeReader::ConstructTreeNode(int nodeId)
	{

		auto node = FindStaticNode(nodeId);

		auto treeNode = make_unique<TreeNode>(node.Id, node.Description);

		for (auto staticNode : Nodes)
		{
			if (staticNode.ParentId == treeNode->Id)
			{
				treeNode->Children.push_back(ConstructTreeNode(staticNode.Id));
			}
		}
		return treeNode;
	}


	StaticNamesNode StaticNamesTreeReader::FindStaticNode(int nodeId)
	{
		//fint the node with Id == nodeId
		auto staticNodeIt = find_if(Nodes.begin(), Nodes.end(),
			[&nodeId](const StaticNamesNode& s)
		{
			return s.Id == nodeId;
		});

		return *staticNodeIt;
	}