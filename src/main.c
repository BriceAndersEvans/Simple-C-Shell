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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Loop for taking input & executing the input (in-progress)
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
        // Read lines (line)
        // Split lines (args)
        // Execute lines (status)

        // Free memory 
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
    //Load configuration files

    //Run command for loop
    c_loop();
    //Run closing business (shutdown/clean)

    return EXIT_SUCCESS;
}