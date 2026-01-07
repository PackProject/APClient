using LibWorkBench.Attributes;
using LibWorkBench.Core;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout group block
    /// </summary>
    [BinaryBlockProfile(signature: "grp1")]
    public class GroupBlock : TNW4RBinaryBlock<LayoutBinaryModel>, IUseName, IUseHierarchy<GroupBlock>
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
        public GroupBlock? Parent { get; set; } = null;

        /// <summary>
        /// Child groups
        /// </summary>
        public List<GroupBlock> Children { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            Name = reader.ReadString(
                maxlen: LayoutDefine.RES_NAME_LEN,
                exact: true
            );

            ushort paneNum = reader.ReadU16();
            reader.Align(4);

            for (ushort i = 0; i < paneNum; i++)
            {
                string paneName = reader.ReadString(
                    maxlen: LayoutDefine.RES_NAME_LEN,
                    exact: true
                );

                PaneNames.Add(paneName);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            writer.WriteString(
                Name,
                maxlen: LayoutDefine.RES_NAME_LEN,
                terminate: false,
                exact: true
            );

            if (PaneNames.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many pane names");
            }

            writer.WriteU16((ushort)PaneNames.Count);
            writer.Align(4);

            foreach (var it in PaneNames)
            {
                writer.WriteString(
                    it,
                    maxlen: LayoutDefine.RES_NAME_LEN,
                    terminate: false,
                    exact: true
                );
            }
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            // This group will hold all children
            SyncGroup(src.RootGroup);
        }

        /// <summary>
        /// Updates this block to match the contents of a data-view group
        /// </summary>
        /// <param name="group">Data-view group</param>
        /// <exception cref="FileBrokenException">Group data is invalid</exception>
        private void SyncGroup(Group group)
        {
            Parent = null;
            Children.Clear();

            if (group.Name.Length > LayoutDefine.RES_NAME_LEN)
            {
                throw new FileBrokenException(
                    $"Group name is too long (> {LayoutDefine.RES_NAME_LEN} " +
                    $"characters): {group.Name}"
                );
            }

            Name = group.Name;
            PaneNames = group.PaneNames;

            foreach (var it in group.Children)
            {
                GroupBlock child =
                    Model!.CreateBlock<GroupBlock>(unmanaged: true);

                child.SyncGroup(it);

                child.Parent = this;
                Children.Add(child);
            }
        }
    }
}
