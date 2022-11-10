#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int estresse(void){
    int i,j,k,l=0;
    for(i=0; i< 10000; i++)
        for(j=0; j< 1000; j++)
            for(k=0; k< 1000; k++)
                l++;
    return 0;
}



int main(void){
    int processos = 6;

    time_t start, end;

    time (&start);

    for(int i=0;i<processos;i++) // loop will run n times (n=5)
    {
        // Execução dos N processos filhos
        if(fork() == 0)
        {
            printf("PROCESSO FILHO: pid %d - PROCESSO PAI pid: %d\n",getpid(),getppid()); // Para debug, remover no final
            estresse();
            exit(0);
        }
    }
   
    wait(NULL);
    time (&end);
    double tempo_final = difftime (end,start);

    printf("O programa de estresse levou %f segundos para executar\n", tempo_final); //Para debug, remover no final
    printf("%f", tempo_final);
     
    return 0;

}
