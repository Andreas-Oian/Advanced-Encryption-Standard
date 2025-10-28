#include <stdio.h>

int input[16] = {0x19, 0x3d, 0xe3, 0xbe, 0xa0, 0xf4, 0xe2, 0x2b, 0x9a, 0xc6, 0x8d, 0x2a, 0xe9, 0xf8, 0x48, 0x08};

int state[4][4];

void inputToState(int input[16])
{
    for (int c = 0; c < 4; c++)
    {
    for (int r = 0; r < 4; r++)
    {
        state[r][c] = input[r+4*c];
    }
    }
}

unsigned int binaryLength(int n)
{
  unsigned int count = 0;
  while (n) 
  {
    count += 1;
    n >>= 1;
  }
  return count;
}

unsigned int polynomialAdd(int a, int b)
{
	return a ^ b;
}

unsigned int polynomialMultiplication(int a, int b)
{
	unsigned int product = 0;
	
	while (a)
	{
		product ^= ((a % 2) * b);
		b <<= 1;
		a >>= 1;
	}

	return product;
}

int divisionAlgorithmRest(int a, int b)
{
	int dividend = a;
	int divisor = b;

	int quotient = 0;
	int rest = dividend;

	while (binaryLength(rest) >= binaryLength(divisor))
	{
		int degreeDifference = binaryLength(rest) - binaryLength(divisor);
		rest ^= divisor << degreeDifference;
		quotient += 1 << degreeDifference;
	}

	return rest;
}

int divisionAlgorithmQuotient(int a, int b)
{
	int dividend = a;
	int divisor = b;

	int quotient = 0;
	int rest = dividend;

	while (binaryLength(rest) >= binaryLength(divisor))
	{
		int degreeDifference = binaryLength(rest) - binaryLength(divisor);
		rest ^= divisor << degreeDifference;
		quotient += 1 << degreeDifference;
	}

	return quotient;
}

int GFMultiplication(int a, int b)
{
  return divisionAlgorithmRest(polynomialMultiplication(a, b), 283);
}

int extendedEuclidAlg(int a, int b)
{
  int r1 = a;
  int r2 = b;

  int q = divisionAlgorithmQuotient(r1, r2);
  int r = divisionAlgorithmRest(r1, r2);
    
  int s1 = 1;
  int s2 = 0;
  int s = s1 ^ GFMultiplication(s2, q);
    
  int t1 = 0;
  int t2 = 1;
  int t = t1 ^ GFMultiplication(t2, q);
    
  while (r != 0)
  {
    r1 = r2;
    r2 = r;
      
    q = divisionAlgorithmQuotient(r1, r2);
    r = divisionAlgorithmRest(r1, r2);
      
    s1 = s2;
    s2 = s;
      
    t1 = t2;
    t2 = t;
      
    s = s1 ^ polynomialMultiplication(s2, q);
    t = t1 ^ polynomialMultiplication(t2, q);    
  }
    
  s1 = s2;
  s2 = s;
        
  t1 = t2;
  t2 = t;
    
  r1 = r2;
    
  return s1;
}

char bitN(char b, char n)
{
    char bit_status = (b >> n) & 1; 
    return bit_status;
}

int subByte(int b)
{
	if (b != 0)
	{
	    b = extendedEuclidAlg(b, 283);
	}
	
    int c0 = 1;
    int c1 = 1;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    int c5 = 1;
    int c6 = 1;
    int c7 = 0;
    
    int b0 = bitN(b, 0);
    int b1 = bitN(b, 1);
    int b2 = bitN(b, 2);
    int b3 = bitN(b, 3);
    int b4 = bitN(b, 4);
    int b5 = bitN(b, 5);
    int b6 = bitN(b, 6);
    int b7 = bitN(b, 7);
    
    int b0p = (b0 ^ b4 ^ b5 ^ b6 ^ b7 ^ c0) << 0;
    int b1p = (b1 ^ b5 ^ b6 ^ b7 ^ b0 ^ c1) << 1;
    int b2p = (b2 ^ b6 ^ b7 ^ b0 ^ b1 ^ c2) << 2;
    int b3p = (b3 ^ b7 ^ b0 ^ b1 ^ b2 ^ c3) << 3;
    int b4p = (b4 ^ b0 ^ b1 ^ b2 ^ b3 ^ c4) << 4;
    int b5p = (b5 ^ b1 ^ b2 ^ b3 ^ b4 ^ c5) << 5;
    int b6p = (b6 ^ b2 ^ b3 ^ b4 ^ b5 ^ c6) << 6;
    int b7p = (b7 ^ b3 ^ b4 ^ b5 ^ b6 ^ c7) << 7;
    
    int bp = b0p ^ b1p ^ b2p ^ b3p ^ b4p ^ b5p ^ b6p ^ b7p;
    return bp;
}

void subBytes(int state[4][4])
{
    for (int c = 0; c < 4; c++)
    {
    for (int r = 0; r < 4; r++)
    {
        state[r][c] = subByte(state[r][c]);
    }
    }
}

void shiftRows(int state[4][4])
{
	for (int r = 0; r < 4; r++)
	{
		int row[4] = { state[r][0], state[r][1], state[r][2], state[r][3]};
		for (int c = 0; c < 4; c++)
		{
			state[r][c] = row[(c + r)%4];
		}
	}
}


int main() {
	inputToState(input);
	subBytes(state);
	shiftRows(state);
	for (int r = 0; r < 4; r++)
	{
		printf("%4x %4x %4x %4x\n", state[r][0], state[r][1], state[r][2], state[r][3]);
	}
}
