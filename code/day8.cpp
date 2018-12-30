#include "days.h"
#include "util.h"

#include <map>

struct Instruction
{
  std::string condition;
  int comparator;
  std::string conditionregister;

  std::string opregister;
  int amount;
};

void day8()
{
  printf("DAY 8\n");
  std::vector<char> buf = readfile("../data/day8/input.txt");
  std::vector<std::string> lines = split(buf, '\n');

  std::map<std::string,int> registers;
  std::vector<Instruction> instructions;

  for(int i=0;i<lines.size();++i)
  {
    // c inc -20 if c == 10
    std::vector<std::string> parts = split(lines[i], ' ');

    Instruction newinst;
    newinst.opregister = parts[0];
    newinst.amount = atoi(parts[2].c_str());
    if(parts[1]=="dec")
    {
      newinst.amount= -newinst.amount;
    }

    newinst.conditionregister = parts[4];
    newinst.condition = parts[5];
    newinst.comparator = atoi(parts[6].c_str());

    if(registers.find(newinst.opregister)==registers.end())
    {
      registers.insert(std::pair<std::string,int>(newinst.opregister,0));
    }

    if(registers.find(newinst.conditionregister)==registers.end())
    {
      registers.insert(std::pair<std::string,int>(newinst.conditionregister,0));
    }

    instructions.push_back(newinst);
  }

  for(int i=0;i<instructions.size();++i)
  {
    Instruction inst = instructions[i];
    printf("%s %i if %s %s %i\n", inst.opregister.c_str(), inst.amount, inst.conditionregister.c_str(), inst.condition.c_str(), inst.comparator);
  }

  int largesttotal=0;
  for(int i=0;i<instructions.size();++i)
  {
    Instruction inst = instructions[i];

    bool doaction=false;
    if(inst.condition=="==")
    {
      if(registers[inst.conditionregister]==inst.comparator) doaction=true;
    }
    if(inst.condition==">=")
    {
      if(registers[inst.conditionregister]>=inst.comparator) doaction=true;
    }
    if(inst.condition=="<=")
    {
      if(registers[inst.conditionregister]<=inst.comparator) doaction=true;
    }
    if(inst.condition=="!=")
    {
      if(registers[inst.conditionregister]!=inst.comparator) doaction=true;
    }
    if(inst.condition==">")
    {
      if(registers[inst.conditionregister]>inst.comparator) doaction=true;
    }
    if(inst.condition=="<")
    {
      if(registers[inst.conditionregister]<inst.comparator) doaction=true;
    }

    if(doaction)
    {
      registers[inst.opregister]+=inst.amount;

      if( registers[inst.opregister]>largesttotal )
      {
        largesttotal = registers[inst.opregister];
      }
    }

  }

  int largest=0;
  for(auto i=registers.begin(); i!=registers.end(); ++i)
  {
    if(i->second>largest) 
    {
      largest = i->second;
    }
    printf("%s %i\n", i->first.c_str(), i->second);
  }

  printf("largest %i, largest total %i\n",largest, largesttotal);

}
