#ifndef OPCODE_H
#define OPCODE_H

struct OpCode
{
  std::string command;
  char regleft;
  char regright;
  int opleft;
  int opright;

  void print()
  {
    printf("%s ", command.c_str());
    if(regleft!=' ')
    {
      printf("%c ", regleft);
    }
    else
    {
      printf("%i ", opleft);
    }

    if(regright!=' ')
    {
      printf("%c", regright);
    }
    else
    {
      printf("%i", opright);
    }
  }
};

#endif // OPCODE_H

