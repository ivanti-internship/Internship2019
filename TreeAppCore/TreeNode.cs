using System.Collections.Generic;
using System.Linq;

namespace TreeAppCore
{
    public sealed class TreeNode : System.IComparable<TreeNode>
    {
        public int FatherId { get; set; }
        public int Id { get; set; }

        public string Description { get; set; }

        public List<TreeNode> Children { get; set; }

        public override string ToString()
        {
            return Id + " " + Description + "";
        }

        public int CompareTo(TreeNode other)
        {
            return Description.CompareTo(other.Description);
        }

       
    }

}
