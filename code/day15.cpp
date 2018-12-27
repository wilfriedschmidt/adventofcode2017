#include "days.h"
#include "util.h"

#include <memory.h>

void day15()
{
  printf("DAY 15\n");

  int iterations=40000000;

  uint64_t A=516;
  uint64_t B=190;

  int count=0;

  for(int i=0;i<iterations;i++)
  {
    A = A*16807 % 2147483647;
    B = B*48271 % 2147483647;

    if((A&0xffff) == (B&0xffff))
    {
      count++;
    }

    //printf("%" PRIu64 "\n", A);
    //printf("%" PRIu64 "\n\n", B);

    if(i%100000==0)
    {
      printf("processing %i\n", i);
    }
  }

  printf("%i\n", count);

}

void day15_2()
{
  printf("DAY 15.2\n");

  uint64_t A=516;
  uint64_t B=190;

  //uint64_t A=65;
  //uint64_t B=8921;

  int count=0;
  int iterations=5000000;

  for(int i=0;i<iterations;i++)
  {
    while(true)
    {
      A = A*16807 % 2147483647;
      if( A%4 == 0 )
      {
        break;
      }
    }

    while(true)
    {
      B = B*48271 % 2147483647;
      if( B%8 == 0 )
      {
        break;
      }
    }

    if((A&0xffff) == (B&0xffff))
    {
      count++;
    }

    //printf("%" PRIu64 "\n", A);
    //printf("%" PRIu64 "\n\n", B);

    if(i%100000==0)
    {
      printf("processing %i\n", i);
    }
  }

  printf("%i\n", count);

}
