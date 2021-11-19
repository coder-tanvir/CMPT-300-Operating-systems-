	// Shell starter file
	// You may make any changes to any part of this file.

	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/wait.h>


	#define COMMAND_LENGTH 1024
	#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
	#define HISTORY_DEPTH 100
	int command_count=0,k=0;



	char history[HISTORY_DEPTH][COMMAND_LENGTH];

	/**
	 * Command Input and Processing
	 */

	/*
	 * Tokenize the string in 'buff' into 'tokens'.
	 * buff: Character array containing string to tokenize.
	 *       Will be modified: all whitespace replaced with '\0'
	 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
	 *       Will be modified so tokens[i] points to the i'th token
	 *       in the string buff. All returned tokens will be non-empty.
	 *       NOTE: pointers in tokens[] will all point into buff!
	 *       Ends with a null pointer.
	 * returns: number of tokens.
	 */
	int tokenize_command(char *buff, char *tokens[])
	{
		int token_count = 0;
		_Bool in_token = false;
		int num_chars = strnlen(buff, COMMAND_LENGTH);
		for (int i = 0; i < num_chars; i++) {
			switch (buff[i]) {
			// Handle token delimiters (ends):
			case ' ':
			case '\t':
			case '\n':
				buff[i] = '\0';
				in_token = false;
				break;

			// Handle other characters (may be start)
			default:
				if (!in_token) {
					tokens[token_count] = &buff[i];
					token_count++;
					in_token = true;
				}
			}
		}
		tokens[token_count] = NULL;
		return token_count;
	}

	/**
	 * Read a command from the keyboard into the buffer 'buff' and tokenize it
	 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
	 * buff: Buffer allocated by the calling code. Must be at least
	 *       COMMAND_LENGTH bytes long.
	 * tokens[]: Array of character pointers which point into 'buff'. Must be at
	 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
	 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
	 * in_background: pointer to a boolean variable. Set to true if user entered
	 *       an & as their last token; otherwise set to false.
	 */
	void read_command(char *buff, char *tokens[], _Bool *in_background)
	{
		*in_background = false;

		// Read input
		int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);

		if (length < 0) {
			perror("Unable to read command from keyboard. Terminating.\n");
			exit(-1);
		}

		// Null terminate and strip \n.
		buff[length] = '\0';
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = '\0';
		}
	    
	                 
						   
					  command_count++;
						     
						     
					  strcpy (history[k], buff);

						     
						     
					  k= (k+1)%10;
						  

	   
	    
		




		// Tokenize (saving original command string)
		int token_count = tokenize_command(buff, tokens);
		if (token_count == 0) {
			return;
		}

		// Extract if running in background:
		if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
			*in_background = true;
			tokens[token_count - 1] = 0;
		}
	}

	/**
	 * Main and Execute Commands
	 */
	int main(int argc, char* argv[])
	{    char lala[1023];

		char input_buffer[COMMAND_LENGTH];
		char *tokens[NUM_TOKENS];
		while (true) {

			// Get command
			// Use write because we need to use read() to work with
			// signals, and read() is incompatible with printf().
			write(STDOUT_FILENO, "$ ", strlen("$ "));
			_Bool in_background = false;
			read_command(input_buffer, tokens, &in_background);
			if(tokens[0]==NULL)
			{
				continue;
			}
			 
			 if(strcmp(tokens[0], "exit") == 0)
			 {
			 	exit(0);
			 }

			 if(strcmp(tokens[0],"pwd")==0)
			 {
			 	getcwd( lala,sizeof(lala));
			 }

			 if(strcmp(tokens[0],"cd")==0)
			 {
	               const char *f_arg[1027];
	               f_arg[0]=tokens[1];
	              int i=chdir(f_arg[0]);
	              if(i==0)
	              {
	              	write(STDOUT_FILENO, "Was a success", strlen("Was a success"));

	              }
	              else if(i==-1)
	              {
	              	write(STDOUT_FILENO, "error", strlen("error"));
	              }
	              else
	              {
	              	printf("dont know the directory");
	              }

			 }


			 if(strcmp(tokens[0],"type")==0)
			 {
			 	if((strcmp(tokens[1],"cd")==0 ))
			 	{
			 		write(STDOUT_FILENO, "cd is a shell 300 builtin", strlen("cd is a shell 300 builtin"));

			 	}
			 	else if(strcmp(tokens[1],"exit")==0)  
			 	{
			 		write(STDOUT_FILENO, "exit is a shell 300 builtin", strlen("exit is a shell 300 builtin"));
			 	}

			 	else if(strcmp(tokens[1],"pwd")==0)
			 	{
			 		write(STDOUT_FILENO, "pwd is a shell 300 builtin", strlen("pwd is a shell 300 builtin"));
			 	}

			 	else
			 	{   
			 		write(STDOUT_FILENO,tokens[1], strlen(tokens[1]));
			 		write(STDOUT_FILENO," is external to shell builtin", strlen(" is external to shell builtin"));
			 	}

			 }


			 if(strcmp(tokens[0],"history")==0)
				           {     
				                   





				                   /*
				                      for (int i = 0; i < HISTORY_DEPTH; i++)
				                     {
					                       for (int j = 0; j < COMMAND_LENGTH; j++)
					                     {
						                  history[HISTORY_DEPTH][COMMAND_LENGTH];
					                     }*/
					                     

                                         int lu=k;
					                     int first_pos;
					                     int last_pos;
					                   
                                         if(command_count<10)
                                            {
                                            	last_pos=k;
                                            	first_pos=0;
                                            	char stringmama[10];
                                            	for(int j=first_pos;j<=last_pos;j++)
                                            	{
                                            		sprintf (stringmama, "%d", j);
				                         	write(STDOUT_FILENO, stringmama, strlen(stringmama));
				                         	write(STDOUT_FILENO, "\t", strlen("\t"));
				                         	write(STDOUT_FILENO, history[j], strlen(history[j]));
				                         	write(STDOUT_FILENO, "\n", strlen("\n"));
				                       
				                         	lu=(lu+1)%10;

                                            	}
                                            }



                                           
					                       








					                     else
					                     { 
					                     			
					                     			first_pos=command_count+1-10;	
					                     				last_pos=first_pos+9;

					                     
				                       		
				                       				  char stringmama[10];
				                      			  for(int j=first_pos;j<=last_pos;j++)
				                        		 {
				                         		sprintf (stringmama, "%d", j);
				                         	write(STDOUT_FILENO, stringmama, strlen(stringmama));
				                         	write(STDOUT_FILENO, "\t", strlen("\t"));
				                         	write(STDOUT_FILENO, history[lu], strlen(history[lu]));
				                         	write(STDOUT_FILENO, "\n", strlen("\n"));
				                              
				                         	lu=(lu+1)%10;

				                         			}
                                         }

                                        





				            } 

                            //double figure !nn

				            if((tokens[0][0]=='!')&&(tokens[0][2] !='\0'))
				            {       char token1[5];
				            	    token1[0]=tokens[0][1];
				            	    token1[1]=tokens[0][2];
				            	int number_char=atoi(token1);
				            	
				            	char empty[120];
				            	
				            	sprintf (empty, "%d", number_char);
				                 write(STDOUT_FILENO, empty, strlen(empty));
				                 write(STDOUT_FILENO, history[number_char], strlen(history[number_char]));
                                  int l=0;
				                 char tokenize_string[10];
				                 
                                for( l=0;l<100;l++)
                                {
				                 tokenize_string[l]=history[number_char][l];
				             }
				                 tokenize_string[l]='\0';
				                 

				                 tokenize_command(tokenize_string,tokens);

				            }  


                              //single figure !n
				            if((tokens[0][0]=='!'))
				            {       char token1[5];
				            	    token1[0]=tokens[0][1];
				            	int number_char=atoi(token1);
				            	
				            	
				            	
				            	
				                 write(STDOUT_FILENO, history[number_char], strlen(history[number_char]));
                                  int l=0;
				                 char tokenize_string[10];
				                 
                                for( l=0;l<7;l++)
                                {
				                 tokenize_string[l]=history[number_char][l];
				             }
				                 tokenize_string[l]='\0';
				                 

				                 tokenize_command(tokenize_string,tokens);

				            }





	    

			// DEBUG: Dump out arguments:
			for (int i = 0; tokens[i] != NULL; i++) {
				write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
				write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
				write(STDOUT_FILENO, "\n", strlen("\n"));
			}
			if (in_background) {
				write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
			}
	        
	         pid_t i=fork();
	         if(i==0)
	         	{
	         		printf("This is the child process");
	         execvp(tokens[0], tokens);
	         
	                  
	            }
	             
	           else{  
	           	
	                if (in_background==false)
	                   {
	                   	waitpid(i,NULL,0);
	                   }
	                  
	             	}

	          


				           
				                      
	           	   









	         }

	       /*
			 * Steps For Basic Shell:
			 * 1. Fork a child process
			 * 2. Child process invokes execvp() using results in token array.
			 * 3. If in_background is false, parent waits for
			 *    child to finish. Otherwise, parent loops back to
			 *    read_command() again immediately.
			 */

		
		return 0;

	}