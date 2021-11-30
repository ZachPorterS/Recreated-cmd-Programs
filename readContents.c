/*
 * Zachary S. Porter
 * 2021/06/07
 * CSCI 4100
 * This program will read the contents of a given text file
 * to the command line
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *stream;
	int reader;
	char *fileName = argv[1];

	stream = fopen(fileName, "r");

	/* Checks if the file requested exists. */
	if (stream == NULL) {
		printf("ERROR: No such File exists.\n");
		return 1;
	}

	while ((reader = getc(stream)) != EOF)
		putc(reader, stdout);

	fclose(stream);
	return 0;
}
