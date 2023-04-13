/****************************************
 * Name            : minishell.c
 * Authors         : Anita Bui-Martinez (adb2221) and Cristopher Marte Marte (cjm...)
 * Version:          
 * Last modified   :
 * Description     :
 */
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
	struct sigaction action; 
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = catch_signal; 

	if(sigaction(SIGINT, &action, NULL) == -1){
		perror("sigaction(SIGINT)");
		return EXIT_FAILURE;
	}
	
	char cwd[1024]; 
	if(getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd() error"); 
		return EXIT_FAILURE;
	}

	char buf[128];
	while(true){
		printf("%s[%s]$ ", BRIGHTBLUE, cwd);
		printf("%s", DEFAULT);
		fflush(stdout);
		if(fgets(buf, sizeof(buf), stdin) == NULL){
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
		// this is just to test - have to remove
		printf("You entered '%s'.\n", buf);
		if(!strcmp(buf, "exit")) {
			break;
		}
	}

	return EXIT_SUCCESS; 


}
