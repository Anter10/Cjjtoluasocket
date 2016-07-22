#include "SocketManager_lua.hpp"
#include "SocketManager.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_SocketManager_SocketManager_sendData(lua_State* tolua_S)
{
    int argc = 0;
    SocketManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SocketManager_SocketManager_sendData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "SocketManager:sendData");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_SocketManager_SocketManager_sendData'", nullptr);
            return 0;
        }
        bool ret = cobj->sendData(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketManager:sendData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SocketManager_SocketManager_sendData'.",&tolua_err);
#endif

    return 0;
}
int lua_SocketManager_SocketManager_connectHost(lua_State* tolua_S)
{
    int argc = 0;
    SocketManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (SocketManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SocketManager_SocketManager_connectHost'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:connectHost"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:connectHost");

            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "SocketManager:connectHost"); arg2 = arg2_tmp.c_str();

            if (!ok) { break; }
            bool ret = cobj->connectHost(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:connectHost"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:connectHost");

            if (!ok) { break; }
            bool ret = cobj->connectHost(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:connectHost"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:connectHost");

            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "SocketManager:connectHost"); arg2 = arg2_tmp.c_str();

            if (!ok) { break; }
            const char* arg3;
            std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "SocketManager:connectHost"); arg3 = arg3_tmp.c_str();

            if (!ok) { break; }
            bool ret = cobj->connectHost(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "SocketManager:connectHost",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SocketManager_SocketManager_connectHost'.",&tolua_err);
#endif

    return 0;
}
int lua_SocketManager_SocketManager_DestroySocket(lua_State* tolua_S)
{
    int argc = 0;
    SocketManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SocketManager_SocketManager_DestroySocket'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_SocketManager_SocketManager_DestroySocket'", nullptr);
            return 0;
        }
        cobj->DestroySocket();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketManager:DestroySocket",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SocketManager_SocketManager_DestroySocket'.",&tolua_err);
#endif

    return 0;
}
int lua_SocketManager_SocketManager_CallBackData(lua_State* tolua_S)
{
    int argc = 0;
    SocketManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_SocketManager_SocketManager_CallBackData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_SocketManager_SocketManager_CallBackData'", nullptr);
            return 0;
        }
        cobj->CallBackData();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketManager:CallBackData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_SocketManager_SocketManager_CallBackData'.",&tolua_err);
#endif

    return 0;
}
int lua_SocketManager_SocketManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    SocketManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:SocketManager"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:SocketManager");

            if (!ok) { break; }
            cobj = new SocketManager(arg0, arg1);
            tolua_pushusertype(tolua_S,(void*)cobj,"SocketManager");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new SocketManager();
            tolua_pushusertype(tolua_S,(void*)cobj,"SocketManager");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:SocketManager"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:SocketManager");

            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "SocketManager:SocketManager"); arg2 = arg2_tmp.c_str();

            if (!ok) { break; }
            cobj = new SocketManager(arg0, arg1, arg2);
            tolua_pushusertype(tolua_S,(void*)cobj,"SocketManager");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "SocketManager:SocketManager"); arg0 = arg0_tmp.c_str();

            if (!ok) { break; }
            unsigned short arg1;
            ok &= luaval_to_ushort(tolua_S, 3, &arg1, "SocketManager:SocketManager");

            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "SocketManager:SocketManager"); arg2 = arg2_tmp.c_str();

            if (!ok) { break; }
            const char* arg3;
            std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "SocketManager:SocketManager"); arg3 = arg3_tmp.c_str();

            if (!ok) { break; }
            cobj = new SocketManager(arg0, arg1, arg2, arg3);
            tolua_pushusertype(tolua_S,(void*)cobj,"SocketManager");
            tolua_register_gc(tolua_S,lua_gettop(tolua_S));
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "SocketManager:SocketManager",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_SocketManager_SocketManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_SocketManager_SocketManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SocketManager)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"SocketManager",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        SocketManager* self = (SocketManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_SocketManager_SocketManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"SocketManager");
    tolua_cclass(tolua_S,"SocketManager","SocketManager","",lua_SocketManager_SocketManager_finalize);

    tolua_beginmodule(tolua_S,"SocketManager");
        tolua_function(tolua_S,"new",lua_SocketManager_SocketManager_constructor);
        tolua_function(tolua_S,"sendData",lua_SocketManager_SocketManager_sendData);
        tolua_function(tolua_S,"connectHost",lua_SocketManager_SocketManager_connectHost);
        tolua_function(tolua_S,"DestroySocket",lua_SocketManager_SocketManager_DestroySocket);
        tolua_function(tolua_S,"CallBackData",lua_SocketManager_SocketManager_CallBackData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SocketManager).name();
    g_luaType[typeName] = "SocketManager";
    g_typeCast["SocketManager"] = "SocketManager";
    return 1;
}
TOLUA_API int register_all_SocketManager(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_SocketManager_SocketManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

