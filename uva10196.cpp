// Author: João Xavier
// Date: 20-04-2010

/*	@JUDGE_ID:	'00000'	10196	C++	"Check the Check"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

#define isUpper(x) ((x >= 65 && x < 97) ? 1 : 0)
#define toLower(x) (x+32)

bool checkP1[15][15];
bool checkP2[15][15];

void dgMovement(int player, int i, int j, const char field[15][15])
{
	for (int a = i-1, b = j-1; a >= 3 && b >= 3; a--, b--)
		if (field[a][b] != '.')
		{
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
	
	for (int a = i+1, b = j+1; a < 11 && b < 11; a++, b++)
		if (field[a][b] != '.')
		{
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);

	for (int a = i+1, b = j-1; a < 11 && b >= 3; a++, b--)
		if (field[a][b] != '.')
		{
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);

	for (int a = i-1, b = j+1; b < 11 && a >= 3; a--, b++)
		if (field[a][b] != '.')
		{
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][b] = true : checkP1[a][b] = true);
}

void hvMovement(int player, int i, int j, const char field[15][15])
{
	for (int a = i-1; a >= 3; a--)
		if (field[a][j] != '.')
		{
			(player == 1 ? checkP2[a][j] = true : checkP1[a][j] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][j] = true : checkP1[a][j] = true);

	for (int a = i+1; a < 11; a++)
		if (field[a][j] != '.')
		{
			(player == 1 ? checkP2[a][j] = true : checkP1[a][j] = true);
			break;
		}
		else
			(player == 1 ? checkP2[a][j] = true : checkP1[a][j] = true);

	for (int b = j-1; j >= 3; b--)
		if (field[i][b] != '.')
		{
			(player == 1 ? checkP2[i][b] = true : checkP1[i][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[i][b] = true : checkP1[i][b] = true);

	for (int b = j+1; j < 11; b++)
		if (field[i][b] != '.')
		{
			(player == 1 ? checkP2[i][b] = true : checkP1[i][b] = true);
			break;
		}
		else
			(player == 1 ? checkP2[i][b] = true : checkP1[i][b] = true);
}

int main()
{
	char field[15][15];
	bool end = false;
	int player, p1ki, p1kj, p2ki, p2kj, ngame = 0;
	char piece;

	while (!end)
	{
		end = true;
	
		ngame++;
		memset(field, 0, sizeof(char)*225);
		memset(checkP1, false, sizeof(bool)*225);
		memset(checkP2, false, sizeof(bool)*225);

		for (int i = 3; i != 11; i++)
			for (int j = 3; j != 11; j++)
			{
				cin >> field[i][j];

				if (field[i][j] != '.')
					end = false;
			}

		if (!end)
		{
			for (int i = 3; i != 11; i++)
				for (int j = 3; j != 11; j++)
				{
					piece = field[i][j];
					player = (isUpper(piece) ? 1 : 2);
					
					if (isUpper(piece))
						piece = toLower(piece);

					switch (piece)
					{
						case 'p':
							if (player == 1)
							{
								checkP2[i-1][j-1] = true;
								checkP2[i-1][j+1] = true;
							}
							else
							{
								checkP1[i+1][j-1] = true;
								checkP1[i+1][j+1] = true;
							}
							break;
						case 'k':
							if (player == 1)
							{
								p1ki = i;
								p1kj = j;
							}
							else
							{
								p2ki = i;
								p2kj = j;
							}

							for (int a = -1; a <= 1; a++)
								for (int b = -1; b <= 1; b++)
									if (!(a == 0 && b == 0))
										(player == 1 ? checkP2[i+a][j+b] = true : checkP1[i+a][j+b] = true);
							break;
						case 'q':
							hvMovement(player, i, j, field);
							dgMovement(player, i, j, field);
							break;
						case 'r':
							hvMovement(player, i, j, field);
							break;
						case 'b':
							dgMovement(player, i, j, field);
							break;
						case 'n':
							if (player == 1)
							{
								checkP2[i-2][j-1] = true;
								checkP2[i-1][j-2] = true;
								checkP2[i-2][j+1] = true;
								checkP2[i-1][j+2] = true;
								checkP2[i+2][j-1] = true;
								checkP2[i+1][j-2] = true;
								checkP2[i+2][j+1] = true;
								checkP2[i+1][j+2] = true;
							}
							else
							{
								checkP1[i-2][j-1] = true;
								checkP1[i-1][j-2] = true;
								checkP1[i-2][j+1] = true;
								checkP1[i-1][j+2] = true;
								checkP1[i+2][j-1] = true;
								checkP1[i+1][j-2] = true;
								checkP1[i+2][j+1] = true;
								checkP1[i+1][j+2] = true;
							}
							break;
					}
				}

				// result
				if (checkP1[p1ki][p1kj])
					printf("Game #%d: white king is in check.\n", ngame);
				else if (checkP2[p2ki][p2kj])
					printf("Game #%d: black king is in check.\n", ngame);
				else
					printf("Game #%d: no king is in check.\n", ngame);
		}
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
