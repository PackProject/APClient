#include <libkiwi.h>

#include <cstdlib>

namespace kiwi {

/**
 * @brief HTTP request method names
 */
const char* HttpRequest::METHOD_NAMES[EMethod_Max] = {"GET", "POST"};

/**
 * @brief HTTP protocol version
 */
const char* HttpRequest::PROTOCOL_VERSION = "HTTP/1.1";

/**
 * @brief Constructor
 * @details If not specified, the port is determined by the protocol.
 *
 * @param rHost Server hostname
 * @param port Connection port
 */
HttpRequest::HttpRequest(const String& rHost, u16 port)
    : mHost(rHost), mPort(port), mSocket(SO_PF_INET, SO_SOCK_STREAM) {

    K_ASSERT_EX(!rHost.StartsWith("https://"),
                "Secure HTTP is not yet supported.");

    K_ASSERT(mSocket.IsOpen());

    // Auto-detect port from the connection protocol
    if (mPort == 0) {
        mPort = rHost.StartsWith("https://") ? DEFAULT_PORT_HTTPS
                                             : DEFAULT_PORT_HTTP;
    }

    bool success = mSocket.Bind();
    K_ASSERT(success);

    Init();
}

/**
 * @brief Destructor
 */
HttpRequest::~HttpRequest() {
    K_ASSERT_EX(mpCallback == nullptr,
                "Don't destroy this object while async request is pending.");
}

/**
 * @brief Performs common initialization
 */
void HttpRequest::Init() {
    mMethod = EMethod_Max;
    mResource = "/";
    mTimeOut = OS_MSEC_TO_TICKS(DEFAULT_TIMEOUT);

    mpCallback = nullptr;
    mpCallbackArg = nullptr;

    mHeader["Host"] = mHost;
    mHeader["User-Agent"] = "libkiwi";
    mHeader["Connection"] = "close";
}

/**
 * @brief Sends request synchronously
 *
 * @param method Request method
 * @return Server response
 */
const HttpResponse& HttpRequest::Send(EMethod method) {
    K_ASSERT(method < EMethod_Max);
    K_ASSERT(mSocket.IsOpen());

    mMethod = method;
    mpCallback = nullptr;
    mpCallbackArg = nullptr;

    SendImpl();
    return mResponse;
}

/**
 * @brief Sends request asynchronously
 *
 * @param pCallback Response callback
 * @param pArg Callback user argument
 * @param method Request method
 */
void HttpRequest::SendAsync(Callback pCallback, void* pArg, EMethod method) {
    K_ASSERT_PTR(pCallback);
    K_ASSERT(method < EMethod_Max);
    K_ASSERT(mSocket.IsOpen());

    mMethod = method;
    mpCallback = pCallback;
    mpCallbackArg = pArg;

    // TODO(kiwi) Need state machine for request/receive
    K_NOT_IMPLEMENTED();
    // Thread t(SendImpl, *this);
}

/**
 * @brief Sends request (internal implementation)
 */
void HttpRequest::SendImpl() {
    K_ASSERT(mMethod < EMethod_Max);
    K_ASSERT(mSocket.IsOpen());

    // Beginning timestamp
    Watch w;
    w.Start();

    // Establish connection with server
    while (true) {
        // Try to resolve the hostname
        SockAddr4 addr(mHost, mPort);
        if (!addr.IsValid()) {
            mResponse.error = EHttpErr_CantConnect;
            mResponse.exError = LibSO::GetLastError();
            break;
        }

        // After connection we can perform the request
        if (mSocket.Connect(addr)) {
            (void)Request();
            (void)Receive();
            break;
        }

        // Connection failure
        if (LibSO::GetLastError() != SO_EWOULDBLOCK) {
            mResponse.error = EHttpErr_CantConnect;
            mResponse.exError = LibSO::GetLastError();
        }

        // Connection timeout
        if (w.Elapsed() >= mTimeOut) {
            mResponse.error = EHttpErr_TimedOut;
            mResponse.exError = LibSO::GetLastError();
            break;
        }
    }

    // Dispatch user callback
    if (mpCallback != nullptr) {
        mpCallback(mResponse, mpCallbackArg);
    }

    // Signal to destructor
#ifndef NDEBUG
    mpCallback = nullptr;
#endif
}

/**
 * @brief Sends request data
 *
 * @return Success
 */
bool HttpRequest::Request() {
    K_ASSERT(mMethod < EMethod_Max);
    K_ASSERT(mSocket.IsOpen());

    // Request line begins with the resource
    String request = mResource;

    // URL parameter string
    K_FOREACH (it, mParams) {
        // Parameters delimited by ampersand
        String fmt = it == mParams.Begin() ? "?%s=%s" : "&%s=%s";
        request += Format(fmt, it->key.CStr(), it->value.CStr());
    }

    // Finish request line
    request = Format("%s %s %s\n", METHOD_NAMES[mMethod], request.CStr(),
                     PROTOCOL_VERSION);

    // Build header fields
    K_FOREACH (it, mHeader) {
        request += Format("%s: %s\n", it->key.CStr(), it->value.CStr());
    }

    // Request ends with extra newline
    request += "\n";

    // Socket needs memory allocated in MEM2
    WorkBufferArg arg;
    arg.region = EMemory_MEM2;
    arg.size = request.Length();

    WorkBuffer buffer(arg);
    std::memcpy(buffer.Contents(), request.CStr(), request.Length());

    // Send request data
    Optional<u32> sent = mSocket.SendBytes(buffer.Contents(), buffer.Size());
    bool success = sent && *sent == buffer.Size();

    // Record socket library error if it failed
    if (!success) {
        mResponse.error = EHttpErr_Socket;
        mResponse.exError = LibSO::GetLastError();
    }

    return success;
}

/**
 * @brief Receives response data
 *
 * @return Successs
 */
bool HttpRequest::Receive() {
    K_ASSERT(mMethod < EMethod_Max);
    K_ASSERT(mSocket.IsOpen());

    // Beginning timestamp
    Watch w;
    w.Start();

    /******************************************************************************
     * Receive response headers
     ******************************************************************************/
    // Buffer for headers
    String work;
    // Try to avoid reallocation
    work.Reserve(TEMP_BUFFER_SIZE * 2);

    // Socket needs memory allocated in MEM2
    WorkBufferArg arg;
    arg.region = EMemory_MEM2;
    arg.size = TEMP_BUFFER_SIZE;
    WorkBuffer buffer(arg);

    size_t end = String::npos;
    while (end == String::npos) {
        Optional<u32> nrecv =
            mSocket.RecvBytes(buffer.Contents(), buffer.AlignedSize() - 1);

        // Record socket library error if it failed
        if (!nrecv) {
            mResponse.error = EHttpErr_Socket;
            mResponse.exError = LibSO::GetLastError();
            return false;
        }

        // Server has terminated the connection
        if (*nrecv == 0 && LibSO::GetLastError() != SO_EWOULDBLOCK) {
            mResponse.error = EHttpErr_Closed;
            mResponse.exError = LibSO::GetLastError();
            return false;
        }

        if (*nrecv > 0) {
            // Continue to build string
            buffer.Contents()[*nrecv] = '\0';
            work += reinterpret_cast<char*>(buffer.Contents());

            // Response header ends in double newline
            end = work.Find("\r\n\r\n");
        }

        // Connection timeout
        if (w.Elapsed() >= mTimeOut) {
            mResponse.error = EHttpErr_TimedOut;
            mResponse.exError = LibSO::GetLastError();
            return false;
        }
    }

    // Point index at end of sequence instead of start
    end += sizeof("\r\n\r\n") - 1;
    String headers = work.SubStr(0, end);

    /******************************************************************************
     * Build header dictionary
     ******************************************************************************/
    TVector<String> lines = headers.Split("\r\n");

    // Needs at least one line (for status code)
    if (lines.Empty()) {
        mResponse.error = EHttpErr_BadResponse;
        mResponse.exError = LibSO::GetLastError();
        return false;
    }

    // Extract status code
    int num = std::sscanf(lines[0], Format("%s %%d", PROTOCOL_VERSION).CStr(),
                          &mResponse.status);
    if (num != 1) {
        mResponse.error = EHttpErr_BadResponse;
        mResponse.exError = LibSO::GetLastError();
        return false;
    }

    // Other lines contain key/value pairs
    for (u32 i = 1; i < lines.Size(); i++) {
        // NOTE: Use Find over Split in case the value also contains a colon
        u32 pos = lines[i].Find(": ");
        u32 after = pos + sizeof(": ") - 1;

        // Malformed line (or part of \r\n\r\n ending)
        if (pos == String::npos) {
            // If this isn't one of the trailing newlines, we have a problem
            if (lines[i] != "\r\n") {
                mResponse.error = EHttpErr_BadResponse;
                mResponse.exError = LibSO::GetLastError();
                return false;
            }

            continue;
        }

        // Create key/value pair
        String key = lines[i].SubStr(0, pos);
        String value = lines[i].SubStr(after);
        mResponse.header.Insert(key, value);
    }

    /******************************************************************************
     * Receive response body
     ******************************************************************************/
    // If we were given the length, we can be 100% sure
    Optional<u32> len;
    if (mResponse.header.Contains("Content-Length")) {
        len =
            std::strtoul(*mResponse.header.Find("Content-Length"), nullptr, 0);
    }

    // We may have read some of the body earlier
    if (end != work.Length()) {
        mResponse.body = work.SubStr(end);
    }

    // Receive the rest of the body
    while (true) {
        Optional<u32> nrecv =
            mSocket.RecvBytes(buffer.Contents(), buffer.AlignedSize() - 1);

        // Record socket library error if it failed
        if (!nrecv) {
            mResponse.error = EHttpErr_Socket;
            mResponse.exError = LibSO::GetLastError();
            return false;
        }

        // Server is likely done and has terminated the connection
        if (*nrecv == 0 && LibSO::GetLastError() != SO_EWOULDBLOCK) {
            // This is only okay if we've read enough of the body
            if (!len || mResponse.body.Length() >= *len) {
                break;
            }

            mResponse.error = EHttpErr_Closed;
            mResponse.exError = LibSO::GetLastError();
            return false;
        }

        // Continue building string
        buffer.Contents()[*nrecv] = '\0';
        mResponse.body += reinterpret_cast<char*>(buffer.Contents());

        // Timeout may be the only way to end the body, so not a failure
        if (w.Elapsed() >= mTimeOut) {
            break;
        }
    };

    mResponse.error = EHttpErr_Success;
    mResponse.exError = LibSO::GetLastError();
    return true;
}

} // namespace kiwi
