using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Binary.Details;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace LibWorkBench.Formats.NW4R.Details
{
    /// <summary>
    /// Base class for NW4R binary-view models (implementation details)
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    /// <typeparam name="TBlockFactory">Block factory class</typeparam>
    public abstract class NW4RBinaryModel : BlockBinaryModel
    {
        /// <summary>
        /// Version of this file's specification
        /// </summary>
        public uint Version { get; set; } = 0;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="factory">Factory used for block creation</param>
        public NW4RBinaryModel(BinaryBlockFactory factory)
            : base(factory)
        {
        }

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            NW4RBinaryFileHeader fileHeader = new();
            fileHeader.Read(reader);

            if (fileHeader.Signature != Profile.Signature)
            {
                throw new FileSignatureException(
                    $"File signature does not match " +
                    $"(expected {Profile.Signature}, got {fileHeader.Signature})");
            }

            Version = fileHeader.Version;
            if (!Profile.Versions.Contains(Version))
            {
                throw new FileNotSupportedException(
                    $"This version ({Version}) is not supported");
            }

            if (fileHeader.FileSize > reader.Length)
            {
                throw new FileBrokenException("File size is too large");
            }

            if (fileHeader.HeaderSize > fileHeader.FileSize
                || fileHeader.HeaderSize > reader.Length)
            {
                throw new FileBrokenException("Header size is too large");
            }

            // Derived type may have its own header structure
            OnRead(reader);

            // Align to the first block
            reader.Align(Profile.Alignment);

            for (uint i = 0; i < fileHeader.DataBlocks; i++)
            {
                if (reader.Position % Profile.Alignment != 0)
                {
                    throw new FileBrokenException(
                        "Binary block is misaligned");
                }

                // Need to save block position for jumping to the next block
                ulong blockStart = reader.Position;

                NW4RBinaryBlockHeader blockHeader = new();
                blockHeader.Read(reader);

                // Factory decides what to do from the signature
                BinaryBlock block = CreateBlock(blockHeader.Signature);
                block.Read(reader);

                ReadBlockCallback(reader, block);

                // Jump to the next block
                reader.Seek((long)(blockStart + blockHeader.Size),
                            SeekOrigin.Begin);
            }
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            // Version may have been changed so check again
            if (!Profile.Versions.Contains(Version))
            {
                throw new FileNotSupportedException(
                    $"This version ({Version}) is not supported");
            }

            BlocksWritten = 0;

            NW4RBinaryFileHeader fileHeader = new();
            fileHeader.Signature = Profile.Signature;
            fileHeader.Version = (ushort)Version;

            fileHeader.ByteOrder = writer.Endian == EndianUtil.Type.Big
                ? ByteOrder.Big : ByteOrder.Little;

            // Work buffer for tracking filesize
            WorkMemWriter content = new(new BinaryCharEncoding(),
                                        writer.Endian);

            // Write header to make room, will need to correct it later
            fileHeader.Write(content);

            // Derived type may have its own header structure
            OnWrite(content);

            // Save header size for later
            fileHeader.HeaderSize = (ushort)content.Length;

            // Align up to first block
            content.Align(Profile.Alignment);

            // Write blocks
            foreach (var blockList in _manager.Blocks.Values)
            {
                foreach (var block in blockList)
                {
                    // Make sure all blocks are compatible
                    if (Version < block.Profile.MinVersion)
                    {
                        throw new FileNotSupportedException(
                            $"{block.GetType().Name} requires at least " +
                            $"version {block.Profile.MinVersion}");
                    }

                    block.Write(content);
                    content.Align(Profile.Alignment);

                    WriteBlockCallback(content, block);
                }
            }

            // Go back and fix the header
            fileHeader.FileSize = (uint)content.Length;
            fileHeader.DataBlocks = (ushort)BlocksWritten;
            content.Seek(0, SeekOrigin.Begin);
            fileHeader.Write(content);

            // Flush data to the real stream
            writer.Write(content.Buffer, content.Length);
        }

        /// <summary>
        /// Updates this model to match the contents of the data-view model
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void Sync(DataModel dataModel)
        {
            NW4RDataModel src = (NW4RDataModel)dataModel;

            Version = src.Version;

            OnSync(src);
        }

        /// <summary>
        /// Deserializes the contents of this model from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void OnRead(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this model to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void OnWrite(WriteStream writer);

        /// <summary>
        /// Updates this model to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public abstract void OnSync(NW4RDataModel dataModel);
    }
}
