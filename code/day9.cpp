#include "days.h"
#include "util.h"

struct Node
{
  std::vector<Node*> children;
  int score;

  void print()
  {
    printf("{");
    for(int i=0;i<children.size();++i)
    {
      children[i]->print();
      printf(",");
    }
    printf("}");
  }

  void doscore(int s)
  {
    score = s;
    for(int i=0;i<children.size();++i)
    {
      children[i]->doscore(score+1);
    }
  }

  int countscore()
  {
    int sum=score;
    for(int i=0;i<children.size();++i)
    {
      sum+=children[i]->countscore();
    }
    return sum;
  }
};


int recursenodes(Node &root, const std::vector<char> &buf, int index)
{
  while(true)
  {
    if(buf[index]=='}')
    {
      // return
      index++;
      break;
    }
    else if(buf[index]=='{')
    {
      // add a child
      Node *child = new Node();
      index = recursenodes(*child, buf, index+1);
      root.children.push_back(child);
    }
    else if(buf[index]==',')
    {
      // skip,
      index++;
    }
  }

  return index;
}

void day9()
{
  printf("DAY 9\n");
  std::vector<char> buf = readfile("../data/day9/input.txt");

  std::vector<char> preprocessed;

  int garbagecount=0;
  bool ingarbage = false;
  for(int i=0;i<buf.size();++i)
  {
    if(buf[i]=='!')
    {
      // skip
      i++;
    }
    else if(buf[i]=='<')
    {
      if(ingarbage)
      {
        garbagecount++;
      }

      // start garbage
      ingarbage = true;
    }
    else if(buf[i]=='>')
    {
      // end garbage
      if(ingarbage)
      {
        ingarbage = false;
      }
    }
    else
    {
      if(!ingarbage)
      {
        preprocessed.push_back(buf[i]);
      }
      else
      {
        garbagecount++;
      }
    }
  }

  writefile("../data/day9/preprocessed.txt", preprocessed);

  // if open bracket
  // create a new node, recurse

  Node root;
  recursenodes(root, preprocessed, 1);

  root.print();
  root.doscore(1);

  printf("total score %i garbage count %i\n", root.countscore(), garbagecount);
}
