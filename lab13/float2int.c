#include <stdio.h>
#include <math.h>

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))
#define getsig(x)  ((x)>>31 & 1)
#define getexp(x)  ((x)>>23 & 0xff)
#define getfrac(x) ((x) & 0x7fffff)

typedef union { 
  float f;
  unsigned int i;
} U;


int float2int(float fl) {
	U u;
	int number = 0;
	u.f = fl;

	unsigned int s=getsig(u.i),e = getexp(u.i) - 127,frac = getfrac(u.i);
	
	if(fl == 0 || e & 0x80) return 0;	// Quando o valor passado for zero, ou quando o expoente for negativo, retornar 0 (no caso do expoente negativo, aproximar para zero)
	
	if(e > 30 && !s) {	// Se o expoente é maior 30 e o número não é negativo, é um caso de overflow
		printf("Overflow!!!");
		return -1;	// Retorna código -1 quando dá overflow
	}
	if((s != 0 && e == 31 && frac) || e > 31) {	// Se o número é negativo, sua mantissa não é zero, e o expoente é maior que 30, é um caso de overflow
		printf("Overflow!!!");
		return -1;	// Retorna código -1 quando dá overflow
	}

	number |= 1 << (e);
	
	if(e < 23) {
		number |= frac >> (23 - e);
	}
	else {
		number |= frac << (e - 23);
	}
	
	if(s) return -number;

	return number;
}
