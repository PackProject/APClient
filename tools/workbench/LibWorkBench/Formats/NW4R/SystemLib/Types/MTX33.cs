using LibWorkBench.Core;
using LibWorkBench.IO.Streams;

namespace LibWorkBench.Formats.NW4R.SystemLib.Types
{
    /// <summary>
    /// 3x3 matrix
    /// </summary>
    public sealed class MTX33 : IUseBinary
    {
        /// <summary>
        /// Underlying matrix data
        /// </summary>
        public float[,] M = new float[3, 3];

        /// <summary>
        /// Accesses the specified matrix element
        /// </summary>
        /// <param name="row">Element row index</param>
        /// <param name="col">Element column index</param>
        /// <returns>Matrix element</returns>
        public float this[int row, int col]
        { get => M[row, col]; set => M[row, col] = value; }

        /// <summary>
        /// Accesses the element at row 0, column 0
        /// </summary>
        public float M00 { get => M[0, 0]; set => M[0, 0] = value; }
        /// <summary>
        /// Accesses the element at row 0, column 1
        /// </summary>
        public float M01 { get => M[0, 1]; set => M[0, 1] = value; }
        /// <summary>
        /// Accesses the element at row 0, column 2
        /// </summary>
        public float M02 { get => M[0, 2]; set => M[0, 2] = value; }

        /// <summary>
        /// Accesses the element at row 1, column 0
        /// </summary>
        public float M10 { get => M[1, 0]; set => M[1, 0] = value; }
        /// <summary>
        /// Accesses the element at row 1, column 1
        /// </summary>
        public float M11 { get => M[1, 1]; set => M[1, 1] = value; }
        /// <summary>
        /// Accesses the element at row 1, column 2
        /// </summary>
        public float M12 { get => M[1, 2]; set => M[1, 2] = value; }

        /// <summary>
        /// Accesses the element at row 2, column 0
        /// </summary>
        public float M20 { get => M[2, 0]; set => M[2, 0] = value; }
        /// <summary>
        /// Accesses the element at row 2, column 1
        /// </summary>
        public float M21 { get => M[2, 1]; set => M[2, 1] = value; }
        /// <summary>
        /// Accesses the element at row 2, column 2
        /// </summary>
        public float M22 { get => M[2, 2]; set => M[2, 2] = value; }

        /// <summary>
        /// Deserializes the contents of this object from a file
        /// </summary>
        /// <param name="reader">Binary stream to the file</param>
        public void Read(ReadStream reader)
        {
            for (int row = 0; row < M.GetLength(0); row++)
            {
                for (int col = 0; col < M.GetLength(1); col++)
                {
                    M[row, col] = reader.ReadF32();
                }
            }
        }

        /// <summary>
        /// Serializes the contents of this object to a file
        /// </summary>
        /// <param name="writer">Binary stream to the file</param>
        public void Write(WriteStream writer)
        {
            for (int row = 0; row < M.GetLength(0); row++)
            {
                for (int col = 0; col < M.GetLength(1); col++)
                {
                    writer.WriteF32(M[row, col]);
                }
            }
        }
    }
}
