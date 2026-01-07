#include <libkiwi.h>

namespace kiwi {
namespace ListTests {

/**
 * @brief Tests that a list after construction is empty (no elements and zero
 * size)
 */
KT_TEST(TList, Constructor) {
    TList<int> list;

    KT_ASSERT(list.Empty());
    KT_ASSERT_EQ(list.Begin(), list.End());
}

/**
 * @brief Tests that the copy constructor correctly duplicates elements
 */
KT_TEST(TList, CopyConstructor) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    TList<int> clone(list);
    KT_ASSERT_EQ(list.Size(), clone.Size());

    TList<int>::ConstIterator listIt = list.Begin();
    TList<int>::ConstIterator cloneIt = clone.Begin();

    while (listIt != list.End() && cloneIt != clone.End()) {
        KT_ASSERT_EQ(*listIt, *cloneIt);

        // Make sure they don't point to the same memory
        KT_ASSERT_NE(&*listIt, &*cloneIt);

        ++listIt;
        ++cloneIt;
    }

    KT_ASSERT_EQ(listIt, list.End());
    KT_ASSERT_EQ(cloneIt, clone.End());

    // One last duplication check by clearing the original
    list.Clear();
    KT_ASSERT_EQ(list.Size(), 0);
    KT_ASSERT_NE(clone.Size(), 0);
}

/**
 * @brief Tests that the Clear method results in an empty list with no elements
 * and zero size
 */
KT_TEST(TList, Clear) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }
    list.Clear();

    KT_ASSERT(list.Empty());
    KT_ASSERT_EQ(list.Begin(), list.End());
}

/**
 * @brief Tests that Begin provides an iterator to the first element
 */
KT_TEST(TList, Begin) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    KT_ASSERT_NE(list.Begin(), list.End());
    KT_ASSERT_EQ(*list.Begin(), 0);
}

/**
 * @brief Tests that End provides an iterator past the last element
 */
KT_TEST(TList, End) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    KT_ASSERT_NE(list.End(), list.Begin());
    KT_ASSERT_EQ(*--list.End(), 9);
}

/**
 * @brief Tests that the Size method accurately reports the number of elements
 */
KT_TEST(TList, Size) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    KT_ASSERT_EQ(list.Size(), 10);
}

/**
 * @brief Tests that the Empty method accurately reports whether there are no
 * elements
 */
KT_TEST(TList, Empty) {
    TList<int> list;

    KT_ASSERT(list.Empty());
    list.PushBack(1);
    KT_ASSERT(!list.Empty());
}

/**
 * @brief Tests that the PopFront method erases and returns the first element
 */
KT_TEST(TList, PopFront) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    int front = list.PopFront();
    KT_ASSERT_EQ(front, 1);
    KT_ASSERT_EQ(list.Front(), 2);
}

/**
 * @brief Tests that the PopBack method erases and returns the last element
 */
KT_TEST(TList, PopBack) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    int front = list.PopBack();
    KT_ASSERT_EQ(front, 3);
    KT_ASSERT_EQ(list.Back(), 2);
}

/**
 * @brief Tests that the PushFront method prepends to the list
 */
KT_TEST(TList, PushFront) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.PushFront(0);
    KT_ASSERT_EQ(list.Front(), 0);
}

/**
 * @brief Tests that the PushBack method appends to the list
 */
KT_TEST(TList, PushBack) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.PushBack(4);
    KT_ASSERT_EQ(list.Back(), 4);
}

/**
 * @brief Tests that the Front method accesses the first element
 */
KT_TEST(TList, Front) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    KT_ASSERT_EQ(list.Front(), 1);
}

/**
 * @brief Tests that the Back method accesses the last element
 */
KT_TEST(TList, Back) {
    TList<int> list;

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    KT_ASSERT_EQ(list.Back(), 3);
}

/**
 * @brief Tests that the Remove method correctly removes the first occurrence
 */
KT_TEST(TList, Remove) {
    TList<int> list;

    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(2);

    KT_ASSERT(list.Remove(2));
    KT_ASSERT_EQ(list.Front(), 3)
    KT_ASSERT_EQ(list.Back(), 2)

    KT_ASSERT(list.Remove(2));
    KT_ASSERT_EQ(list.Front(), 3)
    KT_ASSERT_EQ(list.Back(), 3)
}

namespace {

bool RemoveIfOdd(const int& x) {
    return x % 2 != 0;
}

} // namespace

/**
 * @brief Tests that the RemoveIf method correctly removes selected elements
 */
KT_TEST(TList, RemoveIf) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    u32 removeNum = list.RemoveIf(RemoveIfOdd);
    KT_ASSERT_EQ(removeNum, 10 / 2);

    K_FOREACH (it, list) {
        KT_ASSERT(*it % 2 == 0);
    }
}

/**
 * @brief Tests that the Insert method correctly positions the new element
 */
KT_TEST(TList, Insert) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    K_FOREACH (it, list) {
        // Insert another 4 before the 5
        if (*it == 5) {
            TList<int>::Iterator result = list.Insert(it, 4);
            KT_ASSERT_EQ(*result, 4);

            // Ensure they are sequential
            KT_ASSERT_EQ(++result, it);
            break;
        }
    }
}

/**
 * @brief Tests that the Erase method erases the correct element
 */
KT_TEST(TList, Erase) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    K_FOREACH (it, list) {
        if (*it == 5) {
            TList<int>::Iterator next = it;
            ++next;

            TList<int>::Iterator result = list.Erase(it);
            KT_ASSERT_EQ(result, next);
            break;
        }
    }
}

/**
 * @brief Tests that the Erase method erases the correct range of elements
 */
KT_TEST(TList, EraseRange) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    K_FOREACH (it, list) {
        // Erase elements from 5 onwards
        if (*it >= 5) {
            list.Erase(it, list.End());
            break;
        }
    }

    K_FOREACH (it, list) {
        KT_ASSERT_LT(*it, 5);
    }
}

/**
 * @brief Tests that forward iteration produces the expected results
 */
KT_TEST(TList, ForwardIterator) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    TList<int>::Iterator it = list.Begin();
    int i = 0;

    while (i < 10) {
        KT_ASSERT_NE(it, list.End());
        KT_ASSERT_EQ(*it, i);

        i++;
        ++it;
    }
}

/**
 * @brief Tests that reverse iteration produces the expected results
 */
KT_TEST(TList, ReverseIterator) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
    }

    TList<int>::RevIterator it = list.RBegin();
    int i = 0;

    while (i < 10) {
        KT_ASSERT_NE(it, list.REnd());
        KT_ASSERT_EQ(*it, (10 - 1 - i));

        i++;
        ++it;
    }
}

/**
 * @brief Tests that the Sort method correctly sorts all elements
 */
KT_TEST(TList, Sort) {
    TList<int> list;

    for (int i = 0; i < 10; i++) {
        list.PushBack(i);
        list.PushBack(i - 1);
    }

    list.Sort();

    int prev = -999;

    K_FOREACH (it, list) {
        KT_ASSERT_LE(prev, *it);
        prev = *it;
    }
}

} // namespace ListTests
} // namespace kiwi