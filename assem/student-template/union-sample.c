/*
 *
 * For detailed info regarding scanf, refer manpage at linprog
 *    % man 3 scanf 
 *
 * Try keyboard input with -0.75 and compare its internal single precision
 *    floating point representation in page 201
 *   
 */

#include <stdio.h>

union {
  float f;
  unsigned int x;
  struct {
    unsigned int F:23;
    unsigned int E:8;
    unsigned int S:1;
  } FPS;
} u;

int main()
{
  printf("Type any floating point number (suggestion -0.75): ");
  scanf("%f", &u.f);
  printf("Float representation: %08f\n", u.f);
  printf("Hexadecimal representation: %08x\n", u.x);
  printf("FPS: S=%u, E=%u, F=%u\n", u.FPS.S, u.FPS.E, u.FPS.F);
  printf("Compare the output with page 201 our textbook\n");
  return 0;
}
