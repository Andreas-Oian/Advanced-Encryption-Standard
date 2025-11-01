#include <stdio.h>
#include "aes_lib.h"


byte w[44][4];
byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
byte input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
int main() {

	inputToState(input);

	keyExpansion(key, w);

	addRoundKey(state, w, 0);
	
	for (int round = 1; round < 10; round++){
		subBytes(state);
		shiftRows(state);
		mixColumns(state);
		addRoundKey(state, w, round);
	}
	subBytes(state);
	shiftRows(state);
	addRoundKey(state, w, 10);


	for (int r = 0; r < 4; r++)
	{
		printf("%4x%4x%4x%4x\n", state[r][0], state[r][1], state[r][2], state[r][3]);
	}
}
