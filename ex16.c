#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Person
{
	char *name;
	int age;
	int height;
};

struct Person *Person_Create(char *name, int age, int height)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	return who;
}

void Person_Destroy(struct Person *who) {
	assert(who != NULL);
	free(who->name);
	free(who);
}

void Person_Print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tSize: %ld\n", sizeof(who));
}

int main(int argc, char *argv[]) {

	struct Person *sam = Person_Create("Sam", 12, 130);
	struct Person *john = Person_Create("John", 15, 170);

  // print them out and where they are in memory
    printf("Sam is at memory location %p:\n", sam);
    Person_Print(sam);

    printf("John is at memory location %p:\n", john);
    Person_Print(john);	

    Person_Destroy(sam);
    Person_Destroy(john);

	return 0;
}

