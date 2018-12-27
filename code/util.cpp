#include "util.h"

#include <vector>
#include <stdio.h>
#include <string>

std::vector<char> readfile(const char* filename)
{
  FILE *f = fopen(filename,"rt");

  fseek(f,0,2);
  size_t size = ftell(f);
  fseek(f,0,0);

  std::vector<char> buf;
  buf.resize(size);

  fread(buf.data(),1,size,f);

  fclose(f);

  return buf;
}

void writefile(const char* filename, const std::vector<char> &buf)
{
  FILE *f = fopen(filename,"wt");

  fwrite(buf.data(),1,buf.size(),f);

  fclose(f);
}


