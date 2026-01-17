#include <libkiwi.h>

#include <egg/core.h>

#include <revolution/MEM.h>

namespace kiwi {
namespace {

/**
 * @brief Prints heap information
 *
 * @param pName Heap name
 * @param pHeap Heap object
 */
void LogHeap(const char* pName, EGG::Heap* pHeap) {
    if (!PtrUtil::IsPointer(pHeap)) {
        K_LOG_EX("[%s] nullptr ->\n", pName);
        return;
    }

    K_LOG_EX("[%s] %p-> %.2fKB free\n", pName, pHeap,
             OS_MEM_B_TO_KB(static_cast<f32>(pHeap->getAllocatableSize())));
}

/**
 * @brief Catches erroneous double-frees
 *
 * @param pBlock Target of delete operation
 */
void CheckDoubleFree(const void* pBlock) {
#if !defined(NDEBUG)
    // nullptr delete is OK
    if (pBlock == nullptr) {
        return;
    }

    K_ASSERT_PTR(pBlock);

    MEMiHeapHead* pHandle = MEMFindContainHeap(pBlock);
    K_ASSERT_PTR(pHandle);
    K_ASSERT(pHandle->magic == 'EXPH' || pHandle->magic == 'FRMH');

    // Only expanded heaps have memory blocks we can check
    if (pHandle->magic != 'EXPH') {
        return;
    }

    // Heap block lives before the allocated memory
    const MEMiExpHeapMBlock* pMBlock =
        AddToPtr<MEMiExpHeapMBlock>(pBlock, -sizeof(MEMiExpHeapMBlock));

    K_ASSERT_EX(pMBlock->state == 'UD' || pMBlock->state == 'FR',
                "Heap block is corrupted");

    K_ASSERT_EX(pMBlock->state == 'UD', "Double free!");
#endif
}

} // namespace

/**
 * @brief Constructor
 */
MemoryMgr::MemoryMgr() {
    EGG::Heap* pRootHeapMEM1 = RPSysSystem::getRootHeapMem1();
    K_ASSERT_PTR(pRootHeapMEM1);

    EGG::Heap* pRootHeapMEM2 = RPSysSystem::getRootHeapMem2();
    K_ASSERT_PTR(pRootHeapMEM2);

    mpHeapMEM1 = EGG::ExpHeap::create(HEAP_SIZE, pRootHeapMEM1);
    K_ASSERT_PTR(mpHeapMEM1);
    K_ASSERT(OSIsMEM1Region(mpHeapMEM1));

    mpHeapMEM2 = EGG::ExpHeap::create(HEAP_SIZE, pRootHeapMEM2);
    K_ASSERT_PTR(mpHeapMEM2);
    K_ASSERT(OSIsMEM2Region(mpHeapMEM2));

    Dump();
}

/**
 * @brief Destructor
 */
MemoryMgr::~MemoryMgr() {
    delete mpHeapMEM1;
    mpHeapMEM1 = nullptr;

    delete mpHeapMEM2;
    mpHeapMEM2 = nullptr;
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param align Block alignment
 * @param memory Target memory region
 * @return Pointer to allocated block
 */
void* MemoryMgr::Alloc(u32 size, s32 align, EMemory memory) const {
    void* pBlock = GetHeap(memory)->alloc(size, align);
    K_ASSERT_PTR_EX(pBlock, "Out of memory (alloc %d)", size);

    K_ASSERT(memory == EMemory_MEM1 ? OSIsMEM1Region(pBlock)
                                    : OSIsMEM2Region(pBlock));

    return pBlock;
}

/**
 * @brief Frees a block of memory
 *
 * @param pBlock Block
 */
void MemoryMgr::Free(void* pBlock) const {
    CheckDoubleFree(pBlock);
    EGG::Heap::free(pBlock, nullptr);
}

/**
 * @brief Gets the heap corresponding to the specified memory region
 *
 * @param memory Target memory region
 */
EGG::Heap* MemoryMgr::GetHeap(EMemory memory) const {
    switch (memory) {
    case EMemory_MEM1: {
        K_ASSERT_PTR(mpHeapMEM1);
        return mpHeapMEM1;
    }

    case EMemory_MEM2: {
        K_ASSERT_PTR(mpHeapMEM2);
        return mpHeapMEM2;
    }

    default: {
        K_UNREACHABLE();
        return nullptr;
    }
    }
}

/**
 * @brief Gets size of available heap memory
 *
 * @param memory Target memory region
 */
u32 MemoryMgr::GetFreeSize(EMemory memory) const {
    return GetHeap(memory)->getAllocatableSize();
}

/**
 * @brief Gets size of total heap memory
 *
 * @param memory Target memory region
 */
u32 MemoryMgr::GetTotalSize(EMemory memory) const {
    return static_cast<u32>(GetHeap(memory)->getTotalSize());
}

/**
 * @brief Tests whether an address points to an allocation from this manager
 *
 * @param pAddr Memory address
 */
bool MemoryMgr::IsHeapMemory(const void* pAddr) const {
    K_ASSERT_PTR(mpHeapMEM1);
    K_ASSERT_PTR(mpHeapMEM2);

    // Check MEM1 heap
    if (pAddr >= mpHeapMEM1->getStartAddress() &&
        pAddr < mpHeapMEM1->getEndAddress()) {
        return true;
    }

    // Check MEM2 heap
    if (pAddr >= mpHeapMEM2->getStartAddress() &&
        pAddr < mpHeapMEM2->getEndAddress()) {
        return true;
    }

    return false;
}

/**
 * @brief Dumps heap information for debugging purposes
 */
void MemoryMgr::Dump() {
    LogHeap("libkiwi (MEM1)", mpHeapMEM1);
    LogHeap("libkiwi (MEM2)", mpHeapMEM2);

    LogHeap("RootMem1", RPSysSystem::getRootHeapMem1());
    LogHeap("RootMem2", RPSysSystem::getRootHeapMem2());

    LogHeap("SysMem1", RPSysSystem::getSystemHeap());
    LogHeap("SysMem2", RP_GET_INSTANCE(RPSysSystem)->getSystemHeapRP());

    LogHeap("Res", RP_GET_INSTANCE(RPSysSystem)->getResourceHeap());
}

} // namespace kiwi

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @return Pointer to allocated block
 */
void* operator new(size_t size) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, 4, kiwi::EMemory_MEM1);
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @return Pointer to allocated block
 */
void* operator new[](size_t size) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, 4, kiwi::EMemory_MEM1);
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param align Block address alignment
 * @return Pointer to allocated block
 */
void* operator new(size_t size, s32 align) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, align,
                                                kiwi::EMemory_MEM1);
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @param align Block address alignment
 * @return Pointer to allocated block
 */
void* operator new[](size_t size, s32 align) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, align,
                                                kiwi::EMemory_MEM1);
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param memory Target memory region
 * @return Pointer to allocated block
 */
void* operator new(size_t size, kiwi::EMemory memory) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, 4, memory);
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @param memory Target memory region
 * @return Pointer to allocated block
 */
void* operator new[](size_t size, kiwi::EMemory memory) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, 4, memory);
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param pHeap Target heap
 * @return Pointer to allocated block
 */
void* operator new(size_t size, EGG::Heap* pHeap) {
    K_ASSERT_PTR(pHeap);

    void* pBlock = pHeap->alloc(size);
    K_ASSERT_PTR_EX(pBlock, "Out of memory (alloc %d)", size);

    return pBlock;
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @param pHeap Target heap
 * @return Pointer to allocated block
 */
void* operator new[](size_t size, EGG::Heap* pHeap) {
    K_ASSERT_PTR(pHeap);

    void* pBlock = pHeap->alloc(size);
    K_ASSERT_PTR_EX(pBlock, "Out of memory (alloc %d)", size);

    return pBlock;
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param align Block address alignment
 * @param memory Target memory region
 * @return Pointer to allocated block
 */
void* operator new(size_t size, s32 align, kiwi::EMemory memory) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, align, memory);
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @param align Block address alignment
 * @param memory Target memory region
 * @return Pointer to allocated block
 */
void* operator new[](size_t size, s32 align, kiwi::EMemory memory) {
    return kiwi::MemoryMgr::GetInstance().Alloc(size, align, memory);
}

/**
 * @brief Allocates a block of memory
 *
 * @param size Block size
 * @param align Block address alignment
 * @param pHeap Target heap
 * @return Pointer to allocated block
 */
void* operator new(size_t size, s32 align, EGG::Heap* pHeap) {
    K_ASSERT_PTR(pHeap);

    void* pBlock = pHeap->alloc(size, align);
    K_ASSERT_PTR_EX(pBlock, "Out of memory (alloc %d)", size);

    return pBlock;
}
/**
 * @brief Allocates a block of memory for an array
 *
 * @param size Block size
 * @param align Block address alignment
 * @param pHeap Target heap
 * @return Pointer to allocated block
 */
void* operator new[](size_t size, s32 align, EGG::Heap* pHeap) {
    K_ASSERT_PTR(pHeap);

    void* pBlock = pHeap->alloc(size, align);
    K_ASSERT_PTR_EX(pBlock, "Out of memory (alloc %d)", size);

    return pBlock;
}

/**
 * @brief Frees a block of memory
 *
 * @param pBlock Block
 */
void operator delete(void* pBlock) {
    kiwi::MemoryMgr::GetInstance().Free(pBlock);
}
/**
 * @brief Frees a block of memory used by an array
 *
 * @param pBlock Block
 */
void operator delete[](void* pBlock) {
    kiwi::MemoryMgr::GetInstance().Free(pBlock);
}
