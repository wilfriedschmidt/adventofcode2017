#include "days.h"
#include "util.h"

#include <algorithm>

template<typename T>
bool containerisanagram(T str1,T str2)
{
  std::sort(str1.begin(), str1.end());
  std::sort(str2.begin(), str2.end());

  return containerequals(str1,str2);
}

void day4()
{
  printf("DAY 4\n");
  std::vector<char> buf = readfile("../data/day4/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  int total=0;
  int invalidcount=0;
  for(int i=0;i<lines.size();++i)
  {
    std::vector<std::string> parts = split( lines[i], ' ' );

    if(parts.size()>0)
    {
      total++;

      bool valid = true;
      for(int j=0;j<parts.size();++j)
      {
        for(int k=j+1;k<parts.size();++k)
        {
          if(containerequals( parts[j],parts[k] ))
          {
            valid = false;
          }
        }
      }

      if(!valid)
      {
        invalidcount++;
        printf("invalid %s\n", lines[i].c_str());
      }
    }
  }

  printf("%i\n", total - invalidcount);

  int invalidcount2=0;
  for(int i=0;i<lines.size();++i)
  {
    std::vector<std::string> parts = split( lines[i], ' ' );

    if(parts.size()>0)
    {
      bool valid = true;
      for(int j=0;j<parts.size();++j)
      {
        for(int k=j+1;k<parts.size();++k)
        {
          if(containerisanagram( parts[j],parts[k] ))
          {
            valid = false;
          }
        }
      }

      if(!valid)
      {
        invalidcount2++;
        printf("invalid %s\n", lines[i].c_str());
      }
    }
  }

  printf("%i\n", total - invalidcount2);
}
