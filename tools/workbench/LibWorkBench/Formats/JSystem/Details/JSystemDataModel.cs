using LibWorkBench.Core.Models.Binary;
using LibWorkBench.Core.Models.Data;

namespace LibWorkBench.Formats.JSystem.Details
{
    /// <summary>
    /// Base class for JSYSTEM data-view models (implementation details)
    /// </summary>
    /// <typeparam name="TParentResource">Parent resource class</typeparam>
    public abstract class JSystemDataModel : DataModel
    {
        /// <summary>
        /// Updates this model to match the contents of the binary-view model
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public override void Sync(BinaryModel binaryModel)
        {
            JSystemBinaryModel src = (JSystemBinaryModel)binaryModel;

            OnSync(src);
        }

        /// <summary>
        /// Updates this model to match the contents of the binary-view model (derived implementation)
        /// </summary>
        /// <param name="binaryModel">Binary-view model</param>
        public abstract void OnSync(JSystemBinaryModel binaryModel);
    }
}
