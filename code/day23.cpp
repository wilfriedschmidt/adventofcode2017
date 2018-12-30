#include "days.h"
#include "util.h"
#include "opcode.h"
#include "context.h"

#include <inttypes.h>

int runcontext_2(const std::vector<OpCode> &codes, Context &context)
{
  while(true)
  {
    if(context.ic<0 || context.ic>=codes.size())
    {
      return 2;
    }

    OpCode op = codes[context.ic];

    // deref right
    int valueright = op.opright;
    if(op.regright!=' ')
    {
      valueright = context.registers[op.regright];
    }

    int jumpdist=1;
    if(op.command=="set")
    {
      context.registers[op.regleft] = valueright;
    }
    else if(op.command=="sub")
    {
      context.registers[op.regleft] -= valueright;
    }
    else if(op.command=="mul")
    {
      context.registers[op.regleft] *= valueright;
      context.numsent++;
    }
    else if(op.command=="jnz")
    {
      if(op.regleft==' ')
      {
        if(op.opleft!=0)
        {
          jumpdist=valueright;
        }
      }
      else
      {
        if(context.registers[op.regleft]!=0)
        {
          jumpdist = valueright;
        }
      }
    }

    printf("%i ", context.ic);
    op.print();
    printf("\n");
    for(auto i=context.registers.begin(); i!=context.registers.end(); i++)
    {
      printf("%c:%" PRIi64 " ", i->first, i->second);
    }
    printf("\n");

    context.ic+=jumpdist;
  }

  return 0;
}

void day23()
{
  printf("DAY 23\n");
  std::vector<char> input = readfile("../data/day23/input.txt");
  std::vector<std::string> parts = split(input, '\n');

  std::vector<OpCode> codes;
  std::map<char,int64_t> registers;

  for(int i=0;i<parts.size();++i)
  {
    std::vector<std::string> subparts = split(parts[i],' ');
    OpCode op;
    op.command = subparts[0];

    if(isdigit(subparts[1][0]) || subparts[1][0]=='-')
    {
      op.regleft = ' ';
      op.opleft = atoi(subparts[1].c_str());
    }
    else
    {
      op.regleft = subparts[1][0];
      op.opleft = 0;
      if(registers.find(op.regleft)==registers.end())
      {
        registers.insert(std::pair<char,int>(op.regleft,0));
      }
    }

    if(subparts.size()>2)
    {
      if(isdigit(subparts[2][0]) || subparts[2][0]=='-')
      {
        op.regright=' ';
        op.opright = atoi(subparts[2].c_str());
      }
      else
      {
        op.regright = subparts[2][0];
        op.opright = 0;
        if(registers.find(op.regright)==registers.end())
        {
          registers.insert(std::pair<char,int>(op.regright,0));
        }
      }
    }
    else
    {
      op.regright = ' ';
      op.opright = 0;
    }

    codes.push_back(op);
  }

  for(int i=0;i<codes.size();++i)
  {
    OpCode& op = codes[i];
    printf("%i ",i);
    op.print();
    printf("\n");
  }

  for(auto i=registers.begin(); i!=registers.end(); ++i)
  {
    printf("%c %i\n", i->first, i->second);
  }

  Context context0;
  context0.ic=0;
  context0.registers = registers;
  context0.numsent=0;

  context0.registers['a'] = 1;

  while(true)
  {
    int res0 = runcontext_2(codes,context0);
    if(res0!=0)
    {
      break;
    }
  }


  for(auto i=registers.begin(); i!=registers.end(); ++i)
  {
    printf("%c %i\n", i->first, i->second);
  }

  printf("numsent %i\n", context0.numsent);
}

void day23_2()
{
  int notprimes=0;
  for(int i=105700;i<=122700;i+=17)
  {
    bool notp=false;

    for(int j=2;j<i;j++)
    {
      if(i%j==0)
      {
        notp=true;
        break;
      }
    }

    if(notp) 
    {
      notprimes++;
    }
    printf("%i\n", i);
  }

  printf("num not primes %i\n", notprimes);
}
