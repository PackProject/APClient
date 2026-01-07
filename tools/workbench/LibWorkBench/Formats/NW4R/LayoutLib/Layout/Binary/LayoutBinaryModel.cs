using LibWorkBench.API.NW4R.LayoutLib;
using LibWorkBench.Attributes;
using LibWorkBench.Core.Models.Binary.Details;
using LibWorkBench.Exceptions;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary
{
    /// <summary>
    /// Layout binary-view model
    /// </summary>
    [BinaryModelProfile(
        signature: "RLYT",
        versions: [8, 10],
        alignment: NW4RDefine.BLOCK_ALIGNMENT
    )]
    public sealed class LayoutBinaryModel
        : TNW4RBinaryModel<LayoutFile, LayoutBlockFactory>
    {
        /// <summary>
        /// Current parent pane (for use while parsing)
        /// </summary>
        private PaneBlock? _parentWork = null;

        /// <summary>
        /// Most recent pane (for use while parsing)
        /// </summary>
        private PaneBlock? _prevWork = null;

        /// <summary>
        /// Root of the pane hierarchy
        /// </summary>
        private PaneBlock? _rootPane = null;

        /// <summary>
        /// Root of the group hierarchy
        /// </summary>
        private GroupBlock? _rootGroup = null;

        /// <summary>
        /// Deserializes the contents of this model from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void OnRead(ReadStream reader)
        {
        }

        /// <summary>
        /// Serializes the contents of this model to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void OnWrite(WriteStream writer)
        {
            // Remove virtual block types
            RemoveAll<PaneStartBlock>();
            RemoveAll<PaneEndBlock>();
            RemoveAll<GroupStartBlock>();
            RemoveAll<GroupEndBlock>();
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void OnSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            GetOne<LayoutBlock>(create: true).Sync(src);

            GetOne<TextureListBlock>(create: true).Sync(src);
            GetOne<FontListBlock>(create: true).Sync(src);
            GetOne<MaterialListBlock>(create: true).Sync(src);

            GetOne<PaneBlock>(create: true).Sync(src);
            GetOne<GroupBlock>(create: true).Sync(src);
        }

        /// <summary>
        /// Allows additional logic after reading each block in the model
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="block">Block that was just read</param>
        public override void ReadBlockCallback(ReadStream reader, BinaryBlock block)
        {
            switch (block)
            {
                case PaneBlock pane:
                    OnReadPaneBlock(reader, pane);
                    break;

                case GroupBlock group:
                    OnReadGroupBlock(reader, group);
                    break;

                case PaneStartBlock paneStart:
                    OnReadPaneStartBlock(reader, paneStart);
                    break;

                case PaneEndBlock paneEnd:
                    OnReadPaneEndBlock(reader, paneEnd);
                    break;
            }
        }

        /// <summary>
        /// Allows additional logic after writing each block in the model
        /// </summary>
        /// <param name="writer">Binary stream that will contain the block data</param>
        /// <param name="block">Block that was just written</param>
        public override void WriteBlockCallback(WriteStream writer, BinaryBlock block)
        {
            switch (block)
            {
                case PaneBlock pane:
                    OnWritePaneBlock(writer, pane);
                    break;

                case GroupBlock group:
                    OnWriteGroupBlock(writer, group);
                    break;
            }
        }

        /// <summary>
        /// Performs additional hierarchy logic after reading a pane block
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="pane">Pane block that was just read</param>
        /// <exception cref="FileBrokenException">The root pane is missing or malformed</exception>
        private void OnReadPaneBlock(ReadStream reader, PaneBlock pane)
        {
            // The first pane in the file must be the root pane
            if (_rootPane == null)
            {
                // RootPane cannot be derived pane types
                if (pane.GetType() != typeof(PaneBlock))
                {
                    throw new FileBrokenException(
                        "The root pane must only be a Pane");
                }

                if (pane.Name != "RootPane")
                {
                    throw new FileBrokenException(
                        "The root pane must be named RootPane");
                }

                _rootPane = pane;
            }

            // Child panes are owned by their parent (not by this model)
            if (_parentWork != null)
            {
                _parentWork.Children.Add(pane);
                pane.Parent = _parentWork;

                // Block list should only hold the root pane
                GetAll(pane.GetType()).Remove(pane);
            }

            _prevWork = pane;
        }

        /// <summary>
        /// Performs additional hierarchy logic after reading a group block
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="group">Group block that was just read</param>
        /// <exception cref="FileBrokenException">The root group is missing or is malformed</exception>
        private void OnReadGroupBlock(ReadStream reader, GroupBlock group)
        {
            // The first group in the file must be the root group
            if (_rootGroup == null)
            {
                if (group.Name != "RootGroup")
                {
                    throw new FileBrokenException(
                        "The root group must be named RootGroup");
                }

                _rootGroup = group;
            }
            // Child groups are owned by their parent (not by this model)
            else
            {
                _rootGroup.Children.Add(group);
                group.Parent = _rootGroup;

                // Block list should only hold the root group
                GetAll<GroupBlock>().Remove(group);
            }
        }

        /// <summary>
        /// Performs additional hierarchy logic after reading a pane start block
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="paneStart">Pane start block that was just read</param>
        private void OnReadPaneStartBlock(ReadStream reader, PaneStartBlock paneStart)
        {
            _parentWork = _prevWork;
        }

        /// <summary>
        /// Performs additional hierarchy logic after reading a pane end block
        /// </summary>
        /// <param name="reader">Binary stream that contained the block data</param>
        /// <param name="paneEnd">Pane end block that was just read</param>
        /// <exception cref="FileBrokenException">The pane hierarchy is invalid</exception>
        private void OnReadPaneEndBlock(ReadStream reader, PaneEndBlock paneEnd)
        {
            if (_prevWork == null || _parentWork == null)
            {
                throw new FileBrokenException("Pane child underflow");
            }

            _prevWork = _parentWork;
            _parentWork = _prevWork.Parent;
        }

        /// <summary>
        /// Performs additional hierarchy logic after writing a pane block
        /// </summary>
        /// <param name="writer">Binary stream that will contain the block data</param>
        /// <param name="pane">Pane block that was just written</param>
        private void OnWritePaneBlock(WriteStream writer, PaneBlock pane)
        {
            if (pane.Children.Count == 0)
            {
                return;
            }

            PaneStartBlock start
                = CreateBlock<PaneStartBlock>(unmanaged: true);

            start.Write(writer);

            foreach (var it in pane.Children)
            {
                it.Write(writer);
                writer.Align(Profile.Alignment);

                WriteBlockCallback(writer, it);
            }

            PaneEndBlock end =
                CreateBlock<PaneEndBlock>(unmanaged: true);

            end.Write(writer);
        }

        /// <summary>
        /// Performs additional hierarchy logic after writing a group block
        /// </summary>
        /// <param name="writer">Binary stream that will contain the block data</param>
        /// <param name="group">Group block that was just written</param>
        private void OnWriteGroupBlock(WriteStream writer, GroupBlock group)
        {
            if (group.Children.Count == 0)
            {
                return;
            }

            GroupStartBlock start
                = CreateBlock<GroupStartBlock>(unmanaged: true);

            start.Write(writer);

            foreach (var it in group.Children)
            {
                it.Write(writer);
                writer.Align(Profile.Alignment);

                WriteBlockCallback(writer, it);
            }

            GroupEndBlock end =
                CreateBlock<GroupEndBlock>(unmanaged: true);

            end.Write(writer);
        }
    }
}
