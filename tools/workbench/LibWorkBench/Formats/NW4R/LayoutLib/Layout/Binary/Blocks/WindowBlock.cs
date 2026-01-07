using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout window block
    /// </summary>
    [BinaryBlockProfile(signature: "wnd1")]
    public class WindowBlock : PaneBlock
    {
        /// <summary>
        /// Content inflation
        /// </summary>
        public WindowInflation Inflation { get; set; } = new();

        /// <summary>
        /// Window content
        /// </summary>
        public ResWindowContent Content { get; set; } = new();

        /// <summary>
        /// Texture coordinates
        /// </summary>
        public List<TexCoord> TexCoords { get; set; } = new();

        /// <summary>
        /// Window frames
        /// </summary>
        public List<ResWindowFrame> Frames { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            // Frame offsets are relative to the start of the block data
            ulong startOffset =
                reader.Position - NW4RBinaryBlockHeader.STRUCT_SIZE;

            // Common pane attributes
            base.DoRead(reader);

            Inflation.Read(reader);

            byte frameNum = reader.ReadU8();
            reader.Align(4);

            uint contentOffset = reader.ReadU32();
            uint frameOffsetTblOffset = reader.ReadU32();

            // Seek to window content
            reader.Seek((long)(startOffset + contentOffset), SeekOrigin.Begin);
            Content.Read(reader);

            // Texture coordinates follow the window content
            for (uint i = 0; i < Content.TexCoordNum; i++)
            {
                TexCoord texCoord = new();
                texCoord.Read(reader);
                TexCoords.Add(texCoord);
            }

            // Seek to frame offset table
            reader.Seek((long)(startOffset + frameOffsetTblOffset),
                        SeekOrigin.Begin);

            List<uint> offsetList = new();
            for (uint i = 0; i < frameNum; i++)
            {
                offsetList.Add(reader.ReadU32());
            }

            // Use offsets to read window frame data
            foreach (var it in offsetList)
            {
                reader.Seek((long)(startOffset + it), SeekOrigin.Begin);

                ResWindowFrame frame = new();
                frame.Read(reader);
                Frames.Add(frame);
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void DoWrite(WriteStream writer)
        {
            WorkMemWriter work = new(new BinaryCharEncoding(),
                                     writer.Endian);

            // Common pane attributes
            base.DoWrite(work);

            Inflation.Write(work);

            if (Frames.Count > byte.MaxValue)
            {
                throw new FileBrokenException("Too many window frames");
            }

            work.WriteU8((byte)Frames.Count);
            work.Align(4);

            // Reserve space for content offset
            long contentOffsetPos = (long)work.Position;
            work.WriteDebugFill(sizeof(uint));

            // Reserve space for frame offset table offset
            long frameOffsetTblOffsetPos = (long)work.Position;
            work.WriteDebugFill(sizeof(uint));

            if (TexCoords.Count > byte.MaxValue)
            {
                throw new FileBrokenException("Too many texture coordinates");
            }

            Content.TexCoordNum = (byte)TexCoords.Count;

            uint contentOffset = (uint)work.Position;
            Content.Write(work);

            // Texture coordinates follow the window content
            TexCoords.ForEach(it => it.Write(work));

            // Reserve space for frame offset table
            long frameOffsetTblPos = (long)work.Position;
            work.WriteDebugFill((ulong)(sizeof(uint) * Frames.Count));

            List<uint> offsetList = new();
            foreach (var it in Frames)
            {
                offsetList.Add((uint)work.Position);
                it.Write(work);
            }

            // Go back and fix the content offset
            work.Seek(contentOffsetPos, SeekOrigin.Begin);
            // Offset includes the data block header
            work.WriteU32(contentOffset + NW4RBinaryBlockHeader.STRUCT_SIZE);

            // Go back and fix the frame offset table offset
            work.Seek(frameOffsetTblOffsetPos, SeekOrigin.Begin);
            // Offset includes the data block header
            work.WriteU32((uint)frameOffsetTblPos
                + NW4RBinaryBlockHeader.STRUCT_SIZE);

            // Go back and fix the frame offset table
            work.Seek(frameOffsetTblPos, SeekOrigin.Begin);
            // Frame offset includes the data block header
            offsetList.ForEach(
                it => work.WriteU32(it + NW4RBinaryBlockHeader.STRUCT_SIZE));

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
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
            Window window = (Window)pane;

            Inflation = window.Inflation;
            Content = ConvertWindowConvent(window.Content);
            TexCoords = window.Content.TexCoords;
            Frames = window.Frames.Select(ConvertWindowFrame).ToList();
        }

        /// <summary>
        /// Converts data-view window content into its binary-view representation
        /// </summary>
        /// <param name="content">Data-view window content</param>
        /// <returns>Binary-view window content</returns>
        /// <exception cref="FileBrokenException">Content material is invalid</exception>
        /// <exception cref="FileBrokenException">Content holds too many texture coordinates</exception>
        private ResWindowContent ConvertWindowConvent(WindowContent content)
        {
            ResWindowContent res = new();

            MaterialListBlock matList = Model!.GetOne<MaterialListBlock>();

            int index = matList.Materials.FindIndex(
                it => it.Name == content.MaterialName);

            if (index < 0)
            {
                throw new FileBrokenException(
                    $"Material does not exist: {content.MaterialName}");
            }

            if (content.TexCoords.Count > byte.MaxValue)
            {
                throw new FileBrokenException(
                    "Too many texture coordinates");
            }

            res.VertexColors = content.VertexColors;
            res.MaterialIndex = (ushort)index;
            res.TexCoordNum = (byte)content.TexCoords.Count;

            return res;
        }

        /// <summary>
        /// Converts a data-view window frame into its binary-view representation
        /// </summary>
        /// <param name="frame">Data-view window frame</param>
        /// <returns>Binary-view window frame</returns>
        /// <exception cref="FileBrokenException">Frame material is invalid</exception>
        private ResWindowFrame ConvertWindowFrame(WindowFrame frame)
        {
            ResWindowFrame res = new();

            MaterialListBlock matList = Model!.GetOne<MaterialListBlock>();

            int index = matList.Materials.FindIndex(
                it => it.Name == frame.MaterialName);

            if (index < 0)
            {
                throw new FileBrokenException(
                    $"Material does not exist: {frame.MaterialName}");
            }

            res.MaterialIndex = (ushort)index;
            res.TextureFlip = frame.TextureFlip;

            return res;
        }
    }
}
