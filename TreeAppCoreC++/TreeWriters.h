#pragma once
#include "TreeNode.h"
#include "DtabaseUtil.h"

class ITreeWriter
{
public:
	ITreeWriter() {}
	virtual ~ITreeWriter() {}
	virtual void WriteTree(TreeNode& rootNode) = 0;
};


class DatabaseTreeWriter : ITreeWriter
{
private:
	string const  _databaseName;

public:
	DatabaseTreeWriter(string databaseName);
	virtual ~DatabaseTreeWriter();

public:
	void WriteTree(TreeNode& rootNode);

private:
	void WriteNode(TreeNode& node, int parentId, sqlite3* conn);
	void WriteNodeInfo(TreeNode& node, sqlite3* conn);
	void WriteNodesRelation(int nodeId, int parentId, sqlite3* conn);
	void CleanupTables(sqlite3* conn);
};