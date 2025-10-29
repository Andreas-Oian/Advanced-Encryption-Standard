#include <stdio.h>
#include <aes_lib.h>

int input[16] = {0x19, 0x3d, 0xe3, 0xbe, 0xa0, 0xf4, 0xe2, 0x2b, 0x9a, 0xc6, 0x8d, 0x2a, 0xe9, 0xf8, 0x48, 0x08};

int state[4][4];

int main() {
	inputToState(input);
	subBytes(state);
	shiftRows(state);
	mixColumns(state);
	for (int r = 0; r < 4; r++)
	{
		printf("%4x %4x %4x %4x\n", state[r][0], state[r][1], state[r][2], state[r][3]);
	}
}
