namespace LibWorkBench.Core
{
    /// <summary>
    /// Interface for parent/child relationships
    /// </summary>
    /// <typeparam name="TDerived">Derived type</typeparam>
    public interface IUseHierarchy<TDerived>
        where TDerived : IUseHierarchy<TDerived>
    {
        /// <summary>
        /// Parent object
        /// </summary>
        TDerived? Parent { get; set; }

        /// <summary>
        /// Children objects
        /// </summary>
        List<TDerived> Children { get; set; }
    }
}
