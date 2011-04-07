// Author: João Xavier
// Date: 17-05-2010

/*	@JUDGE_ID:	'00000'	10142	C++	"Australian Voting"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
using namespace std;

int main()
{
	int candidateVoteCount[21];
	int candidateVotes[1001][42];
	char candidateNames[21][128];

	int n;
	char line[128];

	for (scanf("%d", &n); n; n--)
	{
		int totalCandidates = 0, totalBallots = 0;

		memset(candidateVoteCount, 0, sizeof(int)*21);
		memset(candidateVotes, 0, sizeof(int)*1001*42);
		memset(candidateNames, 0, sizeof(char)*21*128);

		scanf("%d", &totalCandidates);

		for (int i = 0; i <= totalCandidates; i++)
			cin.getline(candidateNames[i], 128);

		cin.getline(line, 128);
		while (line[0])
		{
			if (cin.eof())
				break;

			candidateVotes[++totalBallots][1] = atoi(strtok(line, " "));

			for (int i = 2; i <= totalCandidates; i++)
				candidateVotes[totalBallots][i] = atoi(strtok(NULL, " "));

			cin.getline(line, 128);
		}

		bool winnerFound = false;
		while (!winnerFound)
		{
			int max = 0, min = 21;

			for (int i = 1; i <= totalCandidates; i++)
				if (candidateVoteCount[i] != -1)
					candidateVoteCount[i] = 0;

			for (int i = 1; i <= totalBallots; i++)
				candidateVoteCount[candidateVotes[i][1]]++;

			for (int i = 1; i <= totalCandidates; i++)
			{
				if (candidateVoteCount[i] > max)
					max = candidateVoteCount[i];

				if ((candidateVoteCount[i] != -1) && (candidateVoteCount[i] < min))
					min = candidateVoteCount[i];
			}

			if ((max == min) || (((float)max / (float)totalBallots) > 0.5f))
			{
				for (int i = 1; i <= totalCandidates; i++)
					if (candidateVoteCount[i] == max)
						printf("%s\n", candidateNames[i]);

				winnerFound = true;
			}
			else
			{
				for (int i = 1; i <= totalCandidates; i++)
					if (candidateVoteCount[i] == min)
					{
						for (int j = 1; j <= totalBallots; j++)
							for (int k = 1; k <= totalCandidates; k++)
								if (candidateVotes[j][k] == i)
								{
									memcpy(candidateVotes[j] + k, candidateVotes[j] + k + 1, sizeof(int)*(totalCandidates - k));
									memset(candidateVotes[j] + totalCandidates - k, 0, sizeof(int)*21);
								}

						candidateVoteCount[i] = -1;
					}
			}
		}

		if (n != 1)
			putchar('\n');
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
