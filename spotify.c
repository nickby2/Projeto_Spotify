#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arquivo(FILE *fileName, FILE *newFile)
{

    // Abertura do arquivo de dados
    fileName = fopen("Reviews_modified.csv", "r");
    if (fileName == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    // Abertura de arquivo novo para gravar médias
    newFile = fopen("Graph_data.csv", "w+");
    if (newFile == NULL)
    {
        printf("Erro ao gerar arquivo para escrita");
        exit(1);
    }
    
};

int linhaArq(int c){

    int nlinhas = 0; /* contador do número de linhas */
    FILE *fp;
    fp = fopen("Reviews_modified.csv", "rt");
    if (fp == NULL)
    {
        printf("Não é possivel abrir o arquivo\n");
        return 1;
    }
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
            nlinhas++;
    }
    fclose(fp);
    return nlinhas;

};

int quickSort(arquivo aqv){
    
};


int main(void)
{

    FILE *fileName, *newFile;

    // Abertura do arquivo de dados
    fileName = fopen("Reviews_modified.csv", "r");
    if (fileName == NULL)
    {
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    // Abertura de arquivo novo para gravar médias
    newFile = fopen("Graph_data.csv", "w+");
    if (newFile == NULL)
    {
        printf("Erro ao gerar arquivo para escrita");
        exit(1);
    }

    // Inicialização para var que irá conter a linha
    char linhaDoArquivo[22];

    // Inicialização para var que irá marcar mês e ano
    char year_month[7];
    year_month[0] = 'X';

    // Inicialização para vars que irão calcular Media do Mês
    float month_media = 0;
    int qnt_linhas = 1;

    // Loop para ler linhas
    while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo), fileName))
    {

        // Primeira vez que rodar, irá salvar ano-mês da primeira linha
        if (year_month[0] == 'X')
        {
            strncpy(year_month, linhaDoArquivo, 7);
        }

        // Verificação de mudança de mês
        if (strncmp(year_month, linhaDoArquivo, 7) != 0)
        {

            // Escrita da linha em novo arquivo
            for (int i = 0; i <= 9; i++)
            {
                if (i == 4)
                {
                    fputc('_', newFile);
                }
                else if (i == 7)
                {
                    fputc(',', newFile);
                }
                else if (i == 8)
                {

                    // Calculo real da média, caso 1 linha apenas (evitar divisão por 0)
                    if (qnt_linhas == 1)
                    {
                        month_media = month_media / (qnt_linhas);
                    }

                    else
                    {
                        // Calculo real da media
                        month_media = month_media / (qnt_linhas - 1);
                    }

                    fprintf(newFile, "%f", month_media);
                }
                else if (i == 9)
                {
                    fputc('\n', newFile);
                }
                else
                {
                    fputc(year_month[i], newFile);
                }
            }

            // Mudando o mês para nova média
            year_month[0] = '\0';
            strncpy(year_month, linhaDoArquivo, 7);

            // Reiniciando a media
            month_media = 0;
            qnt_linhas = 1;
        }

        // Inicialização de variável para guardar as colunas do csv
        char *separatedLine;

        // Separar colunas pela vírgula
        separatedLine = strtok(linhaDoArquivo, ",");
        // separatedLine = AAAA-MM-DD HH:MM:SS

        // Variável para verificar coluna
        int coluna = 0;

        while (separatedLine != NULL)
        {

            // Calcular media
            if (coluna == 1)
            {

                // Transformar string em int;
                month_media += atoi(separatedLine);
                qnt_linhas++;
            }
            else
            {
                coluna++;
            }
            // Mudar para próxima coluna
            separatedLine = strtok(NULL, ",");
        }
        printf("\n");
    }
    fclose("Reviews_test.csv");
    fclose("Graph_data.csv");
    return 0;
}
