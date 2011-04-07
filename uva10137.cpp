// Author: João Xavier
// Date: 17-05-2010

/*	@JUDGE_ID:	'00000'	10137'	C++	"The Trip"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

int main()
{
	double expenses[1001];
	int total;

	scanf("%d", &total);
	while (total)
	{
		memset(expenses, 0, sizeof(double)*1001);
		double avg = 0.0, negativeDifference = 0.0, positiveDifference = 0.0;

		for (int i = 1; i <= total; i++)
		{
			scanf("%lf", &expenses[i]);
			avg += expenses[i];
		}

		avg /= total;

		for (int i = 1; i <= total; i++)
			if (expenses[i] > avg)
				positiveDifference += (double)((long)((expenses[i] - avg) * 100.0)) / 100.0;
			else
				negativeDifference += (double)((long)((avg - expenses[i]) * 100.0)) / 100.0;

		if (negativeDifference > positiveDifference)
			printf("$%.2lf\n", negativeDifference);
		else
			printf("$%.2lf\n", positiveDifference);

		scanf("%d", &total);
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
