#include "days.h"
#include "util.h"

#include <memory.h>
#include <map>

struct DanceMove
{
  char move;
  int size;
  int leftindex;
  int rightindex;
  char leftname;
  char rightname;
};

void day16()
{
  printf("DAY 16\n");
  std::vector<char> input = readfile("../data/day16/input.txt");
  std::vector<std::string> parts = split(input, ',');

  char buf[17] = "abcdefghijklmnop";
  //char buf[16] = "abcde";
  int numdancers = strlen(buf);

  std::vector<DanceMove> moves;
  for(int i=0;i<parts.size();i++)
  {
    DanceMove move;
    if(parts[i][0]=='s')
    {
      move.move = 's';
      move.size = atoi(parts[i].substr(1).c_str());
    }
    else if(parts[i][0]=='x')
    {
      move.move = 'x';

      // swap by index
      std::vector<std::string> lr = split(parts[i].substr(1),'/');

      move.leftindex = atoi(lr[0].c_str());
      move.rightindex = atoi(lr[1].c_str());
    }
    else if(parts[i][0]=='p')
    {
      move.move = 'p';

      // swap by name
      std::vector<std::string> lr = split(parts[i].substr(1),'/');

      move.leftname = lr[0][0];
      move.rightname = lr[1][0];
    }

    moves.push_back(move);
  }

  int iterations=1000000000;

  std::map<std::string,std::string> startend;

  for(int k=0;k<iterations;k++)
  {
    std::string start = buf;

    auto l = startend.find(start);
    if(l!=startend.end())
    {
      // shortcut, skip this iter
      strncpy(buf,l->second.c_str(),16);
    }
    else
    {
      for(int i=0;i<moves.size();i++)
      {
        DanceMove& move = moves[i];

        if(move.move=='s')
        {
          char temp[16];
          memcpy(temp+move.size,buf,numdancers-move.size);
          memcpy(temp,buf+(numdancers-move.size),move.size);

          memcpy(buf,temp,16);
        }
        else if(moves[i].move=='x')
        {
          char temp = buf[move.leftindex];
          buf[move.leftindex] = buf[move.rightindex];
          buf[move.rightindex] = temp;
        }
        else if(moves[i].move=='p')
        {
          int left=-1,right=-1;
          for(int j=0;j<16;j++)
          {
            if(buf[j]==move.leftname)
              left = j;

            if(buf[j]==move.rightname)
              right = j;
          }

          char temp = buf[left];
          buf[left] = buf[right];
          buf[right] = temp;
        }
      }

      std::string end = buf;
      startend.insert(std::pair<std::string,std::string>(start,end));
    }

    if(k%1000000==0)
    {
      printf("processing %i\n", k);
    }
  }

  printf("%s\n", buf);
}
