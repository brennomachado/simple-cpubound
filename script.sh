#!/bin/bash

#----------------------------------------------------#
######## INÍCIO DA VERIFICAÇÃO DE PARÂMETROS #########

#Função de ajuda, mostra caso haja erro de parâmetros de entrada
helpFunction()
{
    echo ""
    echo -e "Como usar: $0 -i [Valor X] -p [Valor X] -t [A ou B]\n"
    echo -e "\t-i Valor X para executar X bilhões de iterações no Teste 1 (Ex: Se X=5, executará 5 bilhões de iterações)"
    echo -e "\t-p Número Y para definir quantos processos o teste executará ao mesmo tempo"
    echo -e "\t-t Para T=A executa Teste A, para T=B executa Teste B\n\t   OBS.: Na opção '-t B' Teste B ignora a contagem de iterações)\n\n"
    exit 1 # Sai do script após imprimir a ajuda
}

while getopts "i:p:t:v:" opt
    do
        case "$opt" in
            i ) parametroI="$OPTARG" ;;
            p ) parametroP="$OPTARG" ;;
            t ) parametroT="$OPTARG" ;;
            v ) parametroV="$OPTARG" ;; # numero de vezes que é repetido, add na ajuda
            n ) parametroN="$OPTARG" ;; # implementar a indicação do nome; add na ajuda
            a ) parametroA="$OPTARG" ;; # implementar um modo assistido, passo a passo; add na ajuda
            ? ) helpFunction ;; # Mostra a ajuda caso tenha parâmetro inválido; add na ajuda
        esac
done

# Imprime a função de ajuda se tiver parâmetro obrigatório vazio
if [ -z "$parametroI" ] || [ -z "$parametroP" ] || [ -z "$parametroT" ]
    then
        echo -e "\nERRO: Um ou mais parâmetros estão vazios";
        helpFunction
fi


if [ -z "$parametroV" ]
    then
        n_testes=2 #número de retepições do teste de estresse
    else
        n_testes=$parametroV
fi


# Se inserir número inválido para a escolha de teste chama a ajuda
if [ $parametroT == "A" ]
    then
        echo -e "\nO Teste A será executado o $n_testes vez(es), com $parametroI bilhão(ões) de iterações, usando $parametroP processo(s) no processador\n"
        teste=1
    elif [ $parametroT == "B" ]
    then
        echo -e "\nO Teste B será executado o $n_testes vez(es), usando $parametroP processo(s) no processador.\n"
        teste=2
    else
        echo -e "\nNão foi escolhido o teste certo\n"
        helpFunction
fi

########## FIM DA VERIFICAÇÃO DE PARÂMETROS ##########
#----------------------------------------------------#



#----------------------------------------------------#

# Definições de variáveis para execução

executavel="cpu-teste" #nome do executável
data="$(date +%Y%m%d_%Hh%Mm%Ss)" #cria parte do nome do arquivo de resultados com base na data e hora

#Executa o programa e salva os resultados em arquivo txt
echo -e "Exibindo resultado(s) do(s) teste(s) de estresse:\n"
for i in $(seq 1 $n_testes); do 
    resultado=$(./$executavel $parametroI $parametroP $teste)
    echo -e "\t$i˚ - ${resultado} segundos"
    echo "$resultado" >> "resultado_$data".txt
done

echo -e "\nDados foram salvos em 'resultado_$data.txt'\n"
