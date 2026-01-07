using LibWorkBench.Core;
using LibWorkBench.IO.Streams;
using LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types;
using System.Text.Json.Serialization;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Animation.Types.Details
{
    /// <summary>
    /// Base class for animation key frames
    /// </summary>
    [JsonPolymorphic(TypeDiscriminatorPropertyName = "curve")]
    [JsonDerivedType(typeof(StepKey), typeDiscriminator: "step")]
    [JsonDerivedType(typeof(HermiteKey), typeDiscriminator: "hermite")]
    public abstract class KeyFrameImpl : IUseBinary
    {
        /// <summary>
        /// Key frame type
        /// </summary>
        public enum Type
        {
            /// <summary>
            /// Value is constant
            /// </summary>
            None,

            /// <summary>
            /// Value changes through linear frame values
            /// </summary>
            Step,

            /// <summary>
            /// Value changes through Hermite interpolation
            /// </summary>
            Hermite
        }

        /// <summary>
        /// Key frame type
        /// </summary>
        [JsonPropertyOrder(int.MinValue)]
        public Type KeyType { get; private set; } = Type.None;

        /// <summary>
        /// Key frame index
        /// </summary>
        [JsonPropertyOrder(int.MinValue + 1)]
        public float Frame { get; set; } = 0.0f;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="type">Key frame type</param>
        public KeyFrameImpl(Type type)
        {
            KeyType = type;
        }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void Read(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void Write(WriteStream writer);
    }
}
