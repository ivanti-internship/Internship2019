using System.Collections.Generic;

namespace TreeAppCore
{
    public sealed class TreeNode
    {
        public int Id { get; set; }

        public string Description { get; set; }

        public List<TreeNode> Children { get; set; }
    }
}
