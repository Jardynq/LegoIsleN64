#ifndef MXDEBUG_H
#define MXDEBUG_H


#ifdef _DEBUG

// In debug mode, replace the macro with the function call.
#define MxTrace _MxTrace

void _MxTrace(const char* format, ...);
int DebugHeapState();

#else

// If not debug, MxTrace is a no-op.
// Use variadic args for macro (C99)
#define MxTrace(...)

#endif // _DEBUG

#endif // MXDEBUG_H
