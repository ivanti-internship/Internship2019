#pragma once
#include<string> 
#include <list>

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
};

