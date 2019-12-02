
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PERMISSION_FILE "permission.txt"
#define DATA_FILE "data.txt"

int main(int argc, char *argv[])
{
	char ch;
	FILE *pp, *fp;

	if (argc != 2) {
		fprintf(stderr, "Usage:%s <Message>", argv[0]);
		exit(0);
		}
	char *data = argv[1];

	/*Open permission file and write no, so that the other process does not read from the file untill all the contents are written */
	if((pp = fopen(PERMISSION_FILE, "w")) == NULL) {
		printf("Error opening pp file");
		exit(0);
		}
	fprintf(pp, "%s", "N");
	fclose(pp);

/*Getting user input data  and storing in data file */
	fp = fopen(DATA_FILE, "w");
	fprintf(fp, "%s", argv[1]);
	fclose(fp);

	/*Changing permission of permission file to Y so that the other process can read*/
	if((pp = fopen(PERMISSION_FILE, "w")) == NULL) {
		printf("Error opening pp file");
		exit(0)
		}
	fprintf(pp, "%s", "Y");
	fclose(pp);


	return 0;
	
	

}


