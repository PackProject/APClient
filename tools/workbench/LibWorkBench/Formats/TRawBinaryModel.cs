using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Details;
using LibWorkBench.Exceptions;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats
{
    /// <summary>
    /// Base class for simple/"single-block" binary-view models
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class TRawBinaryModel<TParentResource> : BinaryModel
        where TParentResource : ResourceImpl
    {
        /// <summary>
        /// Resource that owns this model
        /// </summary>
        public new TParentResource? Resource
            => (TParentResource?)base.Resource;

        /// <summary>
        /// Deserializes the contents of this model from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void Read(ReadStream reader)
        {
            string signature = reader.ReadString(
                maxlen: Profile.Signature.Length
            );

            if (signature != Profile.Signature)
            {
                throw new FileSignatureException(
                    $"File signature does not match " +
                    $"(expected {Profile.Signature}, got {signature})");
            }

            OnRead(reader);
        }

        /// <summary>
        /// Serializes the contents of this model to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void Write(WriteStream writer)
        {
            writer.WriteString(
                Profile.Signature,
                exact: true
            );

            OnWrite(writer);
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
    }
}
