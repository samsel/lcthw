#include <stdio.h>

int main(int argc, char *argv[]) {

	int numbers[4] = {0};
	char characters[4] = {'a'};

	//raw print
	printf("numbers variable: %d, %d, %d, %d, \n", numbers[0], numbers[1], numbers[2], numbers[3]);
	printf("characters variable: %c, %c, %c, %c, \n", characters[0], characters[1], characters[2], characters[3]);

	printf("characters : %s \n", characters);

	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;

	characters[0] = 'S';
	characters[1] = 'A';
	characters[2] = 'M';
	characters[3] = '\0';

	printf("numbers variable: %d, %d, %d, %d, \n", numbers[0], numbers[1], numbers[2], numbers[3]);
	printf("characters variable: %c, %c, %c, %c, \n", characters[0], characters[1], characters[2], characters[3]);

	printf("sizeof numbers: %ld \n", sizeof(numbers));	
	printf("sizeof characters: %ld \n", sizeof(characters));
	printf("sizeof int: %ld \n", sizeof(int));	

	char *another_way = "sam";	
	printf("characters variable: %c, %c, %c, %c, \n", another_way[0], another_way[1], another_way[2], another_way[3]);

	return 0;
}

//In C, string is an array of chars terminated by '\0' - null byte. 