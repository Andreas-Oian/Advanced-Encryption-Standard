#include <stdio.h>
#include <aes_lib.h>


unsigned char w[44][4];
unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};


void keyExpansion(unsigned char key[16], unsigned char w[44][4])
{
    unsigned char temp[4];

    for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
    {
        w[i][j] = key[4*i+j];
    }
        printf("%2d, %2x%2x%2x%2x\n", i, w[i][0], w[i][1], w[i][2], w[i][3]);

    }
    
    
    for (int i = 4; i < 44; i++)
    {
        assignWord(temp, w[i-1]);
        if (i%4 == 0) {
            rotWord(temp);
            subWord(temp);
            xorRcon(temp, rcon(i/4));
        }
        xorWord(temp, w[i-4]);
        assignWord(w[i], temp);
        printf("%2d, %2x%2x%2x%2x\n", i, w[i][0], w[i][1], w[i][2], w[i][3]);
    }
}

int main() {
    keyExpansion(key, w);
}
