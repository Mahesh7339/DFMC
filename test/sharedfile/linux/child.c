<<<<<<< HEAD
#include <unistd.h>
=======

>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PERMISSION_FILE "permission.txt"
#define DATA_FILE "data.txt"

<<<<<<< HEAD
int poll_pfile();
int open_dfile();
int change_pfile();
int read_dfile();
=======
int poll_file();

>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
int main(int argc, char *argv[])
{
	int choice;
	while(1) {
<<<<<<< HEAD
		choice = poll_pfile();
		if(choice == 0) {
//			printf("\n Opening data file to read");
			read_dfile();
			change_pfile();
			}
=======
		choice = poll_file();
		printf("%d.", choice);
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
		}

}

<<<<<<< HEAD
int poll_pfile()
=======
int poll_file()
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
{

	FILE *pp;
	char ch[2];
	if((pp = fopen(PERMISSION_FILE, "r")) == NULL) {
		printf("Error opening pp file");
		exit(0);
		}
<<<<<<< HEAD
		fgets(ch, 2, pp);
//		printf("%s.", ch);
		fflush(stdout);
		sleep(2);
=======

	fgets(ch, 2, pp);
	printf("%s.", ch);
	//sleep(2);
	fclose(pp);
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
	if (strcmp(ch, "Y") == 0)
		return 0;

	return 1;

}
<<<<<<< HEAD

int read_dfile()
{

	FILE *fp;
	char buffer[32];
	if((fp = fopen(DATA_FILE, "r")) == NULL) {
		printf("Error opening fp file");
		exit(0);
		}
	fgets(buffer, 32, fp);
	printf("data is %s", buffer);

	fclose(fp);
}

int change_pfile()
{
	FILE *pp;
	char write_buffer[2];
	if((pp = fopen(PERMISSION_FILE, "w")) == NULL) {
		printf("Error opening file");
		exit(0);
		}
	fputs("N", pp);
	fclose(pp);
}
	
	
=======
>>>>>>> 09d3d428e7b867f9e5e1b5c517d46ae75a0284d9
