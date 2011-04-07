// Author: João Xavier
// Date: 24-04-2010

/*	@JUDGE_ID:	'00000'	10267	C++	"Graphical Editor"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
#include <queue>
using namespace std;

char table[255][255];
int M, N;

#define NOT_PART_OF(i, j, M, N) ((i < 1) || (i > N) || (j < 1) || (j > M))
#define PART_OF(i, j, M, N) ((i >= 1) && (i <= N) && (j >= 1) && (j <= M))

void draw(int i, int j, char color)
{
	if (NOT_PART_OF(i, j, M, N))
		return;

	table[j][i] = color;
}

void drawRectangle(int i, int iEnd, int jj, int jEnd, char color)
{
	for (; i <= iEnd; i++)
		for (int j = jj; j <= jEnd; j++)
			if (PART_OF(i, j, M, N))
				table[j][i] = color;
}

inline void addCondition(queue<pair<int, int> >& Q, const int i, const int j, const char oldColor, const char newColor)
{
	if ((PART_OF(i, j, M, N)) && (table[j][i] == oldColor))
	{
		table[j][i] = newColor;
		Q.push(make_pair(i, j));
	}
}

void fill(int i, int j, char newColor)
{
	if (NOT_PART_OF(i, j, M, N))
		return;

	queue<pair<int, int> > Q;
	Q.push(make_pair(i, j));

	char oldColor = table[j][i];

	if (oldColor == newColor)
		return;

	table[j][i] = newColor;

	while (!Q.empty())
	{
		pair<int, int> n = Q.front();
		i = n.first; j = n.second;

		Q.pop();

		addCondition(Q, i, j-1, oldColor, newColor);
		addCondition(Q, i, j+1, oldColor, newColor);
		addCondition(Q, i-1, j, oldColor, newColor);
		addCondition(Q, i+1, j, oldColor, newColor);
	}
}

void clear()
{
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			table[j][i] = 'O';
}

void print(char* name)
{
	printf("%s\n", name);

	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
			printf("%c", table[i][j]);

		putchar('\n');
	}
}

int main()
{
	char* line = new char[256];
	char color, command;
	int i1, i2, j1, j2;

	memset(table, 0, sizeof(char)*255*255);
	M = 0; N = 0;
	clear();

	while(scanf("%c", &command) != EOF)
	{	
		switch (command)
		{
			case 'I':
				scanf("%d %d", &N, &M);

			case 'C':
				clear();
				break;

			case 'L':
				scanf("%d %d %c", &i1, &j1, &color);
				draw(i1, j1, color);
				break;

			case 'V':
				scanf("%d %d %d %c", &i1, &j1, &j2, &color);
				
				if (j1 > j2) swap(j1, j2);

				drawRectangle(i1, i1, j1, j2, color);
				break;

			case 'H':
				scanf("%d %d %d %c", &i1, &i2, &j1, &color);

				if (i1 > i2) swap(i1, i2);

				drawRectangle(i1, i2, j1, j1, color);
				break;

			case 'K':
				scanf("%d %d %d %d %c", &i1, &j1, &i2, &j2, &color);

				if (i1 > i2) swap(i1, i2);
				if (j1 > j2) swap(j1, j2);

				drawRectangle(i1, i2, j1, j2, color);
				break;

			case 'S':
				scanf("%s", line);
				print(line);
				break;

			case 'F':
				scanf("%d %d %c", &i1, &j1, &color);
				fill(i1, j1, color);
				break;

			case 'X':
				return 0;
		}
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
