//
#if defined(__INTEL_COMPILER)
#include <mkl.h> // intel math kernel library
#else
#include <cblas.h> //BLAS library, input type: double
#endif

//
#include "types.h"

//Baseline - naive implementation
void dgemm_ijk(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n)
{
  for (u64 i = 0; i < n; i++)
    for (u64 j = 0; j < n; j++)
      for (u64 k = 0; k < n; k++)
	c[i * n + j] += a[i * n + k] * b[k * n + j];
}

//First optimization (loop interchange) 
//memory access optimized
void dgemm_ikj(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n)
{
  for (u64 i = 0; i < n; i++)
    for (u64 k = 0; k < n; k++)
      for (u64 j = 0; j < n; j++)
	c[i * n + j] += a[i * n + k] * b[k * n + j];
}

//Second optimization (loop interchange + invariant extraction) 
//intermediate expression, less memory accesses
void dgemm_iex(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n)
{
  for (u64 i = 0; i < n; i++)
    {
      for (u64 k = 0; k < n; k++)
	{
	  const f64 _a_ = a[i * n + k];
	  
	  for (u64 j = 0; j < n; j++)
	    c[i * n + j] +=  _a_ * b[k * n + j];
	}
    }
}

//loop unrolling : 4 results returned in each iteration
void dgemm_unroll4(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n)
{

#define UNROLL4 4
  
  for (u64 i = 0; i < n; i++)
    {
      for (u64 k = 0; k < n; k++)
	{
	  const f64 _a_ = a[i * n + k];

	  //Unroll 4 times
	  for (u64 j = 0; j < (n - (n & (UNROLL4 - 1))); j += UNROLL4)
	    {
	      c[i * n + j]     +=  _a_ * b[k * n + j];
	      c[i * n + j + 1] +=  _a_ * b[k * n + j + 1];
	      c[i * n + j + 2] +=  _a_ * b[k * n + j + 2];
	      c[i * n + j + 3] +=  _a_ * b[k * n + j + 3];
	    }

	  //Manage the leftovers
	  for (u64 j = (n - (n & 3)); j < n; j++)
	    c[i * n + j]     +=  _a_ * b[k * n + j];
	}
    }
}

//loop unrolling : 8 results returned in each iteration
void dgemm_unroll8(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n) 
{
    #define UNROLL8 8

    for (u64 i = 0; i < n; i++) {
        for (u64 k = 0; k < n; k++) {
            const f64 _a_ = a[i * n + k];

            // Unroll 8 times
            for (u64 j = 0; j < (n - (n % UNROLL8)); j += UNROLL8) 
			{
                c[i * n + j]     += _a_ * b[k * n + j];
                c[i * n + j + 1] += _a_ * b[k * n + j + 1];
                c[i * n + j + 2] += _a_ * b[k * n + j + 2];
                c[i * n + j + 3] += _a_ * b[k * n + j + 3];
                c[i * n + j + 4] += _a_ * b[k * n + j + 4];
                c[i * n + j + 5] += _a_ * b[k * n + j + 5];
                c[i * n + j + 6] += _a_ * b[k * n + j + 6];
                c[i * n + j + 7] += _a_ * b[k * n + j + 7];
            }

            // Manage the leftovers
            for (u64 j = (n - (n % UNROLL8)); j < n; j++) {
                c[i * n + j] += _a_ * b[k * n + j];
            }
        }
    }
}


//high performance function from CBLAS library
void dgemm_cblas(f64 *restrict a, f64 *restrict b, f64 *restrict c, u64 n)
{
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, a, n, b, n, 0.0, c, n);
}
