#include <stdio.h>

int main(int argc, char *argv[]) {

	int numeric[] = {1, 2, 3, 4, 5};
	char *alpha[] = {"one", "two", "three", "four", "five"};

	int count = sizeof(numeric)/sizeof(int);

	//normal print
	for(int i = 0; i < count; i++) {
		printf("Alpha - %s is %d\n", alpha[i], numeric[i]);
	}

	printf("------\n");

	int *numericPtr = numeric;
	char **alphaPtr = alpha;

	//print using pointer array
	for(int i = 0; i < count; i++) {
		printf("Alpha - %s is %d\n", alphaPtr[i], numericPtr[i]);
	}	

	printf("------\n");

	//print using pointer
	for(int i = 0; i < count; i++) {
		printf("Alpha - %s is %d\n", *(alphaPtr + i), *(numericPtr + i));
	}	

	return 0;
}