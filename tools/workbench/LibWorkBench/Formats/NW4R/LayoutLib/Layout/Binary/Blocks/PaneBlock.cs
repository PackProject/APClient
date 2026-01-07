using LibWorkBench.Attributes;
using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Formats.NW4R.SystemLib.Types;
using LibWorkBench.Utility;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout pane block
    /// </summary>
    [BinaryBlockProfile(signature: "pan1")]
    public class PaneBlock : TNW4RBinaryBlock<LayoutBinaryModel>, IUseName, IUseHierarchy<PaneBlock>
    {
        /// <summary>
        /// Bit flag indices
        /// </summary>
        public enum Flag
        {
            /// <summary>
            /// Controls whether the pane will be rendered
            /// </summary>
            Visible,

            /// <summary>
            /// Controls whether the pane's alpha is influenced by its parent
            /// </summary>
            InfluencedAlpha,

            /// <summary>
            /// Whether the pane's scale should be influenced by location adjust
            /// </summary>
            LocationAdjust
        }

        /// <summary>
        /// Bit flag array
        /// </summary>
        public BitFlag<byte, Flag> Flags { get; set; } = new();

        /// <summary>
        /// Base position configuration
        /// </summary>
        public BasePosition BasePosition { get; set; } = new();

        /// <summary>
        /// Opaqueness
        /// </summary>
        public byte Alpha { get; set; } = 0;

        /// <summary>
        /// Pane name
        /// </summary>
        public string Name { get; set; } = "";

        /// <summary>
        /// Pane userdata
        /// </summary>
        public string UserData { get; set; } = "";

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
        public PaneBlock? Parent { get; set; } = null;

        /// <summary>
        /// Child panes
        /// </summary>
        public List<PaneBlock> Children { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            Flags.SetDirect(reader.ReadU8());
            BasePosition.Read(reader);

            Alpha = reader.ReadU8();
            reader.Align(4);

            Name = reader.ReadString(
                maxlen: LayoutDefine.RES_NAME_LEN,
                exact: true
            );

            UserData = reader.ReadString(
                maxlen: LayoutDefine.USERDATA_LEN,
                exact: true
            );

            Translate.Read(reader);
            Rotate.Read(reader);
            Scale.Read(reader);
            Size.Read(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            writer.WriteU8(Flags.GetDirect());
            BasePosition.Write(writer);

            writer.WriteU8(Alpha);
            writer.Align(4);

            writer.WriteString(
                Name,
                maxlen: LayoutDefine.RES_NAME_LEN,
                terminate: false,
                exact: true
            );

            writer.WriteString(
                UserData,
                maxlen: LayoutDefine.USERDATA_LEN,
                terminate: false,
                exact: true
            );

            Translate.Write(writer);
            Rotate.Write(writer);
            Scale.Write(writer);
            Size.Write(writer);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            // This pane block will hold all children
            SyncPane(src.RootPane);
        }

        /// <summary>
        /// Updates this block to match the contents of a data-view pane
        /// </summary>
        /// <param name="pane">Data-view pane</param>
        /// <exception cref="FileBrokenException">Pane data is invalid</exception>
        protected virtual void SyncPane(Pane pane)
        {
            Parent = null;
            Children.Clear();

            if (pane.Name.Length > LayoutDefine.RES_NAME_LEN)
            {
                throw new FileBrokenException(
                    $"Pane name is too long (> {LayoutDefine.RES_NAME_LEN} " +
                    $"characters): {pane.Name}"
                );
            }

            if (pane.UserData.Length > LayoutDefine.USERDATA_LEN)
            {
                throw new FileBrokenException(
                    "Pane userdata is too long (> " +
                    $"{LayoutDefine.RES_NAME_LEN} characters): {pane.Name}"
                );
            }

            Flags.MakeAllZero();
            Flags.ChangeBit(Flag.Visible, pane.Visible);
            Flags.ChangeBit(Flag.InfluencedAlpha, pane.InfluencedAlpha);
            Flags.ChangeBit(Flag.LocationAdjust, pane.LocationAdjust);

            BasePosition = pane.BasePosition;
            Alpha = pane.Alpha;

            Name = pane.Name;
            UserData = pane.UserData;

            Translate = pane.Translate;
            Rotate = pane.Rotate;
            Scale = pane.Scale;
            Size = pane.Size;

            foreach (var it in pane.Children)
            {
                PaneBlock child =
                    Model!.CreateBlock<PaneBlock>(unmanaged: true);

                switch (it)
                {
                    case Bounding bounding:
                        child =
                            Model!.CreateBlock<BoundingBlock>(unmanaged: true);
                        break;

                    case Picture picture:
                        child =
                            Model!.CreateBlock<PictureBlock>(unmanaged: true);
                        break;

                    case TextBox textBox:
                        child =
                            Model!.CreateBlock<TextBoxBlock>(unmanaged: true);
                        break;

                    case Window window:
                        child =
                            Model!.CreateBlock<WindowBlock>(unmanaged: true);
                        break;
                }

                child.Model = Model!;
                child.SyncPane(it);

                child.Parent = this;
                Children.Add(child);
            }
        }
    }
}
