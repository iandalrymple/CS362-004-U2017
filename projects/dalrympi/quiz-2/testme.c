#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define STR_LEN 5

// Create global char array on stack to preserve heap mem
char s[(int)STR_LEN + 1];

// rand() % (max_number + 1 - minimum_number) + minimum_number
// only look at printable chars from 32 to 126 (space to ~)
char inputChar()
{
	char retChar = rand() % (126 + 1 - 32) + 32;
	return retChar;
}

// using a smattering of small leters and numbers 
// https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c
void inputString()
{
	static char charSet[] = "resethkfderml13";
	int len = (int)STR_LEN;
	int i = 0;
	
	for(i = 0; i < len; i++)
	{
		int key = rand() % ((int)(sizeof(charSet) - 1));
		s[i] = charSet[key];
	}
	
	s[len] = '\0';
}

void testme()
{
	int tcCount = 0;
	char c;
	int state = 0;

	while (1)
	{
		tcCount++;
		c = inputChar();
		inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) 
			state = 1;
		if (c == '(' && state == 1) 
			state = 2;
		if (c == '{' && state == 2) 
			state = 3;
		if (c == ' '&& state == 3) 
			state = 4;
		if (c == 'a' && state == 4) 
			state = 5;
		if (c == 'x' && state == 5) 
			state = 6;
		if (c == '}' && state == 6) 
			state = 7;
		if (c == ')' && state == 7) 
			state = 8;
		if (c == ']' && state == 8) 
			state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
