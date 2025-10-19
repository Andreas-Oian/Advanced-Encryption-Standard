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

int main()
{
    for (int i = 1; i < 284; i++)
    {
        int inverse = extendedEuclidAlg(i, 283);
        printf("%d * %d = %d\n", i, inverse, GFMultiplication(i, inverse));
    }
    
    
	return 0;
}
