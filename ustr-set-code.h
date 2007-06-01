/* Copyright (c) 2007 James Antill -- See LICENSE file for terms. */

#ifndef USTR_SET_H
#error " You should have already included ustr-set.h, or just include ustr.h."
#endif

/* copy and paste from ustr-main-code.h */
#if 0
#define USTR__EXACT_BYTES(x) (!((x)->data[0] &  0x80))

#define USTR__DUPX_DEF       USTR_CONF_REF_BYTES, USTR_CONF_EXACT_BYTES, 0
#define USTR__DUPX_FROM(x)   USTR__REF_LEN(x), USTR__EXACT_BYTES(x), ustr_enomem(x)
#endif

USTR_CONF_e_PROTO int ustrp__set_undef(void *p, struct Ustr **ps1, size_t nlen)
    USTR__COMPILE_ATTR_NONNULL_L((2));
USTR_CONF_i_PROTO int ustrp__set_undef(void *p, struct Ustr **ps1, size_t nlen)
{
  struct Ustr *s1  = USTR_NULL;
  struct Ustr *ret = USTR_NULL;
  size_t clen = 0;
  size_t sz  = 0;
  size_t oh  = 0;
  size_t osz = 0;
  size_t nsz = 0;
  int alloc = USTR_FALSE;
  
  USTR_ASSERT(ps1 && ustr_assert_valid(*ps1));

  s1 = *ps1;
  clen = ustr_len(s1);
  if ((nlen == clen) && ustr_owner(s1))
    return (USTR_TRUE);
  else if (nlen > clen)
  {
    if (ustr__rw_add(s1, nlen, &sz, &oh, &osz, &nsz, &alloc))
      return (ustrp__add_undef(p, ps1, (nlen - clen)));
  }
  else
    if (ustr__rw_del(s1, nlen, &sz, &oh, &osz, &nsz, &alloc))
      return (ustrp__del(p, ps1, (clen - nlen)));
  
  if (ustr_limited(s1))
  {
    ustr_set_enomem_err(s1);
    return (USTR_FALSE);
  }

  if (!ustr_alloc(s1))
    ret = ustrp__dupx_undef(p, USTR__DUPX_DEF, nlen);
  else
    ret = ustrp__dupx_undef(p, USTR__DUPX_FROM(s1), nlen);
  
  if (!ret)
    return (USTR_FALSE);
  
  ustrp__sc_free2(p, ps1, ret);
  
  return (USTR_TRUE);
}
USTR_CONF_I_PROTO int ustr_set_undef(struct Ustr **ps1, size_t nlen)
{ return (ustrp__set_undef(0, ps1, nlen)); }
USTR_CONF_I_PROTO int ustrp_set_undef(void *p, struct Ustrp **ps1, size_t nlen)
{ return (ustrp__set_undef(p, USTR__PPTR(ps1), nlen)); }

USTR_CONF_e_PROTO
int ustrp__set_buf(void *p, struct Ustr **ps1, const void *buf, size_t len)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3));
USTR_CONF_i_PROTO
int ustrp__set_buf(void *p, struct Ustr **ps1, const void *buf, size_t len)
{
  USTR_ASSERT(ps1 && ustr_assert_valid(*ps1));

  if (!ustrp__set_undef(p, ps1, len))
    return (USTR_FALSE);
  
  ustr__memcpy(*ps1, 0, buf, len);

  USTR_ASSERT(ustr_assert_valid(*ps1));
  return (USTR_TRUE);
}
USTR_CONF_I_PROTO
int ustr_set_buf(struct Ustr **ps1, const void *buf, size_t len)
{ return (ustrp__set_buf(0, ps1, buf, len)); }
USTR_CONF_I_PROTO
int ustrp_set_buf(void *p, struct Ustrp **ps1, const void *buf, size_t len)
{ return (ustrp__set_buf(p, USTR__PPTR(ps1), buf, len)); }

USTR_CONF_e_PROTO int ustrp__set(void *p,struct Ustr **ps1,const struct Ustr*s2)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3));
USTR_CONF_i_PROTO int ustrp__set(void *p,struct Ustr **ps1,const struct Ustr*s2)
{
  struct Ustr *ret = USTR_NULL;
  
  USTR_ASSERT(ps1 && ustr_assert_valid(*ps1) && ustr_assert_valid(s2));

  if (*ps1 == s2)
    return (USTR_TRUE);
  
  if (ustr__treat_as_buf(*ps1, 0, s2, ustr_len(s2)))
    return (ustrp__set_buf(p, ps1, ustr_cstr(s2), ustr_len(s2)));

  if (!ustr_alloc(*ps1))
    ret = ustrp__dup(p, s2);
  else 
    ret = ustrp__dupx(p, USTR__DUPX_FROM(*ps1), s2);
  
  if (!ret)
    return (USTR_FALSE);
  
  ustrp__sc_free2(p, ps1, ret);
  
  return (USTR_TRUE);
}
USTR_CONF_I_PROTO int ustr_set(struct Ustr **ps1, const struct Ustr *s2)
{ return (ustrp__set(0, ps1, s2)); }
USTR_CONF_I_PROTO int ustrp_set(void *p,struct Ustrp**ps1,const struct Ustrp*s2)
{ return (ustrp__set(p, USTR__PPTR(ps1), &s2->s)); }

USTR_CONF_e_PROTO
int ustrp__set_subustr(void *p, struct Ustr **ps1, const struct Ustr *s2,
                       size_t pos, size_t len)
    USTR__COMPILE_ATTR_NONNULL_L((2, 3));
USTR_CONF_i_PROTO
int ustrp__set_subustr(void *p, struct Ustr **ps1, const struct Ustr *s2,
                       size_t pos, size_t len)
{
  size_t clen = 0;
  
  USTR_ASSERT(ps1 && ustr_assert_valid(*ps1));

  clen = ustr__valid_subustr(s2, pos, len);
  if (!clen)
    return (USTR_FALSE);
  if (len == clen)
    return (ustrp__set(p, ps1, s2));
  
  if (*ps1 != s2)
    return (ustrp__set_buf(p, ps1, ustr_cstr(s2) + pos, len));

  if (ustr_owner(s2))
  {
    --pos;
    ustrp__del(p, ps1, clen - (pos + len)); /* delete bit after */
    ustrp__del_subustr(p, ps1, 1, pos);     /* delete bit before */
  }
  else
  {
    struct Ustr *ret = ustrp__dup_subustr(p, s2, pos, len);

    if (!ret)
      return (USTR_FALSE);

    ustrp__sc_free2(p, ps1, ret);
  }
  
  return (USTR_TRUE);
}
USTR_CONF_I_PROTO int ustr_set_subustr(struct Ustr **ps1, const struct Ustr *s2,
                                       size_t pos, size_t len)
{ return (ustrp__set_subustr(0, ps1, s2, pos, len)); }
USTR_CONF_I_PROTO
int ustrp_set_subustrp(void *p, struct Ustrp **ps1, const struct Ustrp *s2,
                       size_t pos, size_t len)
{ return (ustrp__set_subustr(p, USTR__PPTR(ps1), &s2->s, pos, len)); }

USTR_CONF_e_PROTO
int ustrp__set_rep_chr(void *p, struct Ustr **ps1, char chr, size_t len)
    USTR__COMPILE_ATTR_NONNULL_L((2));
USTR_CONF_i_PROTO
int ustrp__set_rep_chr(void *p, struct Ustr **ps1, char chr, size_t len)
{
  USTR_ASSERT(ps1 && ustr_assert_valid(*ps1));

  if (!ustrp__set_undef(p, ps1, len))
    return (USTR_FALSE);

  ustr__memset(*ps1, 0, chr, len);

  USTR_ASSERT(ustr_assert_valid(*ps1));
  return (USTR_TRUE);
}
USTR_CONF_I_PROTO
int ustr_set_rep_chr(struct Ustr **ps1, char chr, size_t len)
{ return (ustrp__set_rep_chr(0, ps1, chr, len)); }
USTR_CONF_I_PROTO
int ustrp_set_rep_chr(void *p, struct Ustrp **ps1, char chr, size_t len)
{ return (ustrp__set_rep_chr(p, USTR__PPTR(ps1), chr, len)); }
