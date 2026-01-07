using LibWorkBench.Core.Models;
using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.JSystem
{
    /// <summary>
    /// Base class for JSYSTEM resources
    /// </summary>
    /// <typeparam name="TBinaryModel">Binary-view model class</typeparam>
    /// <typeparam name="TDataModel">Data-view model class</typeparam>
    public abstract class TJSystemResource<TBinaryModel, TDataModel> : TResource<TBinaryModel, TDataModel>
        where TBinaryModel : BinaryModel, new()
        where TDataModel : DataModel, new()
    {
    }
}
