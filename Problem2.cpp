// Problem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

char str[100][100], words[100][100];
int R, C, W; // R: row count, C: column count, W: word count

void wordPuzzleForAlgorithm1()
{
	cout << "Algorithm 1" << endl;
	int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int dy[] = { 1, 0, -1, 1, -0, 1, 0, -1 };
	int r, c, orien;

	for (r = 0; r < R; r++)
	{
		for (c = 0; c < C; c++)
		{
			for (orien = 0; orien < 8; orien++)
			{
				// ordered triple (r, c, orien)
				for (int i = 0; i < W; i++)
				{
					int k;
					for (k = 0; k < strlen(words[i]); k++)
					{
						char letter = words[i][k];
						int x = r + dx[orien] * k;
						int y = c + dy[orien] * k;

						if (!(x >= 0 && y >= 0 && x < R && y < C && str[x][y] == letter))
						{
							break;
						}
					}
					if (k == strlen(words[i]))
					{
						int len = strlen(words[i]);
						cout << words[i] << " goes from (" << r + 1 << ", " << c + 1 << ") to (" << r + dx[orien] * (len - 1) + 1 << ", " << c + dy[orien] * (len - 1) + 1 << ")" << endl;
					}
				}
			}
		}
	}

	cout << endl;
}

void wordPuzzleForAlgorithm2()
{
	cout << "Algorithm 2" << endl;
	int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int dy[] = { 1, 0, -1, 1, -0, 1, 0, -1 };
	int r, c, orien, nc, maxlen = 0;

	for (int i = 0; i < W; i++)
	{
		maxlen = max(maxlen, strlen(words[i]));
	}

	maxlen = min(maxlen, R);
	maxlen = min(maxlen, C);

	for (r = 0; r < R; r++)
	{
		for (c = 0; c < C; c++)
		{
			for (orien = 0; orien < 8; orien++)
			{
				for (nc = 1; nc <= maxlen; nc++)
				{
					// quadruple (r, c, orien, number of characters)
					for (int i = 0; i < W; i++)
					{
						int len = strlen(words[i]), k;
						if (len != nc)
						{
							continue;
						}
						int limx = r + dx[orien] * (len - 1);
						int limy = c + dy[orien] * (len - 1);

						//check that number of characters.
						if (limx < 0 || limy < 0 || limx >= R || limy >= C)
						{
							continue;
						}

						for (k = 0; k < strlen(words[i]); k++)
						{
							char letter = words[i][k];
							int x = r + dx[orien] * k;
							int y = c + dy[orien] * k;

							if (!(x >= 0 && y >= 0 && x < R && y < C && str[x][y] == letter))
							{
								break;
							}
						}
						if (k == strlen(words[i]))
						{
							int len = strlen(words[i]);
							cout << words[i] << " goes from (" << r + 1 << ", " << c + 1 << ") to (" << r + dx[orien] * (len - 1) + 1 << ", " << c + dy[orien] * (len - 1) + 1 << ")" << endl;
							break;
						}
					}
				}
			}
		}
	}
	cout << endl;
}

void sortWords()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(words[i], words[j]) == -1)
			{
				char temp[100];
				strcpy_s(temp, words[i]);
				strcpy_s(words[i], words[j]);
				strcpy_s(words[j], temp);
			}
		}
	}
}

int findIndex(char letter)
{
	int low = 0, high = W - 1;

	while (low + 1 < high)
	{
		int mid = (low + high) / 2;

		if (words[mid][0] > letter)
		{
			high = mid;
		}
		else if (words[mid][0] < letter)
		{
			low = mid;
		}
		else
		{
			low = mid;
			break;
		}
	}

	for (; low >= 0; low--)
	{
		if (words[low][0] != letter)
			break;
	}

	return low+1;
}

void wordPuzzleForAlgorithm1BinarySearch()
{
	cout << "Algorithm 1 using binary search" << endl;
	int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int dy[] = { 1, 0, -1, 1, -0, 1, 0, -1 };
	int r, c, orien;

	for (r = 0; r < R; r++)
	{
		for (c = 0; c < C; c++)
		{
			for (orien = 0; orien < 8; orien++)
			{
				// ordered triple (r, c, orien)
				
				for (int i = findIndex(str[r][c]); i < W; i++)
				{
					if (words[i][0] != str[r][c])
					{
						break;
					}

					int k;
					for (k = 0; k < strlen(words[i]); k++)
					{
						char letter = words[i][k];
						int x = r + dx[orien] * k;
						int y = c + dy[orien] * k;

						if (!(x >= 0 && y >= 0 && x < R && y < C && str[x][y] == letter))
						{
							break;
						}
					}
					if (k == strlen(words[i]))
					{
						int len = strlen(words[i]);
						cout << words[i] << " goes from (" << r + 1 << ", " << c + 1 << ") to (" << r + dx[orien] * (len - 1) + 1 << ", " << c + dy[orien] * (len - 1) + 1 << ")" << endl;
					}
				}
			}
		}
	}

	cout << endl;
}

void wordPuzzleForAlgorithm2BinarySearch()
{
	cout << "Algorithm 2 using binary search" << endl;
	int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int dy[] = { 1, 0, -1, 1, -0, 1, 0, -1 };
	int r, c, orien, nc, maxlen = 0;

	for (int i = 0; i < W; i++)
	{
		maxlen = max(maxlen, strlen(words[i]));
	}

	maxlen = min(maxlen, R);
	maxlen = min(maxlen, C);

	for (r = 0; r < R; r++)
	{
		for (c = 0; c < C; c++)
		{
			for (orien = 0; orien < 8; orien++)
			{
				for (nc = 1; nc <= maxlen; nc++)
				{
					// quadruple (r, c, orien, number of characters)
					for (int i = findIndex(str[r][c]); i < W; i++)
					{
						int len = strlen(words[i]), k;
						if (len != nc || words[i][0] != str[r][c])
						{
							continue;
						}
						int limx = r + dx[orien] * (len - 1);
						int limy = c + dy[orien] * (len - 1);

						//check that number of characters.
						if (limx < 0 || limy < 0 || limx >= R || limy >= C)
						{
							continue;
						}

						for (k = 0; k < strlen(words[i]); k++)
						{
							char letter = words[i][k];
							int x = r + dx[orien] * k;
							int y = c + dy[orien] * k;

							if (!(x >= 0 && y >= 0 && x < R && y < C && str[x][y] == letter))
							{
								break;
							}
						}
						if (k == strlen(words[i]))
						{
							int len = strlen(words[i]);
							cout << words[i] << " goes from (" << r + 1 << ", " << c + 1 << ") to (" << r + dx[orien] * (len - 1) + 1 << ", " << c + dy[orien] * (len - 1) + 1 << ")" << endl;
							break;
						}
					}
				}
			}
		}
	}
	cout << endl;
}

int main()
{
	cin >> R >> C;

	for (int i = 0; i < R; i++)
	{
		cin >> str[i];
	}

	cin >> W;

	for (int i = 0; i < W; i++)
	{
		cin >> words[i];
	}

	wordPuzzleForAlgorithm1();
	wordPuzzleForAlgorithm2();

	sortWords();
	for (int i = 0; i < W; i++)
	{
		cout << words[i] << " ";
	}

	cout << endl;

	wordPuzzleForAlgorithm1BinarySearch();
	wordPuzzleForAlgorithm2BinarySearch();

	return 0;
}

/*
4 4
this
wats
oahg
fgdt
4
this two fat that
*/
/*
* Word finding problem
* 
* A. Complexity of algorithms
*		1. O(80 * R * C * W)
*		2. O(80 * ML * R * C * W) // ML: MAXLENGTH OF WORDS
* B. Complexity of algorithms
*		1. O(80 * R * C * log(W))
*		2. O(80 * ML * R * C * log(W)) // ML: MAXLENGTH OF WORDS
*/

/*
* Problem 3.
* 
*	A. Evaluate 2^100 (mod 5)
*			2^1 = 2 (mod 5) ---  initial
*			2^2 = 4 (mod 5)
*			2^3 = 3 (mod 5)
*			2^4 = 1 (mod 5)	---  initial
* 
*			2^5 = 2 (mod 5) ---
*			2^6 = 4 (mod 5) 
*			2^7 = 3 (mod 5) 
*			2^8 = 1 (mod 5) ---
* 
*			As you can see, a period exists.
*			2^x = 2^(x-4) (mod 5) when x>=4
*			
*			so, 2^100 = 2^96 = ... = 2^4 (mod 5) => 2^100 = 1(mod 5)
* 
*	B. Given the fibonaaci numbers fn = fn-1 + fn-2, with f0 = 1; f1 = 1,
*			
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
