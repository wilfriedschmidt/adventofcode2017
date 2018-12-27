#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <map>

struct Context
{
  int ic;
  std::map<char,int64_t> registers;
  std::vector<int64_t> *out;
  std::vector<int64_t> *in;
  int numsent;
};

#endif // CONTEXT_H

