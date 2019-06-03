using System;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace TreeAppCore
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

            var nodeGeorge = tree.ListNodeSiblings("George");
            try
            {
                for (int i = 0; i < nodeGeorge.Capacity - 1; i++)
                {
                    Console.WriteLine(nodeGeorge[i].Description);
                }
            }
            catch(Exception e)
            {
                Console.WriteLine("Nu au fost gasite persoane");
            }


            List<TreeNode> list = new List<TreeNode>();

            TreeToList(tree,ref list); //Creare de lista
            
            list.Sort((x, y) => x.Description.CompareTo(y.Description)); //Sortare de lista

            for(int i = 0; i< list.Count; i++)
            {
                Console.WriteLine(list[i].Id + " " + list[i].Description);
            }

            Console.WriteLine("Done.");

            //list the siblings of the node with the specified name (e.g. George)
            //TODO: uncomment line and implement method
            //var nodeGeorge = tree.ListNodeSiblings("George");

            Console.ReadKey();
        }

        private static void TreeToList(TreeNode tree, ref List<TreeNode> list)
        {
            //List<TreeNode> list = new List<TreeNode>;
            list.Add(tree);

            foreach (var child in tree.Children ?? Enumerable.Empty<TreeNode>())
            {
                TreeToList(child, ref list);
            }
        }
    }
}
