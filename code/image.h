#ifndef IMAGE_H
#define IMAGE_H

#include <memory.h>
#include <vector>
#include <string>

struct Image
{
  int size;
  std::vector<char> values;

  void init(int s)
  {
    size = s;
    values.resize(size*size,'.');
  }

  void init(const std::string &v)
  {
    std::vector<std::string> parts = split(v, '/');
    init(parts.size());
    for(int i=0;i<parts.size();i++)
    {
      memcpy(values.data()+i*size, parts[i].c_str(), size);
    }
  }

  void print() const
  {
    for(int i=0;i<size;++i)
    {
      char buf[256];
      memcpy(buf,values.data()+i*size,size);
      buf[size] = 0;
      printf("%s\n", buf);
    }
    printf("\n");
  }

  void print(int x,int y) const
  {
    for(int i=0;i<size;++i)
    {
      for(int j=0;j<size;++j)
      {
        if(i==y && j==x)
        {
          printf("[%c]", values[i*size+j]);
        }
        else
        {
          printf(" %c ", values[i*size+j]);
        }
      }
      printf("\n\n");
    }
    printf("\n");
  }

  std::string tostr() const
  {
    std::string str;

    for(int i=0;i<size;++i)
    {
      char buf[256];
      memcpy(buf, values.data()+i*size,size);
      buf[size] = 0;
      str+=buf;

      if(i!=size-1)
      {
        str+="/";
      }
    }

    return str;
  }

  Image crop(int x, int y, int s) const
  {
    Image img;
    img.init(s);

    for(int i=0;i<s;++i)
    {
      for(int j=0;j<s;++j)
      {
        img.values[ i*s+j ] = values[ (i+y)*size + j+x ];
      }
    }

    return img;
  }

  void copy(int x, int y, const Image &subimg)
  {
    int s = subimg.size;
    for(int i=0;i<s;++i)
    {
      for(int j=0;j<s;++j)
      {
        values[ (i+y)*size + j+x ] = subimg.values[ (i*s) + j ];
      }
    }
  }

  int numon() const
  {
    int count=0;
    for(int i=0;i<values.size();++i)
    {
      if(values[i]=='#')
      {
        count++;
      }
    }

    return count;
  }

  Image rotate() const
  {
    Image img;
    img.init(size);

    for(int i=0;i<size;++i)
    {
      for(int j=0;j<size;++j)
      {
        img.values[ ((size - j)-1)*size + i ] = values[ i*size + j ];
      }
    }

    return img;
  }

  Image fliph() const
  {

    Image img;
    img.init(size);

    for(int i=0;i<size;++i)
    {
      for(int j=0;j<size;++j)
      {
        img.values[ i*size + ((size - j)-1) ] = values[ i*size + j ];
      }
    }

    return img;
  }

  Image flipv() const
  {

    Image img;
    img.init(size);

    for(int i=0;i<size;++i)
    {
      for(int j=0;j<size;++j)
      {
        img.values[ ((size - i) -1)*size + j ] = values[ i*size + j ];
      }
    }

    return img;
  }
};

#endif // IMAGE_H

