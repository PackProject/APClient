using LibWorkBench.Core;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Collection of UI panes
    /// </summary>
    public sealed class Group : IUseName, IUseHierarchy<Group>
    {
        /// <summary>
        /// Group name
        /// </summary>
        public string Name { get; set; } = "";

        /// <summary>
        /// Names of all panes contained within this group
        /// </summary>
        public List<string> PaneNames { get; set; } = new();

        /// <summary>
        /// Parent group
        /// </summary>
        [JsonIgnore]
        public Group? Parent { get; set; } = null;

        /// <summary>
        /// Child groups
        /// </summary>
        public List<Group> Children { get; set; } = new();

        /// <summary>
        /// Appends a new child of this group
        /// </summary>
        /// <param name="child">Child group</param>
        public void AppendChild(Group child)
        {
            Children.Add(child);
            child.Parent = this;
        }

        /// <summary>
        /// Removes a child of this group
        /// </summary>
        /// <param name="child">Child group</param>
        public void RemoveChild(Group child)
        {
            Children.Remove(child);

            // Avoid clobbering other hierarchy
            if (child.Parent == this)
            {
                child.Parent = null;
            }
        }
    }
}
