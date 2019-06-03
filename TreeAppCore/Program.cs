using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;

namespace TreeAppCore
{
 
    class Program
    {

        public static void DFSparent(TreeNode currNode, List<TreeNode> visited, int parentId)
        {
            visited.Add(currNode);

            if (parentId != -1)
                currNode.FatherId = parentId;

            foreach (TreeNode i in currNode.Children)
            {
                if (visited.Contains(i) == false)
                    DFSparent(i, visited, currNode.Id);
            }

        }

        public static void DFS5(TreeNode currNode, List<TreeNode> visited)
        {
            visited.Add(currNode);

            foreach (TreeNode i in currNode.Children)
            {
                if (visited.Contains(i) == false)
                    DFS5(i, visited);
            }

        }

        public static void DFS(TreeNode currNode, List<TreeNode> visited, string toBeFoundDescription)
        {
            visited.Add(currNode);

            bool foundIT = false;

            foreach (TreeNode i in currNode.Children)
                if (i.Description == toBeFoundDescription)
                    foundIT = true;

            if (foundIT)
            {
                Console.WriteLine("It's siblings are :");
                foreach (TreeNode i in currNode.Children)
                    if (i.Description != toBeFoundDescription)
                        Console.WriteLine(i.Description);
                Console.WriteLine("");
            }    
            else foreach (TreeNode i in currNode.Children)
            {
                if (visited.Contains(i) == false)
                    DFS(i, visited, toBeFoundDescription);
            }
        }

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

            Console.WriteLine("Enter name for node:");
            string referenceName = Console.ReadLine();

            //LA 2 fac DFS , cand gasesc in ipostaza de fiu(In for-ul de copii din dfs) //
            //nodul cu descriptia aia, ii printez fratii. 
            List<TreeNode> visited = new List<TreeNode>();
            DFS(tree, visited, referenceName);

            //La 5 basic dfs(Am tratat fiecare task individual) si am facut un sort dupa comparer(
            // cu lista de prioritati(Pot sa o fac :D) - nu stiu cat de mult accent se pune pe timp
            visited = new List<TreeNode>();
            DFS5(tree, visited);

            visited.Sort();

            foreach(TreeNode i in visited)
            {
                Console.WriteLine(i);
            }

            //La optimizare baza de date, in loc sa fac 2*N conexiuni la baza, fac dfs-ul intai cu un
            //camp de parentId, si fac numai 1 conexiuni si mai multe statementuri. 
            visited = new List<TreeNode>();
            DFSparent(tree, visited, -1);

            //list the siblings of the node with the specified name (e.g. George)
            //TODO: uncomment line and implement method
            //var nodeGeorge = tree.ListNodeSiblings("George");

            treeWriter.AnotherWriteMethod(visited);

            Console.ReadKey();
        }
    }
}
