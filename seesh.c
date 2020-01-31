/* CSC360 SEESH Assignment
 * Katherine Jacobs
 * V00783178
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include<sys/wait.h>

#define BUFSIZE 64
#define DELIM "\t\r\n\a "

/*
 * Function Signatures
*/
char *get_input(void);
char **split_line(char *line);
void main_loop();
int execute_command(char **args);
int seesh_cd(char **args);
int seesh_help(char **args);
int seesh_exit(char **args);
int seesh_setvar(char **args);
int seesh_unsetvar(char **args);
int seesh_pwd(char **args);
void handle_sigint(int sig);

int main(int argc, char **argv){

    //load config files if any.
    FILE *rcfile;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **init_args;

    char *rcloc = strcat(getenv("HOME"), "/.SEEshrc\0");
    rcfile = fopen(rcloc, "r");

    if (rcfile == NULL){
        printf("No RC File found\n");
    }
    //read rc file line by line
    if (rcfile != NULL){
        while ((read = getline(&line, &len, rcfile)) != -1){
            init_args = split_line(line);

            //Print line from rc file
            for (int i = 0; init_args[i] != NULL; i++){
                printf("%s ", init_args[i]);
            }
            printf("\n");
            execute_command(init_args);
            free(line);
            for(int i=0; init_args[i]!=NULL; i++) free(init_args[i]);
            free(init_args);
        }
    fclose(rcfile);
    }
    //get input loop
    main_loop();
} // end of main()


void main_loop(){
    char *line;
    char **args;
    int status;

    do {
        printf("? ");
        line = get_input();
        args = split_line(line);
        status = execute_command(args);

        free(line);
        for(int i=0; args[i]!=NULL; i++) free(args[i]);
        free(args);
    } while (status);
} // end of main_loop()


/*
 *seesh_read_line() reads input from user at command line
 * See README: function from tutorial
*/
char *get_input(void){
    char *line = NULL;
    size_t bufsize = 0;
    int val = getline(&line, &bufsize, stdin);
    if (val == -1){
        printf("Goodbye!\n");
        exit(0);
    }
    return line;
} // end of seesh_read_line()

/*
 * split_line() takes user input from read_line and
 * splits into tokens
 * See README: function from tutorial
*/
char **split_line(char* line){
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "SEEsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens){
                fprintf(stderr, "SEEsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DELIM);
    } // end of while loop
    tokens[position] = NULL;
    return tokens;
} // end of seesh_split_line()


/*
 * execute_command() executes command from SEEsh's command line
 * if command is not built-in, SEEsh forks and calls execvp()
*/
int execute_command(char **args){
    if (args == NULL){
        fprintf(stderr, "Error: NULL arguments\n");
        return 1;
    } else if (args[0] == NULL) {
        fprintf(stderr, "Error: NULL arguments\n");
        return 1;
    }

    size_t cmd_len = strlen(args[0]);

    if (strncmp(args[0], "cd", cmd_len) == 0) return seesh_cd(args);
    if (strncmp(args[0], "help", cmd_len) == 0) return seesh_help(args);
    if (strncmp(args[0], "exit", cmd_len) == 0) return seesh_exit(args);
    if (strncmp(args[0], "set", cmd_len) == 0) return seesh_setvar(args);
    if (strncmp(args[0], "unset", cmd_len) == 0) return seesh_unsetvar(args);
    if (strncmp(args[0], "pwd", cmd_len) == 0) return seesh_pwd(args);

    int pid = fork();
    if (pid < 0){
        printf("Error: Forking Failed");
        return 1;
    }
    if (pid == 0){
        //child process
        int status_code = execvp(args[0], args);
        if (status_code == -1){
            printf("Error with child\n");
        }
    } else {
        // parent process
        signal(SIGINT, handle_sigint);
        wait(NULL);
        }
    return 1;
} // end of execute_command()



/*
 * Built in Commands!
*/

/*
 * Prints the users current working directory
*/
int seesh_pwd(char **args){
    char *buf = (char*)malloc(sizeof(char)*128);
    getcwd(buf, 128);
    printf("%s\n", buf);
    free(buf);
    return 1;
} // end of seesh_pwd()

/*
 * sets environmental variable. If only 'set' is entered, prints list of environmental
 * variables. If variable already existis, updates value of variable.
*/
int seesh_setvar(char **args){

    if (args[1] == NULL){
        char *env_cmd = (char*)malloc(4 * sizeof(char));
        strcpy(env_cmd, "env\0");
        char **envx = (char**)malloc(2 * sizeof(char*));
        envx[0] = env_cmd;
        envx[1] = NULL;
        execute_command(envx);
        free(envx[0]);
        free(envx);
        return 1;
    } else if (args[2] == NULL) {
        if (setenv(args[1], "", 1) == -1) {
            printf("Error: set env variable");
        }
    } else if (args[3] == NULL) {
        if (setenv(args[1], args[2], 1) == -1){
            printf("Error: set env variable");
        }
    } else {
        printf("Too many arguments passed\n");
    }

    return 1;
} // end of seesh_setvar()

/*
 * removes environmental variable if it exists.
*/
int seesh_unsetvar(char **args){
    char *unset_var = args[1];
    unsetenv(unset_var);
    return 1;
} // end of seesh_unsetvar()

/*
int seesh_history(char **args){
    return 1;
}
*/

/*
 * changes the current working directory
*/
int seesh_cd(char **args){
    if (args[1] == NULL){
        chdir(getenv("HOME"));
        return 1;
    } else if (chdir(args[1]) != 0){
        printf("Error: directory does not exist\n");
    }
    return 1;
} // end of seesh_cd()

/*
 * exits SEEsh
*/
int seesh_exit(char **args){
    printf("Bye!\n");
    return 0;
}

/*
 * prints information about SEEsh's built in commands
*/
int seesh_help(char **args){
    printf("Katherine Jacob's SEEsh!\n");
    printf("The following commands are built into this shell:\n");
    printf("exit: terminates SEEsh.\n");
    printf("pwd: prints list of items in the current directory.\n");
    printf("cd: change current directory.\n");
    printf("set var [value]: creates an environment variable if it does not already exist.\n");
    printf("set: displays all environmental variables and values.\n");
    printf("unset var [value]: removes environment variable.\n");
    //printf("history: displays history of commands typed into SEEsh.\n");

    return 1;
} // end of seesh_help()

/*
 * handle_sigint catches if ctrl-C is entered to terminate child.
*/
void handle_sigint(int sig){
    printf("child terminated\n");
}
