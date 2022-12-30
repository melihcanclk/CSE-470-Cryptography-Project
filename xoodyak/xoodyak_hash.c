
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "xoodyak_cycle.h"

#define IO 4096
#define HASH 32

static void print8(u8 *bytes, size len)
{
  size i;

  FOR(i, len) {
    printf("%02x", (unsigned int)bytes[i]);
  }
  printf("\n");
}

int main(void)
{
  u8 io[IO];
  int len = 0;
  size i = 0;
  xoocycle cyc;
    printf("This program will take values from user and\n");
    printf("gives a calculated 64-bit hash value and continues taking values.\n");
    printf("until no value entered (pressing enter button two times.\n");

  FOR(i, IO) {
    io[i] = 0;
  }
  xoocycle_cyclist(&cyc, xoocycle_empty, 0, xoocycle_empty, 0,
                   xoocycle_empty, 0);
  printf("Xoodyak Settings Done!!\n");
  while (1) {
    len = read(STDIN_FILENO, io, IO);
    if (len < 0) {
      fprintf(stderr, "error\n");
      exit(EXIT_FAILURE);
    }
    if (len == 1) {
      break;
    }
    xoocycle_absorb(&cyc, io, len);
    printf("Hash Creating - ");
    print8(io, HASH);
  }
  xoocycle_squeeze(&cyc, io, HASH);
  printf("Final hash Created - ");
  print8(io, HASH);
  xoocycle_erase(&cyc);
  printf("Xoodyak Settings Removed!!\n");
  return 0;
}