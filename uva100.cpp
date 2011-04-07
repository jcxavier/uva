// Author: João Xavier
// Date: 19-04-2010

/*	@JUDGE_ID:	'00000'	100	C++	" The 3n + 1 problem"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#define MAX_VAL		1000001

#include <iostream>
using namespace std;

int seq[MAX_VAL];

void cycle(long long n, int &max)
{
	int count = 0;

	while (n != 1)
	{
		if (n < MAX_VAL)
			n=seq[n];
		else
			n = (n % 2 == 0 ? n/2 : 3*n + 1);

		count++;
	}

	if (count+1 > max)
		max = count+1;
}

int main()
{
	memset(seq, 0, MAX_VAL*sizeof(int));
	int lower, upper;

	for (int n = 2; n != MAX_VAL; n++)
		seq[n] = (n % 2 == 0 ? n/2 : 3*n + 1);

	while (scanf("%d %d\n", &lower, &upper) != EOF)
	{
		int max = 0;

		if (lower < upper)
		{
			for (int i = lower; i <= upper; i++)
				cycle(i, max);
		}
		else
		{
			for (int i = lower; i >= upper; i--)
				cycle(i, max);
		}

		printf("%d %d %d\n", lower, upper, max);
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
