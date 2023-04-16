/****************************************
 * Name            : minishell.c
 * Authors         : Anita Bui-Martinez (adb2221) and Cristopher Marte Marte (cjm2301)
 * Version:          
 * Last modified   :
 * Description     :
**************************************** */

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BRIGHTBLUE "\x1b[34;1m"
#define DEFAULT    "\x1b[0m"

volatile sig_atomic_t signal_val = 0;

/* Signal Handler */
void catch_signal(int sig){
	signal_val = sig;
}

int main(){
	//set up the signal catcher 
	struct sigaction action; 
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = catch_signal; 

	if(sigaction(SIGINT, &action, NULL) == -1){
		perror("sigaction(SIGINT)");
		return EXIT_FAILURE;
	}
	
	// this is to get the cwd so you can print it later
	char cwd[1024]; 
	if(getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd() error"); 
		return EXIT_FAILURE;
	}

	// the main looop
	while(true){
		char buf[4096];
		char *args[2048];
		char *token;
		int num_args = 0;

		printf("%s[%s]$ ", BRIGHTBLUE, cwd);
		printf("%s", DEFAULT);
		fflush(stdout);
		if(fgets(buf, 4096, stdin) == NULL){
			if(errno = EINTR) {
				printf("\n");
				errno = 0;
				continue; 
				// we need to fix this. see part 6
			} else if (feof(stdin)) {
				printf("\n");
				return EXIT_SUCCESS; 
			} else if (ferror(stdin)) {
				printf("\n");
				return EXIT_FAILURE;
			}
		}
		char *eoln = strchr(buf, '\n');
		if(eoln != NULL){
			*eoln = '\0';
		}

		token = strtok(buf, " \t\n");
		while(token != NULL && num_args < 2048 - 1){
			args[num_args++] = token; 
			token = strtok(NULL, " \t\n");
		}
		args[num_args] = NULL;

		// this is just to test - have to remove
		//printf("You entered: '%s'.\n", buf);
		for(int i = 0; i < num_args; i++){
			printf("args[%d] = %s\n", i, args[i]); 
		}

		// see what the user entered and if it's a special command 
		// if not, we need to send it to exec
		if(!strcmp(args[0], "exit")) {
			break;
		}
	}


	/*
	 * Attempting Part 5
	 */
	  struct passwd *pw = getpwnam(username);
	  if (!pw) {
	  fprintf(stderr, "Error: Cannot get passwd entry. %s.\n", strerror(errno);
	  return EXIT_FAILURE;
	 

	return EXIT_SUCCESS; 


}
