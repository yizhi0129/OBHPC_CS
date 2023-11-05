//
#if defined(__INTEL_COMPILER)
#include <mkl.h>
#else
#include <cblas.h>
#endif

#include <stdio.h>
//
#include "types.h"

//Baseline - naive implementation
//dot product of two vectors
f64 dotprod_base(f64 *restrict a, f64 *restrict b, u64 n)
{
  double d = 0.0;
  
  for (u64 i = 0; i < n; i++)
    d += a[i] * b[i];

  return d;
}

//optimization 1: loop unrolling by 4
f64 dotprod_unroll4(f64 *restrict a, f64 *restrict b, u64 n)
{
  #define UNROLL4 4

  f64 d1 = 0.0;
  f64 d2 = 0.0;
  f64 d3 = 0.0;
  f64 d4 = 0.0;

  //Unroll 4 times
  for (u64 i = 0; i < (n - (n & (UNROLL4 - 1))); i += UNROLL4)
  {
    d1 += a[i] * b[i];
    d2 += a[i + 1] * b[i + 1];
    d3 += a[i + 2] * b[i + 2];
    d4 += a[i + 3] * b[i + 3];
  }

  //Manage the leftovers
  for (u64 i = (n - (n & 3)); i < n; i++)
    {
        d1 += a[i] * b[i];
    }

  return d1 + d2 + d3 + d4;
}

//optimization 2: loop unrolling by 8
f64 dotprod_unroll8(f64 *restrict a, f64 *restrict b, u64 n)
{
  #define UNROLL8 8

  f64 d1 = 0.0;
  f64 d2 = 0.0;
  f64 d3 = 0.0;
  f64 d4 = 0.0;
  f64 d5 = 0.0;
  f64 d6 = 0.0;
  f64 d7 = 0.0;
  f64 d8 = 0.0;

  //Unroll 8 times
  for (u64 i = 0; i < (n - (n & (UNROLL8 - 1))); i += UNROLL8)
  {
    d1 += a[i] * b[i];
    d2 += a[i + 1] * b[i + 1];
    d3 += a[i + 2] * b[i + 2];
    d4 += a[i + 3] * b[i + 3];
    d5 += a[i + 4] * b[i + 4];
    d6 += a[i + 5] * b[i + 5];
    d7 += a[i + 6] * b[i + 6];
    d8 += a[i + 7] * b[i + 7];
  }


  //Manage the leftovers
  for (u64 i = (n - (n % UNROLL8)); i < n; i++)
  {
    d1 += a[i] * b[i];
  }

  return d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8;
}

//high performance function from CBLAS library
f64 dotprod_cblas(f64 *restrict a, f64 *restrict b, u64 n)
{
  return cblas_ddot(n, a, 1, b, 1); 
}