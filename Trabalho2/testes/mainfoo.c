#include <stdio.h>

unsigned char codigo[] = { 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xc7, 0x01, 0x48, 0x89, 0xf8, 0xc9, 0xc3  };


typedef int (*funcp) (int x);


int main()
{
  funcp f = (funcp)codigo;
  int i = (*f)(5);
  printf("%d\n", i);
  return 0;
}
