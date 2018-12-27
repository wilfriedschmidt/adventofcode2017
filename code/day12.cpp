#include "days.h"
#include "util.h"

struct PipeNode
{
  int id;
  std::vector<int> connectionids;
  std::vector<PipeNode*> connections;

  int visited = -1;
};

void visitpipenodes(PipeNode *node, int id)
{
  if(node->visited==-1)
  {
    node->visited = id;
    for(int i=0;i<node->connections.size();i++)
    {
      visitpipenodes(node->connections[i],id);
    }
  }
  else if(node->visited!=id)
  {
    printf("ERROR a node in this group is somehow overlapping?");
  }
}

void day12()
{
  printf("DAY 12\n");
  std::vector<char> buf = readfile("../data/day12/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  std::vector<PipeNode> nodes;

  for(int i=0;i<lines.size();i++)
  {
    std::vector<std::string> parts = split(lines[i], ' ');

    PipeNode node;
    node.id = atoi(parts[0].c_str());

    if(node.id!=i)
    {
      printf("ERROR index mismatch");
    }

    for(int j=2;j<parts.size();j++)
    {
      node.connectionids.push_back( atoi(parts[j].c_str()) );
    }

    nodes.push_back(node);
  }

  for(int i=0;i<nodes.size();i++)
  {
    for(int j=0;j<nodes[i].connectionids.size();j++)
    {
      int k=nodes[i].connectionids[j];
      nodes[i].connections.push_back( &nodes[k] );
    }
  }

  int count=0;

  for(int i=0;i<nodes.size();i++)
  {
    if(nodes[i].visited==-1)
    {
      visitpipenodes(&nodes[i],count);
      count++;
    }
  }

  printf("groups %i\n", count);
}
