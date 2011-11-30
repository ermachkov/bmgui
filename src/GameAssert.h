#ifndef GAME_ASSERT_H
#define GAME_ASSERT_H

#include "Exception.h"

#define QUOTE(x) #x
#define QUOTE_LINE(x) QUOTE(x)
#define GAME_ASSERT(cond) { if (!(cond)) throw Exception("Assertion '" #cond "' failed in file: '" __FILE__ "', line: " QUOTE_LINE(__LINE__)); }

#endif
