using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;
using LibWorkBench.Formats.Revolution.GX.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout picture block
    /// </summary>
    [BinaryBlockProfile(signature: "pic1")]
    public class PictureBlock : PaneBlock
    {
        /// <summary>
        /// Vertex colors
        /// </summary>
        public VertexColorSet VertexColors { get; set; } = new();

        /// <summary>
        /// Material list index
        /// </summary>
        public ushort MaterialIndex { get; set; } = 0;

        /// <summary>
        /// Texture coordinates
        /// </summary>
        public List<TexCoord> TexCoords { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            // Common pane attributes
            base.DoRead(reader);

            VertexColors.Read(reader);
            MaterialIndex = reader.ReadU16();

            byte texCoordNum = reader.ReadU8();
            if (texCoordNum > (byte)GXTexCoordID.GX_MAX_TEXCOORD)
            {
                throw new FileBrokenException("Too many texture coordinates");
            }

            // Padding after texture coordinate count
            reader.Align(4);

            for (uint i = 0; i < texCoordNum; i++)
            {
                TexCoord texCoord = new();
                texCoord.Read(reader);
                TexCoords.Add(texCoord);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            // Common pane attributes
            base.DoWrite(writer);

            VertexColors.Write(writer);
            writer.WriteU16(MaterialIndex);

            if (TexCoords.Count > (byte)GXTexCoordID.GX_MAX_TEXCOORD)
            {
                throw new FileBrokenException("Too many texture coordinates");
            }

            writer.WriteU8((byte)TexCoords.Count);

            // Padding after texture coordinate count
            writer.Align(4);

            // Texture coordinate data
            TexCoords.ForEach(it => it.Write(writer));
        }

        /// <summary>
        /// Updates this block to match the contents of a data-view pane
        /// </summary>
        /// <param name="pane">Data-view pane</param>
        /// <exception cref="FileBrokenException">Pane data is invalid</exception>
        protected override void SyncPane(Pane pane)
        {
            // Common pane attributes
            base.SyncPane(pane);
            Picture picture = (Picture)pane;

            MaterialListBlock matList = Model!.GetOne<MaterialListBlock>();

            int index = matList.Materials.FindIndex(
                it => it.Name == picture.MaterialName);

            if (index < 0)
            {
                throw new FileBrokenException(
                    $"Material does not exist: {picture.MaterialName}");
            }

            VertexColors = picture.VertexColors;
            MaterialIndex = (ushort)index;
            TexCoords = picture.TexCoords;
        }
    }
}
