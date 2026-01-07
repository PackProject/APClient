using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Formats.JSystem.Details;
using LibWorkBench.IO.Encodings;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace LibWorkBench.Formats.JSystem
{
    /// <summary>
    /// Base class for JSYSTEM binary-view blocks
    /// </summary>
    /// <typeparam name="TParentModel">Parent model class</typeparam>
    public abstract class TJSystemBinaryBlock<TParentModel> : TBinaryBlock<TParentModel>
        where TParentModel : JSystemBinaryModel, new()
    {
        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public override void OnRead(ReadStream reader)
        {
            DoRead(reader);
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public override void OnWrite(WriteStream writer)
        {
            JSystemBinaryBlockHeader blockHeader = new();
            blockHeader.Signature = Profile.Signature;

            // Work buffer for tracking filesize
            WorkMemWriter content = new(new BinaryCharEncoding(),
                                        writer.Endian);

            // Write header to make room, will need to correct it later
            blockHeader.Write(content);

            // Derived block contents
            DoWrite(content);

            // Reflect accurate block size in the header
            blockHeader.Size = Util.RoundUp((uint)content.Length,
                                            Model!.Profile.Alignment);

            // Go back and fix the header
            content.Seek(0, SeekOrigin.Begin);
            blockHeader.Write(content);

            // Flush data to the real stream
            writer.Write(content.Buffer, content.Length);
        }

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void OnSync(DataModel dataModel)
        {
            JSystemDataModel src = (JSystemDataModel)dataModel;

            DoSync(src);
        }

        /// <summary>
        /// Deserializes the contents of this object from a file (derived implementation)
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public abstract void DoRead(ReadStream reader);

        /// <summary>
        /// Serializes the contents of this object to a file (derived implementation)
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public abstract void DoWrite(WriteStream writer);

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public abstract void DoSync(JSystemDataModel dataModel);
    }
}
