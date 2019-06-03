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

void TreeNode::ListNodeSiblings(std::list<shared_ptr<TreeNode>> Children, std::string nume)
{
	list<shared_ptr<TreeNode>> temp = Children;
	int ok;
	for (auto i : Children)
		if(i->Description == nume)
			ok = i->Id;
	//for (auto i : Children)
		//if (i->idParent == ok);
		//std::cout << i->Description; aici ar trebui sa afisez toate nodurile care au numele parentului = cu numele nodului pe care l am gasit
	//nu imi dau seama cum sa analizez fiecare nod in parte si mai exact unde gasesc i->IdParent
}
