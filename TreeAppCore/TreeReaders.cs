using System;
using System.Collections.Generic;
using System.Linq;

namespace TreeAppCore
{
    public interface ITreeReader
    {
        TreeNode ConstructTree();
    }

    public class StaticNamesTreeReader : ITreeReader
    {
        private class StaticNamesNode
        {
            public StaticNamesNode(int id, string description, int? parentId = null)
            {
                Id = id;
                Description = description;
                ParentId = parentId;
            }

            public int Id { get; }
            public string Description { get; }
            public int? ParentId { get; }
        };

        private static readonly List<StaticNamesNode> Nodes = 
            new List<StaticNamesNode>
            {
                new StaticNamesNode(10, "Radacina"),
                new StaticNamesNode(100, "Popescu", 10),
                new StaticNamesNode(111, "Papuc", 100),
                new StaticNamesNode(112, "Piedone", 100),
                new StaticNamesNode(113, "Pavel", 100),
                new StaticNamesNode(1131, "Paleologu", 113),
                new StaticNamesNode(113101, "Paleontologu", 1131),
                new StaticNamesNode(113102, "Panageu", 1131),
                new StaticNamesNode(11310201, "Gata", 113102),
                new StaticNamesNode(1132, "Pavaza", 113),
                new StaticNamesNode(200, "Ionescu", 10),
                new StaticNamesNode(221, "Ivan", 200),
                new StaticNamesNode(22101, "Ivanescu", 221),
                new StaticNamesNode(22102, "Ivanciuc", 221),
                new StaticNamesNode(222, "Ioana", 200),
            };

        public TreeNode ConstructTree() {
            //var rootNodeId = Nodes.Where(n => n.ParentId == null).First().Id;

            var rootNodeId = Nodes.SingleOrDefault(n => n.ParentId == null).Id; // Ar trebui sa fie o singura radacina, asa ca aruncam
            var rootNode = ConstructTreeNode(rootNodeId);                      // exceptie in cazul in care sunt mai multe potentiale radacini
            return rootNode;
        }

        private TreeNode ConstructTreeNode(int nodeId)
        {
            var staticNode = FindStaticNode(nodeId);

            var treeNode = new TreeNode { Id = staticNode.Id, Description = staticNode.Description };

            treeNode.Children = Nodes
                .Where(n => n.ParentId == staticNode.Id)
                .Select(n => ConstructTreeNode(n.Id))
                .ToList();  

            return treeNode;
        }

        private StaticNamesNode FindStaticNode(int nodeId)
        {
            return Nodes.SingleOrDefault(n => n.Id == nodeId);
        }
    }
}
