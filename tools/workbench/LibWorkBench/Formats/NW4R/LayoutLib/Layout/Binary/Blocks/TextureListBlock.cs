using LibWorkBench.Attributes;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout texture list block
    /// </summary>
    [BinaryBlockProfile(signature: "txl1")]
    public class TextureListBlock : ResListBlock
    {
        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            Resources.Clear();
            HashSet<string> names = new();

            foreach (var mat in src.Materials)
            {
                foreach (var tex in mat.TexMaps)
                {
                    // Don't include duplicate resources
                    if (!names.Contains(tex.TextureName))
                    {
                        names.Add(tex.TextureName);
                        Resources.Add(new(tex.TextureName));
                    }
                }
            }

            // Original tools seem to sort these alphabetically
            Resources.Sort((lhs, rhs) => lhs.Name.CompareTo(rhs.Name));
        }
    }
}
