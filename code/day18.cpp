#include "days.h"
#include "util.h"
#include "opcode.h"
#include "context.h"

#include <map>
#include <inttypes.h>

void day18()
{
  printf("DAY 18\n");
  std::vector<char> input = readfile("../data/day18/input.txt");
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
    printf("%i: %s ", i, op.command.c_str());
    if(op.regleft!=' ') 
    {
      printf("%c ", op.regleft);
    }
    else 
    {
      printf("%i ", op.opleft);
    }

    if(op.regright!=' ') 
    {
      printf("%c\n", op.regright);
    }
    else 
    {
      printf("%i\n", op.opright);
    }
  }

  for(auto i=registers.begin(); i!=registers.end(); ++i)
  {
    printf("%c %i\n", i->first, i->second);
  }

  int sound=0;
  int ic=0;
  while(true)
  {
    OpCode op = codes[ic];

    // deref right
    int valueright = op.opright;
    if(op.regright!=' ')
    {
      valueright = registers[op.regright];
    }

    bool jumping = false;
    if(op.command=="snd")
    {
      sound = registers[op.regleft];
    }
    else if(op.command=="set")
    {
      registers[op.regleft] = valueright;
    }
    else if(op.command=="add")
    {
      registers[op.regleft] += valueright;
    }
    else if(op.command=="mul")
    {
      registers[op.regleft] *= valueright;
    }
    else if(op.command=="mod")
    {
      registers[op.regleft] %= valueright;
    }
    else if(op.command=="rcv")
    {
      if(registers[op.regleft]!=0)
      {
        registers[op.regleft] = sound;
      }
    }
    else if(op.command=="jgz")
    {
      if(op.regleft==' ')
      {
        if(op.opleft>0)
        {
          ic+=valueright;
          jumping = true;
        }
      }
      else
      {
        if(registers[op.regleft]>0)
        {
          ic+=valueright;
          jumping = true;
        }
      }
    }

    if(!jumping)
    {
      ic++;
    }

    if(ic<0 || ic>=codes.size())
    {
      break;
    }
  }

  printf("%i\n",sound);

}

int runcontext(const std::vector<OpCode> &codes, Context &context)
{
  if(context.ic<0 || context.ic>=codes.size())
  {
    return 2;
  }

  while(true)
  {
    OpCode op = codes[context.ic];

    // deref right
    int valueright = op.opright;
    if(op.regright!=' ')
    {
      valueright = context.registers[op.regright];
    }

    bool jumping = false;
    if(op.command=="snd")
    {
      context.out->push_back(context.registers[op.regleft]);
      context.numsent++;
    }
    else if(op.command=="set")
    {
      context.registers[op.regleft] = valueright;
    }
    else if(op.command=="add")
    {
      context.registers[op.regleft] += valueright;
    }
    else if(op.command=="mul")
    {
      context.registers[op.regleft] *= valueright;
    }
    else if(op.command=="mod")
    {
      context.registers[op.regleft] %= valueright;
    }
    else if(op.command=="rcv")
    {
      if(context.in->empty())
      {
        // yield
        return 1;
      }
      else
      {
        context.registers[op.regleft] = (*context.in)[0];
        context.in->erase(context.in->begin());
      }
    }
    else if(op.command=="jgz")
    {
      if(op.regleft==' ')
      {
        if(op.opleft>0)
        {
          context.ic+=valueright;
          jumping = true;
        }
      }
      else
      {
        if(context.registers[op.regleft]>0)
        {
          context.ic+=valueright;
          jumping = true;
        }
      }
    }

    printf("%i ", context.ic);
    for(auto i=context.registers.begin(); i!=context.registers.end(); ++i)
    {
      printf("%c:%" PRIi64 "\t\t\t\t", i->first, i->second);
    }
    printf("\n");

    if(!jumping)
    {
      context.ic++;
    }

    if(context.ic<0 || context.ic>=codes.size())
    {
      return 2;
    }
  }

  return 0;
}

void day18_2()
{
  printf("DAY 18\n");
  std::vector<char> input = readfile("../data/day18/input.txt");
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
    printf("%i: %s ", i, op.command.c_str());
    if(op.regleft!=' ') 
    {
      printf("%c ", op.regleft);
    }
    else 
    {
      printf("%i ", op.opleft);
    }

    if(op.regright!=' ') 
    {
      printf("%c\n", op.regright);
    }
    else 
    {
      printf("%i\n", op.opright);
    }
  }

  for(auto i=registers.begin(); i!=registers.end(); ++i)
  {
    printf("%c %i\n", i->first, i->second);
  }

  Context context0;
  context0.ic=0;
  context0.registers = registers;
  context0.registers['p'] = 0;
  context0.numsent=0;

  Context context1;
  context1.ic=0;
  context1.registers = registers;
  context1.registers['p'] = 1;
  context1.numsent=0;

  std::vector<int64_t> A;
  std::vector<int64_t> B;

  context0.in = &A;
  context0.out = &B;

  context1.in = &B;
  context1.out = &A;

  while(true)
  {
    int res0 = runcontext(codes,context0);
    printf("YIELD %i %i\n", A.size(), B.size());

    int res1 = runcontext(codes,context1);
    printf("YIELD %i %i\n", A.size(), B.size());

    if(res0==2 && res1==2)
    {
      printf("deadlock\n");
      break;
    }
  }

  printf("numsent %i %i\n", context0.numsent, context1.numsent);
}
