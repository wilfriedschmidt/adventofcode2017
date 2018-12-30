#include "days.h"
#include "util.h"

void day10()
{
  printf("DAY 10\n");
  std::vector<char> buf = readfile("../data/day10/input.txt");
  std::vector<std::string> parts = split(buf, ',');

  std::vector<int> sizes;
  for(int i=0;i<parts.size();++i)
  {
    sizes.push_back(atoi(parts[i].c_str()));
  }

  for(int i=0;i<parts.size();++i)
  {
    printf("%i, ", sizes[i]);
  }

  std::vector<int> knots;
  int knotssize = 256;
  knots.resize(knotssize);
  for(int i=0;i<knotssize;++i)
  {
    knots[i] = i;
  }

  int index=0;
  int skipsize = 0;
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

    printf("reverse len %i index %i skipsize %i \n", reverselength, index, skipsize);
    for(int j=0;j<knotssize;++j)
    {
      printf("%i ", knots[j]);
    }
    printf("\n");
  }

}

void day10_2()
{
  printf("DAY 10.2\n");
  std::vector<char> buf = readfile("../data/day10/input.txt");

  std::vector<int> sizes;
  for(int i=0;i<buf.size()-1;++i)
  {
    sizes.push_back( static_cast<int>(buf[i]) );
  }

  sizes.push_back(17);
  sizes.push_back(31);
  sizes.push_back(73);
  sizes.push_back(47);
  sizes.push_back(23);

  for(int i=0;i<sizes.size();++i)
  {
    printf("%i, ", sizes[i]);
  }

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

  printf("%s\n", tohex(dense).c_str());
}
