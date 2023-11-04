
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//
#include "types.h"

//print a n*n matrix, type double
void print_f64(f64 *restrict a, u64 n)
{
  for (u64 i = 0; i < n * n; i++)
  {
    printf("%lf%c", a[i], ((i + 1) % n) ? ' ' : '\n');
  }
  printf("\n");
}

//fill the matrix with random values, zeros, or constant values
void init_f64(f64 *restrict a, u64 n, const ascii m)
{
  //Random value per entry
  if (m == 'r' || m == 'R')
    {
      for (u64 i = 0; i < n * n; i++)
      {
	      a[i] = (f64)RAND_MAX / (f64)rand();
      }
    }

  //Zeroing up the array
  else 
    if (m == 'z' || m == 'Z')
      {
	      for (u64 i = 0; i < n * n; i++)
        {
	        a[i] = 0.0;
        }
      }

  //Same value per entry
  else 
    if (m == 'c' || m == 'C')
	    {
	      f64 c = (f64)RAND_MAX / (f64)rand();
	  
	      for (u64 i = 0; i < n * n; i++)
        {
	        a[i] = c;
        }
	    }
}

//sort ascending
void sort_f64(f64 *restrict a, u64 n)
{
  for (u64 i = 0; i < n; i++)
    for (u64 j = i + 1; j < n; j++)
      if (a[i] > a[j])
	{
	  f64 tmp = a[i];

	  a[i] = a[j];
	  a[j] = tmp;
	}
}

//calculate mean value 
f64 mean_f64(f64 *restrict a, u64 n)
{
  f64 m = 0.0;

  for (u64 i = 0; i < n; i++)
    m += a[i];

  m /= (f64)n;

  return m;
}

//standard deviation
f64 stddev_f64(f64 *restrict a, u64 n)
{
  f64 d = 0.0;
  f64 m = mean_f64(a, n);

  for (u64 i = 0; i < n; i++)
    d += (a[i] - m) * (a[i] - m);

  d /= (f64)(n - 1);
  
  return sqrt(d);
}
