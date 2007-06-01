#include "tst.h"

int tst(void)
{
  char buf_s3[1024];
  Ustr *s3 = USTR(buf_s3);
  char buf_s4[15 + sizeof(USTR_END_FIXEDx)] = "x123456abcd";
  Ustr *s4 = USTR_SC_INIT_AUTO(buf_s4, USTR_TRUE, 4);

  memset(buf_s3, 'x', sizeof(buf_s3));
  
  ASSERT(!ustr_init_size(1, 0, 0, USTR__SIZE_MAX));
  if (USTR_CONF_HAVE_64bit_SIZE_MAX)
  ASSERT( ustr_init_size(0, 8, 1, 0));
  
  ASSERT(!ustr_init_fixed(buf_s3, 1, USTR_TRUE, 0));
  ASSERT(!ustr_init_fixed(buf_s3, 2, USTR_TRUE, 0));
  ASSERT(!ustr_init_fixed(buf_s3, 4, USTR_TRUE, 0));
  ASSERT(!ustr_init_fixed(buf_s3, 7, USTR_TRUE, 0));
  if (sizeof(USTR_END_FIXEDx) == 1)
  ASSERT(s3 == ustr_init_fixed(buf_s3, 8, USTR_TRUE, 0));
  
  memset(buf_s3, 'x', sizeof(buf_s3));
  
  ASSERT(s3 == ustr_init_fixed(buf_s3, sizeof(buf_s3), USTR_FALSE, 0));
  ASSERT(s4 == USTR(buf_s4));
  ASSERT(!ustr_limited(s3));
  ASSERT( ustr_limited(s4));

  ASSERT(ustr_size(s3) == (sizeof(buf_s3) - ustr_overhead(s3)));
  ASSERT(ustr_size(s4) == (sizeof(buf_s4) - ustr_overhead(s4)));

  ASSERT(ustr_len(s3) == 0);
  ASSERT(ustr_len(s4) == 4);
  ASSERT(ustr_cmp_eq(s3, USTR1(\x0, "")));
  ASSERT(ustr_cmp_eq(s4, USTR1(\x4, "abcd")));

  ASSERT(!ustr_add_rep_chr(&s4, 'Z', 32));
  ASSERT( ustr_enomem(s4));
  ASSERT( ustr_add(&s4, s2));
  ASSERT(s4 == USTR(buf_s4));
  ASSERT(ustr_len(s4) == 6);
  ASSERT(ustr_cmp_eq(s4, USTR1(\x6, "abcds2")));

  ASSERT( ustr_add(&s3, s2));
  ASSERT(s3 == USTR(buf_s3));
  ASSERT(ustr_len(s3) == 2);
  ASSERT(ustr_cmp_eq(s3, s2));
  ASSERT( ustr_set(&s3, s2));
  ASSERT(s3 == USTR(buf_s3));
  ASSERT(ustr_len(s3) == 2);
  ASSERT(ustr_cmp_eq(s3, s2));
  
  ASSERT(s4 == USTR(buf_s4));
  
  ustr_free(s3);
  /* don't bother free'ing s4 */
  
  return (EXIT_SUCCESS);
}
