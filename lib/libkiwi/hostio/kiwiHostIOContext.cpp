#include <libkiwi.h>

namespace kiwi {
namespace hostio {

/**
 * @brief Constructor
 */
Context::Context() : mpMessageBuffer(nullptr) {
    mpMessageBuffer = new u8[MESSAGE_BUFFER_SIZE];
    K_ASSERT_PTR(mpMessageBuffer);

    mMessageStream.Open(mpMessageBuffer, MESSAGE_BUFFER_SIZE);
}

/**
 * @brief Destructor
 */
Context::~Context() {
    delete[] mpMessageBuffer;
    mpMessageBuffer = nullptr;
}

/**
 * @brief Resets the message context
 */
void Context::Reset() {
    mMessageStream.Seek(ESeekDir_Begin, 0);
}

/**
 * @brief Starts generation of a node message
 *
 * @param rNode Host I/O node
 */
void Context::StartGenNode(const Reflexible& rNode) {
    K_ASSERT_EX(!mMessageStream.IsEOF(), "GenMessage overflow");

    mMessageStream.Write_u8(ECommand_StartGenNode);
    mMessageStream.Write_string(rNode.GetName());
}

/**
 * @brief Ends generation of a node message
 *
 * @param rNode Host I/O node
 */
void Context::EndGenNode(const Reflexible& rNode) {
    K_ASSERT_EX(!mMessageStream.IsEOF(), "GenMessage overflow");

    mMessageStream.Write_u8(ECommand_EndGenNode);
}

/**
 * @brief Generates a control message
 *
 * @param rControl Host I/O control
 */
void Context::GenControl(IControl& rControl) {
    K_ASSERT_EX(!mMessageStream.IsEOF(), "GenMessage overflow");

    mMessageStream.Write_u8(rControl.GetType());
    mMessageStream.Write_string(rControl.GetName());
    mMessageStream.Write_u32(rControl.GetID());
    rControl.GenMessage(*this);
}

} // namespace hostio
} // namespace kiwi