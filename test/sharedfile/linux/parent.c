<<<<<<< HEAD
=======

>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
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
<<<<<<< HEAD
	fputs("N", pp);
=======
	fprintf(pp, "%s", "N");
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
	fclose(pp);

/*Getting user input data  and storing in data file */
	fp = fopen(DATA_FILE, "w");
<<<<<<< HEAD
	fputs(argv[1], fp);
=======
	fprintf(fp, "%s", argv[1]);
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
	fclose(fp);

	/*Changing permission of permission file to Y so that the other process can read*/
	if((pp = fopen(PERMISSION_FILE, "w")) == NULL) {
		printf("Error opening pp file");
<<<<<<< HEAD
		exit(0);
		}
	fputs("Y", pp);
	fclose(pp);

	return 0;

=======
		exit(0)
		}
	fprintf(pp, "%s", "Y");
	fclose(pp);


	return 0;
	
	
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9

}


