using System;
using System.Collections.Generic;
using System.Linq;

namespace TreeAppCore
{
    public sealed class TreeNode
    {
        public int Id { get; set; }

        public string Description { get; set; }

        public List<TreeNode> Children { get; set; }

        public List<TreeNode> ListNodeSiblings(string key) {
            Queue<TreeNode> queue = new Queue<TreeNode>();

            queue.Enqueue(this);
            while (queue.Count != 0) {
                TreeNode node = queue.Dequeue();
                foreach (TreeNode child in node.Children) {
                    queue.Enqueue(child);
                    if (child.Description == key) {
                        return node.Children.Where(n => n.Description != key).ToList();
                    }
                }
            }

            return null;
        } 

        public List<TreeNode> ToList() {
            Queue<TreeNode> queue = new Queue<TreeNode>();
            List<TreeNode> list = new List<TreeNode>();

            queue.Enqueue(this);
            while (queue.Count != 0) {
                TreeNode node = queue.Dequeue();

                list.Add(node);
                foreach (TreeNode child in node.Children) {
                    queue.Enqueue(child);
                }
            }
            list.Sort((x, y) => x.Description.CompareTo(y.Description));
            return list;
        }
    }
}
