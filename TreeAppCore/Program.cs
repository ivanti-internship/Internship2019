using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Linq;

namespace TreeAppCore
{
    class Program
    {
        static void ReadTree(TreeNode root) {
            Console.WriteLine(root.Id);
            foreach(TreeNode child in root.Children) {
                ReadTree(child);
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Constructing tree...");
            TreeNode tree;
            try {
                tree = new StaticNamesTreeReader().ConstructTree();
            } catch (InvalidOperationException) { 
                Console.WriteLine("Multiple potential roots. Exiting...");
                return;
            }

            //ReadTree(tree);
            Console.WriteLine("Persisting tree...");
            var connStringBuilder = new SqlConnectionStringBuilder {
                DataSource = "(localdb)\\MSSQLLocalDB",
                IntegratedSecurity = true,
                AttachDBFilename = Path.GetFullPath(".\\treenodes.mdf"),
                InitialCatalog = "tnodes"
            };
            var treeWriter = new DatabaseTreeWriter(connStringBuilder.ConnectionString);
            treeWriter.WriteTree(tree);

            Console.WriteLine("Done.");

            Console.WriteLine("------------------------------------");

            //list the siblings of the node with the specified name (e.g. George)
            //TODO: uncomment line and implement method

            var nodeGeorge = tree.ListNodeSiblings("Ivanciuc");
            try {
                foreach (var child in nodeGeorge) {
                    Console.WriteLine(child.Description);
                }
            } catch (NullReferenceException) {
                Console.WriteLine("Node not found");
            }

            Console.WriteLine("------------------------------------");
            // lista obtinuta din tree
            var nodeList = tree.ToList();
            foreach (var child in nodeList) {
                Console.WriteLine(child.Description);
            }

            Console.WriteLine("------------------------------------");
            Console.ReadKey();
        }
    }
}
