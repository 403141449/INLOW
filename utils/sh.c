#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static int executeCommand(char* arguments[]);
static const char* getExecutablePath(const char* command);

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	
	while (true)
	{
		fputs("$>", stderr);
		char buffer[81];
		fgets(buffer, sizeof(buffer), stdin);
		size_t length = strlen(buffer);

		if (buffer[length - 1] == '\n')
				buffer[length - 1] = '\0';

		size_t argumentCount = 1;
		for (size_t i = 0; buffer[i]; i++)
		{
			if (buffer[i] == ' ')
			{
				argumentCount++;
			}
		}

		char** arguments = malloc((argumentCount + 1) * sizeof(char*));
		char* str = strtok(buffer, " ");
		for (size_t i = 0; i < argumentCount; i++)
		{
			arguments[i] = str;
			str = strtok(NULL, " ");
		}
		arguments[argumentCount] = NULL;

		if (arguments[0])
			executeCommand(arguments);
		free(arguments);
	}
}
static int executeCommand(char* arguments[])
{
	const char* command = arguments[0];
	char argumentexit[] = "exit";
	if (strcmp(command,argumentexit) == 0)
	{
		exit(0);
	}
	pid_t pid = fork();

	if (pid < 0)
	{
		fputs("fork() failed\n", stderr);
		return -1;
	}
	else if (pid == 0)
	{
		if (!strchr(command, '/'))
		{
			command = getExecutablePath(command);
		}
		if (command)
		{
			execv(command, arguments);
		}
		fputs("Command not found\n", stderr);
		_Exit(127);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}

static const char* getExecutablePath(const char* command)
{
	size_t commandLength = strlen(command);
	const char* path = getenv("PATH");
	while (*path)
	{
		size_t length = strcspn(path, ":");
		char* buffer = malloc(commandLength + length + 2);
		memcpy(buffer, path, length);
		buffer[length] = '/';
		memcpy(buffer + length + 1, command, commandLength);
		buffer[commandLength + length + 1] = '\0';

		if (access(buffer, X_OK) == 0)
		{
			return buffer;
		}
		free(buffer);
		path += length + 1;
	}
	return NULL;
}
