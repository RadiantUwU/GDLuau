#ifndef RBLX_EVENTS
#define RBLX_EVENTS

#include <godot_cpp/variant/variant.hpp>
#include <lua.h>
#include <lualib.h>
#include <godot_cpp/templates/vector.hpp>
#include "rblx_main.hpp"

namespace godot {

class RBXScriptSignal;

class RBXScriptConnection final {
    RBXScriptSignal* signal;
    int ref;
    RBXScriptConnection();
    friend class RBXScriptSignal;
public:
    ~RBXScriptConnection();
    bool isConnected();
    void Disconnect();
    static int lua_isConnected(lua_State *L);
    static int lua_Disconnect(lua_State *L);
};

class RBXScriptSignal final {
    lua_State *L;
    int ref;
    friend class RBXScriptConnection;
    friend class Instance;
    friend class RobloxVMInstance;
public:
    RBXScriptSignal(lua_State *L);
    RBXScriptSignal(luau_State *L);
    ~RBXScriptSignal();
    RBXScriptSignal(RBXScriptSignal&) = delete;            // deny copying
    RBXScriptSignal& operator=(RBXScriptSignal&) = delete;

    static int lua_connect(lua_State* L); // signal instance, function - return RBXScriptConnection
    static int lua_once(lua_State* L); // signal instance, function - return RBXScriptConnection
    static int lua_connectparallel(lua_State* L); // signal instance, function - return RBXScriptConnection
    static int lua_wait(lua_State* L); // signal instance - return vararg
    static int lua_fire(lua_State* L); // signal instance, vararg - return no args
    static int lua_onfire(lua_State *L);
    static int lua_onfire_autodisconnect(lua_State *L);
    static int lua_resume_onfire(lua_State *L);
};

}

#endif