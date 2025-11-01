typedef unsigned char byte;
typedef unsigned int poly;

byte state[4][4];

void inputToState(byte input[16])
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

poly polynomialAdd(poly a, poly b)
{
	return a ^ b;
}

poly polynomialMultiplication(poly a, poly b)
{
	poly product = 0;
	
	while (a)
	{
		product ^= ((a % 2) * b);
		b <<= 1;
		a >>= 1;
	}

	return product;
}

poly divisionAlgorithmRest(poly a, poly b)
{
	poly dividend = a;
	poly divisor = b;

	poly quotient = 0;
	poly rest = dividend;

	while (binaryLength(rest) >= binaryLength(divisor))
	{
		int degreeDifference = binaryLength(rest) - binaryLength(divisor);
		rest ^= divisor << degreeDifference;
		quotient += 1 << degreeDifference;
	}

	return rest;
}

poly divisionAlgorithmQuotient(poly a, poly b)
{
	poly dividend = a;
	poly divisor = b;

	poly quotient = 0;
	poly rest = dividend;

	while (binaryLength(rest) >= binaryLength(divisor))
	{
		int degreeDifference = binaryLength(rest) - binaryLength(divisor);
		rest ^= divisor << degreeDifference;
		quotient += 1 << degreeDifference;
	}

	return quotient;
}

poly GFMultiplication(poly a, poly b)
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
	
    byte c0 = 1;
    byte c1 = 1;
    byte c2 = 0;
    byte c3 = 0;
    byte c4 = 0;
    byte c5 = 1;
    byte c6 = 1;
    byte c7 = 0;

    byte b0 = bitN(b, 0);
    byte b1 = bitN(b, 1);
    byte b2 = bitN(b, 2);
    byte b3 = bitN(b, 3);
    byte b4 = bitN(b, 4);
    byte b5 = bitN(b, 5);
    byte b6 = bitN(b, 6);
    byte b7 = bitN(b, 7);

    byte b0p = (b0 ^ b4 ^ b5 ^ b6 ^ b7 ^ c0) << 0;
    byte b1p = (b1 ^ b5 ^ b6 ^ b7 ^ b0 ^ c1) << 1;
    byte b2p = (b2 ^ b6 ^ b7 ^ b0 ^ b1 ^ c2) << 2;
    byte b3p = (b3 ^ b7 ^ b0 ^ b1 ^ b2 ^ c3) << 3;
    byte b4p = (b4 ^ b0 ^ b1 ^ b2 ^ b3 ^ c4) << 4;
    byte b5p = (b5 ^ b1 ^ b2 ^ b3 ^ b4 ^ c5) << 5;
    byte b6p = (b6 ^ b2 ^ b3 ^ b4 ^ b5 ^ c6) << 6;
    byte b7p = (b7 ^ b3 ^ b4 ^ b5 ^ b6 ^ c7) << 7;
    
    byte bp = b0p ^ b1p ^ b2p ^ b3p ^ b4p ^ b5p ^ b6p ^ b7p;
    return bp;
}

void subBytes(byte state[4][4])
{
    for (int c = 0; c < 4; c++)
    {
    for (int r = 0; r < 4; r++)
    {
        state[r][c] = subByte(state[r][c]);
    }
    }
}

void shiftRows(byte state[4][4])
{
	for (int r = 0; r < 4; r++)
	{
		byte row[4] = { state[r][0], state[r][1], state[r][2], state[r][3]};
		for (int c = 0; c < 4; c++)
		{
			state[r][c] = row[(c + r)%4];
		}
	}
}

void mixColumns(byte state[4][4])
{
	for (int c = 0; c < 4; c++)
	{
		byte s0 = state[0][c];
		byte s1 = state[1][c];
		byte s2 = state[2][c];
		byte s3 = state[3][c];
		
		byte s0p = GFMultiplication(0x02, s0) ^ GFMultiplication(0x03, s1) ^ s2 ^ s3;
		
		byte s1p = s0 ^ GFMultiplication(0x02, s1) ^ GFMultiplication(0x03, s2) ^ s3;
				https://www.onlinegdb.com/online_c_compiler#_editor_1040591611
		byte s2p = s0 ^ s1 ^ GFMultiplication(0x02, s2) ^ GFMultiplication(0x03, s3);
				
		byte s3p = GFMultiplication(0x03, s0) ^ s1 ^ s2 ^ GFMultiplication(0x02, s3);
				
		state[0][c] = s0p;
		state[1][c] = s1p;
		state[2][c] = s2p;
		state[3][c] = s3p;
	}
}

void assignWord(byte temp[4], byte word[4])
{
    for (int j = 0; j < 4; j++)
    {
        temp[j] = word[j];
    }
}

void rotWord(byte temp[4])
{
    byte t0 = temp[0];
    byte t1 = temp[1];
    byte t2 = temp[2];
    byte t3 = temp[3];
    
    temp[0] = t1;
    temp[1] = t2;
    temp[2] = t3;
    temp[3] = t0;
}

void subWord(byte temp[4])
{
    for (int j = 0; j < 4; j++)
    {
        byte t = temp[j];
        byte s = subByte(t);
        temp[j] = s;
    }
}

byte rcon(int i)
{
    return divisionAlgorithmRest(1<<(i-1), 283);
}

void xorRcon(byte temp[4], byte rcon)
{
    temp[0] = temp[0] ^ rcon;
}

void xorWord(byte temp[4], byte word[4])
{
    for (int j = 0; j < 4; j++)
    {
        temp[j] = temp[j] ^ word[j];
    }
}

void keyExpansion(byte key[16], byte w[44][4])
{
    byte temp[4];

    for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
    {
        w[i][j] = key[4*i+j];
    }
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
    }
}

void addRoundKey(byte state[4][4], byte word[44][4], int round)
{
	for (int r = 0; r < 4; r++)
	{
	for (int c = 0; c < 4; c++)
	{
	state[r][c] = state[r][c] ^ word[c+4*round][r];
	}
	}
}
	

