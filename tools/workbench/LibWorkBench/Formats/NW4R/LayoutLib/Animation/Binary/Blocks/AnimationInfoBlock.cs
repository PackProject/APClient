using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Binary.Blocks
{
    /// <summary>
    /// Layout animation info block
    /// </summary>
    [BinaryBlockProfile(signature: "pai1")]
    public sealed class AnimationInfoBlock : TNW4RBinaryBlock<AnimationBinaryModel>
    {
        /// <summary>
        /// Number of frames in this animation
        /// </summary>
        public ushort Length { get; set; } = 0;

        /// <summary>
        /// Whether this animation should loop
        /// </summary>
        public bool Loop { get; set; } = false;

        /// <summary>
        /// Animation contents
        /// </summary>
        public List<AnimationContent> Contents { get; set; } = new();

        /// <summary>
        /// Names of all texture resources required by this animation
        /// </summary>
        public List<string> TextureNames { get; set; } = new();

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            // Content table offset is relative to this block
            long blockPos = (long)reader.Position
                - NW4RBinaryBlockHeader.STRUCT_SIZE;

            Length = reader.ReadU16();

            Loop = reader.ReadBool();
            reader.Align(4);

            ushort textureNum = reader.ReadU16();
            ushort animContNum = reader.ReadU16();
            uint animContOffsetTblOffset = reader.ReadU32();

            // Parse texture string table
            long textureTblPos = (long)reader.Position;
            List<uint> textureOffsets = new();

            for (uint i = 0; i < textureNum; i++)
            {
                textureOffsets.Add(reader.ReadU32());
            }

            foreach (var it in textureOffsets)
            {
                if ((ulong)textureTblPos + it > reader.Length)
                {
                    throw new FileBrokenException(
                        "Invalid string table offset");
                }

                reader.Seek(textureTblPos + it, SeekOrigin.Begin);
                TextureNames.Add(reader.ReadString());
            }

            // Parse animation content table
            reader.Seek(blockPos + animContOffsetTblOffset, SeekOrigin.Begin);
            List<uint> contentOffsets = new();

            for (uint i = 0; i < animContNum; i++)
            {
                contentOffsets.Add(reader.ReadU32());
            }

            foreach (var it in contentOffsets)
            {
                reader.Seek(blockPos + it, SeekOrigin.Begin);

                AnimationContent content = new();
                content.Read(reader);
                Contents.Add(content);
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

            work.WriteU16(Length);
            work.WriteBool(Loop);
            work.Align(4);

            if (TextureNames.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many texture names");
            }

            work.WriteU16((ushort)TextureNames.Count);

            if (Contents.Count > ushort.MaxValue)
            {
                throw new FileBrokenException("Too many animation contents");
            }

            work.WriteU16((ushort)Contents.Count);

            // Reserve space for content offset table offset
            long contentOffsetTblOffsetPos = (long)work.Position;
            work.WriteDebugFill(sizeof(uint));

            // Reserve space for the texture string table
            long textureTblPos = (long)work.Position;
            work.WriteDebugFill((ulong)TextureNames.Count * sizeof(uint));

            // Calculate offset for each texture name
            List<uint> textureOffsets = new();
            foreach (var it in TextureNames)
            {
                ulong offset = work.Position - (ulong)textureTblPos;

                if (offset > uint.MaxValue)
                {
                    throw new FileBrokenException(
                        "Texture string table too large");
                }

                textureOffsets.Add((uint)offset);
                work.WriteString(it);
            }

            work.Align(4);

            // Reserve space for content offset table
            long contentOffsetTblPos = (long)work.Position;
            work.WriteDebugFill((ulong)Contents.Count * sizeof(uint));

            // Calculate offset for each animation content
            List<uint> contentOffsets = new();
            foreach (var it in Contents)
            {
                // Offset includes the data block header
                ulong offset = work.Position
                    + NW4RBinaryBlockHeader.STRUCT_SIZE;

                if (offset > uint.MaxValue)
                {
                    throw new FileBrokenException(
                        "Animation content table too large");
                }

                contentOffsets.Add((uint)offset);
                it.Write(work);
            }

            // Go back and fix content offset table offset
            work.Seek(contentOffsetTblOffsetPos, SeekOrigin.Begin);
            // Offset includes the data block header
            work.WriteU32((uint)contentOffsetTblPos
                + NW4RBinaryBlockHeader.STRUCT_SIZE);

            // Go back and fix texture string table
            work.Seek(textureTblPos, SeekOrigin.Begin);
            textureOffsets.ForEach(work.WriteU32);

            // Go back and fix content offset table
            work.Seek(contentOffsetTblPos, SeekOrigin.Begin);
            contentOffsets.ForEach(work.WriteU32);

            // Flush data to the real stream
            writer.Write(work.Buffer, work.Length);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
        }
    }
}
