/* Copyright (c) 2007 James Antill -- See LICENSE file for terms. */

#ifndef USTR_PARSE_H
#error " You should have already included ustr-parse.h, or just include ustr.h."
#endif

#if ! USTR_CONF_HAVE_STDINT_H
# define USTR__UMAX unsigned long
#else
# define USTR__UMAX uintmax_t
#endif

/* basically uses: [ ]*[-+](0b|0B|0o|0O|0x|0X|0)[0-9a-z_]+ */
USTR_CONF_e_PROTO
int ustr__parse_num_beg(const char **ptr, size_t *len,
                        unsigned int flags, int *tst_neg, int *tst_0,
                        unsigned int *ern)
    USTR__COMPILE_ATTR_WARN_UNUSED_RET() USTR__COMPILE_ATTR_NONNULL_A();
USTR_CONF_i_PROTO
int ustr__parse_num_beg(const char **ptr, size_t *len,
                        unsigned int flags, int *tst_neg, int *tst_0,
                        unsigned int *ern)
{
  unsigned int base = flags & USTR__MASK_PARSE_NUM_BASE;
  int auto_base = USTR_FALSE;

  if (!base)
    auto_base = USTR_TRUE;
  else if (base > 36)
    base = 36;
  else if (base == 1)
    ++base;

  if (flags & USTR_FLAG_PARSE_NUM_SPACE)
  {
    while (*len && (**ptr == ' '))
    {
      ++*ptr;
      --*len;
    }    

    if (!*len)
    {
      *ern = USTR_TYPE_PARSE_NUM_ERR_ONLY_S;
      return (0);
    }
  }

  if (!(flags & USTR_FLAG_PARSE_NUM_NO_BEG_PM))
  {
    switch (**ptr)
    {
      case '-':
        *tst_neg = USTR_TRUE;
      case '+':
        ++*ptr;
        --*len;
    }
    if (!*len)
    {
      *ern = USTR_TYPE_PARSE_NUM_ERR_ONLY_SPM;
      return (0);
    }
  }

  if (**ptr != '0')
  {
    if (base)
      return (base);
    return (10);
  }
  
  ++*ptr;
  --*len;
  
  if (!*len)
  {
    *tst_0 = USTR_TRUE;    
    return (10);
  }
  else if ((auto_base || (base ==  2)) && ((**ptr == 'b') || (**ptr == 'B')))
    base =  2;
  else if ((auto_base || (base ==  8)) && ((**ptr == 'o') || (**ptr == 'O')))
    base =  8;
  else if ((auto_base || (base == 16)) && ((**ptr == 'x') || (**ptr == 'X')))
    base = 16;
  else if ((flags & USTR_FLAG_PARSE_NUM_NO_BEG_ZERO) &&
           (!auto_base || (**ptr == '0')))
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_BEG_ZERO;
    return (0);
  }
  else
  {
    *tst_0 = USTR_TRUE;
    if (base)
      return (base);
    return (8);
  }
  
  ++*ptr;
  --*len;
  
  if (!*len)
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_ONLY_SPMX;
    return (0);
  }

  if ((flags & USTR_FLAG_PARSE_NUM_NO_BEG_ZERO) && (**ptr == '0') && (*len > 1))
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_BEG_ZERO;
    return (0);
  }

  return (base);
}
#if USTR_CONF_HAVE_STDINT_H
USTR_CONF_I_PROTO
#else
USTR_CONF_e_PROTO
USTR__UMAX ustr_parse_uintmaxx(const struct Ustr *, unsigned int,
                               USTR__UMAX, char, unsigned int *)
    USTR__COMPILE_ATTR_WARN_UNUSED_RET() USTR__COMPILE_ATTR_NONNULL_L((1));
USTR_CONF_i_PROTO
#endif
USTR__UMAX ustr_parse_uintmaxx(const struct Ustr *s1, unsigned int flags,
                               USTR__UMAX num_max, char sym_sep,
                               unsigned int *ern)
{
  static const char local_let_low[]  = "abcdefghijklmnopqrstuvwxyz";
  static const char local_let_high[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned int dummy_ern;
  unsigned int num_base = 0;
  int tst_neg   = USTR_FALSE;
  int tst_0     = USTR_FALSE;
  int done_once = USTR_FALSE;
  char num_end = '9';
  const char *ptr = ustr_cstr(s1);
  size_t      len = ustr_len(s1);
  USTR__UMAX ret = 0;

  USTR_ASSERT(ustr_assert_valid(s1));
  
  if (!ern) ern = &dummy_ern;
  *ern = USTR_TYPE_PARSE_NUM_ERR_NONE;
  
  if (!(num_base = ustr__parse_num_beg(&ptr,&len, flags, &tst_neg,&tst_0, ern)))
    return (0);

  if (tst_neg && (flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE))
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_NEGATIVE;
    return (0);
  }
  
  if (num_base < 10)
    num_end = '0' + num_base - 1;
  
  done_once = tst_0;
  while (len)
  {
    const char *end = 0;
    unsigned int add_num = 0;
    USTR__UMAX old_ret = ret;
      
    if (done_once && (*ptr == sym_sep))
    {
      if (!(flags & USTR_FLAG_PARSE_NUM_SEP)) break;
      ++ptr;
      --len;
      continue;
    }
    else
    {
      if ((*ptr >= '0') && (*ptr <= num_end))
        add_num = (*ptr - '0');
      else if (num_base <= 10)
        break;
      else if ((end = memchr(local_let_low,  *ptr, num_base - 10)))
        add_num = 10 + (end - local_let_low);
      else if ((end = memchr(local_let_high, *ptr, num_base - 10)))
        add_num = 10 + (end - local_let_high);
      else
        break;
    }
    
    ret = (ret * num_base) + add_num;
    if ((flags & USTR_FLAG_PARSE_NUM_OVERFLOW) &&
        (((ret - add_num) / num_base) != old_ret))
    {
      *ern = USTR_TYPE_PARSE_NUM_ERR_OVERFLOW;
      ret = num_max + tst_neg;
      break;
    }

    ++ptr;
    --len;
    done_once = USTR_TRUE;
  }

  if (!done_once)
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_OOB;
    return (0);
  }
  
  if (!*ern && (flags & USTR_FLAG_PARSE_NUM_EXACT) && len)
    *ern = USTR_TYPE_PARSE_NUM_ERR_OOB;

  /* assumes 2's compliment in that abs(lim) + 1 == abs(-lim) */
  if (!*ern && (flags & USTR_FLAG_PARSE_NUM_OVERFLOW) && ret &&
      ((ret - tst_neg) > num_max))
  {
    *ern = USTR_TYPE_PARSE_NUM_ERR_OVERFLOW;
    ret = num_max + tst_neg;
  }
  
  if (tst_neg)
    return (-ret);
  
  return (ret);
}

#if USTR_CONF_HAVE_STDINT_H
USTR_CONF_I_PROTO
uintmax_t ustr_parse_uintmax(const struct Ustr *s1, unsigned int flags,
                             unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  flags |= USTR_FLAG_PARSE_NUM_NO_NEGATIVE;
  return (ustr_parse_uintmaxx(s1, flags, UINTMAX_MAX, '_', ern));
}
USTR_CONF_I_PROTO
intmax_t ustr_parse_intmax(const struct Ustr *s1, unsigned int flags,
                           unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  return (ustr_parse_uintmaxx(s1, flags, INTMAX_MAX, '_', ern));
}
#endif

USTR_CONF_I_PROTO
unsigned long ustr_parse_ulongx(const struct Ustr *s1, unsigned int flags,
                                unsigned long num_max, char sym_sep,
                                unsigned int *ern)
{ return (ustr_parse_uintmaxx(s1, flags, num_max, sym_sep, ern)); }

USTR_CONF_I_PROTO
unsigned long ustr_parse_ulong(const struct Ustr *s1, unsigned int flags,
                               unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  flags |= USTR_FLAG_PARSE_NUM_NO_NEGATIVE;
  return (ustr_parse_uintmaxx(s1, flags, ULONG_MAX, '_', ern));
}
USTR_CONF_I_PROTO
long ustr_parse_long(const struct Ustr *s1, unsigned int flags,
                     unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  return (ustr_parse_uintmaxx(s1, flags, LONG_MAX, '_', ern));
}

USTR_CONF_I_PROTO
unsigned int ustr_parse_uint(const struct Ustr *s1, unsigned int flags,
                             unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  flags |= USTR_FLAG_PARSE_NUM_NO_NEGATIVE;
  return (ustr_parse_uintmaxx(s1, flags, UINT_MAX, '_', ern));
}
USTR_CONF_I_PROTO
int ustr_parse_int(const struct Ustr *s1, unsigned int flags,
                   unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  return (ustr_parse_uintmaxx(s1, flags, INT_MAX, '_', ern));
}

USTR_CONF_I_PROTO
unsigned short ustr_parse_ushort(const struct Ustr *s1, unsigned int flags,
                                 unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  flags |= USTR_FLAG_PARSE_NUM_NO_NEGATIVE;
  return (ustr_parse_uintmaxx(s1, flags, USHRT_MAX, '_', ern));
}
USTR_CONF_I_PROTO
short ustr_parse_short(const struct Ustr *s1, unsigned int flags,
                       unsigned int *ern)
{
  ustr_assert(!(flags & USTR_FLAG_PARSE_NUM_NO_NEGATIVE));
  return (ustr_parse_uintmaxx(s1, flags, SHRT_MAX, '_', ern));
}

/* void *ustr_parse_num(const struct Ustr *s1, unsigned int flags,
                        unsigned int *ern,
                        void *(*func)(unsigned int, int,unsigned int *, void *),
                        void *data)

  if (is_neg) add_num = -add_num;
  
  if (!(ret = func(num_base, add_num, err, ret)) && !*err)
    return (NULL);
*/
