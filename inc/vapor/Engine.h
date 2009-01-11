/************************************************************************
*
* vaporEngine by triton � (2008-2009)
*
*	<http://www.portugal-a-programar.org/
*
************************************************************************/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Compile-time options
/////////////////////////////////////////////////////////////////////////////

#include "vapor/CompileOptions.h"

/////////////////////////////////////////////////////////////////////////////
// Platform-dependent stuff
/////////////////////////////////////////////////////////////////////////////

#include "vapor/Platform.h"

/////////////////////////////////////////////////////////////////////////////
// Logging macros
/////////////////////////////////////////////////////////////////////////////

#include "vapor/log/Log.h"
using namespace vapor::log;

#define info	Log::getLogger()->info
#define warn	Log::getLogger()->warn
#define error	Log::getLogger()->error