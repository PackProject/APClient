using LibWorkBench.Exceptions;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;
using System.Text;
using System.Text.RegularExpressions;
using LibWorkBench.Formats.JSystem.JMessage.Utility;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;

namespace LibWorkBench.Formats.JSystem.JMessage.Tag
{
    /// <summary>
    /// Base class for message tag code processors
    /// </summary>
    public abstract class TagProcessorBase
    {
        /// <summary>
        /// Regular expression to use when extracting tag instances
        /// </summary>
        private readonly Regex TAG_INSTANCE_REGEX = new("(\\{[^{}]+\\})");

        /// <summary>
        /// Regular expression to use when replacing tag escape characters
        /// </summary>
        private readonly Regex TAG_ESCAPE_REGEX = new("{|}");

        /// <summary>
        /// Mapping of tag code IDs to names
        /// </summary>
        private readonly Dictionary<uint, string> _tagIDToName = new();

        /// <summary>
        /// Mapping of tag code names to IDs
        /// </summary>
        private readonly Dictionary<string, uint> _tagNameToID = new();

        /// <summary>
        /// Registers a new tag code with this tag processor
        /// </summary>
        /// <param name="id">Tag code unique ID</param>
        /// <param name="name">Tag code readable name</param>
        public void RegisterTag(uint id, string name)
        {
            _tagIDToName[id] = name;
            _tagNameToID[name] = id;
        }

        /// <summary>
        /// Encodes the specified string and writes it to the output stream
        /// </summary>
        /// <param name="writer">Binary output stream</param>
        /// <param name="encoding">Text encoding type</param>
        /// <param name="text">Message text</param>
        public void Encode(WriteStream writer, TextEncoding encoding,
                           string text)
        {
            // Separate tag codes from text
            string[] tokens = TAG_INSTANCE_REGEX.Split(text);

            foreach (var token in tokens)
            {
                // Not a tag, just write the raw text
                if (!token.StartsWith('{'))
                {
                    // Convert Unicode escape sequences back into characters
                    EncodingUtil.WriteString(writer, encoding,
                        Regex.Unescape(token), terminate: false);
                }
                // Encode the tag into binary form
                else
                {
                    EncodeTag(writer, encoding, token);
                }
            }

            // Null terminator
            EncodingUtil.WriteChar(writer, encoding, 0x00);
        }

        /// <summary>
        /// Decodes the string from the input stream at the current position
        /// </summary>
        /// <param name="reader">Binary input stream</param>
        /// <param name="encoding">Text encoding type</param>
        /// <returns>Decoded string</returns>
        public string Decode(ReadStream reader, TextEncoding encoding)
        {
            // Resulting string
            StringBuilder builder = new();
            // Whether we are currently inside of a tag code
            bool isTag = false;

            while (!reader.EOF)
            {
                // Decode the tag if we just saw the marker
                if (isTag)
                {
                    builder.Append(DecodeTag(reader, encoding));

                    isTag = false;
                    continue;
                }

                uint ch = EncodingUtil.ReadChar(reader, encoding);

                // Null terminator
                if (ch == 0)
                {
                    break;
                }

                // Tag code marker
                if (ch == TagCode.MARK)
                {
                    isTag = true;
                    continue;
                }

                builder.Append(
                    EncodingUtil.DecodeChar(encoding, reader.Endian, ch));
            }

            return builder.ToString();
        }

        /// <summary>
        /// Calculates the byte-size of the specified string after it has been encoded
        /// </summary>
        /// <param name="encoding">Text encoding</param>
        /// <param name="text">Text string</param>
        /// <returns>Bytes needed to encode the string</returns>
        public ulong CalcStringSize(TextEncoding encoding, string text)
        {
            WorkMemWriter writer = new(new BinaryCharEncoding(),
                                       EndianUtil.Type.Big);

            Encode(writer, encoding, text);
            return writer.Length;
        }

        /// <summary>
        /// Encodes a message tag code and writes it to the specified stream
        /// </summary>
        /// <param name="writer">Output binary stream</param>
        /// <param name="encoding">Text encoding</param>
        /// <param name="s">Tag string</param>
        /// <exception cref="FileBrokenException">The tag name is unknown</exception>
        private void EncodeTag(WriteStream writer, TextEncoding encoding,
                               string s)
        {
            // Remove tag escape characters
            s = TAG_ESCAPE_REGEX.Replace(s, string.Empty).Trim();

            // Everything after the name is considered a parameter
            string[] tokens = s.Split((char[]?)null, count: 2,
                options: StringSplitOptions.RemoveEmptyEntries);

            string name = tokens[0];

            // Need to map the provided name to an ID
            if (!_tagNameToID.TryGetValue(name, out uint id))
            {
                throw new FileBrokenException($"Unknown tag name: {name}");
            }

            byte[] params_ = tokens.Length > 1
                           ? Util.FromHex(tokens[1]) : [];

            TagCode tag = new(id, params_);
            tag.Write(writer, encoding);
        }

        /// <summary>
        /// Decodes a message tag code from the specified stream
        /// </summary>
        /// <param name="reader">Input binary stream</param>
        /// <returns>The string representation of the tag and its parameters</returns>
        /// <exception cref="FileBrokenException">The tag ID is unknown</exception>
        private string DecodeTag(ReadStream reader, TextEncoding encoding)
        {
            TagCode tag = new();
            tag.Read(reader, encoding);

            // Need to map the provided ID to a name
            if (!_tagIDToName.TryGetValue(tag.ID, out string? name))
            {
                throw new FileBrokenException($"Unknown tag ID: {tag.ID}");
            }

            if (tag.Params.Length > 0)
            {
                // { NAME 00 01 02 ... }
                return $"{{ {name} {Util.ToHex(tag.Params)} }}";
            }
            else
            {
                // { NAME }
                return $"{{ {name} }}";
            }
        }
    }
}
