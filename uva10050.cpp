// Author: João Xavier
// Date: 20-05-2010

/*	@JUDGE_ID:	'00000'	10050'	C++	"Hartals"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;


int main()
{
	int n;
	int parties;
	int days;
	int hartalP[101];

	for (scanf("%d", &n); n; n--)
	{
		scanf("%d", &days);
		scanf("%d", &parties);

		memset(hartalP, 0, sizeof(int)*101);

		for (int i = 1; i <= parties; i++)
			scanf("%d", &hartalP[i]);

		int hartals = 0;
		
		for (int currentDay = 1; currentDay <= days; currentDay++)
			if ((((currentDay+1) % 7) != 0) && ((currentDay % 7) != 0))
			{
				for (int j = 1; j <= parties; j++)
					if (currentDay % hartalP[j] == 0)
					{
						hartals++;
						break;
					}
			}

		printf("%d\n", hartals);
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
