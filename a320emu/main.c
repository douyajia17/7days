#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "cpu.h"
#include "load.h"
#include "disasm.h"

extern uint8_t *mem;

int main(int argc, char** argv)
{
  cpu p;
  int c, opt_disasm=0, opt_regdump=0, opt_interactive=0;

  while((c = getopt(argc, argv, "drit")) != -1){
    switch(c){
    case 'd':
      opt_disasm = 1;
      break;
    case 'r':
      opt_regdump = 1;
      break;
    case 'i':
      opt_interactive = 1;
      break;
    case 't':
      opt_interactive = 2;
      break;
    default:
      printf("invalid option %c\n", c);
      return -1;
    }
  }

  if(argc <= optind){
    printf("usage:\n  a320emu [drit] xxx.app\n");
    return -1;
  }

  mem = load_app(argv[optind], opt_disasm);
  if(opt_disasm){
    return 0;
  }

  init_cpu(&p);
  while(1){
    run_app(&p, opt_interactive, opt_regdump);
  }
  return 0;
}
