#define USTR_CONF_INCLUDE_CODEONLY_HEADERS 1
#include "ustr-conf.h"
#define USTR_CONF_E_PROTO  extern
#define USTR_CONF_I_PROTO  extern inline
#define USTR_CONF_EI_PROTO extern
#define USTR_CONF_II_PROTO extern inline
#include "ustr-main.h"
#include "ustr-srch.h"
#undef  USTR_CONF_I_PROTO
#define USTR_CONF_I_PROTO  inline
#undef  USTR_CONF_II_PROTO
#define USTR_CONF_II_PROTO inline
#include "ustr-spn.h"
