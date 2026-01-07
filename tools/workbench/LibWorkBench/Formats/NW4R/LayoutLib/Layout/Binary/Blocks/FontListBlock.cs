using LibWorkBench.Attributes;
using LibWorkBench.Core.Models.Data;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks.Details;
using LibWorkBench.Formats.NW4R.LayoutLib.Layout.Data;

namespace LibWorkBench.Formats.NW4R.LayoutLib.Layout.Binary.Blocks
{
    /// <summary>
    /// Layout font list block
    /// </summary>
    [BinaryBlockProfile(signature: "fnl1")]
    public class FontListBlock : ResListBlock
    {
        /// <summary>
        /// Font set used when building the resource list
        /// </summary>
        private HashSet<string> _fontWork = new();

        /// <summary>
        /// Updates this block to match the contents of the data-view model (derived implementation)
        /// </summary>
        /// <param name="dataModel">Data-view model</param>
        public override void DoSync(NW4RDataModel dataModel)
        {
            LayoutDataModel src = (LayoutDataModel)dataModel;

            Resources.Clear();

            _fontWork.Clear();
            FindFonts(src.RootPane);

            // Original tools seem to sort these alphabetically
            Resources.Sort((lhs, rhs) => lhs.Name.CompareTo(rhs.Name));
        }

        /// <summary>
        /// Finds all unique font resources in the pane hierarchy
        /// </summary>
        /// <param name="pane">Root pane</param>
        private void FindFonts(Pane pane)
        {
            // Only textboxes can reference font resources
            if (pane.GetType() == typeof(TextBox))
            {
                TextBox textBox = (TextBox)pane;

                // Don't include duplicate resources
                if (!_fontWork.Contains(textBox.FontName))
                {
                    _fontWork.Add(textBox.FontName);
                    Resources.Add(new(textBox.FontName));
                }
            }

            pane.Children.ForEach(FindFonts);
        }
    }
}
