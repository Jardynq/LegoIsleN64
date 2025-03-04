#ifndef DEBUG_H
#define DEBUG_H

#if true
#define debug(a) ;
#else
#define debug(a) printf(a)
#endif

#endif // DEBUG_H