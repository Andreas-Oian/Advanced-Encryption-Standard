#include <stdio.h>

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
	
    char c0 = 1;
    char c1 = 1;
    char c2 = 0;
    char c3 = 0;
    char c4 = 0;
    char c5 = 1;
    char c6 = 1;
    char c7 = 0;
    
    char b0 = bitN(b, 0);
    char b1 = bitN(b, 1);
    char b2 = bitN(b, 2);
    char b3 = bitN(b, 3);
    char b4 = bitN(b, 4);
    char b5 = bitN(b, 5);
    char b6 = bitN(b, 6);
    char b7 = bitN(b, 7);
    
    char b0p = (b0 ^ b4 ^ b5 ^ b6 ^ b7 ^ c0) << 0;
    char b1p = (b1 ^ b5 ^ b6 ^ b7 ^ b0 ^ c1) << 1;
    char b2p = (b2 ^ b6 ^ b7 ^ b0 ^ b1 ^ c2) << 2;
    char b3p = (b3 ^ b7 ^ b0 ^ b1 ^ b2 ^ c3) << 3;
    char b4p = (b4 ^ b0 ^ b1 ^ b2 ^ b3 ^ c4) << 4;
    char b5p = (b5 ^ b1 ^ b2 ^ b3 ^ b4 ^ c5) << 5;
    char b6p = (b6 ^ b2 ^ b3 ^ b4 ^ b5 ^ c6) << 6;
    char b7p = (b7 ^ b3 ^ b4 ^ b5 ^ b6 ^ c7) << 7;
    
    char bp = b0p ^ b1p ^ b2p ^ b3p ^ b4p ^ b5p ^ b6p ^ b7p;
    return bp;
}

int main()
{
    printf("%d", subByte(0x00));
}
