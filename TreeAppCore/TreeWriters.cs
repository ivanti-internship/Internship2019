using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;

namespace TreeAppCore
{
    public interface ITreeWriter
    {
        void WriteTree(TreeNode rootNode);
    }

    public class DatabaseTreeWriter : ITreeWriter
    {
        private readonly string _connectionString;

        public DatabaseTreeWriter(string connectionString)
        {
            _connectionString = connectionString;
        }

        public void WriteTree(TreeNode rootNode)
        {
            CleanupTables();

            WriteNode(rootNode, null);
        }

        private void WriteNode(TreeNode node, int? parentId)
        {
            WriteNodeInfo(node);
            if (parentId != null)
            {
                WriteNodesRelation(node.Id, parentId.Value);
            }

            foreach (var child in node.Children ?? Enumerable.Empty<TreeNode>())
            {
                WriteNode(child, node.Id);
            }
        }

        public  void AnotherWriteMethod(List<TreeNode> list)
        {
            CleanupTables();
            var sqlConn = new SqlConnection(_connectionString);
            sqlConn.Open();

            foreach (TreeNode i in list)
            {

                var sqlComm = new SqlCommand($"insert into TreeNodes (Id, Description) values (@id, @description)", sqlConn);
                sqlComm.Prepare();
                sqlComm.Parameters.Clear();
                sqlComm.Parameters.AddWithValue("@id", i.Id);
                sqlComm.Parameters.AddWithValue("@description", i.Description);
                sqlComm.ExecuteNonQuery();

                if (i.FatherId != 0)
                {
                    var sqlComm1 = new SqlCommand($"insert into TreeNodeRelations (Id, ParentId) values (@id, @parentId)", sqlConn);
                    sqlComm1.Prepare();
                    sqlComm1.Parameters.Clear();
                    sqlComm1.Parameters.AddWithValue("@id", i.Id);
                    sqlComm1.Parameters.AddWithValue("@parentId", i.FatherId);

                    sqlComm1.ExecuteNonQuery();
                }
            }
            sqlConn.Close();
        }
       
        private void WriteNodeInfo(TreeNode node)
        {
            var sqlConn = new SqlConnection(_connectionString);
            sqlConn.Open();
            var sqlComm = new SqlCommand($"insert into TreeNodes (Id, Description) values (@id, @description)", sqlConn);
            sqlComm.Prepare();
            sqlComm.Parameters.Clear();
            sqlComm.Parameters.AddWithValue("@id", node.Id);
            sqlComm.Parameters.AddWithValue("@description", node.Description);
            
            sqlComm.ExecuteNonQuery();
            sqlConn.Close();
        }

        private void WriteNodesRelation(int nodeId, int parentId)
        {
            var sqlConn = new SqlConnection(_connectionString);
            sqlConn.Open();
            var sqlComm = new SqlCommand($"insert into TreeNodeRelations (Id, ParentId) values (@id, @parentId)", sqlConn);
            sqlComm.Prepare();
            sqlComm.Parameters.Clear();
            sqlComm.Parameters.AddWithValue("@id", nodeId);
            sqlComm.Parameters.AddWithValue("@parentId", parentId);
           
            sqlComm.ExecuteNonQuery();
            sqlConn.Close();
        }

        private void CleanupTables()
        {
            var sqlConn = new SqlConnection(_connectionString);
            sqlConn.Open();
            var sqlComm = new SqlCommand("", sqlConn);
            sqlComm.CommandText = "delete from TreeNodes";
            sqlComm.Prepare();
            sqlComm.ExecuteNonQuery();

            sqlComm.CommandText = "delete from TreeNodeRelations";
            sqlComm.Prepare();
            sqlComm.ExecuteNonQuery();
            sqlConn.Close();
        }
    }
}
