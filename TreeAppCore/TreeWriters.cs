using System.Data.SqlClient;
using System.Linq;

namespace TreeAppCore
{
    public interface ITreeWriter
    {
        void WriteTree(TreeNode rootNode);
    }

    public class DatabaseTreeWriter : ITreeWriter {
        private readonly string _connectionString;

        public DatabaseTreeWriter(string connectionString) {
            _connectionString = connectionString;
        }

        public void WriteTree(TreeNode rootNode) {
            CleanupTables();

            WriteNode(rootNode, null);
        }

        private void WriteNode(TreeNode node, int? parentId) {
            WriteNodeInfo(node);
            if (parentId != null) {
                WriteNodesRelation(node.Id, parentId.Value);
            }

            foreach (var child in node.Children ?? Enumerable.Empty<TreeNode>()) {
                WriteNode(child, node.Id);
            }
        }

        //Conexiunile SQL nu erau deschise
        private void WriteNodeInfo(TreeNode node) {
            using (SqlConnection sqlConn = new SqlConnection(_connectionString)) {
                var sqlComm = new SqlCommand($"insert into TreeNodes (Id, Description) values (@id, @description)", sqlConn);
                sqlConn.Open();
                sqlComm.Parameters.AddWithValue("@id", node.Id);
                sqlComm.Parameters.AddWithValue("@description", node.Description);
                sqlComm.ExecuteNonQuery();
            }
        }

        private void WriteNodesRelation(int nodeId, int parentId)
        {
            using (SqlConnection sqlConn = new SqlConnection(_connectionString)) {
                var sqlComm = new SqlCommand($"insert into TreeNodeRelations (Id, ParentId) values (@id, @parentId)", sqlConn);
                sqlConn.Open();
                sqlComm.Parameters.AddWithValue("@id", nodeId);
                sqlComm.Parameters.AddWithValue("@parentId", parentId);
                sqlComm.ExecuteNonQuery();
            }
        }

        private void CleanupTables()
        {
            using (SqlConnection sqlConn = new SqlConnection(_connectionString)) {
                var sqlComm = new SqlCommand("delete from TreeNodes", sqlConn);
                sqlConn.Open();
                sqlComm.ExecuteNonQuery();
                sqlComm.CommandText = "delete from TreeNodeRelations";
                sqlComm.ExecuteNonQuery();
            }
        }
    }
}
