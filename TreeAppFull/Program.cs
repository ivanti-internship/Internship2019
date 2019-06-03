using System;
using System.Data.SqlClient;
using System.IO;

namespace TreeAppFull
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Constructing tree...");
            var tree = new StaticNamesTreeReader().ConstructTree();

            Console.WriteLine("Persisting tree...");
            var connStringBuilder = new SqlConnectionStringBuilder
            {
                DataSource = "(localdb)\\MSSQLLocalDB",
                IntegratedSecurity = true,
                AttachDBFilename = Path.GetFullPath(".\\treenodes.mdf"),
                InitialCatalog = "tnodes"
            };
            var treeWriter = new DatabaseTreeWriter(connStringBuilder.ConnectionString);
            treeWriter.WriteTree(tree);

            Console.WriteLine("Done.");

            //list the siblings of the node with the specified name (e.g. George)
            //TODO: uncomment line and implement method
            //var nodeGeorge = tree.ListNodeSiblings("George");

            Console.ReadKey();
        }
    }
}
