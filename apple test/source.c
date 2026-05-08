#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <Windows.h>

int main()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 30; i++)
	{
		int ran = rand() % 28 + 1;
		printf("%d\n", ran);
	}


	return 0;
}