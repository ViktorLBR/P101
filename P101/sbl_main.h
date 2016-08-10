#include "stdafx.h"

namespace sbl {};
using namespace sbl;

#ifndef SBL_MAIN
#define SBL_MAIN

extern "C"
{
#include "lua.hpp"
}
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <string>
#include <vector>
#include <iostream>
#include <map>

lua_State * getEnv();

#pragma comment(lib, "lua53.lib")


typedef long unsigned int sblAdr;
typedef int (flua)(lua_State *);

#include "sbl_element.h"

typedef sblElement * pElement;

typedef pair<string, pElement> mappSpElement;
typedef pair<sblAdr, pElement> mappNadrElement;


#include "sbl_env.h"
#include "sbl_hub.h"

extern sblHub * hub_lua;

#include "sbl_interface_hub.h"
#endif
