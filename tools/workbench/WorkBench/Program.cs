using LibWorkBench.API.Pack.Common;
using LibWorkBench.IO.Streams;
using LibWorkBench.Utility;

namespace WorkBench
{
    public class Program
    {
        static void Main(string[] args)
        {
            MapDataFile res = new();

            using (BinaryFileReader f = new("D:/Downloads/mapdata/cow_field1P.pmp",
                                            EndianUtil.Type.Big))
            {
                res.Read(f);
            }

            using (JsonFileWriter f = new("D:/Downloads/pnprally/cow_field1P.json"))
            {
                res.Dump(f);
            }

            //res = new();

            //using (JsonFileReader f = new("D:/Downloads/lyt/dummy.json"))
            //{
            //    res.Load(f);
            //}

            //using (BinaryFileWriter f = new("D:/Downloads/lyt/dummy.brlyt",
            //                                EndianUtil.Type.Big))
            //{
            //    res.Write(f);
            //}
        }
    }
}
