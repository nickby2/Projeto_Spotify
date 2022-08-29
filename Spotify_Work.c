#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main (void){

    FILE *fileName, *newFile;

    //Abertura do arquivo de dados
    fileName = fopen("Reviews_modified.csv","r");
    if (fileName == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    //Abertura de arquivo novo para gravar médias
    newFile = fopen("Graph_data.csv","w+");
if (newFile == NULL){
        printf("Erro ao gerar arquivo para escrita");
        exit(1);
    }

    //Inicialização para var que irá conter a linha
    char linhaDoArquivo[22];

    //Inicialização para var que irá marcar mês e ano
    char ano[5], mes[3], verify_mes[3];

    //Inicialização para vars que irão calcular Media do Mês
    float month_media = 0;
    int qnt_linhas = 0;

    //Loop para ler linhas
    while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo)+1, fileName)){

        //Var que guarda a string separada pelo caractere
        char *separated_line, *test_line;

        test_line = strtok(linhaDoArquivo,"-");
        test_line = strtok(NULL,"-");
        strcpy(verify_mes, test_line);

        //Retornando conectivos para linhaDoArquivo
        linhaDoArquivo[4]= '-';
        linhaDoArquivo[7]= '-';

        //Só rodar quando mês da linha atual for diferente do mês da linha anterior
        if (mes[0] == '\0'|| strcmp(mes,verify_mes) != 0){


        //Escrevendo em novo arquivo (com segurança para não acontecer na primeira vez que o programa rodar)
        if (month_media > 0){

            //Calculo real da média
            month_media = (month_media*1.0)/qnt_linhas;

            //Escrita
            fprintf(newFile, "%s_%s,%.2f\n",ano,mes,month_media);
            
            printf("\n%d\n",qnt_linhas);
            //Reset de variáveis
            month_media = 0;
            qnt_linhas = 0;

            printf("Escrito mes\n");
        }

        //Separando por -
        separated_line = strtok(linhaDoArquivo,"-");
        // separated_line = AAAA

        //ano irá receber AAAA
        strcpy(ano,separated_line);

        //Separando por - novamente
        separated_line = strtok(NULL,"-");
        // = MM

        //mes irá receber MM
        strcpy(mes,separated_line);

        //Retornando conectivos para linhaDoArquivo
        linhaDoArquivo[4]= '-';
        linhaDoArquivo[7]= '-';

        }

        // Separando antes da vírgula
        separated_line = strtok(linhaDoArquivo,",");

        //Indo para após a primeira vírgula
        separated_line = strtok(NULL,",");

        //Convertendo string em inteiro
        month_media += atoi(separated_line);

        //Finalização da linha
        qnt_linhas++;

        //printf("%s",linhaDoArquivo);
    
    }
    ////Calculo real da média para último mês
     month_media = (month_media*1.0)/qnt_linhas;

            //Escrita no arquivo para último mês
            fprintf(newFile, "%s_%s,%.2f\n",ano,mes,month_media);

    printf("\n");

    //Fechando arquivos
    fclose(fileName);
    fclose(newFile);
    
    return 0;
}
