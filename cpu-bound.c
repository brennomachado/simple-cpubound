#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Função estresse: Gera estresse de CPU por meio de adição em loop
//      Parâmentro bilhoes:  inteiro que representa o número de bilhões de iteração que serão realizadas
int estresse(int bilhoes){
    int i, j, k, l=0;
    for(i=0; i < bilhoes; i++)
        for(j=0; j< 1000; j++)
            for(k=0; k< 1000; k++)
                l++;
    return 0;
}

// Função main:
//      Parâmetro 1: inteiro que representa o número de bilhões de iteração que serão realizadas no teste de estresse
//      Parâmetro 2: inteiro que representa o número de processos que serão abertos para o teste de estresse
int main(int argc, char *argv[]){

        if( argc == 3){

            int processos = atoi(argv[2]); // Número de processos que serão abertos
            int iteracoes = atoi(argv[1]) * 1000; // Número de iterações de adição em bilhões
            pid_t pid;
            time_t start, end;

            time (&start);
            for(int i=0; i < processos; i++)
            {
                // Execução dos N processos filhos
                pid = fork();
                if (pid < 0){
                    printf("Erro na criação do processo. Verifique\n");
                    return 0;
                }
                else if(pid == 0)
                {
                    printf("PROCESSO FILHO N: %d - pid %d - PROCESSO PAI pid: %d\n", i+1, getpid(),getppid()); // Para debug, remover no final
                    estresse(iteracoes);
                    exit(0);
                }
            }
            
            if (pid > 0){
                wait(NULL);
                time (&end);
                double tempo_final = difftime (end,start);
                printf("O programa de estresse levou %f segundos para executar\n", tempo_final); //Para debug, remover no final
                printf("%f\n", tempo_final);
            }
        }
        else {
            printf("ERRO: Não foram inseridos o número de argumentos corretos");
        }
        
    return 0;
}