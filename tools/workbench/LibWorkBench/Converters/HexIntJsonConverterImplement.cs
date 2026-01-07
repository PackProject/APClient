using LibWorkBench.Converters.Details;

namespace LibWorkBench.Converters
{
    /// <summary>
    /// JSON hexadecimal converter for unsigned 8-bit integers
    /// </summary>
    public sealed class HexUInt8JsonConverter : HexJsonConverterImpl<byte>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for unsigned 16-bit integers
    /// </summary>
    public sealed class HexUInt16JsonConverter : HexJsonConverterImpl<ushort>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for unsigned 32-bit integers
    /// </summary>
    public sealed class HexUInt32JsonConverter : HexJsonConverterImpl<uint>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for unsigned 64-bit integers
    /// </summary>
    public sealed class HexUInt64JsonConverter : HexJsonConverterImpl<ulong>
    {
    }

    /// <summary>
    /// JSON hexadecimal converter for signed 8-bit integers
    /// </summary>
    public sealed class HexInt8JsonConverter : HexJsonConverterImpl<sbyte>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for signed 16-bit integers
    /// </summary>
    public sealed class HexInt16JsonConverter : HexJsonConverterImpl<short>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for signed 32-bit integers
    /// </summary>
    public sealed class HexInt32JsonConverter : HexJsonConverterImpl<int>
    {
    }
    /// <summary>
    /// JSON hexadecimal converter for signed 64-bit integers
    /// </summary>
    public sealed class HexInt64JsonConverter : HexJsonConverterImpl<long>
    {
    }
}
