#include "days.h"
#include "util.h"
#include "image.h"
#include "sparsegrid.h"

#include <memory.h>

void day22()
{
  printf("DAY 22\n");
  std::vector<char> input = readfile("../data/day22/input.txt");
  std::vector<std::string> parts = split(input, '\n');

  Image img;
  img.init(parts.size());
  for(int i=0;i<parts.size();i++)
  {
    for(int j=0;j<parts[i].size();j++)
    {
      img.values[i*img.size+j] = parts[i][j];
    }
  }


  int x=img.size/2;
  int y=img.size/2;
  int dir=0; // 0 up, 1 right, 2 down, 3 left

  //img.print(x,y);

  int numinfections=0;
  int iterations=10000;
  for(int i=0;i<iterations;i++)
  {
    // turn
    if(img.values[y*img.size+x]=='#')
    {
      dir+=1;
      if(dir>3) dir=0;
      img.values[y*img.size+x]='.';
    }
    else
    {
      dir-=1;
      if(dir<0) dir = 3;
      img.values[y*img.size+x]='#';
      numinfections++;
    }

    switch(dir)
    {
      case 0: y--; break;
      case 1: x++; break;
      case 2: y++; break;
      case 3: x--; break;
    }

    if(x<0 || y<0 || x>=img.size || y>=img.size)
    {
      Image newimg;
      newimg.init(img.size+2);
      newimg.copy(1,1,img);

      img = newimg;
      x+=1;
      y+=1;
    }

    //img.print(x,y);
  }

  //img.print();
  printf("numinfections %i", numinfections);
}

void day22_2()
{
  printf("DAY 22.2\n");
  std::vector<char> input = readfile("../data/day22/input.txt");
  std::vector<std::string> parts = split(input, '\n');


  SparseGrid img;
  int x,y;
  y = parts.size();
  for(int i=0;i<parts.size();i++)
  {
    for(int j=0;j<parts[i].size();j++)
    {
      img.set(j,i, parts[i][j]);
    }
    x = parts[i].size();
  }

  x/=2;
  y/=2;
  int dir=0; // 0 up, 1 right, 2 down, 3 left

  int numinfections=0;
  int iterations=10000000;
  for(int i=0;i<iterations;i++)
  {
    // turn
    if(img.get(x,y)=='#')
    {
      // turn right
      dir+=1;
      if(dir>3) dir=0;
      img.set(x,y,'F');
    }
    else if(img.get(x,y)=='.')
    {
      // turn left
      dir-=1;
      if(dir<0) dir = 3;
      img.set(x,y,'W');
    }
    else if(img.get(x,y)=='W')
    {
      // keep going
      img.set(x,y,'#');
      numinfections++;
    }
    else if(img.get(x,y)=='F')
    {
      // reverse direction
      switch(dir)
      {
        case 0: dir=2; break;
        case 1: dir=3; break;
        case 2: dir=0; break;
        case 3: dir=1; break;
      }
      img.set(x,y,'.');
    }

    switch(dir)
    {
      case 0: y--; break;
      case 1: x++; break;
      case 2: y++; break;
      case 3: x--; break;
    }

    if(i%10000==0) printf("%i\n",i);
  }

  /*for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if((i-3)==y && (j-3)==x)
      {
        printf("[%c]", img.get(j-3,i-3));
      }
      else
      {
        printf(" %c ", img.get(j-3,i-3));
      }
    }
    printf("\n\n");
  }*/

  printf("%i %i %i\n",x,y,dir);
  printf("numinfections %i\n", numinfections);
}

