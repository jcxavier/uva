// Author: João Xavier
// Date: 19-04-2010

/*	@JUDGE_ID:	'00000'	10189	C++	" Minesweeper"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

#define MAX 102

int main()
{
	int m, n, number = 1;
	char c;
	int field[MAX][MAX];

	scanf("%d %d", &m, &n);
	while (m != 0 && n != 0)
	{
		memset(field, 0, sizeof(int)*MAX*MAX);

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
			{
				cin >> c;
				field[i][j] = (c == '*' ? -10 : 0);
			}

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				if (field[i][j] < 0)
				{
					for (int newI = i-1; newI <= i+1; newI++)
						for (int newJ = j-1; newJ <= j+1; newJ++)
							field[newI][newJ]++;
				}

		printf("Field #%d:\n", number);

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
				if (field[i][j] < 0)
					putchar('*');
				else
					printf("%d", field[i][j]);

			putchar('\n');
		}

		number++;
		scanf("%d %d", &m, &n);

		if (m != 0 && n != 0)
			putchar('\n');
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
