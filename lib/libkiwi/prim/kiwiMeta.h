#ifndef LIBKIWI_PRIM_META_H
#define LIBKIWI_PRIM_META_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

namespace mp {
//! @addtogroup libkiwi_mp
//! @{

/******************************************************************************
 *
 * Type trait constants
 *
 ******************************************************************************/

/**
 * @name Primitive constants
 */
/**@{*/
template <typename T, T V> struct integral_constant {
    static const T value = V;
};

struct true_type : integral_constant<bool, true> {};
struct false_type : integral_constant<bool, false> {};
/**@}*/

/******************************************************************************
 *
 * Type categories
 *
 ******************************************************************************/

/**
 * @name Tests whether the specified type is a pointer
 */
/**@{*/
template <class T> struct is_pointer : false_type {};

template <class T> struct is_pointer<T*> : true_type {};
template <class T> struct is_pointer<T* const> : true_type {};
template <class T> struct is_pointer<T* volatile> : true_type {};
template <class T> struct is_pointer<T* const volatile> : true_type {};
/**@}*/

/******************************************************************************
 *
 * Type properties
 *
 ******************************************************************************/

/**
 * @name Tests whether the specified type is const-qualified
 */
/**@{*/
template <typename T> struct is_const : false_type {};
template <typename T> struct is_const<const T> : true_type {};
/**@}*/

/******************************************************************************
 *
 * Type modifications
 *
 ******************************************************************************/

/**
 * @name Adds a const qualifier to the specified type
 */
/**@{*/
template <typename T> struct add_const {
    typedef const T type;
};
/**@}*/

/**
 * @name Removes the const qualifier from the specified type
 */
/**@{*/
template <typename T> struct remove_const {
    typedef T type;
};
template <typename T> struct remove_const<const T> {
    typedef T type;
};
/**@}*/

/**
 * @name Moves the const qualifier from the first type to the second type
 */
/**@{*/
template <typename TFrom, typename TTo> struct move_const {
    typedef TTo type;
};

template <typename TFrom, typename TTo>
struct move_const<const TFrom, const TTo> {
    typedef const typename remove_const<TTo>::type type;
};

template <typename TFrom, typename TTo> struct move_const<const TFrom, TTo> {
    typedef const typename remove_const<TTo>::type type;
};

template <typename TFrom, typename TTo> struct move_const<TFrom, const TTo> {
    typedef const typename remove_const<TTo>::type type;
};
/**@}*/

/******************************************************************************
 *
 * Type transformations
 *
 ******************************************************************************/

/**
 * @name Conditional expression
 */
/**@{*/
template <bool B, typename T, typename F> struct conditional {
    typedef T type;
};

template <typename T, typename F> struct conditional<false, T, F> {
    typedef F type;
};
/**@}*/

/**
 * @name Conditional enable
 */
/**@{*/
template <bool B, typename T = void> struct enable_if {};

template <typename T> struct enable_if<true, T> {
    typedef T type;
};
/**@}*/

//! @}
} // namespace mp

//! @}
} // namespace kiwi

#endif
