using LibWorkBench.Core.Models;
using LibWorkBench.Formats.NW4R.Details;

namespace LibWorkBench.Formats.NW4R
{
    /// <summary>
    /// Base class for NW4R resources
    /// </summary>
    /// <typeparam name="TBinaryModel">Binary-view model class</typeparam>
    /// <typeparam name="TDataModel">Data-view model class</typeparam>
    public abstract class TNW4RResource<TBinaryModel, TDataModel> : TResource<TBinaryModel, TDataModel>
        where TBinaryModel : NW4RBinaryModel, new()
        where TDataModel : NW4RDataModel, new()
    {
    }
}
