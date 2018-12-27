#ifndef SPARSEGRID_H
#define SPARSEGRID_H

#include <map>

struct SparseGrid
{
  std::map<uint64_t,char> grid;

  char get(uint64_t x,uint64_t y)
  {
    uint64_t index = (x << 32) + y;
    auto i = grid.find(index);
    if(i==grid.end())
    {
      return '.';
    }
    else
    {
      return i->second;
    }
  }

  void set(uint64_t x,uint64_t y, char c)
  {
    uint64_t index = (x << 32) + y;
    auto i = grid.find(index);
    if(i==grid.end())
    {
      grid.insert(std::pair<uint64_t,char>(index,c));
    }
    else
    {
      grid[index] = c;
    }
  }
};

#endif // SPARSEGRID_H

