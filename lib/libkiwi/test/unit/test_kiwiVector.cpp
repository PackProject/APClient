#include <libkiwi.h>

namespace kiwi {
namespace VectorTests {

/**
 * @brief Tests that a vector after construction is empty (no elements and zero
 * size)
 */
KT_TEST(TVector, Constructor) {
    TVector<int> vector;

    KT_ASSERT(vector.Empty());
    KT_ASSERT_EQ(vector.Begin(), vector.End());
}

/**
 * @brief Tests that the copy constructor correctly duplicates elements
 */
KT_TEST(TVector, CopyConstructor) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    TVector<int> clone(vector);
    KT_ASSERT_EQ(vector.Size(), clone.Size());

    TVector<int>::ConstIterator vectorIt = vector.Begin();
    TVector<int>::ConstIterator cloneIt = clone.Begin();

    while (vectorIt != vector.End() && cloneIt != clone.End()) {
        KT_ASSERT_EQ(*vectorIt, *cloneIt);

        // Make sure they don't point to the same memory
        KT_ASSERT_NE(&*vectorIt, &*cloneIt);

        ++vectorIt;
        ++cloneIt;
    }

    KT_ASSERT_EQ(vectorIt, vector.End());
    KT_ASSERT_EQ(cloneIt, clone.End());

    // One last duplication check by clearing the original
    vector.Clear();
    KT_ASSERT_EQ(vector.Size(), 0);
    KT_ASSERT_NE(clone.Size(), 0);
}

/**
 * @brief Tests that the Clear method results in an empty vector with no
 * elements and zero size
 */
KT_TEST(TVector, Clear) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }
    vector.Clear();

    KT_ASSERT(vector.Empty());
    KT_ASSERT_EQ(vector.Begin(), vector.End());
}

/**
 * @brief Tests that Begin provides an iterator to the first element
 */
KT_TEST(TVector, Begin) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    KT_ASSERT_NE(vector.Begin(), vector.End());
    KT_ASSERT_EQ(*vector.Begin(), 0);
}

/**
 * @brief Tests that End provides an iterator past the last element
 */
KT_TEST(TVector, End) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    KT_ASSERT_NE(vector.End(), vector.Begin());
    KT_ASSERT_EQ(*--vector.End(), vector.Size() - 1);
}

/**
 * @brief Tests that the Size method accurately reports the number of elements
 */
KT_TEST(TVector, Size) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    KT_ASSERT_EQ(vector.Size(), 10);
}

/**
 * @brief Tests that the Empty method accurately reports whether there are no
 * elements
 */
KT_TEST(TVector, Empty) {
    TVector<int> vector;

    KT_ASSERT(vector.Empty());
    vector.PushBack(1);
    KT_ASSERT(!vector.Empty());
}

/**
 * @brief Tests that the PopBack method erases and returns the last element
 */
KT_TEST(TVector, PopBack) {
    TVector<int> vector;

    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);

    int front = vector.PopBack();
    KT_ASSERT_EQ(front, 3);
    KT_ASSERT_EQ(vector.Back(), 2);
}

/**
 * @brief Tests that the PushBack method appends to the vector
 */
KT_TEST(TVector, PushBack) {
    TVector<int> vector;

    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);

    vector.PushBack(4);
    KT_ASSERT_EQ(vector.Back(), 4);
}

/**
 * @brief Tests that the Front method accesses the first element
 */
KT_TEST(TVector, Front) {
    TVector<int> vector;

    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);

    KT_ASSERT_EQ(vector.Front(), 1);
}

/**
 * @brief Tests that the Back method accesses the last element
 */
KT_TEST(TVector, Back) {
    TVector<int> vector;

    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);

    KT_ASSERT_EQ(vector.Back(), 3);
}

/**
 * @brief Tests that the Remove method correctly removes the first occurrence
 */
KT_TEST(TVector, Remove) {
    TVector<int> vector;

    vector.PushBack(2);
    vector.PushBack(3);
    vector.PushBack(2);

    KT_ASSERT(vector.Remove(2));
    KT_ASSERT_EQ(vector.Front(), 3)
    KT_ASSERT_EQ(vector.Back(), 2)

    KT_ASSERT(vector.Remove(2));
    KT_ASSERT_EQ(vector.Front(), 3)
    KT_ASSERT_EQ(vector.Back(), 3)
}

namespace {

bool RemoveIfOdd(const int& x) {
    return x % 2 != 0;
}

} // namespace

/**
 * @brief Tests that the RemoveIf method correctly removes selected elements
 */
KT_TEST(TVector, RemoveIf) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    u32 removeNum = vector.RemoveIf(RemoveIfOdd);
    KT_ASSERT_EQ(removeNum, 10 / 2);

    K_FOREACH (it, vector) {
        KT_ASSERT(*it % 2 == 0);
    }
}

/**
 * @brief Tests that the Insert method correctly positions the new element
 */
KT_TEST(TVector, Insert) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    K_FOREACH (it, vector) {
        // Insert another 4 before the 5
        if (*it == 5) {
            TVector<int>::Iterator result = vector.Insert(it, 4);
            KT_ASSERT_EQ(*result, 4);

            // Ensure they are sequential
            KT_ASSERT_EQ(*++result, 5);
            break;
        }
    }
}

/**
 * @brief Tests that the Erase method erases the correct element
 */
KT_TEST(TVector, Erase) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    K_FOREACH (it, vector) {
        if (*it == 5) {
            TVector<int>::Iterator result = vector.Erase(it);
            KT_ASSERT_EQ(*result, 6);
            break;
        }
    }
}

/**
 * @brief Tests that the Erase method erases the correct range of elements
 */
KT_TEST(TVector, EraseRange) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    K_FOREACH (it, vector) {
        // Erase elements from 5 onwards
        if (*it >= 5) {
            vector.Erase(it, vector.End());
            break;
        }
    }

    K_FOREACH (it, vector) {
        KT_ASSERT_LT(*it, 5);
    }
}

/**
 * @brief Tests that forward iteration produces the expected results
 */
KT_TEST(TVector, ForwardIterator) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    TVector<int>::Iterator it = vector.Begin();
    int i = 0;

    while (i < 10) {
        KT_ASSERT_NE(it, vector.End());
        KT_ASSERT_EQ(*it, i);

        i++;
        ++it;
    }
}

/**
 * @brief Tests that reverse iteration produces the expected results
 */
KT_TEST(TVector, ReverseIterator) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
    }

    TVector<int>::RevIterator it = vector.RBegin();
    int i = 0;

    while (i < 10) {
        KT_ASSERT_NE(it, vector.REnd());
        KT_ASSERT_EQ(*it, (10 - 1 - i));

        i++;
        ++it;
    }
}

/**
 * @brief Tests that the Sort method correctly sorts all elements
 */
KT_TEST(TVector, Sort) {
    TVector<int> vector;

    for (int i = 0; i < 10; i++) {
        vector.PushBack(i);
        vector.PushBack(i - 1);
    }

    vector.Sort();

    int prev = -999;

    K_FOREACH (it, vector) {
        KT_ASSERT_LE(prev, *it);
        prev = *it;
    }
}

} // namespace VectorTests
} // namespace kiwi