/* This might be Linux/GLibc specific */
#include <bits/wordsize.h>

#if __WORDSIZE == 32
#include <ustr-conf-32.h>
#elif __WORDSIZE == 64
#include <ustr-conf-64.h>
#else
#error "Unknown word size"
#endif
