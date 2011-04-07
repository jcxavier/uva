// Author: João Xavier
// Date: 17-05-2010

/*	@JUDGE_ID:	'00000'	10038'	C++	"Jolly Jumpers"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

int main()
{
	int jolly[3001];
	bool isAbsolute[3001];
	int length;

	while (cin)
	{
		memset(jolly, 0, sizeof(int)*3001);
		memset(isAbsolute, 0, sizeof(bool)*3001);
		
		if (scanf("%d", &length) == EOF)
			break;

		for (int i = 1; i <= length; i++)
			scanf("%d", &jolly[i]);

		for (int i = 1; i <= length-1; i++)
			isAbsolute[abs(jolly[i] - jolly[i+1])] = true;

		bool isJolly = true;
		for (int i = 1; i <= length-1; i++)
			if (!isAbsolute[i])
			{
				isJolly = false;
				break;
			}

		if (isJolly)
			printf("Jolly\n");
		else
			printf("Not jolly\n");
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
