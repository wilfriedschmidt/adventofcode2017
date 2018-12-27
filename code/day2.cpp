#include "days.h"
#include "util.h"

void day2()
{
  printf("DAY 2\n");
  std::vector<char> buf = readfile("../data/day2/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  /*lines.clear();
  lines.push_back("5\t1\t9\t5");
  lines.push_back("7\t5\t3");
  lines.push_back("2\t4\t6\t8");*/

  int checksum=0;
  for(int i=0;i<lines.size();i++)
  {
    std::vector<std::string> parts = split(lines[i], '\t');
    int min = 10000;
    int max = -1;
    for(int j=0;j<parts.size();j++)
    {
      int value = atoi(parts[j].c_str());
      if(value < min) min = value;
      if(value > max) max = value;

      printf("|%i|\t",value);
    }

    checksum += (max - min);

    printf("min %i, max %i, checksum %i\n", min, max, checksum);
  }

  std::vector<std::vector<int>> ints;

  int checksum2=0;
  for(int i=0;i<lines.size();i++)
  {
    std::vector<std::string> parts = split(lines[i], '\t');
    std::vector<int> subints;
    for(int j=0;j<parts.size();j++)
    {
      subints.push_back(atoi(parts[j].c_str()));
    }
    ints.push_back(subints);
  }

  for(int i=0;i<ints.size();i++)
  {
    for(int j=0;j<ints[i].size();j++)
    {
      for(int k=0;k<ints[i].size();k++)
      {
        if((j!=k) && (ints[i][j] % ints[i][k]) == 0)
        {
          int result = (ints[i][j] / ints[i][k]);
          if(result>0)
          {
            printf("adding %i / %i\n", ints[i][j] , ints[i][k]);
            checksum2+=result;
          }
        }
      }
    }
  }

  printf("checksum2 %i\n", checksum2);
}
