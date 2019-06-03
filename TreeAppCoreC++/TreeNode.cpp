#include "pch.h"
#include "TreeNode.h"

#include <vector>

TreeNode::TreeNode(int id, string description)
	:Id(id),
	Description(description),
	Children()
{
	
}


TreeNode::~TreeNode()
{
}

std::vector<TreeNode*> TreeNode::ListNodeSiblings(string name) {
	return this->_ListNodeSiblings(name).first;
}

pair<std::vector<TreeNode*>, bool> TreeNode::_ListNodeSiblings(const string& name) {
	int id = -1;
	for (const auto& node: this->Children) {
		if (node->Description == name) {
			id = node->Id;
			break;
		}
	}
	if (id != -1) {
		std::vector<TreeNode*> siblings;
		for (const auto& node: this->Children) {
			if (node->Id != id) {
				siblings.push_back(node.get());
			}
		}
		return make_pair(siblings, true);
	}
	for (const shared_ptr<TreeNode>& node: this->Children) {
		auto res = node->_ListNodeSiblings(name);
		if (res.second) {
			return res;
		}
	}
	return make_pair(vector<TreeNode*>(), false);
}

vector<TreeNode*> TreeNode::ListAll() {
	vector<TreeNode*> nodes;
	this->_ListAll(nodes);
	sort(nodes.begin(), nodes.end(), [&](const TreeNode* a, const TreeNode* b) -> bool {
		return a->Description < b->Description;
	});
	return nodes;
}

void TreeNode::_ListAll(vector<TreeNode*>& nodes) {
	nodes.push_back(this);
	for (const auto& node: this->Children) {
		node->_ListAll(nodes);
	}
}