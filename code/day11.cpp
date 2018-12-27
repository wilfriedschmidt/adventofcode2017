#include "days.h"
#include "util.h"

#include <algorithm>

struct HexNode
{
  int x;
  int y;
  int z;

  void move(const std::string &dir)
  {
    if(dir=="nw")
    {
      x--;
      z--;
    }
    if(dir=="ne")
    {
      x++;
      y--;
    }
    if(dir=="n")
    {
      y--;
      z--;
    }

    if(dir=="sw")
    {
      x--;
      y++;
    }
    if(dir=="se")
    {
      x++;
      z++;
    }
    if(dir=="s")
    {
      y++;
      z++;
    }
  }

  int dist() const
  {
    return(abs(x) + abs(y) + abs(z));
  }

  bool operator <(const HexNode &p) const
  {
    return dist() < p.dist();
  }
};

int getsteps(HexNode node)
{
  std::vector<HexNode> nodes(6);

  int steps = 0;
  while(true)
  {
    if(node.dist()==0)
    {
      break;
    }

    for(int i=0;i<6;i++)
    {
      nodes[i] = node;
    }

    nodes[0].move("n");
    nodes[1].move("ne");
    nodes[2].move("nw");
    nodes[3].move("s");
    nodes[4].move("se");
    nodes[5].move("sw");

    std::sort(nodes.begin(), nodes.end());

    node = nodes[0];

    steps++;
  }

  return steps;
}

void day11()
{

  printf("DAY 11\n");
  std::vector<char> buf = readfile("../data/day11/input.txt");
  std::vector<std::string> dirs = split(buf, ',');

  /*dirs.clear();
  dirs.push_back("ne");
  dirs.push_back("ne");
  dirs.push_back("ne");

  dirs.clear();
  dirs.push_back("ne");
  dirs.push_back("ne");
  dirs.push_back("sw");
  dirs.push_back("sw");

  dirs.clear();
  dirs.push_back("ne");
  dirs.push_back("ne");
  dirs.push_back("s");
  dirs.push_back("s");

 /* dirs.clear();
  dirs.push_back("se");
  dirs.push_back("sw");
  dirs.push_back("se");
  dirs.push_back("sw");
  dirs.push_back("sw");*/

  HexNode node;
  node.x=0;
  node.y=0;
  node.z=0;

  int maxsteps=0;
  for(int i=0;i<dirs.size();i++)
  {
    node.move(dirs[i]);

    int steps = getsteps(node);
    if(steps>maxsteps)
    {
      maxsteps = steps;
    }
  }

  //printf("%i %i %i\n", node.x, node.y, node.z);
  int steps = getsteps(node);

  printf("dist %i %i\n", steps, maxsteps);
}
