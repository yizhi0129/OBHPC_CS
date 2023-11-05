//
#if defined(__INTEL_COMPILER)
#include <mkl.h>
#else
#include <cblas.h>
#endif

//
#include "types.h"

//Baseline - naive implementation
//sum of all elements in array a
f64 reduc_base(f64 *restrict a, u64 n)
{
  f64 d = 0.0;
  
  for (u64 i = 0; i < n; i++)
    d += a[i];

  return d;
}

//Unrolling by 4
f64 reduc_unroll4(f64 *restrict a, u64 n)
{
  #define UNROLL4 4

  f64 d1 = 0.0;
  f64 d2 = 0.0;
  f64 d3 = 0.0;
  f64 d4 = 0.0;

  for (u64 i = 0; i < (n - (n & (UNROLL4 - 1))); i += UNROLL4)
    {
      d1 += a[i + 0];
      d2 += a[i + 1];
      d3 += a[i + 2];
      d4 += a[i + 3];
    } 

  for (u64 i = (n - (n & (UNROLL4 - 1))); i < n; i++)
    d1 += a[i];

  return d1 + d2 + d3 + d4;  
}


//Unrolling by 8
f64 reduc_unroll8(f64 *restrict a, u64 n)
{
  #define UNROLL8 8

  u64 d1 = 0.0;
  u64 d2 = 0.0;
  u64 d3 = 0.0;
  u64 d4 = 0.0;
  u64 d5 = 0.0;
  u64 d6 = 0.0;
  u64 d7 = 0.0;
  u64 d8 = 0.0;

  for (u64 i = 0; i < (n - (n & (UNROLL8 - 1))); i += UNROLL8)
    {
      d1 += a[i + 0];
      d2 += a[i + 1];
      d3 += a[i + 2];
      d4 += a[i + 3];
      d5 += a[i + 4];
      d6 += a[i + 5];
      d7 += a[i + 6];
      d8 += a[i + 7];
    } 

  for (u64 i = (n - (n & (UNROLL8 - 1))); i < n; i++)
    d1 += a[i];

  return d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8;  
}

//CBLAS library
f64 reduc_cblas(f64 *restrict a, u64 n)
{
  return cblas_dasum(n, a, 1);
}