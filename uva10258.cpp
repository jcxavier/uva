// Author: João Xavier
// Date: 20-05-2010

/*	@JUDGE_ID:	'00000'	10258'	C++	"Contest Scoreboard"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Contestant
{
	int id;
	int score;
	int solvedCount;
	bool hasSubmitted;

	int penalty[10];
	bool solved[10];

	Contestant() {}

	Contestant(int pID): id(pID), score(0), solvedCount(0), hasSubmitted(false)
	{
		memset(penalty, 0, sizeof(int)*10);
		memset(solved, 0, sizeof(bool)*10);
	}
};

bool sortContestants(const Contestant& c1, const Contestant& c2)
{
	if (c1.solvedCount != c2.solvedCount)
		return c1.solvedCount > c2.solvedCount;

	if (c1.score != c2.score)
		return c1.score < c2.score;

	return c1.id < c2.id;
}

int main()
{
	char line[256];
	int n;
	vector<Contestant> contestants(101);

	for (scanf("%d\n", &n); n; n--)
	{
		for (int i = 0; i != 101; i++)
			contestants[i] = Contestant(i);

		cin.getline(line, 256);

		if (line[0] == 0)
			cin.getline(line, 256);

		while (!cin.eof() && (line[0] != 0))
		{
			int id = atoi(strtok(line, " "));
			int problem = atoi(strtok(NULL, " "));
			int time = atoi(strtok(NULL, " "));
			char type = strtok(NULL, " ")[0];

			contestants[id].hasSubmitted = true;

			if ((type == 'C') && (!contestants[id].solved[problem]))
			{
				contestants[id].solved[problem] = true;
				contestants[id].score += time + contestants[id].penalty[problem];
				contestants[id].solvedCount++;
			}
			else if (type == 'I')
				contestants[id].penalty[problem] += 20;

			cin.getline(line, 256);
		}

		sort(contestants.begin(), contestants.end(), sortContestants);

		for (int i = 0; i != 101; i++)
			if (contestants[i].hasSubmitted)
				printf("%d %d %d\n", contestants[i].id, contestants[i].solvedCount, contestants[i].score);

		if (n > 1)
			putchar('\n');
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
