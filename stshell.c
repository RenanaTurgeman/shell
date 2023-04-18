#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>

int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char *token;
	// flags:
	int flag_pipe = 0; // |

	while (1)
	{
		printf("\033[1;32m"); // Set the text color to green and bold
		printf("stshell> ");
		printf("\033[0m"); // Reset the text color to the default

		fgets(command, 1024, stdin);
		command[strlen(command) - 1] = '\0'; // replace \n with \0

		/* parse command line */
		i = 0;
		token = strtok(command, " ");
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;

		/* Is command empty */
		if (argv[0] == NULL)
			continue;

		// Check if user wants to exit
		if (strcmp(command, "exit") == 0)
		{
			return 0;
		}

		pid_t pid = fork();
		if (pid == 0) // child
		{
			for (int j = 0; argv[j] != NULL; j++)
			{
				if (strcmp(argv[j], ">>")==0)
				{
					argv[j] = NULL;
					char* text= argv[j+1];
					int outA = open(text, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
					dup2(outA, STDOUT_FILENO);
					close(outA);
					break;
				}
				else if (strcmp(argv[j], ">")==0) //out
				{
					argv[j] = NULL;
					char* text= argv[j+1];
					int out = open(text, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
					dup2(out, STDOUT_FILENO);
					close(out);
					break;
				}
				else if (strcmp(argv[j], "<")==0) //in
				{
					argv[j] = NULL;
					char* text= argv[j+1];
					int in = open(text, O_RDONLY);
					dup2(in, STDIN_FILENO);
					close(in);
				}
				if (strcmp(argv[j], "|")==0)
				{
					flag_pipe = 1;
					
				}
			}

				execvp(argv[0], argv);

				fprintf(stderr, "Error: %s\n", strerror(errno));
		}
		wait(NULL);
		// if (getppid())
		// {
		// 	/* code */
		// }
	}
}
