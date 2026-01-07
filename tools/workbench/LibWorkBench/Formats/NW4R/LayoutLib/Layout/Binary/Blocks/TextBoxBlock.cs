using LibWorkBench.Attributes;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Types;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout textbox block
    /// </summary>
    [BinaryBlockProfile(signature: "txt1")]
    public class TextBoxBlock : PaneBlock
    {
        /// <summary>
        /// Text buffer capacity, in bytes
        /// </summary>
        public ushort TextCapacity { get; set; } = 0;

        /// <summary>
        /// Material list index
        /// </summary>
        public ushort MaterialIndex { get; set; } = 0;

        /// <summary>
        /// Font list index
        /// </summary>
        public ushort FontIndex { get; set; } = 0;

        /// <summary>
        /// Text base position
        /// </summary>
        public BasePosition TextPosition { get; set; } = new();

        /// <summary>
        /// Text alignment
        /// </summary>
        public TextAlignment TextAlignment { get; set; } = TextAlignment.Left;

        /// <summary>
        /// Text vertex colors
        /// </summary>
        public TextColorSet TextColors { get; set; } = new();

        /// <summary>
        /// Text font size
        /// </summary>
        public Size FontSize { get; set; } = new();

        /// <summary>
        /// Spacing between characters
        /// </summary>
        public float CharSpace { get; set; } = 0.0f;

        /// <summary>
        /// Spacing between lines
        /// </summary>
        public float LineSpace { get; set; } = 0.0f;

        /// <summary>
        /// Text string contents
        /// </summary>
        public string TextContent { get; set; } = "";

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void DoRead(ReadStream reader)
        {
            // Start position is the base for offsets
            ulong startOffset = reader.Position;

            // Common pane attributes
            base.DoRead(reader);

            TextCapacity = reader.ReadU16();
            ushort textBytes = reader.ReadU16();

            MaterialIndex = reader.ReadU16();
            FontIndex = reader.ReadU16();

            TextPosition.Read(reader);
            TextAlignment = (TextAlignment)reader.ReadU8();

            // Padding after text alignment
            reader.Align(4);

            // Text offset is relative to the start of the block data
            uint textOffset =
                reader.ReadU32() - NW4RBinaryBlockHeader.STRUCT_SIZE;

            TextColors.Read(reader);
            FontSize.Read(reader);

            CharSpace = reader.ReadF32();
            LineSpace = reader.ReadF32();

            reader.Seek((long)(startOffset + textOffset), SeekOrigin.Begin);

            TextContent = reader.ReadWideString(
                maxlen: textBytes / sizeof(ushort));
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

            // Null terminator is included in the byte size
            uint textBytes = ((uint)TextContent.Length + 1) * sizeof(ushort);
            if (textBytes > ushort.MaxValue)
            {
                throw new FileBrokenException("Text content is too long");
            }

            // Capacity must at least fit the text content
            TextCapacity = Math.Max(TextCapacity, (ushort)textBytes);

            work.WriteU16(TextCapacity);
            work.WriteU16((ushort)textBytes);

            work.WriteU16(MaterialIndex);
            work.WriteU16(FontIndex);

            TextPosition.Write(work);
            work.WriteU8((byte)TextAlignment);

            // Padding after text alignment
            work.Align(4);

            // Reserve space for text offset
            long textOffsetPos = (long)work.Position;
            work.WriteDebugFill(sizeof(uint));

            TextColors.Write(work);
            FontSize.Write(work);

            work.WriteF32(CharSpace);
            work.WriteF32(LineSpace);

            uint textOffset =
                (uint)work.Position + NW4RBinaryBlockHeader.STRUCT_SIZE;

            work.WriteWideString(TextContent);

            // Go back and fix the text offset
            work.Seek(textOffsetPos, SeekOrigin.Begin);
            work.WriteU32(textOffset);

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
            TextBox textBox = (TextBox)pane;

            MaterialListBlock matList = Model!.GetOne<MaterialListBlock>();

            int matIndex = matList.Materials.FindIndex(
                it => it.Name == textBox.MaterialName);

            if (matIndex < 0)
            {
                throw new FileBrokenException(
                    $"Material does not exist: {textBox.MaterialName}");
            }

            FontListBlock fontList = Model!.GetOne<FontListBlock>();

            int fontIndex = fontList.Resources.FindIndex(
                it => it.Name == textBox.FontName);

            if (fontIndex < 0)
            {
                throw new FileBrokenException(
                    $"Font does not exist: {textBox.FontName}");
            }

            TextCapacity = textBox.TextCapacity;
            MaterialIndex = (ushort)matIndex;
            FontIndex = (ushort)fontIndex;
            TextPosition = textBox.TextPosition;
            TextAlignment = textBox.TextAlignment;
            TextColors = textBox.TextColors;
            FontSize = textBox.FontSize;
            CharSpace = textBox.CharSpace;
            LineSpace = textBox.LineSpace;
            TextContent = textBox.TextContent;
        }
    }
}
