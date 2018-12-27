#include "days.h"
#include "util.h"

void day1()
{
  printf("DAY 1\n");
  std::vector<char> buf = readfile("../data/day1/input.txt");

  std::vector<uint8_t> digits;
  for(int i=0;i<buf.size();i++)
  {
    if(isdigit(buf[i]))
      digits.push_back(buf[i] - '0');
  }

  printf("chars %i\n", digits.size());

  int sum=0;
  for(int i=0;i<digits.size();i++)
  {
    char first = digits[i];
    char second = digits[ (i+1) % digits.size() ];

    if(first==second)
    {
      sum+=first;
    }
  }

  printf("sum: %i\n", sum);

/*
  buf.resize(6);
  memcpy(buf.data(), "123123", 6);
  digits.clear();
  for(int i=0;i<buf.size();i++)
  {
    if(isdigit(buf[i]))
      digits.push_back(buf[i] - '0');
  }*/

  int sum2=0;
  for(int i=0;i<digits.size();i++)
  {
    char first = digits[i];
    char second = digits[ (i+digits.size()/2) % digits.size() ];

    if(first==second)
    {
      sum2+=first;
    }
  }

  printf("sum2: %i\n\n", sum2);
}
