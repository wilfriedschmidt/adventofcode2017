#include "days.h"
#include "util.h"
#include "sparsegrid.h"

#include <map>

void day19()
{
  printf("DAY 19\n");
  std::vector<char> input = readfile("../data/day19/input.txt");
  std::vector<std::string> lines = split(input, '\n');

  int x,y;
  SparseGrid grid;
  for(int i=0;i<lines.size();i++)
  {
    for(int j=0;j<lines[i].size();j++)
    {
      if(i==0 && lines[i][j]=='|')
      {
        x=j;
        y=0;
      }
      grid.set(j,i, lines[i][j]);
    }
  }

  int dir=2; // 0 up, 1 right, 2 down, 3 left

  int count=0;
  std::string str;
  while(true)
  {
    char current = grid.get(x,y);

    if(current=='+')
    {
      // change dir
      if(grid.get(x-1,y)=='-' && dir!=1)
      {
        dir = 3;
      }
      else if(grid.get(x+1,y)=='-' && dir!=3)
      {
        dir = 1;
      }
      else if(grid.get(x,y-1)=='|' && dir!=2)
      {
        dir = 0;
      }
      else if(grid.get(x,y+1)=='|' && dir!=0)
      {
        dir = 2;
      }
    }
    else if(current=='|')
    {

    }
    else if(current=='-')
    {

    }
    else if(current=='.')
    {
      // stop
      break;
    }
    else if(current==' ')
    {
      // stop
      break;
    }
    else
    {
      str+=current;
    }

    switch(dir)
    {
      case 0: y--; break;
      case 1: x++; break;
      case 2: y++; break;
      case 3: x--; break;
    }
    count++;
  }

  printf("%s %i\n", str.c_str(), count);

}
