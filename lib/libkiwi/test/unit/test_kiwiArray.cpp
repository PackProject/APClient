#include <libkiwi.h>

namespace kiwi {
namespace ArrayTests {

/******************************************************************************
 *
 * TArrayImpl
 *
 ******************************************************************************/

/**
 * @brief Tests that Begin provides an iterator to the first element
 */
KT_TEST(TArrayImpl, Begin) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    KT_ASSERT_NE(array.Begin(), array.End());
    KT_ASSERT_EQ(*array.Begin(), 0);
}

/**
 * @brief Tests that End provides an iterator past the last element
 */
KT_TEST(TArrayImpl, End) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    KT_ASSERT_NE(array.End(), array.Begin());
    KT_ASSERT_EQ(*--array.End(), array.Size() - 1);
}

/**
 * @brief Tests that the Size method accurately reports the number of elements
 */
KT_TEST(TArrayImpl, Size) {
    TArray<int, 10> array;
    KT_ASSERT_EQ(array.Size(), 10);
}

/**
 * @brief Tests that the Front method accesses the first element in the array
 */
KT_TEST(TArrayImpl, Front) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    KT_ASSERT_EQ(array.Front(), 0);
}

/**
 * @brief Tests that the Back method accesses the last element in the array
 */
KT_TEST(TArrayImpl, Back) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    KT_ASSERT_EQ(array.Back(), array.Size() - 1);
}

/**
 * @brief Tests that the At method accurately reports the specified element
 */
KT_TEST(TArrayImpl, At) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        // Don't use At to set the values
        array.Data()[i] = i;
    }

    for (int i = 0; i < array.Size(); i++) {
        KT_ASSERT_EQ(array.At(i), i);
    }
}

/**
 * @brief Tests that the operator[]/operator() methods accurately report the
 * specified element
 */
KT_TEST(TArrayImpl, OperatorAt) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        // Don't use At to set the values
        array.Data()[i] = i;
    }

    for (int i = 0; i < array.Size(); i++) {
        KT_ASSERT_EQ(array[i], i);
        KT_ASSERT_EQ(array(i), i);
    }
}

/**
 * @brief Tests that forward iteration produces the expected results
 */
KT_TEST(TArrayImpl, ForwardIterator) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    TArray<int, 10>::Iterator it = array.Begin();
    int i = 0;

    while (i < array.Size()) {
        KT_ASSERT_NE(it, array.End());
        KT_ASSERT_EQ(*it, i);

        i++;
        ++it;
    }
}

/**
 * @brief Tests that reverse iteration produces the expected results
 */
KT_TEST(TArrayImpl, ReverseIterator) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        array[i] = i;
    }

    TArray<int, 10>::RevIterator it = array.RBegin();
    int i = 0;

    while (i < array.Size()) {
        KT_ASSERT_NE(it, array.REnd());
        KT_ASSERT_EQ(*it, (array.Size() - 1 - i));

        i++;
        ++it;
    }
}

/******************************************************************************
 *
 * TArray1D
 *
 ******************************************************************************/

/**
 * @brief Tests that the Sort method correctly sorts all elements
 */
KT_TEST(TArray1D, Sort) {
    TArray<int, 10> array;

    for (int i = 0; i < array.Size(); i++) {
        // 0, -1, 2, 1, 4, 3, . . .
        array[i] = i % 2 == 0 ? i : i - 2;
    }

    array.Sort();

    int prev = -999;

    K_FOREACH (it, array) {
        KT_ASSERT_LE(prev, *it);
        prev = *it;
    }
}

/******************************************************************************
 *
 * TArray2D
 *
 ******************************************************************************/

/**
 * @brief Tests that the InnerSize method accurately reports the number of
 * columns
 */
KT_TEST(TArray2D, InnerSize) {
    TArray2D<int, 3, 4> array;
    KT_ASSERT_EQ(array.InnerSize(), 4);
}

/**
 * @brief Tests that the At (element) method accurately reports the specified
 * element
 */
KT_TEST(TArray2D, At) {
    TArray2D<int, 3, 4> array;

    for (int i = 0; i < array.Size(); i++) {
        for (int j = 0; j < array.InnerSize(); j++) {
            array[i][j] = array.InnerSize() * i + j;
        }
    }

    KT_ASSERT_EQ(array.At(1, 0), 4);
}

/**
 * @brief Tests that the operator[]/operator() (element) methods accurately
 * report the specified element
 */
KT_TEST(TArray2D, OperatorAt) {
    TArray2D<int, 3, 4> array;

    for (int i = 0; i < array.Size(); i++) {
        for (int j = 0; j < array.InnerSize(); j++) {
            array[i][j] = array.InnerSize() * i + j;
        }
    }

    KT_ASSERT_EQ(array(1, 0), 4);
}

} // namespace ArrayTests
} // namespace kiwi