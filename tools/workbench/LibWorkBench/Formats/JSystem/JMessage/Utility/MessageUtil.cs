using LibWorkBench.Exceptions;
using LibWorkBench.Formats.JSystem.JMessage.MsgRes.Types;

namespace LibWorkBench.Formats.JSystem.JMessage.Utility
{
    /// <summary>
    /// Message utilities
    /// </summary>
    public static class MessageUtil
    {
        /// <summary>
        /// Splits the specified message id into its group and index components
        /// </summary>
        /// <param name="id">Message ID</param>
        /// <param name="form">Message ID format</param>
        /// <param name="group">Message group</param>
        /// <param name="index">Message index</param>
        /// <exception cref="OperationException">Invalid supplemental form was provided</exception>
        public static void SplitID(uint id, FormSupplement form,
                                   out uint group, out uint index)
        {
            switch (form)
            {
                case FormSupplement.Group32:
                    group = id;
                    index = 0;
                    break;

                case FormSupplement.Group24:
                    group = (id & 0xFFFFFF00) >> 8;
                    index = id & 0x000000FF;
                    break;

                case FormSupplement.Group16:
                    group = (id & 0xFFFF0000) >> 16;
                    index = id & 0x0000FFFF;
                    break;

                case FormSupplement.Group8:
                    group = (id & 0xFF000000) >> 24;
                    index = id & 0x000000FF;
                    break;

                case FormSupplement.Group0:
                    group = 0;
                    index = id;
                    break;

                default:
                    throw new OperationException("Invalid FormSupplement");
            }
        }

        /// <summary>
        /// Joins the specified message group and index into a unique ID.
        /// The components are validated to ensure they are compataible with the specified form.
        /// </summary>
        /// <param name="form">Message ID format</param>
        /// <param name="group">Message group</param>
        /// <param name="index">Message index</param>
        /// <returns>Message ID</returns>
        /// <exception cref="OperationException">Invalid supplemental form was provided</exception>
        /// <exception cref="OperationException">Message group/index is too large</exception>
        public static uint JoinID(FormSupplement form, uint group, uint index)
        {
            switch (form)
            {
                case FormSupplement.Group32:
                    return group;

                case FormSupplement.Group24:
                    if ((group & ~0x00FFFFFF) != 0)
                    {
                        throw new OperationException("Group is too large for this form");
                    }
                    if ((index & ~0x000000FF) != 0)
                    {
                        throw new OperationException("Index is too large for this form");
                    }

                    return (group & 0x00FFFFFF) << 8 | index & 0x000000FF;

                case FormSupplement.Group16:
                    if ((group & ~0x0000FFFF) != 0)
                    {
                        throw new OperationException("Group is too large for this form");
                    }
                    if ((index & ~0x0000FFFF) != 0)
                    {
                        throw new OperationException("Index is too large for this form");
                    }

                    return (group & 0x0000FFFF) << 16 | index & 0x0000FFFF;

                case FormSupplement.Group8:
                    if ((group & ~0x000000FF) != 0)
                    {
                        throw new OperationException("Group is too large for this form");
                    }
                    if ((index & ~0x00FFFFFF) != 0)
                    {
                        throw new OperationException("Index is too large for this form");
                    }

                    return (group & 0x000000FF) << 24 | index & 0x00FFFFFF;

                case FormSupplement.Group0:
                    return index;

                default:
                    throw new OperationException("Invalid FormSupplement");
            }
        }
    }
}
