using LibWorkBench.API.NW4R.LayoutLib;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data
{
    /// <summary>
    /// Layout data-view model
    /// </summary>
    public sealed class LayoutDataModel : TNW4RDataModel<LayoutFile>
    {
        /// <summary>
        /// Texture names from the binary
        /// </summary>
        private List<string> _textureNames = new();

        /// <summary>
        /// Font names from the binary
        /// </summary>
        private List<string> _fontNames = new();

        /// <summary>
        /// Position origin type
        /// </summary>
        public OriginType OriginType { get; set; } = OriginType.TopLeft;

        /// <summary>
        /// Size of this layout
        /// </summary>
        public Size Size { get; set; } = new();

        /// <summary>
        /// Root of the pane hierarchy
        /// </summary>
        public Pane RootPane { get; set; } = new();

        /// <summary>
        /// Root of the group hierarchy
        /// </summary>
        public Group RootGroup { get; set; } = new();

        /// <summary>
        /// Pane materials
        /// </summary>
        public List<Material> Materials { get; set; } = new();

        /// <summary>
        /// Constructor
        /// </summary>
        public LayoutDataModel()
        {
            RootPane.Name = "RootPane";
            RootGroup.Name = "RootGroup";
        }

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Stream to the JSON file</param>
        public override void Load(JsonFileReader reader)
        {
            reader.Deserialize(this);
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Stream to the JSON file</param>
        public override void Dump(JsonFileWriter writer)
        {
            writer.Serialize(this);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void OnSync(NW4RBinaryModel binaryModel)
        {
            LayoutBinaryModel src = (LayoutBinaryModel)binaryModel;

            // Layout-wide configuration
            LayoutBlock layout = src.GetOne<LayoutBlock>();
            OriginType = layout.OriginType;
            Size = layout.Size;

            TextureListBlock texList = src.GetOne<TextureListBlock>();
            _textureNames.Clear();
            _textureNames = texList.Resources.Select(it => it.Name).ToList();

            FontListBlock fontList = src.GetOne<FontListBlock>();
            _fontNames.Clear();
            _fontNames = fontList.Resources.Select(it => it.Name).ToList();

            MaterialListBlock matList = src.GetOne<MaterialListBlock>();
            Materials.Clear();
            Materials = matList.Materials.Select(ConvertMaterial).ToList();

            // Traverse the pane/group hierarchy
            RootPane = ConvertPane(src.GetOne<PaneBlock>());
            RootGroup = ConvertGroup(src.GetOne<GroupBlock>());
        }

        /// <summary>
        /// Converts a binary-view material to its data-view representation
        /// </summary>
        /// <param name="res">Binary-view material</param>
        /// <returns>Data-view material</returns>
        private Material ConvertMaterial(ResMaterial res)
        {
            Material mat = new();

            mat.Name = res.Name;
            mat.TevColors = res.TevColors;
            mat.TevKColors = res.TevKColors;
            mat.TexMaps = res.TexMaps.Select(ConvertTexMap).ToList();
            mat.TexSrts = res.TexSrts;
            mat.TexCoordGens = res.TexCoordGens;
            mat.TevSwapTable = res.TevSwapTable;
            mat.IndTexSrts = res.IndTexSrts;
            mat.IndStages = res.IndStages;
            mat.TevStages = res.TevStages;
            mat.AlphaCompare = res.AlphaCompare;
            mat.BlendMode = res.BlendMode;
            mat.ChanCtrl = res.ChanCtrl;
            mat.MaterialColor = res.MaterialColor;

            return mat;
        }

        /// <summary>
        /// Converts a binary-view pane to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view pane</param>
        /// <returns>Data-view pane</returns>
        private Pane ConvertPane(PaneBlock block)
        {
            switch (block)
            {
                case BoundingBlock bounding:
                    return ConvertBounding(bounding);

                case PictureBlock picture:
                    return ConvertPicture(picture);

                case TextBoxBlock textBox:
                    return ConvertTextBox(textBox);

                case WindowBlock window:
                    return ConvertWindow(window);

                default:
                    // Must be just the base Pane class
                    Pane pane = new();
                    SyncPane(pane, block);
                    return pane;
            }
        }

        /// <summary>
        /// Converts a binary-view bounding to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view bounding</param>
        /// <returns>Data-view bounding</returns>
        private Bounding ConvertBounding(BoundingBlock block)
        {
            Bounding bounding = new();

            // Common pane attributes
            SyncPane(bounding, block);

            return bounding;
        }

        /// <summary>
        /// Converts a binary-view picture to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view picture</param>
        /// <returns>Data-view picture</returns>
        private Picture ConvertPicture(PictureBlock block)
        {
            Picture picture = new();

            // Common pane attributes
            SyncPane(picture, block);

            if (block.MaterialIndex >= Materials.Count)
            {
                throw new FileBrokenException("Invalid material index");
            }

            picture.MaterialName = Materials[block.MaterialIndex].Name;
            picture.VertexColors = block.VertexColors;
            picture.TexCoords = block.TexCoords;

            return picture;
        }

        /// <summary>
        /// Converts a binary-view textbox to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view textbox</param>
        /// <returns>Data-view textbox</returns>
        private TextBox ConvertTextBox(TextBoxBlock block)
        {
            TextBox textBox = new();

            // Common pane attributes
            SyncPane(textBox, block);

            if (block.MaterialIndex >= Materials.Count)
            {
                throw new FileBrokenException("Invalid material index");
            }
            if (block.FontIndex >= _fontNames.Count)
            {
                throw new FileBrokenException("Invalid font index");
            }

            textBox.MaterialName = Materials[block.MaterialIndex].Name;
            textBox.FontName = _fontNames[block.FontIndex];

            textBox.FontSize = block.FontSize;
            textBox.CharSpace = block.CharSpace;
            textBox.LineSpace = block.LineSpace;
            textBox.TextContent = block.TextContent;
            textBox.TextCapacity = block.TextCapacity;
            textBox.TextPosition = block.TextPosition;
            textBox.TextAlignment = block.TextAlignment;
            textBox.TextColors = block.TextColors;

            return textBox;
        }

        /// <summary>
        /// Converts a binary-view window to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view window</param>
        /// <returns>Data-view window</returns>
        private Window ConvertWindow(WindowBlock block)
        {
            Window window = new();

            // Common pane attributes
            SyncPane(window, block);

            window.Content = ConvertWindowContent(block.Content);
            window.Content.TexCoords = block.TexCoords;

            window.Inflation = block.Inflation;
            window.Frames = block.Frames.Select(ConvertWindowFrame).ToList();

            return window;
        }

        /// <summary>
        /// Converts a binary-view pane to its data-view representation
        /// </summary>
        /// <param name="pane">Data-view pane</param>
        /// <param name="block">Binary-view pane</param>
        private void SyncPane(Pane pane, PaneBlock block)
        {
            pane.Parent = null;
            pane.Children.Clear();

            pane.Name = block.Name;
            pane.UserData = block.UserData;

            pane.Visible =
                block.Flags.GetBit(PaneBlock.Flag.Visible);
            pane.InfluencedAlpha =
                block.Flags.GetBit(PaneBlock.Flag.InfluencedAlpha);
            pane.LocationAdjust =
                block.Flags.GetBit(PaneBlock.Flag.LocationAdjust);

            pane.BasePosition = block.BasePosition;
            pane.Alpha = block.Alpha;
            pane.Translate = block.Translate;
            pane.Rotate = block.Rotate;
            pane.Scale = block.Scale;
            pane.Size = block.Size;

            foreach (var it in block.Children)
            {
                Pane child = ConvertPane(it);
                pane.AppendChild(child);
            }
        }

        /// <summary>
        /// Converts a binary-view group to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view group</param>
        /// <returns>Data-view group</returns>
        private Group ConvertGroup(GroupBlock block)
        {
            Group group = new();

            group.Name = block.Name;
            group.PaneNames = block.PaneNames;

            foreach (var it in block.Children)
            {
                Group child = ConvertGroup(it);
                group.AppendChild(child);
            }

            return group;
        }

        /// <summary>
        /// Converts a binary-view texture map to its data-view representation
        /// </summary>
        /// <param name="res">Binary-view texture map</param>
        /// <returns>Data-view texture map</returns>
        /// <exception cref="FileBrokenException">Texture index is invalid</exception>
        private TexMap ConvertTexMap(ResTexMap res)
        {
            TexMap texMap = new();

            if (res.TextureIndex >= _textureNames.Count)
            {
                throw new FileBrokenException("Invalid texture index");
            }

            texMap.TextureName = _textureNames[res.TextureIndex];
            texMap.WrapS = res.WrapS;
            texMap.WrapT = res.WrapT;

            return texMap;
        }

        /// <summary>
        /// Converts binary-view window content to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view window content</param>
        /// <returns>Data-view window content</returns>
        /// <exception cref="FileBrokenException">Material index is invalid</exception>
        private WindowContent ConvertWindowContent(ResWindowContent res)
        {
            WindowContent content = new();

            if (res.MaterialIndex >= Materials.Count)
            {
                throw new FileBrokenException("Invalid material index");
            }

            content.MaterialName = Materials[res.MaterialIndex].Name;
            content.VertexColors = res.VertexColors;

            // Caller is responsible for texture coordinates
            return content;
        }

        /// <summary>
        /// Converts a binary-view window frame to its data-view representation
        /// </summary>
        /// <param name="block">Binary-view window frame</param>
        /// <returns>Data-view window frame</returns>
        /// <exception cref="FileBrokenException">Material index is invalid</exception>
        private WindowFrame ConvertWindowFrame(ResWindowFrame res)
        {
            WindowFrame frame = new();

            if (res.MaterialIndex >= Materials.Count)
            {
                throw new FileBrokenException("Invalid material index");
            }

            frame.MaterialName = Materials[res.MaterialIndex].Name;
            frame.TextureFlip = res.TextureFlip;

            return frame;
        }
    }
}