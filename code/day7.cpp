#include "days.h"
#include "util.h"

#include <map>

struct Program
{
  std::string name;
  int weight;
  int newweight;
  std::vector<std::string> refs;
  std::vector< Program* > prefs;
  Program *parent;
};

void day7()
{
  printf("DAY 7\n");
  std::vector<char> buf = readfile("../data/day7/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  std::vector<Program> programs;

  for(int i=0;i<lines.size();++i)
  {
    // ensyb (18) -> usvzfi, uxxtnll, phrkfo, vntjo
    std::vector<std::string> parts = split(lines[i], ' ');

    Program newprog;
    newprog.name = parts[0];
    newprog.weight = atoi(parts[1].substr(1,parts[1].size()-2).c_str());
    newprog.newweight = 0;
    newprog.parent = nullptr;

    for(int j=3;j<parts.size()-1;++j)
    {
      std::string subname = parts[j].substr(0,parts[j].size()-1);
      newprog.refs.push_back(subname);
    }

    if(parts.size() > 2)
    {
      newprog.refs.push_back(parts[parts.size()-1]);
    }

    programs.push_back(newprog);
  }

  std::map<std::string, int> pmap;
  for(int i=0;i<programs.size();++i)
  {
    pmap.insert( std::pair<std::string,int>(programs[i].name, i) );
  }

  for(int i=0;i<programs.size();++i)
  {
    for(int j=0;j<programs[i].refs.size();++j)
    {
      Program *pref = &programs[ pmap[programs[i].refs[j]] ];
      programs[i].prefs.push_back( pref );
      pref->parent = &programs[i];
    }
  }

  for(int i=0;i<programs.size();++i)
  {
    if(programs[i].parent==nullptr)
    {
      printf("root is %s\n", programs[i].name.c_str());
    }
  }

  int count=0;
  int index=0;
  while(count<programs.size())
  {
    if(programs[index].newweight==0)
    {
      bool childrenready=true;
      for(int j=0;j<programs[index].prefs.size();++j)
      {
        if(programs[index].prefs[j]->newweight==0)
        {
          childrenready=false;
        }
      }

      if(childrenready)
      {
        if(programs[index].prefs.size()==0)
        {
          programs[index].newweight = programs[index].weight;
        }
        else
        {
          for(int j=0;j<programs[index].prefs.size();++j)
          {
            programs[index].newweight += programs[index].prefs[j]->newweight;
          }
          programs[index].newweight+=programs[index].weight;
        }
        count++;

        // check children
        if(programs[index].prefs.size()>0)
        {
          for(int j=0;j<programs[index].prefs.size()-1;++j)
          {
            if(programs[index].prefs[j]->newweight != programs[index].prefs[j+1]->newweight)
            {
              printf("bad weights for %s\n", programs[index].name.c_str());
            }
          }
        }
      }
    }

    index++;
    index = index % programs.size();
  }

  for(int i=0;i<programs.size();++i)
  {
    printf("%s %i %i ", programs[i].name.c_str(), programs[i].weight, programs[i].newweight);

    for(int j=0;j<programs[i].prefs.size();++j)
    {
      printf("%s ", programs[i].prefs[j]->name.c_str());
    }
    printf("\n");
  }
}
