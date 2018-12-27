#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <stdio.h>

std::vector<char> readfile(const char* filename);

void writefile(const char* filename, const std::vector<char> &buf);

template<typename T>
std::string tohex(const T &ctr)
{

std::string str;
char* hexmap = "0123456789abcdef";

  for(int i=0;i<ctr.size();i++)
  {
    str+=hexmap[ (ctr[i] >> 4) & 0x0f ];
    str+=hexmap[ ctr[i] & 0x0f ];
  }

  return str;
}

template<typename T>
std::string tobinary(const T &ctr)
{

std::string str;
char* binmap = "01";

  for(int i=0;i<ctr.size();i++)
  {
    for(int j=7;j>=0;j--)
    {
      str += binmap[ ctr[i]>>j & 0x01 ];
    }
  }

  return str;
}

template<typename T>
std::vector<std::string> split(const T &str, char splitchar)
{
  std::vector<std::string> parts;
  char partbuf[1024];
  int columnindex=0;

  for(int i=0;i<str.size();i++)
  {
    if(str[i]==splitchar)
    {
      if(columnindex>0)
      {
        parts.push_back(partbuf);
        columnindex=0;
      }
    }
    else
    {
      partbuf[columnindex++] = str[i];
      partbuf[columnindex]=0;

      if(columnindex>=1024)
        printf("ERROR overflow");
    }
  }

  // include the last one
  if(columnindex>0)
  {
    parts.push_back(partbuf);
  }

  return parts;
}

template<typename T>
bool containerequals(const T &str1, const T &str2)
{
  if(str1.size()!=str2.size())
  {
    return false;
  }

  for(int i=0; i < str1.size(); i++)
  {
    if(str1[i]!=str2[i])
    {
      return false;
    }
  }

  return true;
}

#endif // UTIL_H
