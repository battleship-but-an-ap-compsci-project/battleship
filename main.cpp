#include "include/libwebsockets.h"

static struct lws_context* context;
static struct lws* client_wsi;

static int websocket_callback(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len) {
    switch (reason) {
        case: LWS_CALLBACK_CLIENT_ESTABLISHED:
            // connection to server established
            break;
        case LWS_CALLBACK_CLIENT_RECEIVE:
            // data recieved from the server
            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            // socket ready to send data
            break;
        case LWS_CALLBACK_CLOSED:
            // connection to server has been closed
            break;
        default:
            break;
    }
    return 0;
}

int main() {

    struct lws_context_creation_info info = { 0 };
    struct lws_client_connect_info connect_info = { 0 };

    // create libwebsocket context
    info.port =  CONTEXT_PORT_NO_LISTEN;
    info.iface = NULL;
    info.protocols = NULL;
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.gid = -1;
    info.uid = -1;
    info.options = 0;
    context = lws_create_context(&info);

    // connect to server
    connect_info.context = context;
    connect_info.address = "some://placeholder.site";
    connect_info.port = 443; // ?
    connect_info.path = "/";
    connect_info.host = lws_canonical_hostname(context);
    connect_info.origin = "https://placeholder.com";
    connect_info.protocol = NULL;
    connect_info.ssl_connection = LCCSCF_USE_SSL;
    client_wsi =  lws_client_connect_via_info(&connect_info);

    // event loop
    while (true) {
        lws_service(context, 0);
    }

    // cleanup
    lws_context_destroy(context);

    return 0;
}