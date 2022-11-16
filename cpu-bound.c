#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// Função estresse 1: Gera estresse de CPU por meio de adição em loop
//      Parâmentro total:  inteiro que representa o número de milhões de iteração que serão realizadas
int estresse1(int total){
    int i, j, k, l=0;
    for(i=0; i < total; i++)
        for(j=0; j< 1000; j++)
            for(k=0; k< 1000; k++)
                l++;
    return 0;
}

//Função estresse 2: Gera estresse de CPU calculando números primos
//      Parâmetro total: Inteiro até onde os números primos serão calculados
int estresse2(int total){
    int i, num = 1, primos = 0;
    while (num <= total) { 
        i = 2; 
        while (i <= num) { 
            if(num % i == 0)
                break;
            i++; 
        }
        if (i == num){
            primos++;
            // printf("%d Numeros primos foram calculados até o número %d \n", primos, num);
        }
        num++;
    }

    return 0;
}


// Função main:
//      Parâmetro 1: inteiro que representa o número de bilhões de iteração que serão realizadas no Teste 1 de estresse
//      Parâmetro 2: inteiro que representa o número de processos que serão abertos para o teste de estresse
//      Parâmetro 3: inteiro que representa a escolha do teste de estresse a ser realizado.
int main(int argc, char *argv[]){
        double tempo_final;

        if( argc == 4){
            int teste = atoi(argv[3]); //Escolha do teste a ser executado
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
                    // printf("PROCESSO FILHO N: %d - pid %d - PROCESSO PAI pid: %d\n", i+1, getpid(),getppid()); // Para debug, remover no final
                    
                    if (teste == 1)
                        estresse1(iteracoes);
                    else
                        estresse2(1000000); // calcular primos até o 1 bilhão (1000000)
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