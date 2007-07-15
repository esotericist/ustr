/* Copyright (c) 2007 Paul Rosenfeld
                      James Antill -- See LICENSE file for terms. */
#ifndef USTR_INS_H
#define USTR_INS_H 1

#ifndef USTR_MAIN_H
# error " You should include ustr-main.h before this file, or just ustr.h"
#endif

USTR_CONF_E_PROTO int ustr_ins_undef(struct Ustr **, size_t, size_t)
    USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_E_PROTO int ustr_ins_buf(struct Ustr **, size_t, const void *, size_t)
    USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_E_PROTO int ustr_ins(struct Ustr **, size_t, const struct Ustr *)
    USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_EI_PROTO int ustr_ins_cstr(struct Ustr **, size_t, const char *)
    USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_E_PROTO
int ustr_ins_subustr(struct Ustr **, size_t, const struct Ustr *, size_t,size_t)
    USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_E_PROTO int ustr_ins_rep_chr(struct Ustr **, size_t, char, size_t)
    USTR__COMPILE_ATTR_NONNULL_A();

/* FIXME: ustr_ins_fmt*() */

USTR_CONF_E_PROTO
int ustrp_ins_undef(struct Ustr_pool *, struct Ustrp **, size_t, size_t)
    USTR__COMPILE_ATTR_NONNULL_L((2));
USTR_CONF_E_PROTO int ustrp_ins_buf(struct Ustr_pool *, struct Ustrp **, size_t,
                                    const void *, size_t)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4));
USTR_CONF_E_PROTO
int ustrp_ins(struct Ustr_pool *, struct Ustrp **, size_t, const struct Ustrp *)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4));
USTR_CONF_EI_PROTO
int ustrp_ins_cstr(struct Ustr_pool *, struct Ustrp **, size_t, const char *)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4));
USTR_CONF_E_PROTO
int ustrp_ins_subustrp(struct Ustr_pool *, struct Ustrp **, size_t,
                       const struct Ustrp *, size_t, size_t)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4));
USTR_CONF_E_PROTO
int ustrp_ins_rep_chr(struct Ustr_pool *, struct Ustrp **, size_t, char, size_t)
    USTR__COMPILE_ATTR_NONNULL_L((2));

#if USTR_CONF_INCLUDE_INTERNAL_HEADERS
# include "ustr-ins-internal.h"
#endif

#if USTR_CONF_INCLUDE_CODEONLY_HEADERS
# include "ustr-ins-code.h"
#endif

#if USTR_CONF_COMPILE_USE_INLINE
USTR_CONF_II_PROTO int ustr_ins_cstr(struct Ustr **s1, size_t p, const char *c) 
{ return (ustr_ins_buf(s1, p, c, strlen(c))); }
USTR_CONF_II_PROTO int
ustrp_ins_cstr(struct Ustr_pool *x, struct Ustrp **s1, size_t p, const char *c)
{ return (ustrp_ins_buf(x, s1, p, c, strlen(c))); }
#endif


#endif