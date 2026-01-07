using LibWorkBench.Attributes;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.API.NW4R.LayoutLib
{
    /// <summary>
    /// UI layout file (BRLYT)
    /// </summary>
    [ResourceProfile(name: "layout", extension: "brlyt")]
    public sealed class LayoutFile : TNW4RResource<LayoutBinaryModel, LayoutDataModel>
    {
        /// <summary>
        /// Position origin type
        /// </summary>
        public OriginType OriginType
        {
            get => DataModel.OriginType;
            set { DataModel.OriginType = value; }
        }

        /// <summary>
        /// Size of this layout
        /// </summary>
        public Size Size
        {
            get => DataModel.Size;
            set { DataModel.Size = value; }
        }

        /// <summary>
        /// Root of the pane hierarchy
        /// </summary>
        public Pane RootPane
        {
            get => DataModel.RootPane;
            set { DataModel.RootPane = value; }
        }

        /// <summary>
        /// Root of the group hierarchy
        /// </summary>
        public Group RootGroup
        {
            get => DataModel.RootGroup;
            set { DataModel.RootGroup = value; }
        }

        /// <summary>
        /// Pane materials
        /// </summary>
        public List<Material> Materials
        {
            get => DataModel.Materials;
        }
    }
}
