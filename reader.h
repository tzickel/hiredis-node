#include <v8.h>
#include <node.h>

namespace hiredis {

using namespace v8;
using namespace node;

class Reader : ObjectWrap {
public:
    Reader();
    ~Reader();

    static void Initialize(Handle<Object> target);
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> Feed(const Arguments &args);
    static Handle<Value> Get(const Arguments &args);

    /* Objects created by the reply object functions need to get back to the
     * reader when the reply is requested via Reader::Get(). Keep temporary
     * objects in this handle. Use an array of handles because replies may
     * include nested multi bulks and child-elements need to be added to the
     * right respective parent. handle[0] will be unused, so the real index of
     * an object in this array can be returned from the reply object functions.
     * The returned value needs to be non-zero to distinguish complete replies
     * from incomplete replies. */
    Local<Value> handle[3];

    /* To keep references to objects when Reader::Get couldn't return a full reply,
     * store persistent handles to these objects so they can be recovered
     * as local handles in subsequent calls. */
    Persistent<Value> persistent_handle[3];

    /* Helper function to create string/buffer objects. */
    Local<Value> createString(char *str, size_t len);

private:
    void *reader;

    /* Determines whether to return strings or buffers for single line and bulk
     * replies. This defaults to false, so strings are returned by default. */
    bool return_buffers;

};

};

