#include <libkiwi.h>

namespace kiwi {
namespace HashMapTests {

/******************************************************************************
 *
 * THashMap
 *
 ******************************************************************************/

/**
 * @brief Tests that a hashmap after construction is empty (no elements and zero
 * size)
 */
KT_TEST(THashMap, Constructor) {
    THashMap<int, bool> map;

    KT_ASSERT(map.Empty());
    KT_ASSERT_EQ(map.Begin(), map.End());
}

/**
 * @brief Tests that the copy constructor correctly duplicates elements
 */
KT_TEST(THashMap, CopyConstructor) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }

    THashMap<int, bool> clone(map);
    KT_ASSERT_EQ(map.Size(), clone.Size());

    THashMap<int, bool>::ConstIterator mapIt = map.Begin();
    THashMap<int, bool>::ConstIterator cloneIt = clone.Begin();

    while (mapIt != map.End() && cloneIt != clone.End()) {
        KT_ASSERT_EQ(mapIt->key, cloneIt->key);
        KT_ASSERT_EQ(mapIt->value, cloneIt->value);

        // Make sure they don't point to the same memory
        KT_ASSERT_NE(&*mapIt, &*cloneIt);

        ++mapIt;
        ++cloneIt;
    }

    KT_ASSERT_EQ(mapIt, map.End());
    KT_ASSERT_EQ(cloneIt, clone.End());

    // One last duplication check by clearing the original
    map.Clear();
    KT_ASSERT_EQ(map.Size(), 0);
    KT_ASSERT_NE(clone.Size(), 0);
}

/**
 * @brief Tests that the Clear method results in an empty hashmap with no
 * elements and zero size
 */
KT_TEST(THashMap, Clear) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }
    map.Clear();

    KT_ASSERT(map.Empty());
    KT_ASSERT_EQ(map.Begin(), map.End());
}

/**
 * @brief Tests that the Size method accurately reports the number of elements
 */
KT_TEST(THashMap, Size) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }

    KT_ASSERT_EQ(map.Size(), 10);
}

/**
 * @brief Tests that the Capacity method accurately reports the maximum number
 * of elements
 */
KT_TEST(THashMap, Capacity) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }

    KT_ASSERT_GE(map.Capacity(), map.Size());
}

/**
 * @brief Tests that the Empty method accurately reports whether there are no
 * elements
 */
KT_TEST(THashMap, Empty) {
    THashMap<int, bool> map;

    KT_ASSERT(map.Empty());
    map.Insert(0, true);
    KT_ASSERT(!map.Empty());
}

/**
 * @brief Tests that the Insert method can create new elements
 */
KT_TEST(THashMap, InsertCreate) {
    THashMap<int, bool> map;

    KT_ASSERT(!map.Contains(0));

    map.Insert(0, true);
    KT_ASSERT(map.Contains(0));
    KT_ASSERT_EQ(map[0], true);
}

/**
 * @brief Tests that the Insert method can update existing elements
 */
KT_TEST(THashMap, InsertUpdate) {
    THashMap<int, bool> map;

    KT_ASSERT(!map.Contains(0));

    // Create new element
    map.Insert(0, true);
    KT_ASSERT(map.Contains(0));
    KT_ASSERT_EQ(map[0], true);

    map.Insert(0, false);
    KT_ASSERT_EQ(map[0], false);
}

/**
 * @brief Tests that the Remove method fails when the element does not exist
 */
KT_TEST(THashMap, RemoveFail) {
    THashMap<int, bool> map;

    u32 oldSize = map.Size();

    bool success = map.Remove(0);
    KT_ASSERT(!success);

    KT_ASSERT_EQ(map.Size(), oldSize);
}

/**
 * @brief Tests that the Remove method can remove existing elements
 */
KT_TEST(THashMap, RemoveSuccess) {
    THashMap<int, bool> map;

    map.Insert(0, true);
    KT_ASSERT(map.Contains(0));

    u32 oldSize = map.Size();

    bool oldValue = false;
    bool success = map.Remove(0, &oldValue);
    KT_ASSERT(success);
    KT_ASSERT_EQ(oldValue, true);

    KT_ASSERT(!map.Contains(0));

    KT_ASSERT_EQ(map.Size(), oldSize - 1);
}

namespace {

bool RemoveIfTrue(const THashItem<const int, bool>& rItem) {
    return rItem.value == true;
}

} // namespace

/**
 * @brief Tests that the RemoveIf method correctly removes selected elements
 */
KT_TEST(THashMap, RemoveIf) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }

    u32 oldSize = map.Size();

    u32 removeNum = map.RemoveIf(RemoveIfTrue);
    KT_ASSERT_EQ(removeNum, 10 / 2);

    K_FOREACH (it, map) {
        KT_ASSERT(it->value == false);
    }

    KT_ASSERT_EQ(map.Size(), oldSize - removeNum);
}

/**
 * @brief Tests that the Erase method erases the correct element
 */
KT_TEST(THashMap, Erase) {
    THashMap<int, bool> map;

    for (int i = 0; i < 10; i++) {
        map[i] = i % 2 == 0;
    }

    u32 oldSize = map.Size();

    THashMap<int, bool>::Iterator it = map.Begin();

    // Iterator that should follow the erased one
    THashMap<int, bool>::Iterator expected = it;
    ++expected;

    THashMap<int, bool>::Iterator got = map.Erase(it);
    KT_ASSERT_EQ(expected, got);

    KT_ASSERT_EQ(map.Size(), oldSize - 1);
}

/**
 * @brief Tests that the operator[] method can lookup existing elements
 */
KT_TEST(THashMap, OperatorGet) {
    THashMap<int, bool> map;

    map.Insert(0, true);
    KT_ASSERT_EQ(map[0], true);
}

/**
 * @brief Tests that the operator[] method can create new elements
 */
KT_TEST(THashMap, OperatorCreate) {
    THashMap<int, bool> map;

    map[0] = true;
    KT_ASSERT_EQ(map[0], true);
}

/**
 * @brief Tests that the operator[] method can update existing elements
 */
KT_TEST(THashMap, OperatorUpdate) {
    THashMap<int, bool> map;

    map.Insert(0, true);

    map[0] = false;
    KT_ASSERT_EQ(map[0], false);
}

/**
 * @brief Tests that the Find method returns NULL when no element is found
 */
KT_TEST(THashMap, FindFail) {
    THashMap<int, bool> map;

    bool* pElement = map.Find(0);
    KT_ASSERT_EQ(pElement, nullptr);
}

/**
 * @brief Tests that the Find method can find existing elements by key
 */
KT_TEST(THashMap, FindSuccess) {
    THashMap<int, bool> map;

    map[0] = true;

    bool* pElement = map.Find(0);
    KT_ASSERT_NE(pElement, nullptr);
    KT_ASSERT_EQ(*pElement, true);
}

/**
 * @brief Tests that the Get method returns the default value when no element is
 * found
 */
KT_TEST(THashMap, GetFail) {
    THashMap<int, bool> map;
    KT_ASSERT_EQ(map.Get(0, true), true);
}

/**
 * @brief Tests that the Get method can find existing elements by key
 */
KT_TEST(THashMap, GetSuccess) {
    THashMap<int, bool> map;

    map[0] = true;
    KT_ASSERT_EQ(map.Get(0, false), true);
}

/**
 * @brief Tests that the Contains method accurately reports whether an element
 * exists
 */
KT_TEST(THashMap, Contains) {
    THashMap<int, bool> map;

    KT_ASSERT_EQ(map.Contains(0), false);

    map[0] = true;
    KT_ASSERT_EQ(map.Contains(0), true);
}

/**
 * @brief Tests that the Keys method correctly includes all keys in the map
 */
KT_TEST(THashMap, Keys) {
    THashMap<int, bool> map;

    static const int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool found[LENGTHOF(expected)] = {};

    for (u32 i = 0; i < LENGTHOF(expected); i++) {
        map[expected[i]] = expected[i] % 2 == 0;
    }

    TVector<int> keys = map.Keys();

    // Track keys from the original array that were discovered
    K_FOREACH (it, keys) {
        found[*it] = true;
    }

    for (u32 i = 0; i < LENGTHOF(found); i++) {
        KT_ASSERT_EQ(found[i], true);
    }
}

/**
 * @brief Tests that the Values method correctly includes all values in the map
 */
KT_TEST(THashMap, Values) {
    THashMap<int, bool> map;

    static const int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int numTrue = 0;
    int numFalse = 0;

    for (u32 i = 0; i < LENGTHOF(expected); i++) {
        map[expected[i]] = expected[i] % 2 == 0;
    }

    TVector<bool> values = map.Values();

    // Track values from the original array that were discovered
    K_FOREACH (it, values) {
        if (*it) {
            numTrue++;
        } else {
            numFalse++;
        }
    }

    KT_ASSERT_EQ(numTrue, LENGTHOF(expected) / 2);
    KT_ASSERT_EQ(numFalse, LENGTHOF(expected) / 2);
}

/**
 * @brief Tests that iteration accesses all elements in the map
 */
KT_TEST(THashMap, Iterator) {
    THashMap<int, bool> map;

    static const int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bool found[LENGTHOF(expected)] = {};

    for (u32 i = 0; i < LENGTHOF(expected); i++) {
        map[expected[i]] = expected[i] % 2 == 0;
    }

    // Track keys from the original array that were discovered
    K_FOREACH (it, map) {
        found[it->key] = true;
        KT_ASSERT_EQ(it->value, it->key % 2 == 0);
    }

    for (u32 i = 0; i < LENGTHOF(found); i++) {
        KT_ASSERT_EQ(found[i], true);
    }
}

} // namespace HashMapTests
} // namespace kiwi