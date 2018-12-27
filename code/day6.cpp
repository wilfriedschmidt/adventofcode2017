#include "days.h"
#include "util.h"

void day6()
{
  printf("DAY 6\n");
  std::vector<char> buf = readfile("../data/day6/input.txt");
  std::vector<std::string> parts = split(buf, '\t');

  std::vector<std::vector<int>> previous;

  std::vector<int> banks;
  for(int i=0;i<parts.size();i++)
  {
    banks.push_back( atoi(parts[i].c_str()) );
    printf("%i ", banks[i]);
  }

  /*banks.clear();
  banks.push_back(0);
  banks.push_back(2);
  banks.push_back(7);
  banks.push_back(0);*/

  previous.push_back(banks);

  int count=0;
  bool cycle=false;
  while(!cycle)
  {
    int max=0;
    int maxindex = 0;
    for(int i=0;i<banks.size();i++)
    {
      if(banks[i]>max)
      {
        maxindex=i;
        max = banks[i];
      }
    }

    banks[maxindex]=0;
    for(int i=0;i<max;i++)
    {
      banks[ (maxindex+i+1) % banks.size() ]+=1;
    }

    for(int i=0;i<previous.size();i++)
    {
      if(containerequals(banks,previous[i]))
      {
        count=i;
        cycle = true;
        break;
      }
    }

    if(!cycle)
      previous.push_back(banks);
  }

  printf("cycle found %i %i\n", previous.size(), previous.size() - count);
}
