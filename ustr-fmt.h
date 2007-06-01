/* Copyright (c) 2007 James Antill -- See LICENSE file for terms. */
#ifndef USTR_FMT_H
#define USTR_FMT_H 1

#ifndef USTR_MAIN_H
# error " You should include ustr-main.h before this file, or just ustr.h"
#endif

#include <stdarg.h> /* va_list for *printf like functionality */

#ifndef USTR_CONF_HAVE_VA_COPY
#if defined(__GNUC__) &&                                                \
    (__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96))
#define USTR_CONF_HAVE_VA_COPY 1
#else
#define USTR_CONF_HAVE_VA_COPY 0
#endif
#endif

#if USTR_CONF_HAVE_VA_COPY
USTR_CONF_E_PROTO
int ustr_add_vfmt_lim(struct Ustr **, size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(3, 0);
USTR_CONF_E_PROTO int ustr_add_vfmt(struct Ustr **, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 0);
USTR_CONF_E_PROTO struct Ustr *ustr_dupx_vfmt_lim(size_t, size_t, int, int,
                                                  size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(6, 0);
USTR_CONF_E_PROTO struct Ustr *ustr_dup_vfmt_lim(size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 0);
USTR_CONF_E_PROTO
struct Ustr *ustr_dupx_vfmt(size_t, size_t, int, int, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(5, 0);
USTR_CONF_E_PROTO struct Ustr *ustr_dup_vfmt(const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(1, 0);
# ifdef USTR_SET_H
USTR_CONF_E_PROTO
int ustr_set_vfmt_lim(struct Ustr **, size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(3, 0);
USTR_CONF_E_PROTO int ustr_set_vfmt(struct Ustr **, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 0);
# endif

USTR_CONF_E_PROTO
int ustrp_add_vfmt_lim(void *, struct Ustrp **, size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4)) USTR__COMPILE_ATTR_FMT(4, 0);
USTR_CONF_E_PROTO int ustrp_add_vfmt(void *,struct Ustrp **,const char*,va_list)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3)) USTR__COMPILE_ATTR_FMT(3, 0);
USTR_CONF_E_PROTO
struct Ustrp *ustrp_dupx_vfmt_lim(void *, size_t, size_t, int, int,
                                  size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((7)) USTR__COMPILE_ATTR_FMT(7, 0);
USTR_CONF_E_PROTO
struct Ustrp *ustrp_dup_vfmt_lim(void *, size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((3)) USTR__COMPILE_ATTR_FMT(3, 0);
USTR_CONF_E_PROTO struct Ustrp *ustrp_dupx_vfmt(void *, size_t, size_t, int,
                                                int, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((6)) USTR__COMPILE_ATTR_FMT(6, 0);
USTR_CONF_E_PROTO struct Ustrp *ustrp_dup_vfmt(void *, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((2)) USTR__COMPILE_ATTR_FMT(2, 0);
# ifdef USTR_SET_H
USTR_CONF_E_PROTO
int ustrp_set_vfmt_lim(void *, struct Ustrp **, size_t, const char *, va_list)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4)) USTR__COMPILE_ATTR_FMT(4, 0);
USTR_CONF_E_PROTO int ustrp_set_vfmt(void *,struct Ustrp **,const char*,va_list)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3)) USTR__COMPILE_ATTR_FMT(3, 0);
# endif

#endif

/* even without va_copy, we can still do *_fmt using lots of copy and paste */
USTR_CONF_E_PROTO int ustr_add_fmt(struct Ustr **, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 3);
USTR_CONF_E_PROTO int ustr_add_fmt_lim(struct Ustr **, size_t,const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(3, 4);
USTR_CONF_E_PROTO struct Ustr *ustr_dupx_fmt_lim(size_t, size_t, int, int,
                                                 size_t, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(6, 7);
USTR_CONF_E_PROTO struct Ustr *ustr_dup_fmt_lim(size_t, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 3);
USTR_CONF_E_PROTO
struct Ustr *ustr_dupx_fmt(size_t, size_t, int, int, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(5, 6);
USTR_CONF_E_PROTO struct Ustr *ustr_dup_fmt(const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(1, 2);
#ifdef USTR_SET_H
USTR_CONF_E_PROTO int ustr_set_fmt_lim(struct Ustr **, size_t,const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(3, 4);
USTR_CONF_E_PROTO int ustr_set_fmt(struct Ustr **, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_A() USTR__COMPILE_ATTR_FMT(2, 3);
#endif

USTR_CONF_E_PROTO int ustrp_add_fmt(void *, struct Ustrp **, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3)) USTR__COMPILE_ATTR_FMT(3, 4);
USTR_CONF_E_PROTO
int ustrp_add_fmt_lim(void *, struct Ustrp **, size_t, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4)) USTR__COMPILE_ATTR_FMT(4, 5);
USTR_CONF_E_PROTO struct Ustrp *ustrp_dupx_fmt_lim(void *, size_t, size_t, int,
                                                  int, size_t,const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((7)) USTR__COMPILE_ATTR_FMT(7, 8);
USTR_CONF_E_PROTO struct Ustrp *ustrp_dup_fmt_lim(void*,size_t,const char*, ...)
    USTR__COMPILE_ATTR_NONNULL_L((3)) USTR__COMPILE_ATTR_FMT(3, 4);
USTR_CONF_E_PROTO
struct Ustrp *ustrp_dupx_fmt(void *, size_t,size_t, int, int, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((6)) USTR__COMPILE_ATTR_FMT(6, 7);
USTR_CONF_E_PROTO struct Ustrp *ustrp_dup_fmt(void *, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((2)) USTR__COMPILE_ATTR_FMT(2, 3);
#ifdef USTR_SET_H
USTR_CONF_E_PROTO
int ustrp_set_fmt_lim(void *, struct Ustrp **, size_t, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((2, 4)) USTR__COMPILE_ATTR_FMT(4, 5);
USTR_CONF_E_PROTO int ustrp_set_fmt(void *, struct Ustrp **, const char *, ...)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3)) USTR__COMPILE_ATTR_FMT(3, 4);
#endif

#if USTR_CONF_INCLUDE_CODEONLY_HEADERS
# include "ustr-fmt-code.h"
#endif

#endif
