#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Função estresse 1: Gera estresse de CPU por meio de adição em loop
//      Parâmentro bilhoes:  inteiro que representa o número de bilhões de iteração que serão realizadas
int estresse1(int bilhoes){
    int i, j, k, l=0;
    for(i=0; i < bilhoes; i++)
        for(j=0; j< 1000; j++)
            for(k=0; k< 1000; k++)
                l++;
    return 0;
}

//Função estresse 2: Criar novo método de cálculo, por enquanto é o mesmo o estresse 1 mas com 10bi de interações
int estresse2(void){
    int i, j, k, l=0;
    for(i=0; i < 10000; i++)
        for(j=0; j< 1000; j++)
            for(k=0; k< 1000; k++)
                l++;
    return 0;
}


// Função main:
//      Parâmetro 1: inteiro que representa o número de bilhões de iteração que serão realizadas no teste de estresse
//      Parâmetro 2: inteiro que representa o número de processos que serão abertos para o teste de estresse
int main(int argc, char *argv[]){
        double tempo_final;

        if( argc == 4){
            int teste = atoi(argv[3]); //escolha do teste a ser executado
            int processos = atoi(argv[2]); // Número de processos que serão abertos
            int iteracoes = atoi(argv[1]) * 1000 + 1; // Número de iterações de adição em bilhões

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
                    // printf("PROCESSO FILHO N: %d - pid %d - PROCESSO PAI pid: %d\n", i+1, getpid(),getppid()); // Para debug, remover no final
                    
                    if (teste == 1)
                        estresse1(iteracoes);
                    if (teste == 2)
                        estresse2();
                    exit(0);
                }
            }
            
            if (pid > 0){
                wait(NULL);
                time (&end);
                tempo_final = difftime (end,start);
                // printf("O programa de estresse levou %f segundos para executar\n", tempo_final); //Para debug, remover no final
                printf("%d\n", (int)tempo_final);

                // printf ("valor do teste %d \n", teste);
            }
        }
        else {
            printf("ERRO: Não foram inseridos o número de argumentos corretos\n");
        }
    // printf("tempo final: %d \n\n", (int)tempo_final);
    return (0);
}