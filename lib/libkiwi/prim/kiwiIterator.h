#ifndef LIBKIWI_PRIM_ITERATOR_H
#define LIBKIWI_PRIM_ITERATOR_H
#include <libkiwi/k_types.h>

namespace kiwi {
//! @addtogroup libkiwi_prim
//! @{

namespace detail {
//! @addtogroup libkiwi_prim
//! @{

/**
 * @brief Common iterator implementation
 *
 * @details The derived class must implement the following functions:
 * - `void Next()` For incrementing the iterator once
 * - `void Prev()` For decrementing the iterator once
 * - `void Move(int n)` For advancing the iterator by a specified amount
 * - `int Dist(it) const` For computing distance between iterators
 * - `TValue& Get()` For accessing the iterator's value
 * - `bool Equals(it) const` For comparing for equality with another iterator
 *
 * @tparam TDerived Derived iterator class type
 * @tparam TValue Iterator value type
 * @tparam TPointer Value pointer type
 * @tparam TReference Value reference type
 * @tparam TTag Iterator tag type
 */
template <typename TDerived, typename TValue, typename TPointer,
          typename TReference, typename TTag>
class Iterator {
public:
    // For readability
    typedef Iterator SelfType;
    typedef TDerived DerivedType;
    typedef TPointer PointerType;
    typedef TReference ReferenceType;

    // Expose TValue for iterator adapters
    typedef TValue ValueType;

    // Expose TTag for algorithms
    typedef TTag TagType;

public:
    /**
     * @brief Pre-increment operator
     */
    DerivedType& operator++() {
        detail_DownCast().Next();
        return detail_DownCast();
    }
    /**
     * @brief Post-increment operator
     */
    DerivedType operator++(int) {
        DerivedType clone = detail_DownCast();
        detail_DownCast().Next();
        return clone;
    }

    /**
     * @brief Pre-decrement operator
     */
    DerivedType& operator--() {
        detail_DownCast().Prev();
        return detail_DownCast();
    }
    /**
     * @brief Post-decrement operator
     */
    DerivedType operator--(int) {
        DerivedType clone = detail_DownCast();
        detail_DownCast().Prev();
        return clone;
    }

    /**
     * @brief Increment operator
     *
     * @param n Distance to move
     */
    DerivedType operator+(int n) const {
        DerivedType clone = detail_DownCast();
        clone += n;
        return clone;
    }
    /**
     * @brief In-place increment operator
     *
     * @param n Distance to move
     */
    DerivedType& operator+=(int n) {
        detail_DownCast().Move(n);
        return detail_DownCast();
    }

    /**
     * @brief Decrement operator
     *
     * @param n Distance to move
     */
    DerivedType operator-(int n) const {
        DerivedType clone = detail_DownCast();
        clone -= n;
        return clone;
    }
    /**
     * @brief In-place decrement operator
     *
     * @param n Distance to move
     */
    DerivedType& operator-=(int n) {
        detail_DownCast().Move(-n);
        return detail_DownCast();
    }

    /**
     * @brief Accesses the value at the iterator's position (by reference)
     */
    ReferenceType operator*() {
        return detail_DownCast().Get();
    }
    /**
     * @brief Accesses the value at the iterator's position (by pointer)
     */
    PointerType operator->() {
        return &detail_DownCast().Get();
    }

public:
    /**
     * @brief Views this iterator as its derived type
     */
    K_INLINE DerivedType& detail_DownCast() {
        return *static_cast<DerivedType*>(this);
    }
    /**
     * @brief Views this iterator as its derived type (const-view)
     */
    K_INLINE const DerivedType& detail_DownCast() const {
        return *static_cast<const DerivedType*>(this);
    }
};

/**
 * @brief Tests whether the left-hand-side iterator is positioned earlier than
 * the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator<(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                        const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rLhs.detail_DownCast().Dist(rRhs.detail_DownCast()) > 0;
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned earlier than
 * or at the same position as the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator<=(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                         const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rLhs.detail_DownCast() < rRhs.detail_DownCast() ||
           rLhs.detail_DownCast() == rRhs.detail_DownCast();
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned later than
 * the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator>(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                        const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rLhs.detail_DownCast().Dist(rRhs.detail_DownCast()) < 0;
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned later than or
 * at the same position as the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator>=(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                         const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rLhs.detail_DownCast() > rRhs.detail_DownCast() ||
           rLhs.detail_DownCast() == rRhs.detail_DownCast();
}

/**
 * @brief Computes the distance between two iterators
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE int operator-(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                       const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rRhs.detail_DownCast().Dist(rLhs.detail_DownCast());
}

/**
 * @brief Checks two iterators for equality
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator==(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                         const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return rLhs.detail_DownCast().Equals(rRhs.detail_DownCast());
}
/**
 * @brief Checks two iterators for inequality
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename D1, typename V1, typename P1, typename R1, typename T1,
          typename D2, typename V2, typename P2, typename R2, typename T2>
K_INLINE bool operator!=(const Iterator<D1, V1, P1, R1, T1>& rLhs,
                         const Iterator<D2, V2, P2, R2, T2>& rRhs) {

    return !rLhs.detail_DownCast().Equals(rRhs.detail_DownCast());
}

//! @}
} // namespace detail

/******************************************************************************
 *
 * Common iterator functionality
 *
 ******************************************************************************/

/**
 * @brief Reverse iterator
 *
 * @tparam TIterator Base/adapted iterator type
 */
template <typename TIterator> class ReverseIterator {
public:
    // For readability
    typedef ReverseIterator SelfType;
    typedef TIterator BaseType;

    // Access value types of underlying iterator
    typedef typename TIterator::ValueType ValueType;
    typedef typename TIterator::ReferenceType ReferenceType;
    typedef typename TIterator::PointerType PointerType;

public:
    /**
     * @brief Constructor
     *
     * @param it Base/adapted iterator
     */
    explicit ReverseIterator(BaseType it) : mBase(it) {}

    /**
     * @brief Accesses the base/adapted iterator
     */
    BaseType GetBase() const {
        return mBase;
    }

    /**
     * @brief Pre-increment operator
     */
    SelfType& operator++() {
        --mBase;
        return *this;
    }
    /**
     * @brief Post-increment operator
     */
    SelfType operator++(int) const {
        SelfType clone = *this;
        --mBase;
        return clone;
    }

    /**
     * @brief Pre-decrement operator
     */
    SelfType& operator--() {
        ++mBase;
        return *this;
    }
    /**
     * @brief Post-decrement operator
     */
    SelfType operator--(int) const {
        SelfType clone = *this;
        ++mBase;
        return clone;
    }

    /**
     * @brief Increment operator
     *
     * @param n Distance to move
     */
    SelfType operator+(int n) const {
        SelfType clone = *this;
        clone.mBase -= n;
        return clone;
    }
    /**
     * @brief In-place increment operator
     *
     * @param n Distance to move
     */
    SelfType& operator+=(int n) {
        mBase -= n;
        return *this;
    }

    /**
     * @brief Decrement operator
     *
     * @param n Distance to move
     */
    SelfType operator-(int n) const {
        SelfType clone = *this;
        clone += n;
        return clone;
    }
    /**
     * @brief In-place decrement operator
     *
     * @param n Distance to move
     */
    SelfType& operator-=(int n) {
        mBase += n;
        return *this;
    }

    /**
     * @brief Accesses the value at the iterator's position (by reference)
     */
    ReferenceType operator*() const {
        BaseType it = mBase;
        return *--it;
    }
    /**
     * @brief Accesses the value at the iterator's position (by pointer)
     */
    PointerType operator->() const {
        BaseType it = mBase;
        return &*--it;
    }

private:
    //! Base/adapted iterator
    BaseType mBase;
};

/**
 * @brief Tests whether the left-hand-side iterator is positioned earlier than
 * the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator<(const ReverseIterator<T1>& rLhs,
                        const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() < rRhs.GetBase();
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned earlier than
 * or at the same position as the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator<=(const ReverseIterator<T1>& rLhs,
                         const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() <= rRhs.GetBase();
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned later than
 * the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator>(const ReverseIterator<T1>& rLhs,
                        const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() > rRhs.GetBase();
}

/**
 * @brief Tests whether the left-hand-side iterator is positioned later than or
 * at the same position as the right-hand-side iterator
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator>=(const ReverseIterator<T1>& rLhs,
                         const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() >= rRhs.GetBase();
}

/**
 * @brief Computes the distance between two iterators
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE int operator-(const ReverseIterator<T1>& rLhs,
                       const ReverseIterator<T2>& rRhs) {
    return rRhs.GetBase() - rLhs.GetBase();
}

/**
 * @brief Checks two iterators for equality
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator==(const ReverseIterator<T1>& rLhs,
                         const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() == rRhs.GetBase();
}
/**
 * @brief Checks two iterators for inequality
 *
 * @param rLhs Left-hand side iterator
 * @param rRhs Right-hand side iterator
 */
template <typename T1, typename T2>
K_INLINE bool operator!=(const ReverseIterator<T1>& rLhs,
                         const ReverseIterator<T2>& rRhs) {
    return rLhs.GetBase() != rRhs.GetBase();
}

/******************************************************************************
 *
 * Specialized iterator types
 *
 ******************************************************************************/

/**
 * @brief Random access iterator tag
 */
struct RandomAccessIteratorTag {};

/**
 * @brief Random access iterator implementation
 *
 * @details The derived class must implement the following functions:
 * - `void Next()` For incrementing the iterator once
 * - `void Prev()` For decrementing the iterator once
 * - `void Move(int n)` For advancing the iterator by a specified amount
 * - `int Dist(it) const` For computing distance between iterators
 * - `TValue& Get()` For accessing the iterator's value
 * - `bool Equals(it) const` For comparing for equality with another iterator
 *
 * @tparam TDerived Derived iterator class type
 * @tparam TValue Iterator value type
 * @tparam TPointer Value pointer type
 * @tparam TReference Value reference type
 */
template <typename TDerived, typename TValue, typename TPointer = TValue*,
          typename TReference = TValue&>
class RandomAccessIterator
    : public detail::Iterator<TDerived, TValue, TPointer, TReference,
                              RandomAccessIteratorTag> {
public:
    // For readability
    typedef detail::Iterator<TDerived, TValue, TPointer, TReference,
                             RandomAccessIteratorTag>
        BaseType;

    typedef TDerived DerivedType;
};

/**
 * @brief Bi-directional iterator tag
 */
struct BiDirectionalIteratorTag {};

/**
 * @brief Bi-directional iterator implementation
 *
 * @details The derived class must implement the following functions:
 * - `void Next()` For incrementing the iterator once
 * - `void Prev()` For decrementing the iterator once
 * - `TValue& Get()` For accessing the iterator's value
 *
 * @tparam TDerived Derived iterator class type
 * @tparam TValue Iterator value type
 * @tparam TPointer Value pointer type
 * @tparam TReference Value reference type
 */
template <typename TDerived, typename TValue, typename TPointer = TValue*,
          typename TReference = TValue&>
class BiDirectionalIterator
    : public detail::Iterator<TDerived, TValue, TPointer, TReference,
                              BiDirectionalIteratorTag> {
public:
    // For readability
    typedef detail::Iterator<TDerived, TValue, TPointer, TReference,
                             BiDirectionalIteratorTag>
        BaseType;

    typedef TDerived DerivedType;

private:
    void Move(int /* n */) {
        K_ASSERT_EX(false, "Not for bi-directional iterators");
    }

    int Dist(DerivedType /* other */) const {
        K_ASSERT_EX(false, "Not for bi-directional iterators");
        return 0;
    }
};

/**
 * @brief Forward iterator tag
 */
struct ForwardIteratorTag {};

/**
 * @brief Forward iterator implementation
 *
 * @details The derived class must implement the following functions:
 * - `void Next()` For incrementing the iterator once
 * - `TValue& Get()` For accessing the iterator's value
 *
 * @tparam TDerived Derived iterator class type
 * @tparam TValue Iterator value type
 * @tparam TPointer Value pointer type
 * @tparam TReference Value reference type
 */
template <typename TDerived, typename TValue, typename TPointer = TValue*,
          typename TReference = TValue&>
class ForwardIterator
    : public detail::Iterator<TDerived, TValue, TPointer, TReference,
                              ForwardIteratorTag> {
public:
    // For readability
    typedef detail::Iterator<TDerived, TValue, TPointer, TReference,
                             ForwardIteratorTag>
        BaseType;

    typedef TDerived DerivedType;

private:
    void Prev() {
        K_ASSERT_EX(false, "Not for forward iterators");
    }

    void Move(int /* n */) {
        K_ASSERT_EX(false, "Not for forward iterators");
    }

    int Dist(DerivedType /* other */) const {
        K_ASSERT_EX(false, "Not for forward iterators");
        return 0;
    }
};

/******************************************************************************
 *
 * Boilerplate macros
 *
 ******************************************************************************/

/**
 * @brief Generates iterator typedefs for shorthand
 *
 * @param T_ITERATOR Iterator class type
 * @param T_VALUE Iterator value type
 */
#define K_GEN_ITERATOR_TYPEDEFS(T_ITERATOR, T_VALUE)                           \
    typedef T_ITERATOR<T_VALUE> Iterator;                                      \
    typedef T_ITERATOR<const T_VALUE> ConstIterator;                           \
    typedef ReverseIterator<T_ITERATOR<T_VALUE> > RevIterator;                 \
    typedef ReverseIterator<T_ITERATOR<const T_VALUE> > ConstRevIterator;

/**
 * @brief Generates const/reverse iterator methods
 * @note Requires `Begin` and `End` to already be defined
 *
 * @param T Container class type
 */
#define K_GEN_ITERATOR_METHODS(T)                                              \
    ConstIterator Begin() const {                                              \
        return const_cast<T*>(this)->Begin();                                  \
    }                                                                          \
    ConstIterator End() const {                                                \
        return const_cast<T*>(this)->End();                                    \
    }                                                                          \
    ConstIterator CBegin() const {                                             \
        return Begin();                                                        \
    }                                                                          \
    ConstIterator CEnd() const {                                               \
        return End();                                                          \
    }                                                                          \
    RevIterator RBegin() {                                                     \
        return RevIterator(End());                                             \
    }                                                                          \
    RevIterator REnd() {                                                       \
        return RevIterator(Begin());                                           \
    }                                                                          \
    ConstRevIterator CRBegin() const {                                         \
        return ConstRevIterator(End());                                        \
    }                                                                          \
    ConstRevIterator CREnd() const {                                           \
        return ConstRevIterator(Begin());                                      \
    }

//! @}
} // namespace kiwi

#endif
