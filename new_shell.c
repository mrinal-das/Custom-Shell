#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>

#define MAXCOM 1000  // Max command length
#define MAXLIST 100  // Max number of arguments

// Clear the shell screen
#define clear() printf("\033[H\033[J")

// Function declarations
void init_shell();
int takeInput(char* str);
void printDir();
void execArgs(char** parsed);
void execArgsPiped(char** parsed, char** parsedpipe);
int parsePipe(char* str, char** strpiped);
void parseSpace(char* str, char** parsed);
int processString(char* str, char** parsed, char** parsedpipe);
int ownCmdHandler(char** parsed);
void handle_sigint(int sig);

// Initialize the shell
void init_shell() {
    clear();
    printf("\n\n************ WELCOME TO ENHANCED SHELL ************");
    printf("\nUse 'help' to see available commands, 'exit' to quit.");
    printf("\nUser: @%s", getenv("USER"));
    printf("\n****************************************************\n");
    sleep(1);
    clear();
}

// Handle Ctrl+C gracefully
void handle_sigint(int sig) {
    printf("\nUse 'exit' to quit the shell.\n>>> ");
    fflush(stdout);
}

// Take input from the user
int takeInput(char* str) {
    char* buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        free(buf);  // Free dynamically allocated memory
        return 0;
    }
    free(buf);
    return 1;
}

// Print the current working directory
void printDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\nDir: %s", cwd);
    } else {
        perror("getcwd() error");
    }
}

// Execute a single command
void execArgs(char** parsed) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCommand not found: %s", parsed[0]);
        }
        exit(0);
    } else {
        wait(NULL);
    }
}

// Execute piped commands
void execArgsPiped(char** parsed, char** parsedpipe) {
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        perror("Pipe creation failed");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        perror("Fork failed");
        return;
    }

    if (p1 == 0) {
        close(pipefd[0]);  // Close reading end in the child
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(parsed[0], parsed) < 0) {
            printf("\nFailed to execute: %s", parsed[0]);
            exit(0);
        }
    } else {
        p2 = fork();

        if (p2 < 0) {
            perror("Fork failed");
            return;
        }

        if (p2 == 0) {
            close(pipefd[1]);  // Close writing end in the child
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nFailed to execute: %s", parsedpipe[0]);
                exit(0);
            }
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}

// Check for built-in commands
int ownCmdHandler(char** parsed) {
    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";

    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye!\n");
        exit(0);
    case 2:
        if (chdir(parsed[1]) != 0) {
            perror("cd failed");
        }
        return 1;
    case 3:
        printf("\nAvailable commands:\n - cd\n - exit\n - help\n - hello\n");
        return 1;
    case 4:
        printf("\nHello, %s! This is your custom shell.\n", getenv("USER"));
        return 1;
    default:
        return 0;
    }
}

// Parse input for pipes
int parsePipe(char* str, char** strpiped) {
    for (int i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL) break;
    }
    return (strpiped[1] != NULL);  // Returns 1 if a pipe is found
}

// Parse input by spaces
void parseSpace(char* str, char** parsed) {
    for (int i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL) break;
        if (strlen(parsed[i]) == 0) i--;
    }
}

// Process the input command
int processString(char* str, char** parsed, char** parsedpipe) {
    char* strpiped[2];
    int piped = parsePipe(str, strpiped);

    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
    } else {
        parseSpace(str, parsed);
    }

    if (ownCmdHandler(parsed)) return 0;
    return 1 + piped;
}

// Main function
int main() {
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;

    // Set up signal handling for Ctrl+C
    signal(SIGINT, handle_sigint);

    init_shell();

    while (1) {
        printDir();
        if (takeInput(inputString)) continue;

        execFlag = processString(inputString, parsedArgs, parsedArgsPiped);

        // Execute commands based on input
        if (execFlag == 1) execArgs(parsedArgs);
        if (execFlag == 2) execArgsPiped(parsedArgs, parsedArgsPiped);
    }
    return 0;
}

