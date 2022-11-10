#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>

int main(){

        int fd1[2];
        int fd2[2];
        char fixed_str[] = " have a good day ";
        char input_str[100];
        pid_t P;

        void sigint_handler(int sig);

        if(signal(SIGINT, sigint_handler)==SIG_ERR){
                perror("signal");
                exit(1);
                }

        if (pipe(fd1)==-1 || pipe(fd2)==-1 ){
                fprintf(stderr, "Filed to create pipe" );
        return 1;
        }

        printf("Insert Your Name: ");
        scanf("%s", input_str);

        P = fork();

        if (P < 0){
                fprintf(stderr, "fork Failed" );
                return 1;
                }

        else if (P > 0){

                char concat_str[100];
                close(fd1[0]);
                write(fd1[1], input_str, strlen(input_str)+1);
                close(fd1[1]);
                wait(NULL);
                 close(fd2[1]);
                read(fd2[0], concat_str, 100);
                printf("Hi %s !! \n", concat_str);
                close(fd2[0]);
                }

        else{
                close(fd1[1]);
                char concat_str[100];
                read(fd1[0], concat_str, 100);
                int k = strlen(concat_str);
                int i;
                for (i=0; i<strlen(fixed_str); i++)
                concat_str[k++] = fixed_str[i];
                concat_str[k] = '\0';
                close(fd1[0]);
                close(fd2[0]);
                write(fd2[1], concat_str, strlen(concat_str)+1);
                close(fd2[1]);
                exit(0);
                }
        }

        void sigint_handler(int sig){
        printf("Your Process has been Interuppetd!!\n");
        }




