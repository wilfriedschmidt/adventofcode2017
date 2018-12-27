#include "days.h"
#include "util.h"
#include "image.h"

#include <memory.h>
#include <map>

void day21()
{

  //printf("%s\n", img.tostr().c_str());

  /*
  img.crop(0,0,2).print();
  img.crop(2,0,2).print();
  img.crop(0,2,2).print();
  img.crop(2,2,2).print();
  */

  /*
  img = img.rotate();
  img.print();

  img = img.rotate();
  img.print();

  img = img.rotate();
  img.print();

  img = img.rotate();
  img.print();

  img = img.flipv();
  img.print();

  img = img.flipv();
  img.print();

  img = img.fliph();
  img.print();

  img = img.fliph();
  img.print();*/


  printf("DAY 21\n");
  std::vector<char> input = readfile("../data/day21/input.txt");
  std::vector<std::string> parts = split(input, '\n');

  Image img;
  img.init(".#./..#/###");
  img.print();

  std::map<std::string,std::string> xform;
  for(int i=0;i<parts.size();i++)
  {
    std::vector<std::string> subparts = split(parts[i],' ');
    xform.insert(std::pair<std::string,std::string>(subparts[0],subparts[2]));
  }

  int iterations = 18;
  for(int i=0;i<iterations;i++)
  {
    if(img.size%2==0)
    {
      Image nextimg;
      nextimg.init(img.size*3/2);

      // match each subpart
      for(int j=0;j<img.size;j+=2)
      {
        for(int k=0;k<img.size;k+=2)
        {
          Image totest[12];
          totest[0] = img.crop(k,j,2);
          totest[1] = totest[0].flipv();
          totest[2] = totest[0].fliph();

          totest[3] = totest[0].rotate();
          totest[4] = totest[3].flipv();
          totest[5] = totest[3].fliph();

          totest[6] = totest[3].rotate();
          totest[7] = totest[6].flipv();
          totest[8] = totest[6].fliph();

          totest[9] = totest[6].rotate();
          totest[10] = totest[9].flipv();
          totest[11] = totest[9].fliph();

          bool transformed=false;
          for(int l=0;l<12;l++)
          {
            //printf("checking %s\n", totest[l].tostr().c_str());

            auto f = xform.find(totest[l].tostr());
            if(f!=xform.end())
            {
              Image subimg;
              subimg.init(f->second);

              nextimg.copy(k*3/2,j*3/2,subimg);

              transformed=true;
              break;
            }
            else
            {
              //printf("ERROR transform not found %s\n", totest[l].tostr().c_str());
            }
          }

          if(!transformed)
          {
            printf("couldn't find transform %s\n", totest[0].tostr().c_str());
          }

        }
      }

      img = nextimg;
    }
    else if(img.size%3==0)
    {
      Image nextimg;
      nextimg.init( (img.size*4/3));

      // match each subpart
      for(int j=0;j<img.size;j+=3)
      {
        for(int k=0;k<img.size;k+=3)
        {
          Image totest[12];
          totest[0] = img.crop(k,j,3);
          totest[1] = totest[0].flipv();
          totest[2] = totest[0].fliph();

          totest[3] = totest[0].rotate();
          totest[4] = totest[3].flipv();
          totest[5] = totest[3].fliph();

          totest[6] = totest[3].rotate();
          totest[7] = totest[6].flipv();
          totest[8] = totest[6].fliph();

          totest[9] = totest[6].rotate();
          totest[10] = totest[9].flipv();
          totest[11] = totest[9].fliph();

          bool transformed = false;
          for(int l=0;l<12;l++)
          {
            auto f = xform.find(totest[l].tostr());
            if(f!=xform.end())
            {
              Image subimg;
              subimg.init(f->second);

              nextimg.copy(k*4/3,j*4/3,subimg);
              transformed=true;
              break;
            }
            else
            {
              //printf("ERROR transform not found %s\n", totest[i].tostr().c_str());
            }
          }

          if(!transformed)
          {
            printf("couldn't find transform %s\n", totest[0].tostr().c_str());
          }
        }
      }
      img = nextimg;
    }

    //img.print();
  }

  printf("%i\n", img.numon());
}
