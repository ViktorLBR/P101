// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
extern "C" {
#include "lua.hpp"
}
#include "lunar.h"

#define GLEW_STATIC
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "lua53.lib")

#define method(class, name) {#name, &class::name}

#include "sbl_main.h"

#include "bloc.h"

#include "map.h"

// TODO: reference additional headers your program requires here
