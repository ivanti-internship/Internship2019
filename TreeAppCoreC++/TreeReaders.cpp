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

	unique_ptr<TreeNode> StaticNamesTreeReader::ConstructTreeNode(int nodeId)
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

	//ex b) ->

	StaticNamesNode StaticNamesTreeReader::FindStaticNodeByName(string nodeName)
	{
		//fint the node with Id == nodeName
		auto staticNodeIt = find_if(Nodes.begin(), Nodes.end(),
			[&nodeName](const StaticNamesNode& s)
			{
				return s.Description == nodeName;
			});

		return *staticNodeIt;
	}

	list<StaticNamesNode> StaticNamesTreeReader::ListNodeSiblings(string nodeName)
	{
		list<StaticNamesNode> result;
		StaticNamesNode target = FindStaticNodeByName(nodeName);


		for (auto j = Nodes.begin(); j != Nodes.end(); j++) {
			if (target.Id != j->Id && target.ParentId == j->ParentId) {

				StaticNamesNode aux = FindStaticNode(j->Id);
				result.push_back(aux);
			}
		}

		return result;
	}