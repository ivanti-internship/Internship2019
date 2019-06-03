#include "pch.h"
#include "TreeWriters.h"


DatabaseTreeWriter::DatabaseTreeWriter(string databaseName)
	:_databaseName(databaseName)
{
}

DatabaseTreeWriter::~DatabaseTreeWriter()
{
}

	void DatabaseTreeWriter::WriteTree(TreeNode& rootNode)
	{
		sqlite3* conn = DtabaseUtil::openDatabaseConnection(_databaseName);
		CleanupTables(conn);
		WriteNode(rootNode, TreeNode::ROOT_NODE_ID, conn);
		DtabaseUtil::closeDatabseConnection(conn);
	}

	void DatabaseTreeWriter::WriteNode(TreeNode& node, int parentId, sqlite3* conn)
	{
		WriteNodeInfo(node, conn);
		if (parentId != TreeNode::ROOT_NODE_ID)
		{
			WriteNodesRelation(node.Id, parentId, conn);
		}

		for (auto child : node.Children)
		{
			WriteNode(*child, node.Id, conn);
		}
	}

	void DatabaseTreeWriter::WriteNodeInfo(TreeNode& node, sqlite3* conn)
	{
		string query = "insert into TreeNodes(Id, Description) values(" + to_string(node.Id) + ", '" + node.Description + "')";
		DtabaseUtil::ExecuteNonQuery(query, conn);
	}

	void DatabaseTreeWriter::WriteNodesRelation(int nodeId, int parentId, sqlite3* conn)
	{
		string query = "insert into TreeNodeRelations(Id, ParentId) values(" + to_string(nodeId) + ", " + to_string(parentId) + ")";
		DtabaseUtil::ExecuteNonQuery(query, conn);
	}

	void DatabaseTreeWriter::CleanupTables(sqlite3* conn)
	{
		string query = "delete from TreeNodes";
		DtabaseUtil::ExecuteNonQuery(query, conn);

		query = "delete from TreeNodeRelations";
		DtabaseUtil::ExecuteNonQuery(query, conn);
	}