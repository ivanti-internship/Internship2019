using System.Collections.Generic;
using System;
using System.Linq;

namespace TreeAppCore
{
    public sealed class TreeNode
    {
        public int Id { get; set; }

        public string Description { get; set; }

        public List<TreeNode> Children { get; set; }

        public TreeNode FindParentNodeByName(TreeNode t, string nume)
        {
            /*
            for (int i = 0; i < t.Children.Count; i++)
            {
                if (t.Children[i].Description.Equals(nume))
                {
                    return t;
                }
            }
            */

            if(t.Children.Any(c => c.Description == nume))
            {
                return t;
            }
            
            for (int i = 0; i < t.Children.Count; i++)
                {
                    TreeNode t2 = FindParentNodeByName(t.Children[i], nume);
                    if(t2 != null)
                    {
                        return t2;
                    }
                }
            return null;
        }

        public List<TreeNode> ListNodeSiblings(string nume) // List<TreeNode>
        {
            TreeNode nodParinte = FindParentNodeByName(this, nume);

            if (nodParinte == null)
            {
                return null;
            }

            return nodParinte.Children;

        }
    }
}
