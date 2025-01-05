/**
 * @file main.c
 * @author Brice Anders Evans
 * @brief 
 * @version 0.1
 * @date 2024-12-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* Imports */
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Shell Command Declarations */
int c_cd(char **args);
int c_help(char **args);
int c_exit(char **args);

/* List of builtin commands */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = 
{
  &c_cd,
  &c_help,
  &c_exit
};

int num_builtins() 
{
  return sizeof(builtin_str) / sizeof(char *);
}

/* Builtin Function Implementations */

/**
 * @brief Bultin Command: change directory
 * @param args (args[0] is cd, args[1] is the directory)
 * @return int (returns 1, in order to continue execution)
 */
int c_cd(char **args)
{
  if (args[1] == NULL) 
  {
    fprintf(stderr, "Expected argument to \"cd\"\n");
  } 
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("Error");
    }
  }
  return 1;
}

/**
 * @brief Bultin Command: help/print help
 * @param args (list)
 * @return int (returns 1, in order to continue execution)
 */
int c_help(char **args)
{
  int i;
  printf("Anders' Shell\n");
  printf("Type a program's name and arguments, then press enter \n");
  printf("The following are built in commands:\n");

  for (i = 0; i < lsh_num_builtins(); i++) 
  {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
 * @brief Bultin Command: exit
 * @param args (list)
 * @return int (returns 0 in order to terminate execution)
 */
int c_exit(char **args)
{
  return 0;
}

/**
 * @brief Function launches a program and waits for a signal to terminate
 * @param args (null terminated list) (includes the program itself)
 * @return int (returns 1, in order to continue execution)
 */
int c_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) 
  {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("error");
    }
    exit(EXIT_FAILURE);
  } 
  else if (pid < 0) 
  {
    // Error forking
    perror("error");
  } 
  else 
  {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
 * @brief Function launches a bultin or a process 
 * @param args (null terminated list)
 * @return int, 1 if shell should continue to run, and 0 if the shell should terminate
 */
int c_execute(char **args)
{
  int idx;

  // No command or "empty command"
  if (args[0] == NULL) 
  {
    return 1;
  }

  for (idx = 0; idx < lsh_num_builtins(); idx++) 
  {
    if (strcmp(args[0], builtin_str[idx]) == 0) 
    {
      return (*builtin_func[idx])(args);
    }
  }

  return c_launch(args);
}

/**
 * @brief Function reads line input of file or user
 * @return The line from stdin
 */
#define BUFFSIZE 1024
char *c_read_line(void)
{
    int buffersize = BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffersize);
    int character;

    if(!buffer) 
    {
        fprintf(stderr, " Allocation Error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // character reads a character
        character = getchar();

        if(character == EOF || character == '\n')
        {
            // Null Character
            buffer[position] = '\0';
            return buffer;
        }
        else 
        {
            buffer[position] = character;
        }
        position++;

        // Reallocation of buffer
        if (position >= buffersize)
        {
            buffersize += BUFFSIZE;
            buffer = realloc(buffer, buffersize);
            if (!buffer)
            {
                fprintf(stderr, " Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


/**
 * @brief Function for spliting a line into a list of arguments(tokens)
 * @param line
 * @return Array of tokens (null-terminated)
 */
#define token_buffersize 64
#define token_delim " \t\r\n\a"
char **c_split_line(char *line)
{
    int buffersize = token_buffersize, position = 0;
    char **tokens = malloc(buffersize * sizeof(char*));
    char *token;

    if(!token)
    {
        fprintf(stderr, " Allocation Error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, token_delim);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= buffersize)
        {
            buffersize += token_buffersize;
            tokens = realloc(tokens, buffersize * sizeof(char*));
            if(!tokens)
            {
                printf(stderr, " Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, token_delim);
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * @brief Function for taking input & executing the input
 * 
 */
void c_loop(void)
{
    char *line;
    char **args;
    int status;

    do 
    {
        printf("> ");
        line = c_read_line();
        args = c_split_line(line);
        status = c_excecute(args);

        free(line);
        free(args);
    } while (status);
}

/**
 * @brief Main (in-progress)
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return status code
 */
int main(int argc, char **argv)
{
    //Load configuration files (TBD)

    //Call looping function
    c_loop();

    return EXIT_SUCCESS;
}