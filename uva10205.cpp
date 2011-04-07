// Author: João Xavier
// Date: 20-05-2010

/*	@JUDGE_ID:	'00000'	10205'	C++	"Stack 'em Up"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

int main()
{
	const char* suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	const char* values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

	char line[16];
	int cards[53], newCards[53];
	int shuffles[101][53];
	int n, nShuffles;

	for (scanf("%d", &n); n; n--)
	{
		scanf("%d", &nShuffles);
		memset(shuffles, 0, 101*53*sizeof(int));

		for (int i = 0; i != 53; i++)
			cards[i] = i;

		for (int i = 1; i <= nShuffles; i++)
			for (int j = 1; j <= 52; j++)
				scanf("%d", &shuffles[i][j]);

		cin.getline(line, 16);

		if (line[0] == 0)
			cin.getline(line, 16);

		while (!cin.eof() && (line[0] != 0))
		{
			int shuffle = atoi(line);

			for (int i = 1; i <= 52; i++)
				newCards[i] = cards[ shuffles[shuffle][i] ];

			memcpy(cards, newCards, sizeof(int)*53);
			cin.getline(line, 16);
		}

		for (int i = 1; i <= 52; i++)
			printf("%s of %s\n", values[(cards[i]-1) % 13], suits[(cards[i]-1) / 13]);

		if (n > 1)
			putchar('\n');
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
