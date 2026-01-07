using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.JSystem.JMessage.Utility;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;

namespace LibWorkBench.Formats.JSystem.JMessage.Tag
{
    /// <summary>
    /// Message tag code
    /// </summary>
    public sealed class TagCode
    {
        /// <summary>
        /// Marker for the start of a tag code
        /// </summary>
        public const byte MARK = 0x1A;

        /// <summary>
        /// Minimum length of a tag code
        /// </summary>
        public const int LENGTH_MIN = 4;

        /// <summary>
        /// Unique identifier of this tag code
        /// </summary>
        public uint ID = 0;

        /// <summary>
        /// Parameters for this tag code
        /// </summary>
        public byte[] Params = [];

        /// <summary>
        /// Group ID of this tag code
        /// </summary>
        public uint Group => ID & 0x00FF0000;

        /// <summary>
        /// Index of this tag code
        /// </summary>
        public uint Index => ID & 0x0000FFFF;

        /// <summary>
        /// Constructor
        /// </summary>
        public TagCode()
        {
        }

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="id">Unique identifier</param>
        /// <param name="params_">Parameters</param>
        public TagCode(uint id, byte[] params_)
        {
            ID = id;
            Params = params_;
        }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader, TextEncoding encoding)
        {
            // Length and ID are packed as one 32-bit value
            // LLLL LLLL DDDD DDDD | DDDD DDDD DDDD DDDD
            uint packed = reader.ReadU32();

            uint length = (packed & 0xFF000000) >> 24;
            ID = packed & 0x00FFFFFF;

            if (length > 0)
            {
                int paramSize = (int)length -
                    (int)EncodingUtil.GetCharSize(encoding) - // Tag mark
                    LENGTH_MIN;                               // Length/ID packed field

                // Parameters are optional
                if (paramSize > 0)
                {
                    Params = reader.Read((ulong)paramSize);
                }
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer, TextEncoding encoding)
        {
            // Tag code mark is a character, so it must match the encoding
            EncodingUtil.WriteChar(writer, encoding, MARK);

            uint length = EncodingUtil.GetCharSize(encoding) + // Tag mark
                          LENGTH_MIN +                         // Length/ID packed field
                          (uint)Params.Length;                 // Tag parameters (optional)

            // Only one byte is reserved for the tag code length
            if (length > 0xFF)
            {
                throw new FileBrokenException("Tag code is too long");
            }

            // Length and ID are packed as one 32-bit value
            // LLLL LLLL DDDD DDDD | DDDD DDDD DDDD DDDD
            uint packed = (length & 0x000000FF) << 24 | ID;
            writer.WriteU32(packed);

            writer.Write(Params);
        }
    }
}
