#include "days.h"
#include "util.h"

int64_t gridget(int x, int y, int dim, const std::vector<int64_t> &grid)
{
  if(x>=dim || x<0 || y>=dim || y<0) return 0;
  return grid[y*dim+x];
}

void gridset(int x, int y, int dim, int64_t value, std::vector<int64_t> &grid)
{
  if(x>=dim || x<0 || y>=dim || y<0)
    printf("ERROR tried to write to %i %i\n", x,y);

  if(value>312051)
  {
    printf("next value %i\n", value);
  }

  grid[y*dim+x] = value;
}

int64_t gridsum(int x,int y, int dim, const std::vector<int64_t> &grid)
{
  int64_t sum=0;

  sum+=gridget(x+1,y,dim,grid);
  sum+=gridget(x+1,y+1,dim,grid);
  sum+=gridget(x,y+1,dim,grid);
  sum+=gridget(x-1,y+1,dim,grid);
  sum+=gridget(x-1,y,dim,grid);
  sum+=gridget(x-1,y-1,dim,grid);
  sum+=gridget(x,y-1,dim,grid);
  sum+=gridget(x+1,y-1,dim,grid);

  return sum;
}

void day3()
{
  printf("DAY 3\n");

  int ringwidth=1;
  int ringsize=1;
  int index=1;

  for(int i=0;i<1024;i++)
  {
    int llc = index - ringwidth+1;
    int tlc = llc - ringwidth+1;
    int trc = tlc - ringwidth+1;
    printf("width %i size %i lrc %i llc %i tlc %i trc %i\n", ringwidth, ringsize, index, llc, tlc, trc);

    if( i==2 )
    {
      int xdist = abs(((index + llc)/2) - 23);
      printf("%i %i %i \n", xdist , (ringwidth - 1)/2, xdist + (ringwidth-1)/2 );
      //break;
    }

    if( 312051 < index )
    {
      int xdist = abs(((index + llc)/2) - 312051);
      printf("%i %i %i \n", xdist , (ringwidth - 1)/2, xdist + (ringwidth-1)/2 );
      break;
    }

    ringwidth = ringwidth+2;
    ringsize = ringwidth*4 - 4;
    index+=ringsize;
  }

  int gridsize=559;

  std::vector<int64_t> grid;

  grid.resize(gridsize*gridsize);
  for(int i=0;i<gridsize*gridsize;i++)
  {
    grid[i] = 0;
  }

  int x = gridsize/2;
  int y = gridsize/2;
  gridset(x,y,gridsize,1,grid);

  ringwidth=1;
  ringsize=1;
  index=1;

  x++;

  while(ringwidth <= gridsize)
  {
    int llc = index - ringwidth+1;
    int tlc = llc - ringwidth+1;
    int trc = tlc - ringwidth+1;
    printf("width %i size %i lrc %i llc %i tlc %i trc %i\n", ringwidth, ringsize, index, llc, tlc, trc);

    if(index>1)
    {
      for(int j=0;j<ringwidth-1;j++)
      {
        gridset(x,y,gridsize, gridsum(x,y,gridsize,grid), grid);
        y--;
      }

      y++;
      for(int j=0;j<ringwidth-1;j++)
      {
        gridset(x,y,gridsize, gridsum(x,y,gridsize,grid), grid);
        x--;
      }

      for(int j=0;j<ringwidth-1;j++)
      {
        gridset(x,y,gridsize, gridsum(x,y,gridsize,grid), grid);
        y++;
      }

      for(int j=0;j<ringwidth;j++)
      {
        gridset(x,y,gridsize, gridsum(x,y,gridsize,grid), grid);
        x++;
      }
    }

    ringwidth = ringwidth+2;
    ringsize = ringwidth*4 - 4;
    index+=ringsize;
  }


  /*for(int i=0;i<gridsize;i++)
  {
    for(int j=0;j<gridsize;j++)
    {
      printf("%i\t",grid[i*gridsize+j]);
    }
    printf("\n");
  }*/
}
