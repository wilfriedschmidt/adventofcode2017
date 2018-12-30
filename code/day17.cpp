#include "days.h"
#include "util.h"

#include <list>

void day17()
{
  printf("DAY 17\n");

  std::list<int> buf;
  buf.push_back(0);
  std::list<int>::iterator index = buf.begin();

  int count=1;
  int step = 376;

  for(int j=0;j<50000000;++j)
  {
    for(int k=0;k<step;++k)
    {
      if(index==buf.end())
      {
        index = buf.begin();
      }
      index++;
    }

    buf.insert(index,count);
    count++;

    if((count%100000)==0)
    {
      printf("%i\n", count);
    }
  }

  for(auto i = buf.begin();i!=buf.end();++i)
  {
    if(*i==0)
    {
      i++;
      printf("%i ", *i);
    }
  }
}
