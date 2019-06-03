#pragma once
#include<string> 
#include <list>
#include <memory>
using namespace std; 
class TreeNode final
{
public:
	static const int ROOT_NODE_ID = -1;
	TreeNode(int id , string description);
	// TreeNode() = default;
	~TreeNode();
	int Id;
	string Description;
	list<shared_ptr<TreeNode>> Children;

	vector<TreeNode*> ListNodeSiblings(string name);
	vector<TreeNode*> ListAll();
private:
	pair<vector<TreeNode*>, bool> _ListNodeSiblings(const string& name);
	void _ListAll(vector<TreeNode*>& nodes);
};

