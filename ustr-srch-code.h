/* Copyright (c) 2007 James Antill -- See LICENSE file for terms. */

#ifndef USTR_SRCH_H
#error " Include ustr-srch.h before this file."
#endif

#ifndef USTR_CONF_HAVE_MEMMEM /* GNU extension */
#ifdef __GLIBC__
#define USTR_CONF_HAVE_MEMMEM 1
#else
#define USTR_CONF_HAVE_MEMMEM 0
#endif
#endif

#ifndef USTR_CONF_HAVE_MEMRCHR /* GNU extension */
#ifdef __GLIBC__
#define USTR_CONF_HAVE_MEMRCHR 1
#else
#define USTR_CONF_HAVE_MEMRCHR 0
#endif
#endif

USTR_CONF_I_PROTO size_t ustr_srch_chr_fwd(const struct Ustr *s1, char val)
{
  const char *cstr = ustr_cstr(s1);
  size_t len = ustr_len(s1);
  const char *tmp = memchr(cstr, val, len);

  USTR_ASSERT(ustr_assert_valid(s1));
  
  if (!tmp) return (0);

  len = tmp - cstr;
  return (len + 1);
}

#if USTR_CONF_HAVE_MEMRCHR /* GNU extension */
USTR_CONF_I_PROTO size_t ustr_srch_chr_rev(const struct Ustr *s1, char val)
{
  const char *cstr = ustr_cstr(s1);
  size_t len = ustr_len(s1);
  const char *tmp = memrchr(cstr, val, len);

  USTR_ASSERT(ustr_assert_valid(s1));
  
  if (!tmp) return (0);

  len = tmp - cstr;
  return (len + 1);
}
#else
USTR_CONF_I_PROTO size_t ustr_srch_chr_rev(const struct Ustr *s1, char val)
{ /* slow... */
  const char *cstr = ustr_cstr(s1);
  size_t len = ustr_len(s1);
  const char *tmp = cstr;
  const char *prev = 0;

  USTR_ASSERT(ustr_assert_valid(s1));
  
  while ((tmp = memchr(tmp, val, len - (tmp - cstr))))
  {
    prev = tmp;
    ++tmp;
  }
  
  if (!prev)
    return (0);

  len = prev - cstr;
  return (len + 1);
}
#endif

#if USTR_CONF_HAVE_MEMMEM /* GNU extension */
# define USTR__SYS_MEMMEM memmem
#else
USTR_CONF_E_PROTO void *ustr__sys_memmem(const void*, size_t,const void*,size_t)
    USTR__COMPILE_ATTR_WARN_UNUSED_RET() USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_I_PROTO void *ustr__sys_memmem(const void *hs, size_t hslen,
                                     const void *nd, size_t ndlen)
{
  const char *ptr;
  const char *end;

  if (ndlen == 0)
    return ((void *)hs);

  if (hslen < ndlen)
    return (0);

  end = ((const char *)hs) + hslen - ndlen;
  for (ptr = hs; ptr <= end; ++ptr)
    if (!memcmp(ptr, nd, ndlen))
      return ((void *)ptr);

  return (0);
}
# define USTR__SYS_MEMMEM ustr__sys_memmem
#endif

USTR_CONF_I_PROTO size_t ustr_srch_buf_fwd(const struct Ustr *s1,
                                           const void *val, size_t vlen)
{
  const char *cstr = ustr_cstr(s1);
  size_t len = ustr_len(s1);
  char *tmp = 0;

  USTR_ASSERT(ustr_assert_valid(s1));
  
  if (vlen == 1)
    return (ustr_srch_chr_fwd(s1, ((const char *)val)[0]));

  if (!(tmp = USTR__SYS_MEMMEM(cstr, len, val, vlen)))
    return (0);

  len = tmp - cstr;
  return (len + 1);
}

USTR_CONF_I_PROTO size_t ustr_srch_buf_rev(const struct Ustr *s1,
                                           const void *val, size_t vlen)
{
  const char *cstr = ustr_cstr(s1);
  size_t len = ustr_len(s1);
  const char *prev = 0;
  const char *tmp  = 0;

  USTR_ASSERT(ustr_assert_valid(s1));
  
  if (vlen == 0)
    return (len ? len : 1);
  if (vlen == 1)
    return (ustr_srch_chr_fwd(s1, ((const char *)val)[0]));

  tmp = cstr;
  while (((len - (tmp - cstr)) >= vlen) &&
         (tmp = USTR__SYS_MEMMEM(tmp, len - (tmp - cstr), val, vlen)))
  {
    prev = tmp;
    ++tmp;
  }
  if (!prev)
    return (0);

  len = prev - cstr;
  return (len + 1);
}
