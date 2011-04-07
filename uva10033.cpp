// Author: João Xavier
// Date: 20-04-2010

/*	@JUDGE_ID:	'00000'	10033	C++	"Interpreter"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
#include <string>
using namespace std;

#define FIRST(x)	(x / 100)
#define SECOND(x)	((x / 10) % 10)
#define THIRD(x)	(x % 10)

int main()
{
	string line;
	int words[1000];
	int registers[10];
	int n, instruction;

	scanf("%d\n", &n);
	while (n--)
	{
		int i = 0, count = 0;	
		memset(words, 0, 1000*sizeof(int));
		memset(registers, 0, 10*sizeof(int));

		while (getline(cin, line) && line.size() != 0)
			words[i++] = (line[0]-48)*100 + (line[1]-48)*10 + (line[2]-48);

		i = 0;
		while (words[i] != 100) // 100 means halt
		{
			instruction = words[i];
			i++;
			count++;

			switch (FIRST(instruction))
			{
				case 2: // 2dn means set register d to n (between 0 and 9)
					registers[SECOND(instruction)] = THIRD(instruction);
					break;
				case 3: // 3dn means add n to register d
					registers[SECOND(instruction)] = (registers[SECOND(instruction)]+THIRD(instruction))%1000;
					break;
				case 4: // 4dn means multiply register d by n
					registers[SECOND(instruction)] = (registers[SECOND(instruction)]*THIRD(instruction))%1000;
					break;
				case 5: // 5ds means set register d to the value of register s
					registers[SECOND(instruction)] = registers[THIRD(instruction)];
					break;
				case 6: // 6ds means add the value of register s to register d
					registers[SECOND(instruction)] = (registers[SECOND(instruction)]+registers[THIRD(instruction)])%1000;
					break;
				case 7: // 7ds means multiply register d by the value of register s
					registers[SECOND(instruction)] = (registers[SECOND(instruction)]*registers[THIRD(instruction)])%1000;
					break;
				case 8: // 8da means set register d to the value in RAM whose address is in register a
					registers[SECOND(instruction)] = words[registers[THIRD(instruction)]];
					break;
				case 9: // 9sa means set the value in RAM whose address is in register a to the value of register s
					words[registers[THIRD(instruction)]] = registers[SECOND(instruction)];
					break;
				case 0: // 0ds means goto the location in register d unless register s contains 0
					if (registers[THIRD(instruction)] != 0)
						i = registers[SECOND(instruction)];
					break;
			}
		}

		(n == 0 ? printf("%d\n", count+1) : printf("%d\n\n", count+1));
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
