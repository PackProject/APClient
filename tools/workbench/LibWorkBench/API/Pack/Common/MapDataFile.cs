using LibWorkBench.Attributes;
using LibWorkBench.Core.Models;
using LibWorkBench.Formats.Pack.Common.MapData.Binary;
using LibWorkBench.Formats.Pack.Common.MapData.Data;

namespace LibWorkBench.API.Pack.Common
{
    /// <summary>
    /// Pack Mapdata (PMP) file
    /// </summary>
    [ResourceProfile(name: "mapdata", extension: "pmp")]
    public sealed class MapDataFile : TResource<MapDataBinaryModel, MapDataDataModel>
    {
    }
}
