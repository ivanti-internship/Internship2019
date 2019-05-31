#include "pch.h"
#include "TreeWriters.h"


DatabaseTreeWriter::DatabaseTreeWriter(string databaseName)
	:_databaseName(databaseName)
{
}

DatabaseTreeWriter::~DatabaseTreeWriter()
{
}

	void DatabaseTreeWriter::WriteTree(TreeNode rootNode)
	{
		CleanupTables();

		WriteNode(rootNode, TreeNode::ROOT_NODE_ID);
	}

	void DatabaseTreeWriter::WriteNode(TreeNode node, int parentId)
	{
		WriteNodeInfo(node);
		if (parentId != TreeNode::ROOT_NODE_ID)
		{
			WriteNodesRelation(node.Id, parentId);
		}

		for (auto child : node.Children)
		{
			WriteNode(*child, node.Id);
		}
	}

	void DatabaseTreeWriter::WriteNodeInfo(TreeNode node)
	{
		auto databaseConnection = DtabaseUtil::openDatabaseConnection(_databaseName);
		string query = "insert into TreeNodes(Id, Description) values(" + to_string(node.Id) + ", '" + node.Description + "')";
		DtabaseUtil::ExecuteNonQuery(query, databaseConnection);
	}

	void DatabaseTreeWriter::WriteNodesRelation(int nodeId, int parentId)
	{
		auto databaseConnection = DtabaseUtil::openDatabaseConnection(_databaseName);
		string query = "insert into TreeNodeRelations(Id, ParentId) values(" + to_string(nodeId) + ", " + to_string(parentId) + ")";
		DtabaseUtil::ExecuteNonQuery(query, databaseConnection);
	}

	void DatabaseTreeWriter::CleanupTables()
	{
		auto databaseConnection = DtabaseUtil::openDatabaseConnection(_databaseName);
		string query = "delete from TreeNodes";
		DtabaseUtil::ExecuteNonQuery(query, databaseConnection);

		query = "delete from TreeNodeRelations";
		DtabaseUtil::ExecuteNonQuery(query, databaseConnection);
	}