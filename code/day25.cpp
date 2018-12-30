#include "days.h"
#include "util.h"

#include <map>

void day25()
{
  std::map<int,int> tape;
  int cursor=0;
  int mincursor=10000;
  int maxcursor=-10000;
  int state=0;

  int iterations=12459852;

  for(int i=0;i<iterations;++i)
  {
    auto j=tape.find(cursor);
    if(j==tape.end())
    {
      tape.insert(std::pair<int,int>(cursor,0));
    }

    switch(state)
    {
      case 0:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor++;
          state=1;
        }
        else
        {
          tape[cursor]=1;
          cursor--;
          state=4;
        }
      break;

      case 1:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor++;
          state=2;
        }
        else
        {
          tape[cursor]=1;
          cursor++;
          state=5;
        }
      break;

      case 2:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor--;
          state=3;
        }
        else
        {
          tape[cursor]=0;
          cursor++;
          state=1;
        }
      break;

      case 3:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor++;
          state=4;
        }
        else
        {
          tape[cursor]=0;
          cursor--;
          state=2;
        }
      break;
 
      case 4:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor--;
          state=0;
        }
        else
        {
          tape[cursor]=0;
          cursor++;
          state=3;
        }
      break;

      case 5:
        if(tape[cursor]==0)
        {
          tape[cursor]=1;
          cursor++;
          state=0;
        }
        else
        {
          tape[cursor]=1;
          cursor++;
          state=2;
        }
      break;
    }

    if(cursor<mincursor) 
    {
      mincursor=cursor;
    }
    if(cursor>maxcursor) 
    {
      maxcursor=cursor;
    }

    if(i%100000==0) 
    {
      printf("%i\n", i);
    }
  }


  printf("\n");
  int onecount=0;
  for(int i=mincursor;i<=maxcursor;++i)
  {
    if(tape[i]) 
    {
      onecount++;
    }
  }

  printf("checksum %i\n", onecount);
}
