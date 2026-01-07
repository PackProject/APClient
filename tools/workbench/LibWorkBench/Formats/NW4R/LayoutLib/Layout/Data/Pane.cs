using LibWorkBench.Core;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Formats.NW4R.SystemLib.Types;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Simple UI element
    /// </summary>
    [JsonPolymorphic(TypeDiscriminatorPropertyName = "kind")]
    [JsonDerivedType(typeof(Pane), typeDiscriminator: "pane")]
    [JsonDerivedType(typeof(Bounding), typeDiscriminator: "bounding")]
    [JsonDerivedType(typeof(Picture), typeDiscriminator: "picture")]
    [JsonDerivedType(typeof(TextBox), typeDiscriminator: "textbox")]
    [JsonDerivedType(typeof(Window), typeDiscriminator: "window")]
    public class Pane : IUseName, IUseHierarchy<Pane>
    {
        /// <summary>
        /// Pane name (must be unique)
        /// </summary>
        public string Name { get; set; } = "";

        /// <summary>
        /// User-specific data
        /// </summary>
        public string UserData { get; set; } = "";

        /// <summary>
        /// Whether the pane will be rendered
        /// </summary>
        public bool Visible { get; set; } = true;

        /// <summary>
        /// Whether the pane's alpha is influenced by its parent
        /// </summary>
        public bool InfluencedAlpha { get; set; } = false;

        /// <summary>
        /// Whether the pane's scale should be influenced by location adjust
        /// </summary>
        public bool LocationAdjust { get; set; } = false;

        /// <summary>
        /// Position origin settings
        /// </summary>
        public BasePosition BasePosition { get; set; } = new();

        /// <summary>
        /// Opaqueness
        /// </summary>
        public byte Alpha { get; set; } = 255;

        /// <summary>
        /// Pane translation/position
        /// </summary>
        public VEC3 Translate { get; set; } = new();

        /// <summary>
        /// Pane rotation (in degrees)
        /// </summary>
        public VEC3 Rotate { get; set; } = new();

        /// <summary>
        /// Pane scale
        /// </summary>
        public VEC2 Scale { get; set; } = new();

        /// <summary>
        /// Pane size
        /// </summary>
        public Size Size { get; set; } = new();

        /// <summary>
        /// Parent pane
        /// </summary>
        [JsonIgnore]
        public Pane? Parent { get; set; } = null;

        /// <summary>
        /// Child panes
        /// </summary>
        [JsonPropertyOrder(int.MaxValue)]
        public List<Pane> Children { get; set; } = new();

        /// <summary>
        /// Appends a new child of this pane
        /// </summary>
        /// <param name="child">Child pane</param>
        public void AppendChild(Pane child)
        {
            Children.Add(child);
            child.Parent = this;
        }

        /// <summary>
        /// Removes a child of this pane
        /// </summary>
        /// <param name="child">Child pane</param>
        public void RemoveChild(Pane child)
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
