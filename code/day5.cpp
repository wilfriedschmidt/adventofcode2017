#include "days.h"
#include "util.h"

#include <inttypes.h>

void day5()
{
  printf("DAY 5\n");
  std::vector<char> buf = readfile("../data/day5/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  std::vector<int> jumps;
  for(int i=0;i<lines.size();++i)
  {
    jumps.push_back( atoi(lines[i].c_str()) );
    printf("%i\n", jumps[i]);
  }

  int64_t count=0;
  int index=0;
  while(index>=0 && index<jumps.size())
  {
    int next = jumps[index];
    if(next>=3)
    {
      jumps[index]-=1;
    }
    else
    {
      jumps[index]+=1;
    }

    index+=next;
    count++;
  }

  printf("%" PRId64 "\n", count);

}
