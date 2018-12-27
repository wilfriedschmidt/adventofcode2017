#include "days.h"
#include "util.h"

#include <algorithm>

struct Part
{
  int id;
  int ports[2];

  std::vector<Part*> in;
  std::vector<Part*> out;
};

void recurseparts(std::vector<std::vector<Part*>> &finallists, std::vector<Part*> partlist, Part* part)
{
  bool recursed=false;
  for(size_t i=0;i<part->out.size();i++)
  {
    bool alreadyused=false;
    for(size_t j=0;j<partlist.size();j++)
    {
      if(partlist[j]->id==part->out[i]->id)
        alreadyused=true;
    }

    if(!alreadyused)
    {
      std::vector<Part*> temp = partlist;
      temp.push_back(part->out[i]);
      recurseparts(finallists,temp, part->out[i]);
      recursed=true;
    }
  }

  if(!recursed)
  {
    finallists.push_back(partlist);
    /*for(size_t i=0;i<partlist.size();i++)
    {
      printf("%i/%i ", partlist[i]->ports[0], partlist[i]->ports[1]);
    }
    printf("\n");*/
  }
}

struct BridgeStats
{
  int length;
  int strength;

  bool operator <(const BridgeStats &p) const
  {
    if(length==p.length)
    {
      return strength < p.strength;
    }
    else
    {
      return length < p.length;
    }
  }
};

void day24()
{
  printf("DAY 24\n");
  std::vector<char> input = readfile("../data/day24/input.txt");
  std::vector<std::string> lines = split(input, '\n');

  std::vector<Part> parts;

  for(size_t i=0;i<lines.size();i++)
  {
    std::vector<std::string> ports = split(lines[i],'/');

    Part part;
    part.id=i;
    part.ports[0] = atoi(ports[0].c_str());
    part.ports[1] = atoi(ports[1].c_str());
    parts.push_back(part);

    std::swap(part.ports[0], part.ports[1]);
    parts.push_back(part);
  }

  for(size_t i=0;i<parts.size();i++)
  {
    printf("%i/%i\n", parts[i].ports[0],parts[i].ports[1]);
  }

  std::vector<Part*> startparts;

  for(size_t i=0;i<parts.size();i++)
  {
    for(size_t j=0;j<parts.size();j++)
    {
      if( parts[i].ports[1]==parts[j].ports[0] )
      {
        parts[i].out.push_back(&parts[j]);
        parts[j].in.push_back(&parts[i]);
      }
    }

    if(parts[i].ports[0]==0)
    {
      startparts.push_back(&parts[i]);
    }
  }

  std::vector<std::vector<Part*>> finallists;
  for(size_t i=0;i<startparts.size();i++)
  {
    std::vector<Part*> temp;
    temp.push_back(startparts[i]);
    recurseparts(finallists, temp, startparts[i]);
  }

  std::vector<BridgeStats> stats;

  for(size_t i=0;i<finallists.size();i++)
  {
    int strength=0;
    for(size_t j=0;j<finallists[i].size();j++)
    {
      strength+=finallists[i][j]->ports[0]+finallists[i][j]->ports[1];
    }

    BridgeStats stat;
    stat.length = finallists[i].size();
    stat.strength = strength;
    stats.push_back(stat);

  }

  std::sort(stats.begin(), stats.end());

  for(int i=0;i<5;i++)
  {
    printf("length %i, strength %i\n", stats[stats.size()-(1+i)].length, stats[stats.size()-(1+i)].strength);
  }

  /*
  printf("strongest: %i", stats.);
  for(size_t i=0;i<finallists[maxindex].size();i++)
  {
    printf("%i/%i ", finallists[maxindex][i]->ports[0], finallists[maxindex][i]->ports[1]);
  }
  printf("\n");*/
}
