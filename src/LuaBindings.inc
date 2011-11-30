/*
** Lua binding: LuaBindings
** Generated automatically by tolua++-1.0.92 on 11/29/11 15:16:58.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaBindings_open (lua_State* tolua_S);

#include "Application.h"
#include "Balance.h"
#include "Database.h"
#include "Font.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Profile.h"
#include "ResourceManager.h"
#include "ResourceQueue.h"
#include "Sound.h"
#include "Sprite.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Profile (lua_State* tolua_S)
{
 Profile* self = (Profile*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Sprite (lua_State* tolua_S)
{
 Sprite* self = (Sprite*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CFont (lua_State* tolua_S)
{
 CFont* self = (CFont*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_Sound (lua_State* tolua_S)
{
 Sound* self = (Sound*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Database");
 tolua_usertype(tolua_S,"CFont");
 tolua_usertype(tolua_S,"Keyboard");
 tolua_usertype(tolua_S,"ResourceQueue");
 tolua_usertype(tolua_S,"Application");
 tolua_usertype(tolua_S,"Balance");
 tolua_usertype(tolua_S,"Sprite");
 tolua_usertype(tolua_S,"Graphics");
 tolua_usertype(tolua_S,"ResourceManager");
 tolua_usertype(tolua_S,"Mouse");
 tolua_usertype(tolua_S,"Sound");
 tolua_usertype(tolua_S,"Profile");
}

/* method: getDataDirectory of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_getDataDirectory00
static int tolua_LuaBindings_Application_getDataDirectory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDataDirectory'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getDataDirectory();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDataDirectory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCompanyName of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_getCompanyName00
static int tolua_LuaBindings_Application_getCompanyName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCompanyName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getCompanyName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCompanyName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCompanyName of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_setCompanyName00
static int tolua_LuaBindings_Application_setCompanyName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Application* self = (Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCompanyName'", NULL);
#endif
  {
   self->setCompanyName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCompanyName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getApplicationName of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_getApplicationName00
static int tolua_LuaBindings_Application_getApplicationName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getApplicationName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getApplicationName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getApplicationName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setApplicationName of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_setApplicationName00
static int tolua_LuaBindings_Application_setApplicationName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Application* self = (Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setApplicationName'", NULL);
#endif
  {
   self->setApplicationName(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setApplicationName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getApplicationVersion of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_getApplicationVersion00
static int tolua_LuaBindings_Application_getApplicationVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getApplicationVersion'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getApplicationVersion();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getApplicationVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setApplicationVersion of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_setApplicationVersion00
static int tolua_LuaBindings_Application_setApplicationVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Application* self = (Application*)  tolua_tousertype(tolua_S,1,0);
  const std::string version = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setApplicationVersion'", NULL);
#endif
  {
   self->setApplicationVersion(version);
   tolua_pushcppstring(tolua_S,(const char*)version);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setApplicationVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: quit of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_quit00
static int tolua_LuaBindings_Application_quit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Application* self = (Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'quit'", NULL);
#endif
  {
   self->quit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'quit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Application_getSingleton00
static int tolua_LuaBindings_Application_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Application& tolua_ret = (Application&)  Application::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Application");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isConnected of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_isConnected00
static int tolua_LuaBindings_Balance_isConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Balance",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Balance* self = (const Balance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isConnected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isConnected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isProtocolValid of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_isProtocolValid00
static int tolua_LuaBindings_Balance_isProtocolValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Balance",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Balance* self = (const Balance*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isProtocolValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isProtocolValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isProtocolValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setServerAddr of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setServerAddr00
static int tolua_LuaBindings_Balance_setServerAddr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string addr = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setServerAddr'", NULL);
#endif
  {
   self->setServerAddr(addr);
   tolua_pushcppstring(tolua_S,(const char*)addr);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setServerAddr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOscMode of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setOscMode00
static int tolua_LuaBindings_Balance_setOscMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  int mode = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOscMode'", NULL);
#endif
  {
   self->setOscMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOscMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_getParam00
static int tolua_LuaBindings_Balance_getParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Balance* self = (const Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getParam'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getParam(name);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIntParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_getIntParam00
static int tolua_LuaBindings_Balance_getIntParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Balance* self = (const Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIntParam'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIntParam(name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIntParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFloatParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_getFloatParam00
static int tolua_LuaBindings_Balance_getFloatParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Balance* self = (const Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFloatParam'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFloatParam(name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFloatParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setParam00
static int tolua_LuaBindings_Balance_setParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParam'", NULL);
#endif
  {
   self->setParam(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setParam01
static int tolua_LuaBindings_Balance_setParam01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setParam'", NULL);
#endif
  {
   self->setParam(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 2;
tolua_lerror:
 return tolua_LuaBindings_Balance_setParam00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIntParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setIntParam00
static int tolua_LuaBindings_Balance_setIntParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIntParam'", NULL);
#endif
  {
   self->setIntParam(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIntParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFloatParam of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_setFloatParam00
static int tolua_LuaBindings_Balance_setFloatParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Balance* self = (Balance*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFloatParam'", NULL);
#endif
  {
   self->setFloatParam(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFloatParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Balance */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Balance_getSingleton00
static int tolua_LuaBindings_Balance_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Balance",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Balance& tolua_ret = (Balance&)  Balance::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Balance");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: execQuery of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_execQuery00
static int tolua_LuaBindings_Database_execQuery00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'execQuery'", NULL);
#endif
  {
   self->execQuery(text);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'execQuery'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nextRow of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_nextRow00
static int tolua_LuaBindings_Database_nextRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nextRow'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->nextRow();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nextRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getString of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_getString00
static int tolua_LuaBindings_Database_getString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  const std::string column = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getString(column);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)column);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInt of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_getInt00
static int tolua_LuaBindings_Database_getInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  const std::string column = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getInt(column);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)column);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFloat of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_getFloat00
static int tolua_LuaBindings_Database_getFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
  const std::string column = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFloat'", NULL);
#endif
  {
   double tolua_ret = (double)  self->getFloat(column);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)column);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closeQuery of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_closeQuery00
static int tolua_LuaBindings_Database_closeQuery00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Database* self = (Database*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closeQuery'", NULL);
#endif
  {
   self->closeQuery();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closeQuery'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Database */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Database_getSingleton00
static int tolua_LuaBindings_Database_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Database",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Database& tolua_ret = (Database&)  Database::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Database");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CFont */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_CFont_new00
static int tolua_LuaBindings_CFont_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CFont",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   CFont* tolua_ret = (CFont*)  Mtolua_new((CFont)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CFont");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CFont */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_CFont_new00_local
static int tolua_LuaBindings_CFont_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CFont",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   CFont* tolua_ret = (CFont*)  Mtolua_new((CFont)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CFont");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTextSize of class  CFont */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_CFont_getTextSize00
static int tolua_LuaBindings_CFont_getTextSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CFont",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CFont* self = (CFont*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int width = ((int)  tolua_tonumber(tolua_S,3,NULL));
  int height = ((int)  tolua_tonumber(tolua_S,4,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextSize'", NULL);
#endif
  {
   self->getTextSize(text,&width,&height);
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawText of class  CFont */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_CFont_drawText00
static int tolua_LuaBindings_CFont_drawText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CFont",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CFont* self = (CFont*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  const std::string text = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
  float r = ((float)  tolua_tonumber(tolua_S,5,1.0f));
  float g = ((float)  tolua_tonumber(tolua_S,6,1.0f));
  float b = ((float)  tolua_tonumber(tolua_S,7,1.0f));
  float a = ((float)  tolua_tonumber(tolua_S,8,1.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawText'", NULL);
#endif
  {
   self->drawText(x,y,text,r,g,b,a);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScreenSize of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_setScreenSize00
static int tolua_LuaBindings_Graphics_setScreenSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  float minAspect = ((float)  tolua_tonumber(tolua_S,4,0.0f));
  float maxAspect = ((float)  tolua_tonumber(tolua_S,5,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScreenSize'", NULL);
#endif
  {
   self->setScreenSize(width,height,minAspect,maxAspect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScreenSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getVisibleRect of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_getVisibleRect00
static int tolua_LuaBindings_Graphics_getVisibleRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,NULL));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,NULL));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,NULL));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getVisibleRect'", NULL);
#endif
  {
   self->getVisibleRect(&x1,&y1,&x2,&y2);
   tolua_pushnumber(tolua_S,(lua_Number)x1);
   tolua_pushnumber(tolua_S,(lua_Number)y1);
   tolua_pushnumber(tolua_S,(lua_Number)x2);
   tolua_pushnumber(tolua_S,(lua_Number)y2);
  }
 }
 return 4;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getVisibleRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: show of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_show00
static int tolua_LuaBindings_Graphics_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'", NULL);
#endif
  {
   self->show();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hide of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_hide00
static int tolua_LuaBindings_Graphics_hide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hide'", NULL);
#endif
  {
   self->hide();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isVSync of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_isVSync00
static int tolua_LuaBindings_Graphics_isVSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isVSync'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isVSync();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isVSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVSync of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_setVSync00
static int tolua_LuaBindings_Graphics_setVSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  bool vsync = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVSync'", NULL);
#endif
  {
   self->setVSync(vsync);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFPS of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_getFPS00
static int tolua_LuaBindings_Graphics_getFPS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFPS'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFPS();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFPS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendMode of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_getBlendMode00
static int tolua_LuaBindings_Graphics_getBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendMode'", NULL);
#endif
  {
   BlendMode tolua_ret = (BlendMode)  self->getBlendMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendMode of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_setBlendMode00
static int tolua_LuaBindings_Graphics_setBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  BlendMode blendMode = ((BlendMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendMode'", NULL);
#endif
  {
   self->setBlendMode(blendMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setClipRect of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_setClipRect00
static int tolua_LuaBindings_Graphics_setClipRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setClipRect'", NULL);
#endif
  {
   self->setClipRect(x1,y1,x2,y2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setClipRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetClipRect of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_resetClipRect00
static int tolua_LuaBindings_Graphics_resetClipRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetClipRect'", NULL);
#endif
  {
   self->resetClipRect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetClipRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_clear00
static int tolua_LuaBindings_Graphics_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
  float g = ((float)  tolua_tonumber(tolua_S,3,0));
  float b = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear(r,g,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fillRect of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_fillRect00
static int tolua_LuaBindings_Graphics_fillRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
  float r = ((float)  tolua_tonumber(tolua_S,6,0));
  float g = ((float)  tolua_tonumber(tolua_S,7,0));
  float b = ((float)  tolua_tonumber(tolua_S,8,0));
  float a = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fillRect'", NULL);
#endif
  {
   self->fillRect(x1,y1,x2,y2,r,g,b,a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fillRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: gradientFill of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_gradientFill00
static int tolua_LuaBindings_Graphics_gradientFill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,14,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
  float r1 = ((float)  tolua_tonumber(tolua_S,6,0));
  float g1 = ((float)  tolua_tonumber(tolua_S,7,0));
  float b1 = ((float)  tolua_tonumber(tolua_S,8,0));
  float a1 = ((float)  tolua_tonumber(tolua_S,9,0));
  float r2 = ((float)  tolua_tonumber(tolua_S,10,0));
  float g2 = ((float)  tolua_tonumber(tolua_S,11,0));
  float b2 = ((float)  tolua_tonumber(tolua_S,12,0));
  float a2 = ((float)  tolua_tonumber(tolua_S,13,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'gradientFill'", NULL);
#endif
  {
   self->gradientFill(x1,y1,x2,y2,r1,g1,b1,a1,r2,g2,b2,a2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'gradientFill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Graphics_getSingleton00
static int tolua_LuaBindings_Graphics_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Graphics& tolua_ret = (Graphics&)  Graphics::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Graphics");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeyDown of class  Keyboard */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Keyboard_isKeyDown00
static int tolua_LuaBindings_Keyboard_isKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Keyboard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Keyboard* self = (const Keyboard*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeyDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeyDown(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Keyboard */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Keyboard_getSingleton00
static int tolua_LuaBindings_Keyboard_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Keyboard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Keyboard& tolua_ret = (Keyboard&)  Keyboard::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Keyboard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  Mouse */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Mouse_getPosition00
static int tolua_LuaBindings_Mouse_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Mouse",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Mouse* self = (const Mouse*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,NULL));
  float y = ((float)  tolua_tonumber(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   self->getPosition(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeyDown of class  Mouse */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Mouse_isKeyDown00
static int tolua_LuaBindings_Mouse_isKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Mouse",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Mouse* self = (const Mouse*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeyDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeyDown(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showCursor of class  Mouse */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Mouse_showCursor00
static int tolua_LuaBindings_Mouse_showCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Mouse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Mouse* self = (Mouse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showCursor'", NULL);
#endif
  {
   self->showCursor();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideCursor of class  Mouse */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Mouse_hideCursor00
static int tolua_LuaBindings_Mouse_hideCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Mouse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Mouse* self = (Mouse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hideCursor'", NULL);
#endif
  {
   self->hideCursor();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hideCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  Mouse */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Mouse_getSingleton00
static int tolua_LuaBindings_Mouse_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Mouse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Mouse& tolua_ret = (Mouse&)  Mouse::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Mouse");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_new00
static int tolua_LuaBindings_Profile_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Profile* tolua_ret = (Profile*)  Mtolua_new((Profile)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Profile");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_new00_local
static int tolua_LuaBindings_Profile_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Profile* tolua_ret = (Profile*)  Mtolua_new((Profile)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Profile");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: save of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_save00
static int tolua_LuaBindings_Profile_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'save'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->save();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getString of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_getString00
static int tolua_LuaBindings_Profile_getString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getString(name);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getString of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_getString01
static int tolua_LuaBindings_Profile_getString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string defaultValue = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getString(name,defaultValue);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)defaultValue);
  }
 }
 return 3;
tolua_lerror:
 return tolua_LuaBindings_Profile_getString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setString of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_setString00
static int tolua_LuaBindings_Profile_setString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setString'", NULL);
#endif
  {
   self->setString(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)value);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInt of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_getInt00
static int tolua_LuaBindings_Profile_getInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int defaultValue = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getInt(name,defaultValue);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInt of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_setInt00
static int tolua_LuaBindings_Profile_setInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInt'", NULL);
#endif
  {
   self->setInt(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBool of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_getBool00
static int tolua_LuaBindings_Profile_getBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool defaultValue = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBool(name,defaultValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBool of class  Profile */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Profile_setBool00
static int tolua_LuaBindings_Profile_setBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Profile",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Profile* self = (Profile*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBool'", NULL);
#endif
  {
   self->setBool(name,value);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadResource of class  ResourceManager */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceManager_loadResource00
static int tolua_LuaBindings_ResourceManager_loadResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceManager* self = (ResourceManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadResource'", NULL);
#endif
  {
   self->loadResource(name,fileName);
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadAllResources of class  ResourceManager */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceManager_loadAllResources00
static int tolua_LuaBindings_ResourceManager_loadAllResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceManager* self = (ResourceManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAllResources'", NULL);
#endif
  {
   self->loadAllResources(fileName);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAllResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadResource of class  ResourceManager */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceManager_unloadResource00
static int tolua_LuaBindings_ResourceManager_unloadResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceManager* self = (ResourceManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadResource'", NULL);
#endif
  {
   self->unloadResource(name);
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unloadAllResources of class  ResourceManager */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceManager_unloadAllResources00
static int tolua_LuaBindings_ResourceManager_unloadAllResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceManager* self = (ResourceManager*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unloadAllResources'", NULL);
#endif
  {
   self->unloadAllResources(fileName);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unloadAllResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  ResourceManager */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceManager_getSingleton00
static int tolua_LuaBindings_ResourceManager_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceManager& tolua_ret = (ResourceManager&)  ResourceManager::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"ResourceManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addResource of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_addResource00
static int tolua_LuaBindings_ResourceQueue_addResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceQueue",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceQueue* self = (ResourceQueue*)  tolua_tousertype(tolua_S,1,0);
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addResource'", NULL);
#endif
  {
   self->addResource(name,fileName);
   tolua_pushcppstring(tolua_S,(const char*)name);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAllResources of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_addAllResources00
static int tolua_LuaBindings_ResourceQueue_addAllResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceQueue",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceQueue* self = (ResourceQueue*)  tolua_tousertype(tolua_S,1,0);
  const std::string fileName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAllResources'", NULL);
#endif
  {
   self->addAllResources(fileName);
   tolua_pushcppstring(tolua_S,(const char*)fileName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAllResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startLoading of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_startLoading00
static int tolua_LuaBindings_ResourceQueue_startLoading00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceQueue* self = (ResourceQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startLoading'", NULL);
#endif
  {
   self->startLoading();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startLoading'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isLoadingActive of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_isLoadingActive00
static int tolua_LuaBindings_ResourceQueue_isLoadingActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceQueue* self = (const ResourceQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isLoadingActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isLoadingActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isLoadingActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoadingProgress of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_getLoadingProgress00
static int tolua_LuaBindings_ResourceQueue_getLoadingProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceQueue* self = (const ResourceQueue*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoadingProgress'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getLoadingProgress();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoadingProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleton of class  ResourceQueue */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_ResourceQueue_getSingleton00
static int tolua_LuaBindings_ResourceQueue_getSingleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceQueue",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceQueue& tolua_ret = (ResourceQueue&)  ResourceQueue::getSingleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"ResourceQueue");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_new00
static int tolua_LuaBindings_Sound_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Sound* tolua_ret = (Sound*)  Mtolua_new((Sound)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sound");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_new00_local
static int tolua_LuaBindings_Sound_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   Sound* tolua_ret = (Sound*)  Mtolua_new((Sound)(name));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sound");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPlaying of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_isPlaying00
static int tolua_LuaBindings_Sound_isPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPaused of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_isPaused00
static int tolua_LuaBindings_Sound_isPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPaused'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPaused();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_play00
static int tolua_LuaBindings_Sound_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_pause00
static int tolua_LuaBindings_Sound_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  Sound */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sound_stop00
static int tolua_LuaBindings_Sound_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_new00
static int tolua_LuaBindings_Sprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   Sprite* tolua_ret = (Sprite*)  Mtolua_new((Sprite)(name,x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sprite");
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_new00_local
static int tolua_LuaBindings_Sprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::string name = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   Sprite* tolua_ret = (Sprite*)  Mtolua_new((Sprite)(name,x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
   tolua_pushcppstring(tolua_S,(const char*)name);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_x
static int tolua_get_Sprite_x(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_x());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_x
static int tolua_set_Sprite_x(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_x(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_y
static int tolua_get_Sprite_y(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_y());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_y
static int tolua_set_Sprite_y(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_y(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: red of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_red
static int tolua_get_Sprite_red(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'red'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_red());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: red of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_red
static int tolua_set_Sprite_red(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'red'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_red(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: green of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_green
static int tolua_get_Sprite_green(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'green'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_green());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: green of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_green
static int tolua_set_Sprite_green(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'green'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_green(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: blue of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_blue
static int tolua_get_Sprite_blue(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blue'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_blue());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: blue of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_blue
static int tolua_set_Sprite_blue(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'blue'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_blue(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: alpha of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_alpha
static int tolua_get_Sprite_alpha(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_alpha());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: alpha of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_alpha
static int tolua_set_Sprite_alpha(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_alpha(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumFrames of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_getNumFrames00
static int tolua_LuaBindings_Sprite_getNumFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumFrames'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getNumFrames();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: frame of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_frame
static int tolua_get_Sprite_frame(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frame'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_frame());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: frame of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_frame
static int tolua_set_Sprite_frame(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frame'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_frame(((int)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWidth of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_getWidth00
static int tolua_LuaBindings_Sprite_getWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHeight of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_getHeight00
static int tolua_LuaBindings_Sprite_getHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHotSpot of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_getHotSpot00
static int tolua_LuaBindings_Sprite_getHotSpot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,NULL));
  int y = ((int)  tolua_tonumber(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHotSpot'", NULL);
#endif
  {
   self->getHotSpot(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHotSpot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHotSpot of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_setHotSpot00
static int tolua_LuaBindings_Sprite_setHotSpot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHotSpot'", NULL);
#endif
  {
   self->setHotSpot(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHotSpot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: angle of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_get_Sprite_angle
static int tolua_get_Sprite_angle(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angle'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->get_angle());
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: angle of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_set_Sprite_angle
static int tolua_set_Sprite_angle(lua_State* tolua_S)
{
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angle'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->set_angle(((float)  tolua_tonumber(tolua_S,2,0))
)
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_getScale00
static int tolua_LuaBindings_Sprite_getScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,NULL));
  float y = ((float)  tolua_tonumber(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScale'", NULL);
#endif
  {
   self->getScale(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_setScale00
static int tolua_LuaBindings_Sprite_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setScale'", NULL);
#endif
  {
   self->setScale(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPointInside of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_isPointInside00
static int tolua_LuaBindings_Sprite_isPointInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPointInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPointInside(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPointInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_draw00
static int tolua_LuaBindings_Sprite_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_draw01
static int tolua_LuaBindings_Sprite_draw01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_LuaBindings_Sprite_draw00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_draw02
static int tolua_LuaBindings_Sprite_draw02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw(x1,y1,x2,y2);
  }
 }
 return 0;
tolua_lerror:
 return tolua_LuaBindings_Sprite_draw01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_LuaBindings_Sprite_draw03
static int tolua_LuaBindings_Sprite_draw03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
  float sx1 = ((float)  tolua_tonumber(tolua_S,6,0));
  float sy1 = ((float)  tolua_tonumber(tolua_S,7,0));
  float sx2 = ((float)  tolua_tonumber(tolua_S,8,0));
  float sy2 = ((float)  tolua_tonumber(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw(x1,y1,x2,y2,sx1,sy1,sx2,sy2);
  }
 }
 return 0;
tolua_lerror:
 return tolua_LuaBindings_Sprite_draw02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaBindings_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Application","Application","",NULL);
  tolua_beginmodule(tolua_S,"Application");
   tolua_function(tolua_S,"getDataDirectory",tolua_LuaBindings_Application_getDataDirectory00);
   tolua_function(tolua_S,"getCompanyName",tolua_LuaBindings_Application_getCompanyName00);
   tolua_function(tolua_S,"setCompanyName",tolua_LuaBindings_Application_setCompanyName00);
   tolua_function(tolua_S,"getApplicationName",tolua_LuaBindings_Application_getApplicationName00);
   tolua_function(tolua_S,"setApplicationName",tolua_LuaBindings_Application_setApplicationName00);
   tolua_function(tolua_S,"getApplicationVersion",tolua_LuaBindings_Application_getApplicationVersion00);
   tolua_function(tolua_S,"setApplicationVersion",tolua_LuaBindings_Application_setApplicationVersion00);
   tolua_function(tolua_S,"quit",tolua_LuaBindings_Application_quit00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Application_getSingleton00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Balance","Balance","",NULL);
  tolua_beginmodule(tolua_S,"Balance");
   tolua_function(tolua_S,"isConnected",tolua_LuaBindings_Balance_isConnected00);
   tolua_function(tolua_S,"isProtocolValid",tolua_LuaBindings_Balance_isProtocolValid00);
   tolua_function(tolua_S,"setServerAddr",tolua_LuaBindings_Balance_setServerAddr00);
   tolua_function(tolua_S,"setOscMode",tolua_LuaBindings_Balance_setOscMode00);
   tolua_function(tolua_S,"getParam",tolua_LuaBindings_Balance_getParam00);
   tolua_function(tolua_S,"getIntParam",tolua_LuaBindings_Balance_getIntParam00);
   tolua_function(tolua_S,"getFloatParam",tolua_LuaBindings_Balance_getFloatParam00);
   tolua_function(tolua_S,"setParam",tolua_LuaBindings_Balance_setParam00);
   tolua_function(tolua_S,"setParam",tolua_LuaBindings_Balance_setParam01);
   tolua_function(tolua_S,"setIntParam",tolua_LuaBindings_Balance_setIntParam00);
   tolua_function(tolua_S,"setFloatParam",tolua_LuaBindings_Balance_setFloatParam00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Balance_getSingleton00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Database","Database","",NULL);
  tolua_beginmodule(tolua_S,"Database");
   tolua_function(tolua_S,"execQuery",tolua_LuaBindings_Database_execQuery00);
   tolua_function(tolua_S,"nextRow",tolua_LuaBindings_Database_nextRow00);
   tolua_function(tolua_S,"getString",tolua_LuaBindings_Database_getString00);
   tolua_function(tolua_S,"getInt",tolua_LuaBindings_Database_getInt00);
   tolua_function(tolua_S,"getFloat",tolua_LuaBindings_Database_getFloat00);
   tolua_function(tolua_S,"closeQuery",tolua_LuaBindings_Database_closeQuery00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Database_getSingleton00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CFont","CFont","",tolua_collect_CFont);
  #else
  tolua_cclass(tolua_S,"CFont","CFont","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CFont");
   tolua_function(tolua_S,"new",tolua_LuaBindings_CFont_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaBindings_CFont_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaBindings_CFont_new00_local);
   tolua_function(tolua_S,"getTextSize",tolua_LuaBindings_CFont_getTextSize00);
   tolua_function(tolua_S,"drawText",tolua_LuaBindings_CFont_drawText00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"BLEND_DISABLE",BLEND_DISABLE);
  tolua_constant(tolua_S,"BLEND_ALPHA",BLEND_ALPHA);
  tolua_constant(tolua_S,"BLEND_ADD",BLEND_ADD);
  tolua_constant(tolua_S,"BLEND_SUBTRACT",BLEND_SUBTRACT);
  tolua_constant(tolua_S,"BLEND_MULTIPLY",BLEND_MULTIPLY);
  tolua_cclass(tolua_S,"Graphics","Graphics","",NULL);
  tolua_beginmodule(tolua_S,"Graphics");
   tolua_function(tolua_S,"setScreenSize",tolua_LuaBindings_Graphics_setScreenSize00);
   tolua_function(tolua_S,"getVisibleRect",tolua_LuaBindings_Graphics_getVisibleRect00);
   tolua_function(tolua_S,"show",tolua_LuaBindings_Graphics_show00);
   tolua_function(tolua_S,"hide",tolua_LuaBindings_Graphics_hide00);
   tolua_function(tolua_S,"isVSync",tolua_LuaBindings_Graphics_isVSync00);
   tolua_function(tolua_S,"setVSync",tolua_LuaBindings_Graphics_setVSync00);
   tolua_function(tolua_S,"getFPS",tolua_LuaBindings_Graphics_getFPS00);
   tolua_function(tolua_S,"getBlendMode",tolua_LuaBindings_Graphics_getBlendMode00);
   tolua_function(tolua_S,"setBlendMode",tolua_LuaBindings_Graphics_setBlendMode00);
   tolua_function(tolua_S,"setClipRect",tolua_LuaBindings_Graphics_setClipRect00);
   tolua_function(tolua_S,"resetClipRect",tolua_LuaBindings_Graphics_resetClipRect00);
   tolua_function(tolua_S,"clear",tolua_LuaBindings_Graphics_clear00);
   tolua_function(tolua_S,"fillRect",tolua_LuaBindings_Graphics_fillRect00);
   tolua_function(tolua_S,"gradientFill",tolua_LuaBindings_Graphics_gradientFill00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Graphics_getSingleton00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"KEY_BACKSPACE",CL_KEY_BACKSPACE);
  tolua_constant(tolua_S,"KEY_TAB",CL_KEY_TAB);
  tolua_constant(tolua_S,"KEY_CLEAR",CL_KEY_CLEAR);
  tolua_constant(tolua_S,"KEY_RETURN",CL_KEY_RETURN);
  tolua_constant(tolua_S,"KEY_SHIFT",CL_KEY_SHIFT);
  tolua_constant(tolua_S,"KEY_CONTROL",CL_KEY_CONTROL);
  tolua_constant(tolua_S,"KEY_MENU",CL_KEY_MENU);
  tolua_constant(tolua_S,"KEY_PAUSE",CL_KEY_PAUSE);
  tolua_constant(tolua_S,"KEY_ESCAPE",CL_KEY_ESCAPE);
  tolua_constant(tolua_S,"KEY_SPACE",CL_KEY_SPACE);
  tolua_constant(tolua_S,"KEY_PRIOR",CL_KEY_PRIOR);
  tolua_constant(tolua_S,"KEY_NEXT",CL_KEY_NEXT);
  tolua_constant(tolua_S,"KEY_END",CL_KEY_END);
  tolua_constant(tolua_S,"KEY_HOME",CL_KEY_HOME);
  tolua_constant(tolua_S,"KEY_LEFT",CL_KEY_LEFT);
  tolua_constant(tolua_S,"KEY_UP",CL_KEY_UP);
  tolua_constant(tolua_S,"KEY_RIGHT",CL_KEY_RIGHT);
  tolua_constant(tolua_S,"KEY_DOWN",CL_KEY_DOWN);
  tolua_constant(tolua_S,"KEY_SELECT",CL_KEY_SELECT);
  tolua_constant(tolua_S,"KEY_PRINT",CL_KEY_PRINT);
  tolua_constant(tolua_S,"KEY_EXECUTE",CL_KEY_EXECUTE);
  tolua_constant(tolua_S,"KEY_INSERT",CL_KEY_INSERT);
  tolua_constant(tolua_S,"KEY_DELETE",CL_KEY_DELETE);
  tolua_constant(tolua_S,"KEY_HELP",CL_KEY_HELP);
  tolua_constant(tolua_S,"KEY_0",CL_KEY_0);
  tolua_constant(tolua_S,"KEY_1",CL_KEY_1);
  tolua_constant(tolua_S,"KEY_2",CL_KEY_2);
  tolua_constant(tolua_S,"KEY_3",CL_KEY_3);
  tolua_constant(tolua_S,"KEY_4",CL_KEY_4);
  tolua_constant(tolua_S,"KEY_5",CL_KEY_5);
  tolua_constant(tolua_S,"KEY_6",CL_KEY_6);
  tolua_constant(tolua_S,"KEY_7",CL_KEY_7);
  tolua_constant(tolua_S,"KEY_8",CL_KEY_8);
  tolua_constant(tolua_S,"KEY_9",CL_KEY_9);
  tolua_constant(tolua_S,"KEY_A",CL_KEY_A);
  tolua_constant(tolua_S,"KEY_B",CL_KEY_B);
  tolua_constant(tolua_S,"KEY_C",CL_KEY_C);
  tolua_constant(tolua_S,"KEY_D",CL_KEY_D);
  tolua_constant(tolua_S,"KEY_E",CL_KEY_E);
  tolua_constant(tolua_S,"KEY_F",CL_KEY_F);
  tolua_constant(tolua_S,"KEY_G",CL_KEY_G);
  tolua_constant(tolua_S,"KEY_H",CL_KEY_H);
  tolua_constant(tolua_S,"KEY_I",CL_KEY_I);
  tolua_constant(tolua_S,"KEY_J",CL_KEY_J);
  tolua_constant(tolua_S,"KEY_K",CL_KEY_K);
  tolua_constant(tolua_S,"KEY_L",CL_KEY_L);
  tolua_constant(tolua_S,"KEY_M",CL_KEY_M);
  tolua_constant(tolua_S,"KEY_N",CL_KEY_N);
  tolua_constant(tolua_S,"KEY_O",CL_KEY_O);
  tolua_constant(tolua_S,"KEY_P",CL_KEY_P);
  tolua_constant(tolua_S,"KEY_Q",CL_KEY_Q);
  tolua_constant(tolua_S,"KEY_R",CL_KEY_R);
  tolua_constant(tolua_S,"KEY_S",CL_KEY_S);
  tolua_constant(tolua_S,"KEY_T",CL_KEY_T);
  tolua_constant(tolua_S,"KEY_U",CL_KEY_U);
  tolua_constant(tolua_S,"KEY_V",CL_KEY_V);
  tolua_constant(tolua_S,"KEY_W",CL_KEY_W);
  tolua_constant(tolua_S,"KEY_X",CL_KEY_X);
  tolua_constant(tolua_S,"KEY_Y",CL_KEY_Y);
  tolua_constant(tolua_S,"KEY_Z",CL_KEY_Z);
  tolua_constant(tolua_S,"KEY_LWIN",CL_KEY_LWIN);
  tolua_constant(tolua_S,"KEY_RWIN",CL_KEY_RWIN);
  tolua_constant(tolua_S,"KEY_APPS",CL_KEY_APPS);
  tolua_constant(tolua_S,"KEY_NUMPAD0",CL_KEY_NUMPAD0);
  tolua_constant(tolua_S,"KEY_NUMPAD1",CL_KEY_NUMPAD1);
  tolua_constant(tolua_S,"KEY_NUMPAD2",CL_KEY_NUMPAD2);
  tolua_constant(tolua_S,"KEY_NUMPAD3",CL_KEY_NUMPAD3);
  tolua_constant(tolua_S,"KEY_NUMPAD4",CL_KEY_NUMPAD4);
  tolua_constant(tolua_S,"KEY_NUMPAD5",CL_KEY_NUMPAD5);
  tolua_constant(tolua_S,"KEY_NUMPAD6",CL_KEY_NUMPAD6);
  tolua_constant(tolua_S,"KEY_NUMPAD7",CL_KEY_NUMPAD7);
  tolua_constant(tolua_S,"KEY_NUMPAD8",CL_KEY_NUMPAD8);
  tolua_constant(tolua_S,"KEY_NUMPAD9",CL_KEY_NUMPAD9);
  tolua_constant(tolua_S,"KEY_NUMPAD_ENTER",CL_KEY_NUMPAD_ENTER);
  tolua_constant(tolua_S,"KEY_MULTIPLY",CL_KEY_MULTIPLY);
  tolua_constant(tolua_S,"KEY_ADD",CL_KEY_ADD);
  tolua_constant(tolua_S,"KEY_SEPARATOR",CL_KEY_SEPARATOR);
  tolua_constant(tolua_S,"KEY_SUBTRACT",CL_KEY_SUBTRACT);
  tolua_constant(tolua_S,"KEY_DECIMAL",CL_KEY_DECIMAL);
  tolua_constant(tolua_S,"KEY_DIVIDE",CL_KEY_DIVIDE);
  tolua_constant(tolua_S,"KEY_F1",CL_KEY_F1);
  tolua_constant(tolua_S,"KEY_F2",CL_KEY_F2);
  tolua_constant(tolua_S,"KEY_F3",CL_KEY_F3);
  tolua_constant(tolua_S,"KEY_F4",CL_KEY_F4);
  tolua_constant(tolua_S,"KEY_F5",CL_KEY_F5);
  tolua_constant(tolua_S,"KEY_F6",CL_KEY_F6);
  tolua_constant(tolua_S,"KEY_F7",CL_KEY_F7);
  tolua_constant(tolua_S,"KEY_F8",CL_KEY_F8);
  tolua_constant(tolua_S,"KEY_F9",CL_KEY_F9);
  tolua_constant(tolua_S,"KEY_F10",CL_KEY_F10);
  tolua_constant(tolua_S,"KEY_F11",CL_KEY_F11);
  tolua_constant(tolua_S,"KEY_F12",CL_KEY_F12);
  tolua_constant(tolua_S,"KEY_F13",CL_KEY_F13);
  tolua_constant(tolua_S,"KEY_F14",CL_KEY_F14);
  tolua_constant(tolua_S,"KEY_F15",CL_KEY_F15);
  tolua_constant(tolua_S,"KEY_F16",CL_KEY_F16);
  tolua_constant(tolua_S,"KEY_F17",CL_KEY_F17);
  tolua_constant(tolua_S,"KEY_F18",CL_KEY_F18);
  tolua_constant(tolua_S,"KEY_F19",CL_KEY_F19);
  tolua_constant(tolua_S,"KEY_F20",CL_KEY_F20);
  tolua_constant(tolua_S,"KEY_F21",CL_KEY_F21);
  tolua_constant(tolua_S,"KEY_F22",CL_KEY_F22);
  tolua_constant(tolua_S,"KEY_F23",CL_KEY_F23);
  tolua_constant(tolua_S,"KEY_F24",CL_KEY_F24);
  tolua_constant(tolua_S,"KEY_NUMLOCK",CL_KEY_NUMLOCK);
  tolua_constant(tolua_S,"KEY_SCROLL",CL_KEY_SCROLL);
  tolua_constant(tolua_S,"KEY_LSHIFT",CL_KEY_LSHIFT);
  tolua_constant(tolua_S,"KEY_RSHIFT",CL_KEY_RSHIFT);
  tolua_constant(tolua_S,"KEY_LCONTROL",CL_KEY_LCONTROL);
  tolua_constant(tolua_S,"KEY_RCONTROL",CL_KEY_RCONTROL);
  tolua_constant(tolua_S,"KEY_LMENU",CL_KEY_LMENU);
  tolua_constant(tolua_S,"KEY_RMENU",CL_KEY_RMENU);
  tolua_cclass(tolua_S,"Keyboard","Keyboard","",NULL);
  tolua_beginmodule(tolua_S,"Keyboard");
   tolua_function(tolua_S,"isKeyDown",tolua_LuaBindings_Keyboard_isKeyDown00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Keyboard_getSingleton00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"MOUSE_LEFT",CL_MOUSE_LEFT);
  tolua_constant(tolua_S,"MOUSE_RIGHT",CL_MOUSE_RIGHT);
  tolua_constant(tolua_S,"MOUSE_MIDDLE",CL_MOUSE_MIDDLE);
  tolua_constant(tolua_S,"MOUSE_WHEEL_UP",CL_MOUSE_WHEEL_UP);
  tolua_constant(tolua_S,"MOUSE_WHEEL_DOWN",CL_MOUSE_WHEEL_DOWN);
  tolua_cclass(tolua_S,"Mouse","Mouse","",NULL);
  tolua_beginmodule(tolua_S,"Mouse");
   tolua_function(tolua_S,"getPosition",tolua_LuaBindings_Mouse_getPosition00);
   tolua_function(tolua_S,"isKeyDown",tolua_LuaBindings_Mouse_isKeyDown00);
   tolua_function(tolua_S,"showCursor",tolua_LuaBindings_Mouse_showCursor00);
   tolua_function(tolua_S,"hideCursor",tolua_LuaBindings_Mouse_hideCursor00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_Mouse_getSingleton00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Profile","Profile","",tolua_collect_Profile);
  #else
  tolua_cclass(tolua_S,"Profile","Profile","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Profile");
   tolua_function(tolua_S,"new",tolua_LuaBindings_Profile_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaBindings_Profile_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaBindings_Profile_new00_local);
   tolua_function(tolua_S,"save",tolua_LuaBindings_Profile_save00);
   tolua_function(tolua_S,"getString",tolua_LuaBindings_Profile_getString00);
   tolua_function(tolua_S,"getString",tolua_LuaBindings_Profile_getString01);
   tolua_function(tolua_S,"setString",tolua_LuaBindings_Profile_setString00);
   tolua_function(tolua_S,"getInt",tolua_LuaBindings_Profile_getInt00);
   tolua_function(tolua_S,"setInt",tolua_LuaBindings_Profile_setInt00);
   tolua_function(tolua_S,"getBool",tolua_LuaBindings_Profile_getBool00);
   tolua_function(tolua_S,"setBool",tolua_LuaBindings_Profile_setBool00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ResourceManager","ResourceManager","",NULL);
  tolua_beginmodule(tolua_S,"ResourceManager");
   tolua_function(tolua_S,"loadResource",tolua_LuaBindings_ResourceManager_loadResource00);
   tolua_function(tolua_S,"loadAllResources",tolua_LuaBindings_ResourceManager_loadAllResources00);
   tolua_function(tolua_S,"unloadResource",tolua_LuaBindings_ResourceManager_unloadResource00);
   tolua_function(tolua_S,"unloadAllResources",tolua_LuaBindings_ResourceManager_unloadAllResources00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_ResourceManager_getSingleton00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ResourceQueue","ResourceQueue","",NULL);
  tolua_beginmodule(tolua_S,"ResourceQueue");
   tolua_function(tolua_S,"addResource",tolua_LuaBindings_ResourceQueue_addResource00);
   tolua_function(tolua_S,"addAllResources",tolua_LuaBindings_ResourceQueue_addAllResources00);
   tolua_function(tolua_S,"startLoading",tolua_LuaBindings_ResourceQueue_startLoading00);
   tolua_function(tolua_S,"isLoadingActive",tolua_LuaBindings_ResourceQueue_isLoadingActive00);
   tolua_function(tolua_S,"getLoadingProgress",tolua_LuaBindings_ResourceQueue_getLoadingProgress00);
   tolua_function(tolua_S,"getSingleton",tolua_LuaBindings_ResourceQueue_getSingleton00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Sound","Sound","",tolua_collect_Sound);
  #else
  tolua_cclass(tolua_S,"Sound","Sound","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Sound");
   tolua_function(tolua_S,"new",tolua_LuaBindings_Sound_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaBindings_Sound_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaBindings_Sound_new00_local);
   tolua_function(tolua_S,"isPlaying",tolua_LuaBindings_Sound_isPlaying00);
   tolua_function(tolua_S,"isPaused",tolua_LuaBindings_Sound_isPaused00);
   tolua_function(tolua_S,"play",tolua_LuaBindings_Sound_play00);
   tolua_function(tolua_S,"pause",tolua_LuaBindings_Sound_pause00);
   tolua_function(tolua_S,"stop",tolua_LuaBindings_Sound_stop00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Sprite","Sprite","",tolua_collect_Sprite);
  #else
  tolua_cclass(tolua_S,"Sprite","Sprite","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Sprite");
   tolua_function(tolua_S,"new",tolua_LuaBindings_Sprite_new00);
   tolua_function(tolua_S,"new_local",tolua_LuaBindings_Sprite_new00_local);
   tolua_function(tolua_S,".call",tolua_LuaBindings_Sprite_new00_local);
   tolua_variable(tolua_S,"x",tolua_get_Sprite_x,tolua_set_Sprite_x);
   tolua_variable(tolua_S,"y",tolua_get_Sprite_y,tolua_set_Sprite_y);
   tolua_variable(tolua_S,"red",tolua_get_Sprite_red,tolua_set_Sprite_red);
   tolua_variable(tolua_S,"green",tolua_get_Sprite_green,tolua_set_Sprite_green);
   tolua_variable(tolua_S,"blue",tolua_get_Sprite_blue,tolua_set_Sprite_blue);
   tolua_variable(tolua_S,"alpha",tolua_get_Sprite_alpha,tolua_set_Sprite_alpha);
   tolua_function(tolua_S,"getNumFrames",tolua_LuaBindings_Sprite_getNumFrames00);
   tolua_variable(tolua_S,"frame",tolua_get_Sprite_frame,tolua_set_Sprite_frame);
   tolua_function(tolua_S,"getWidth",tolua_LuaBindings_Sprite_getWidth00);
   tolua_function(tolua_S,"getHeight",tolua_LuaBindings_Sprite_getHeight00);
   tolua_function(tolua_S,"getHotSpot",tolua_LuaBindings_Sprite_getHotSpot00);
   tolua_function(tolua_S,"setHotSpot",tolua_LuaBindings_Sprite_setHotSpot00);
   tolua_variable(tolua_S,"angle",tolua_get_Sprite_angle,tolua_set_Sprite_angle);
   tolua_function(tolua_S,"getScale",tolua_LuaBindings_Sprite_getScale00);
   tolua_function(tolua_S,"setScale",tolua_LuaBindings_Sprite_setScale00);
   tolua_function(tolua_S,"isPointInside",tolua_LuaBindings_Sprite_isPointInside00);
   tolua_function(tolua_S,"draw",tolua_LuaBindings_Sprite_draw00);
   tolua_function(tolua_S,"draw",tolua_LuaBindings_Sprite_draw01);
   tolua_function(tolua_S,"draw",tolua_LuaBindings_Sprite_draw02);
   tolua_function(tolua_S,"draw",tolua_LuaBindings_Sprite_draw03);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaBindings (lua_State* tolua_S) {
 return tolua_LuaBindings_open(tolua_S);
};
#endif

