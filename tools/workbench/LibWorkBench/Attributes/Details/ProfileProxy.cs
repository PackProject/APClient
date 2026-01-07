using LibWorkBench.Exceptions;
using System.Reflection;

namespace LibWorkBench.Attributes.Details
{
    /// <summary>
    /// Profile accessor
    /// </summary>
    /// <typeparam name="TProfile">Profile attribute type</typeparam>
    public abstract class ProfileProxy<TProfile>
        where TProfile : Attribute
    {
        /// <summary>
        /// Accesses the held profile
        /// </summary>
        public TProfile Profile => GetProfile();

        /// <summary>
        /// Accesses the held profile
        /// </summary>
        /// <returns>Profile instance</returns>
        public TProfile GetProfile() => GetAttribute(GetType());

        /// <summary>
        /// Accesses the held profile (static)
        /// </summary>
        /// <typeparam name="THolder">Self type (needed for derived type access)</typeparam>
        /// <returns>Profile instance</returns>
        public static TProfile GetProfileStatic<THolder>()
            => GetAttribute(typeof(THolder));

        /// <summary>
        /// Accesses the held attribute
        /// </summary>
        /// <param name="selfType">Derived self type</param>
        /// <returns>Attribute instance</returns>
        private static TProfile GetAttribute(Type selfType)
        {
            TProfile? attribute = selfType.GetCustomAttribute<TProfile>();

            if (attribute == null)
            {
                throw new MissingAttributeException(
                    $"Please register a ${typeof(TProfile).Name} " +
                    $"with the class ${selfType.FullName}");
            }

            return attribute;
        }
    }
}
