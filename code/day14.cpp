#include "days.h"
#include "util.h"

#include <memory.h>

std::vector<int> knothash(const std::vector<int> &sizes)
{
  std::vector<int> knots;
  int knotssize = 256;
  knots.resize(knotssize);
  for(int i=0;i<knotssize;++i)
  {
    knots[i] = i;
  }

  int index=0;
  int skipsize = 0;
  for(int k=0;k<64;++k)
  {
    for(int i=0;i<sizes.size();++i)
    {
      int reverselength = sizes[i];

      for(int j=0;j<reverselength/2;++j)
      {
        int temp = knots[ (index+j)%knotssize ];
        knots[ (index+j)%knotssize ] = knots[ (index + ((reverselength-j)-1))%knotssize ];
        knots[ (index + ((reverselength-j)-1))%knotssize ] = temp;
      }

      index+=reverselength;
      index+=skipsize;
      index = index % knotssize;

      skipsize++;
    }
  }

  std::vector<int> dense;
  for(int i=0;i<16;++i)
  {
    int value=0;
    for(int j=0;j<16;++j)
    {
      value^=knots[i*16+j];
    }
    dense.push_back(value);
  }

  return dense;
}

void day14()
{
  printf("DAY 14\n");

  std::vector<std::vector<int>> grid;

  int used=0;
  for(int i=0;i<128;++i)
  {
    char buf[256];

    sprintf(buf,"vbqugkhl-%i", i);

    std::vector<int> sizes;
    for(int j=0;j<strlen(buf);++j)
    {
      sizes.push_back( static_cast<int>(buf[j]) );
    }

    sizes.push_back(17);
    sizes.push_back(31);
    sizes.push_back(73);
    sizes.push_back(47);
    sizes.push_back(23);

    std::vector<int> dense = knothash(sizes);

    std::string bin = tobinary(dense);
    printf("%s\n", bin.c_str());

    std::vector<int> row(128,-2);
    for(int j=0;j<bin.size();j++)
    {
      if(bin[j]=='1')
      {
        used++;
        row[j]=-1;
      }
    }
    grid.push_back(row);
  }

  printf("%i\n", used);

  for(int i=0;i<4096;++i)
  {
    printf("attempting %i\n", i);
    bool started = false;
    for(int y=0;y<128;++y)
    {
      for(int x=0;x<128;++x)
      {
        if(!started && grid[y][x]==-1)
        {
          grid[y][x] = i;
          started = true;
          break;
        }
      }
    }

    if(!started)
    {
      printf("couldn't start %i\n", i);
      break;
    }

    while(true)
    {
      bool added = false;
      for(int y=0;y<128;++y)
      {
        for(int x=0;x<128;++x)
        {
          if(grid[y][x]==-1)
          {
            if((x>0) && (grid[y][x-1]==i))
            {
              grid[y][x] = i;
              added = true;
            }
            if((x<127) && (grid[y][x+1]==i))
            {
              grid[y][x] = i;
              added = true;
            }
            if((y>0) && (grid[y-1][x]==i))
            {
              grid[y][x] = i;
              added = true;
            }
            if((y<127) && (grid[y+1][x]==i))
            {
              grid[y][x] = i;
              added = true;
            }
          }
        }
      }

      if(!added) 
      {
        break;
      }
    }
  }
}
