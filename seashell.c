/* Zachary S. Porter
 * CSCI 4100
 * Programming Assignment 2
 * The Seashell -  a simple shell that executes commands
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int MAX_LINE = 256;
const int MAX_ARGS = 64;

void process_cmd(char *cmd, char *args[]);
void execute_cmd(char *args[]);

int main() {
	int length;
	char cmd[MAX_LINE];
	char *args[MAX_ARGS];
	printf("\t***************************\n\t**** Seashell Terminal ****");
	printf("\n\t***************************\n");

	while (1) {
		printf("\n>>> ");
		fflush(stdin);
		fflush(stdout);

		fgets(cmd, sizeof(cmd), stdin);
		length = strlen(cmd);

		/* Trim input buffer */
		if (length > 0 && cmd[length - 1] == '\n') {
			cmd[length - 1] = '\0';
		}

		printf("\n");
		/* Check if the cmd entered if  "exit", if so exit successfully. */
		if (strcmp(cmd, "exit") == 0) {
			printf("Seashell Terminal exited successfully\n");
			exit(0);
		} /* Assume cmd is valid and parse it */
		process_cmd(cmd, args);
	}

	return 0;
}

/* Parse the input from user to read into execute_cmd */
void process_cmd(char *cmd, char *args[]) {
	int i = 0;
	char *separator = " ";
	char *token = strtok(cmd, separator);

	while (token != NULL) {
		args[i] = strdup(token);
		i++;
		token = strtok(NULL, separator);
	}

	args[i] = NULL; /* Clears the buffer */
	execute_cmd(args);
}

/* Create a fork child to execute the command given,
 * and return an error message if fork failed or
 * the command could not be executed.
 */
void execute_cmd(char *args[]) {
	pid_t pid = fork();

	if (pid < 0) {
		printf("ERROR:: Failed to fork child.\n");
	} else if (pid == 0) {
		if (execvp(args[0], args) < 0) {
			printf("ERROR:: Could not execute command: %s", *args, ".\n");
			exit(0);
		}
		/* Run program with parent input */
		execvp(args[0], args);
	} else {
		wait(NULL);
		return;
	}
}
