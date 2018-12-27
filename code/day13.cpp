#include "days.h"
#include "util.h"

void day13()
{
  printf("DAY 13\n");
  std::vector<char> buf = readfile("../data/day13/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  int maxindex=0;
  for(int i=0;i<lines.size();i++)
  {
    std::vector<std::string> parts = split(lines[i], ' ');
    int index = atoi(parts[0].c_str());
    if(index > maxindex) maxindex = index;
  }

  std::vector<int> scanners(maxindex+1,0);
  std::vector<int> indexes(maxindex+1,0);
  std::vector<int> dirs(maxindex+1,1);

  for(int i=0;i<lines.size();i++)
  {
    std::vector<std::string> parts = split(lines[i], ' ');
    int index = atoi(parts[0].c_str());
    int range = atoi(parts[1].c_str());
    scanners[index] = range;
  }

  std::vector<int> severities(maxindex+1,-1);
  std::vector<int> temp(maxindex+1,0);

  int count=0;
  while(true)
  {
    severities[0] = -1;
    for(int j=0;j<scanners.size();j++)
    {
      if(indexes[j]==0 && scanners[j]>0)
      {
        //printf(" collision %i %i\n", j, j * scanners[j]);
        if(severities[j]==-1)
        {
          severities[j]=0;
        }
        severities[j] += j * scanners[j];
      }

      if(indexes[j]==scanners[j]-1)
      {
        dirs[j]=-1;
      }
      else if(indexes[j]==0)
      {
        dirs[j]=1;
      }

      indexes[j]+=dirs[j];
    }

    /*for(int k=0;k<scanners.size();k++)
    {
      printf("%i,  ", severities[k]);
    }
    printf("\n");*/


    if(severities[maxindex]==-1 && count>scanners.size())
    {
      printf("made it! %i\n", count - scanners.size()+1);
      break;
    }
    count++;

    temp = severities;
    std::copy(temp.begin(), temp.end()-1, severities.begin()+1);
  }
}
