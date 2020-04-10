#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Compile with g++ -masm=intel a.cpp && ./a.out 

template <class T>
T reverse_bits(T n) {
	short bits = sizeof(n) * 8; 
	T mask = ~T(0); // equivalent to uint32_t mask = 0b11111111111111111111111111111111;

	while (bits >>= 1) {
		mask ^= mask << (bits); // will convert mask to 0b00000000000000001111111111111111;
		n = (n & ~mask) >> bits | (n & mask) << bits; // divide and conquer
	}

	return n;
}


unsigned char reverse_byte_bits(unsigned char a) {
	__asm__ __volatile__ (R"(
      		mov cx, 8
	loop:
		shr di
		rcl ax
		dec cl
		jnz short loop   
	;)");
}

uint32_t reverse_bits2(uint32_t a) {
	__asm__ __volatile__ (R"(
      		mov ecx, 32
	loop2:
		shr edi
		rcl eax
		dec cl
		jnz short loop2
	;)");
}



template <class T>
void print_binary(T n)
{	T mask = 1UL << ((sizeof(n) * 8) - 1);  // will set the most significant bit
	for(; mask != 0; mask >>= 1) putchar('0' + !!(n & mask));
	putchar('\n');
}

int main() {
	unsigned int n = 12534534U | 1U << 31;
	
	print_binary(n);
	unsigned int o = reverse_bits2(n);
	print_binary(o);
	n = reverse_bits(n);
	print_binary(n);

/*
	uint32_t n = 12;
	print_binary(n);
	n = reverse_bits(n); 
	print_binary(n);
	unsigned char c = 'a';
	print_binary(c);
	c = reverse_bits(c);
	print_binary(c);
	uint16_t s = 12;
	print_binary(s);
	s = reverse_bits(s);
	print_binary(s);
	uint64_t l = 12;
	print_binary(l);
	l = reverse_bits(l);
	print_binary(l);*/
	return 0;
}
