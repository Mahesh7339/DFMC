
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PERMISSION_FILE "permission.txt"
#define DATA_FILE "data.txt"

int poll_file();

int main(int argc, char *argv[])
{
	int choice;
	while(1) {
		choice = poll_file();
		printf("%d.", choice);
		}

}

int poll_file()
{

	FILE *pp;
	char ch[2];
	if((pp = fopen(PERMISSION_FILE, "r")) == NULL) {
		printf("Error opening pp file");
		exit(0);
		}

	fgets(ch, 2, pp);
	printf("%s.", ch);
	//sleep(2);
	fclose(pp);
	if (strcmp(ch, "Y") == 0)
		return 0;

	return 1;

}
