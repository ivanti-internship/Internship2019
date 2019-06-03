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
	~TreeNode();
	int Id;
	string Description;
	list<shared_ptr<TreeNode>> Children;
	
	list<string> listSiblings(string name);
	list<TreeNode> getTreeAsList();

	inline bool operator < (const TreeNode& arg1)
	{
		return (this->Description > arg1.Description);
	}

private:
	void listSiblingsHelper(TreeNode node, string name, list<string>& siblings);
	void getTreeAsListHelper(TreeNode node, list<TreeNode>& siblings);
};

