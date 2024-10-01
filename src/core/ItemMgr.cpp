#include <core/ItemMgr.h>
#include <libkiwi.h>

K_DYNAMIC_SINGLETON_IMPL(AP::ItemMgr);

namespace AP {

/**
 * @brief Constructor
 */
ItemMgr::ItemMgr()
    : mSwfVsBlockFlag(false),
      mSwfPrcPauseFlag(false),
      mSwfSglBlockFlag(false),
      mSwfSglHeartFlag(0) {}

/**
 * @brief Deserializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void ItemMgr::DeserializeImpl(const Header& rHeader) {
    ;
}

/**
 * @brief Serializes binary contents (internal implementation)
 *
 * @param rHeader Binary file header
 */
void ItemMgr::SerializeImpl(Header& rHeader) const {
    ;
}

} // namespace AP