// Author: João Xavier
// Date: 20-04-2010

/*	@JUDGE_ID:	'00000'	706	C++	"LCD Display"	*/

/*	@BEGIN_OF_SOURCE_CODE	*/

#include <iostream>
#include <string>
using namespace std;

#define BIT(x, n) ((x) & (1 << (7-(n))))

/*		  0
		 ---
		|	|
	  1 |	| 2
		| 3	|
		 ---
		|	|
	  4 |	| 5
		|	|
		 ---
		  6
*/

//								0		1		2		3		4		5		6		7		8		9							
unsigned char numbers[10] = {	0xee,	0x24,	0xba,	0xb6,	0x74,	0xd6,	0xde,	0xa4,	0xfe,	0xf6};
int s;
string n, on, off;

void horizontal_print(int bit)
{
	for (int i = 0; i != n.size()-1; i++)
		cout << " " << (BIT(numbers[n[i] - 48], bit) ? on : off) << "  ";

	cout << " " << (BIT(numbers[n[n.size()-1] - 48], bit) ? on : off) << " " << endl;
}

void vertical_print(int bit)
{
	for (int size = 0; size != s; size++)
	{
		for (int i = 0; i != n.size()-1; i++)
			cout << (BIT(numbers[n[i] - 48], bit) ? "|" : " ") << off
				 <<	(BIT(numbers[n[i] - 48], bit+1) ? "|" : " ") << " ";

		cout << (BIT(numbers[n[n.size()-1] - 48], bit) ? "|" : " ") << off
			 << (BIT(numbers[n[n.size()-1] - 48], bit+1) ? "|" : " ") << endl;
	}
}

int main()
{
	cin >> s >> n;

	while (s != 0 || n != "0")
	{
		on = string(s, '-');
		off = string(s, ' ');

		horizontal_print(0);
		vertical_print(1);
		horizontal_print(3);
		vertical_print(4);
		horizontal_print(6);

		cout << endl;
		cin >> s >> n;
	}

	return 0;
}

/*	@END_OF_SOURCE_CODE	*/
