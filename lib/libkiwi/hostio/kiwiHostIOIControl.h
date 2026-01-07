#ifndef LIBKIWI_HOSTIO_HOST_IO_I_CONTROL_H
#define LIBKIWI_HOSTIO_HOST_IO_I_CONTROL_H
#include <libkiwi/hostio/kiwiHostIOContext.h>
#include <libkiwi/hostio/kiwiHostIOEvent.h>
#include <libkiwi/k_types.h>
#include <libkiwi/prim/kiwiString.h>

namespace kiwi {
//! @addtogroup libkiwi_hostio
//! @{
namespace hostio {
//! @addtogroup libkiwi_hostio
//! @{

/******************************************************************************
 *
 * IControl
 *
 ******************************************************************************/

/**
 * @brief UI control
 */
class IControl {
public:
    /**
     * @brief Control type
     */
    enum EType {
        EType_Label,       //!< Text label
        EType_Button,      //!< Clickable button
        EType_Value,       //!< Editable value
        EType_Slider,      //!< Value slider
        EType_CheckBox,    //!< Check box options
        EType_ComboBox,    //!< Combo box options
        EType_RadioButton, //!< Radio button options
        EType_SendFile,    //!< Send file to server
        EType_RecvFile,    //!< Receive file from server

        EType_Max
    };

public:
    /**
     * @brief Constructor
     *
     * @param type Control type
     * @param rName Name
     * @param id Unique ID
     */
    IControl(EType type, const String& rName, u32 id)
        : mType(type), mName(rName), mId(id) {}

    /**
     * @brief Destructor
     */
    virtual ~IControl() {}

    /**
     * @brief Generates object info for host client
     *
     * @param rContext Message context
     */
    void GenMessage(Context& rContext);

    /**
     * @brief Handles property event from host client
     *
     * @param rEvent Event structure from the host
     */
    virtual void ListenPropertyEvent(const PropertyEvent& rEvent) {}

    /**
     * @brief Accesses this control's type
     */
    EType GetType() const {
        return mType;
    }

    /**
     * @brief Accesses this control's name
     */
    const String& GetName() const {
        return mName;
    }

    /**
     * @brief Accesses this control's unique ID
     */
    u32 GetID() const {
        return mId;
    }

private:
    /**
     * @brief Generates object info for host client (derived implementation)
     *
     * @param rContext Message context
     */
    virtual void GenMessageImpl(Context& rContext) {}

private:
    //! Control type (for host client)
    EType mType;
    //! Control name (for host client)
    String mName;
    //! Unique ID
    u32 mId;
};

//! @}
} // namespace hostio
//! @}
} // namespace kiwi

#endif
