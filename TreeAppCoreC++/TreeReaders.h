#pragma once
#include "TreeNode.h"
#include <algorithm> 

class ITreeReader
{
public:
	ITreeReader() {}
	virtual ~ITreeReader() {}
	virtual unique_ptr<TreeNode> ConstructTree() = 0;
};


class StaticNamesNode
{
public:
	StaticNamesNode(int id, string description,   int parentId)
	{
		Id = id;
		Description = description;
		ParentId = parentId;
	}

	int Id;
	string Description;
	int ParentId;
};

class StaticNamesTreeReader :public  ITreeReader
{
private:

	const  list<StaticNamesNode> Nodes =
	{
		StaticNamesNode(10, "Radacina", -1),
		StaticNamesNode(100, "Popescu",10),
		StaticNamesNode(111, "Papuc", 100),
		StaticNamesNode(112, "Piedone", 100),
		StaticNamesNode(113, "Pavel", 100),
		StaticNamesNode(1131, "Paleologu", 113),
		StaticNamesNode(113101, "Paleontologu", 1131),
		StaticNamesNode(113102, "Panageu",1131),
		StaticNamesNode(11310201, "Gata", 113102),
		StaticNamesNode(1132, "Pavaza", 113),
		StaticNamesNode(200, "Ionescu", 10),
		StaticNamesNode(221, "Ivan",200),
		StaticNamesNode(22101, "Ivanescu", 221),
		StaticNamesNode(22102, "Ivanciuc", 221),
		StaticNamesNode(222, "Ioana", 200),
	};

public:
	unique_ptr<TreeNode> ConstructTree();
	StaticNamesNode FindStaticNodeByName(string nodeName);
	unique_ptr<TreeNode> ConstructTreeNode(int nodeId);
	StaticNamesNode FindStaticNode(int nodeId);
	list<StaticNamesNode> ListNodeSiblings(string nodeName);
};

