#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAXIMO 5
#define MINCIC 10
#define MAXNOME 30
#define MINNOME 5
#define MAXMODAL 15
typedef struct
{
    int cic;
    char nomeCurso [MAXNOME+1];     //+'\0'
    char sigla [MAXIMO+1];
    char modalidade[MAXMODAL];
} cadastro;
//============PROTOTIPO==============
void cadastraCurso(cadastro *curso, int numCadastro,FILE *arquivo,char *nomeArq);
void cadastraCic(int *cic,int numCadastro, FILE *arquivo,char *nomeArq);
void cadastraNome(char *nomeCurso);
void cadastraSigla(char *sigla);
void cadastraModalidade(char *modalidade);
void listarTodos(int numCadastro,char *nomeArq);
void editarCurso(int numCadastro,char *nomeArq);
void pesquisarCurso(int numCadastro,char *nomeArq);
void apagaCurso(int posicao,int numCadastro, char *nomeArq);
void escreverArquivo(cadastro curso,int numCadastro,char *nomeArq);
void ordemAlfabetica(cadastro *auxCurso, int aux,int numCadastro);
void tamanhoArquivo (int *numCadastro,char *nomeArq);
void lerArquivo (cadastro *auxCurso, int numCadastro,char *nomeArq);
void apagarArquivo(char *nomeArq);
void terminar(char *nomeArq, int numCadastro);
void tiraBarraN(char *string);
int numeroInteiro (char *codigo, int maximoCic);
void mensagemNenhumCurso ();
void validaSigla (char *sigla);
void validaNome (char *nome);
void limpaString(char *string, int tamanho);
//Sítese
//Objetivo: Cadastrar curso proficionalizantes.
//Entrada: Código de identificação do curso, nome completo do curso, sigla da escola que ofertará o curso, modalidade do curso.
//Saída: Lista de cursos cadastrados.
int main()
{
    //Declarações
    int numCadastro;
    cadastro curso;
    char escolha;
    FILE *arquivo;
    char nomeArq[]="cursos.bin";
    //Instruções
    setlocale(LC_ALL, "portuguese");
    system("TITLE CURSOS PROFISSIONALIZANTES");
    do
    {

        printf(".....MENU.....\n1. Cadastrar\n2. Editar\n3. Listar Todos\n4. Pesquisar\n5. Apagar Arquivo\n0. Terminar\n");
        tamanhoArquivo(&numCadastro,nomeArq);
        printf("\nCursos cadastrados.....%d",numCadastro);
        escolha = getch();
        system("cls");
        switch(escolha)
        {
        case '1':
            cadastraCurso(&curso,numCadastro,arquivo,nomeArq);
            escreverArquivo(curso,numCadastro,nomeArq);
            break;
        case '2':

            if(numCadastro>0)
            {
                editarCurso(numCadastro,nomeArq);
            }
            else
            {
                mensagemNenhumCurso();
            }
            break;
        case '3':
            if(numCadastro>0)
            {
                listarTodos(numCadastro,nomeArq);
            }
            else
            {
                mensagemNenhumCurso();
            }
            break;
        case '4':
            if(numCadastro>0)
            {
                pesquisarCurso(numCadastro,nomeArq);
            }
            else
            {
                mensagemNenhumCurso();
            }
            break;
        case '5':
            apagarArquivo(nomeArq);
            break;
        case '0':
            terminar(nomeArq,numCadastro);
            printf("Os dados adicionados foram salvos no arquivo 'cursos.bin'.\n" );
            break;
        default:
            system("cls");
        }
    }
    while(escolha!='0');
    return 0;
}
//Síntese
//Objetivo: Cadastrar cursos
//Parâmetros: Código de identificação do curso, nome completo do curso, sigla da escola que ofertará o curso, modalidade do curso, número de cadastros, arquivo e nome do arquivo.
//Retorno: nenhum
void cadastraCurso(cadastro *curso, int numCadastro, FILE *arquivo,char *nomeArq)
{
    //Instruções
    cadastraCic(&curso->cic,numCadastro,arquivo,nomeArq);
    cadastraNome(curso->nomeCurso);
    cadastraSigla(curso->sigla);
    cadastraModalidade(curso->modalidade);
}
//Síntese
//Objetivo: Cadastrar código de indentificação de curso
//Parâmetros: Código de identificação do curso, número de cadastros, arquivo e nome do arquivo.
//Retorno: nenhum
void cadastraCic(int *cic, int numCadastro,FILE *arquivo,char *nomeArq)
{
    //Declarações
    int aux;
    const int maximoCic =5;
    cadastro auxCurso;
    char codigo[maximoCic];
    //Instruções
    fflush(stdin);
    printf("...CADASTRANDO...\nCódigo de Identificação de Curso (deve ser um número maior que %d): ", MINCIC);
    fgets(codigo,maximoCic+2,stdin);
    *cic=numeroInteiro(codigo,maximoCic);
    system("cls");
    do
    {
        aux=0;
        while(*cic<=MINCIC||*cic ==-1)
        {
            fflush(stdin);
            printf("...CÓDIGO INVÁLIDO...\nDigite novamente o Código de Identificação de Curso (deve ser um número maior que %d): ", MINCIC);
            fgets(codigo,maximoCic+2,stdin);

            *cic=numeroInteiro(codigo,maximoCic);
            system("cls");
        }
        if(numCadastro>0)
        {
            if((arquivo=fopen(nomeArq,"rb"))!=NULL)
            {
                while(aux<numCadastro)
                {
                    fread(&auxCurso,sizeof(cadastro),1,arquivo);
                    if(*cic == auxCurso.cic)
                    {
                        printf("...CÓDIGO JÁ CADASTRADO...\nDigite novamente o Código de Identificação de Curso (deve ser um número maior que %d): ", MINCIC);
                        fgets(codigo,maximoCic+2,stdin);

                        *cic=numeroInteiro(codigo,maximoCic);
                        aux=0;
                        fseek(arquivo,0,SEEK_SET);
                        system("cls");
                    }
                    else
                    {
                        aux++;
                    }
                }
                if(fclose(arquivo)!=0)
                {
                    system("cls");
                    printf("\nERRO AO FECHAR ARQUIVO.\n");
                }
            }
            else
            {
                printf("\nERRO AO ABRIR ARQUIVO.\n");
            }
        }
    }
    while(*cic<=MINCIC|| *cic ==-1);
}
//Síntese
//Objetivo: Cadastrar nome do curso.
//Parâmetros: Nome completo do curso.
//Retorno: nenhum
void cadastraNome(char *nomeCurso)
{
    //Declarações
    int aux=0;
    char auxNome[MAXNOME+1];
    //Instruções
limpaString(nomeCurso,MAXNOME);
limpaString(auxNome,MAXNOME);
    printf("...CADASTRANDO...\nNome Completo do Curso (evite espaços e caracteres especiais)\n\t..... ");
    fflush(stdin);
    fgets(auxNome, MAXNOME +1, stdin);
    system("cls");
    validaNome(auxNome);
    strcpy(nomeCurso,auxNome);

    for(aux=0; aux<=strlen(nomeCurso); aux++)
    {
        nomeCurso[aux] = toupper(nomeCurso[aux]);
    }
}
//Síntese
//Objetivo: Cadastrar sigla da escola que fornecerá o curso
//Parâmetros: Sigla da escola.
//Retorno: nenhum
void cadastraSigla(char *sigla)
{
//Declarações
    int aux =0;
//Instruções
limpaString(sigla,MAXIMO);
    fflush(stdin);
    printf("...CADASTRANDO...\nSigla da Escola (evite espaços e caracteres especiais)\n\t..... ");
    fgets(sigla, MAXIMO+1, stdin);
    system("cls");
    validaSigla(sigla);

    for(aux=0; aux<strlen(sigla); aux++)
    {
        sigla[aux] = toupper(sigla[aux]);
    }
}
//Síntese
//Objetivo: Cadastrar modalidade do curso.
//Parâmetros:Modalidade do curso.
//Retorno: nenhum
void cadastraModalidade(char *modalidade)
{
    //Declarações
    char modal;
//Instruções
    do
    {
        limpaString(modalidade,MAXMODAL);
        puts("...CADASTRANDO...\nModalidade do Curso\n\nPresencial.......(P)\nSemipresencial.......(S)\nDistância.......(D)");
        fflush(stdin);
        modal = toupper(getch());
        system("cls");
        switch(modal)
        {
        case 'P':
            strcpy(modalidade, "Presencial");
            break;
        case 'S':
            strcpy(modalidade, "Semipresencial");
            break;
        case 'D':
            strcpy(modalidade, "Distância");
            break;
        default:
            system("cls");
        }
    }
    while(modal != 'P'&&modal != 'S'&&modal != 'D');
}
//Síntese
//Objetivo: Listar cursos cadastrados
//Parâmetros: Quantidade de cadastro e nome do arquivo.
//Retorno: nenhum
void listarTodos(int numCadastro,char *nomeArq)
{
    //Declarações
    int aux, esc,ordem,cont;
    cadastro auxCurso[numCadastro];
    //Instruções
    lerArquivo(auxCurso,numCadastro,nomeArq);
    printf("...LISTAR...\nOrdem Crescente...(C)\nOrdem Decrescente...(D)\nPressione Esc para voltar ao Menu...");
    do
    {
        ordem = toupper(getch());
    }
    while(ordem!='C' && ordem!='D' &&ordem!=27);
    system("cls");
    if(ordem!=27)
    {
        if(ordem == 'C')
        {
            for(cont=0; cont<numCadastro-1; cont++)
            {
                for(aux=0; aux<numCadastro-1; aux++)
                {
                    if(strcmp(auxCurso[aux].nomeCurso,auxCurso[aux+1].nomeCurso)>0) //crescente
                    {
                        ordemAlfabetica(auxCurso,aux,numCadastro);
                    }
                }
            }
        }
        else
        {
            for(cont=0; cont<numCadastro-1; cont++)
            {
                for(aux=0; aux<numCadastro-1; aux++)
                {
                    if(strcmp(auxCurso[aux].nomeCurso,auxCurso[aux+1].nomeCurso)<0) //decrescente
                    {
                        ordemAlfabetica(auxCurso,aux,numCadastro);
                    }
                }
            }
        }
        puts("_________________________________________________________________________________________________");
        printf("\t%-5s\t\t%-25s\t\t%-5s\t\t%-15s\t\n", "[CIC]", "[NOME COMPLETO DO CURSO]", "[SIGLA]","[MODALIDADE]");
        for(aux=0; aux < numCadastro; aux++)
        {
            puts("_________________________________________________________________________________________________");
            printf("\t%-5d\t\t%-25s\t\t%-5s\t\t%-15s\t\n",auxCurso[aux].cic,auxCurso[aux].nomeCurso, auxCurso[aux].sigla, auxCurso[aux].modalidade);
        }
        puts("_________________________________________________________________________________________________");
        printf("\nPressione Esc para voltar ao Menu...");
        do
            esc=getch();
        while(esc!=27);
        system("cls");
    }
}
//Síntese
//Objetivo: Editar cursos
//Parâmetros: Quantidade de cadastros, nome do arquivo
//Retorno: nenhum
void editarCurso(int numCadastro,char *nomeArq)
{
    //Declarações
    int busca, posicao =-1,esc,aux;
    const int maximoCic =5;
    char escolha;
    FILE *arquivo;
    cadastro auxCurso[numCadastro];
    cadastro edita;
    char codigo[maximoCic];
    //Instruções
    lerArquivo(auxCurso,numCadastro,nomeArq);


    arquivo = fopen(nomeArq,"rb+");
    if(arquivo == NULL)
    {
        system("cls");
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        do
        {
            printf("...EDITANDO...\nCódigo de Identificação do curso que será editado (0 para voltar ao Menu): ");
            fflush(stdin);
            fgets(codigo,maximoCic+2,stdin);
            busca=numeroInteiro(codigo,maximoCic);
            system("cls");
        }
        while(busca== -1);
        if(busca != 0)
        {
            for(aux = 0; aux<numCadastro; aux++)
            {
                if(busca == auxCurso[aux].cic)
                {
                    posicao=aux;
                }
            }
            fflush(stdin);
            if(posicao==-1)
            {
                printf("...Cadastro não encontado...\nPressione Esc para voltar ao menu...");
                do
                    esc=getch();
                while(esc!=27);
                system("cls");
            }
            else
            {
                do
                {
                    puts("...Cadastro encontrado...");
                    printf("\nNome do Curso..... %s\nSigla da Escola.....%s\nModalidade.....%s\n\n",auxCurso[posicao].nomeCurso,auxCurso[posicao].sigla,auxCurso[posicao].modalidade);
                    puts("...EDITAR...\n1 - Nome do Curso\n2 - Sigla da Escola\n3 - Modalidade\n4 - Apagar Curso\nPressione Esc para voltar ao Menu...");
                    escolha = getch();
                    system("cls");
                    switch(escolha)
                    {
                    case '1':

                        limpaString(auxCurso[posicao].nomeCurso, MAXNOME);
                        cadastraNome(edita.nomeCurso);
                        strcpy(auxCurso[posicao].nomeCurso,edita.nomeCurso);

                        break;
                    case '2':

                        limpaString(auxCurso[posicao].sigla, MAXIMO);
                        cadastraSigla(edita.sigla);
                        strcpy(auxCurso[posicao].sigla,edita.sigla);
                       ;
                        break;
                    case '3':

                        limpaString(auxCurso[posicao].modalidade, MAXMODAL);
                        cadastraModalidade(edita.modalidade);
                        strcpy(auxCurso[posicao].modalidade, edita.modalidade);

                        break;
                    case '4':
                        if(fclose(arquivo)!=0)
                        {
                            system("cls");
                            printf("\nERRO AO FECHAR ARQUIVO.\n");
                        }
                        apagaCurso(posicao,numCadastro,nomeArq);
                    }
                    system("cls");
                }
                while(escolha!=27&&escolha!='4');
                if(escolha!='4')
                {
                    fseek(arquivo,posicao*sizeof(cadastro),SEEK_SET);
                    fwrite(auxCurso+(posicao),sizeof(cadastro),1,arquivo);
                }
            }
        }
    }
    if(escolha!='4')
    {
        if(fclose(arquivo)!=0)
        {
            system("cls");
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
    }
}
//Síntese
//Objetivo: Pesquisar cursos e apresentar na tela
//Parâmetros: Quantidade de cadastros e nome do arquivo
//Retorno: nenhum
void pesquisarCurso(int numCadastro,char *nomeArq)
{
    //Declarações
    char escolha, modalidade[MAXMODAL],ordem,esc;
    int aux,cont, modalidadeCadastrada=0;
    cadastro auxCurso[numCadastro];
    //Instruções
    lerArquivo(auxCurso,numCadastro,nomeArq);
    puts("...PESQUISANDO...\nModalidade do Curso\n\nPresencial.......(P)\nSemipresencial.......(S)\nDistância.......(D)\n\nPressione Esc para voltar ao Menu...");
    do
        escolha=toupper(getch());
    while(escolha!= 'P' && escolha!='S' && escolha!= 'D' &&escolha!=27);
    system("cls");
    if(escolha!=27)
    {
        switch(escolha)
        {
        case 'P':
            strcpy(modalidade, "Presencial");
            break;
        case 'S':
            strcpy(modalidade, "Semipresencial");
            break;
        case 'D':
            strcpy(modalidade, "Distância");
        }

        for(cont=0; cont<numCadastro-1; cont++)
        {
            for(aux=0; aux<numCadastro-1; aux++)
            {
                if(strcmp(auxCurso[aux].sigla,auxCurso[aux+1].sigla)>0) //crescente
                {
                    ordemAlfabetica(auxCurso,aux,numCadastro);
                }
            }
        }

        for(aux=0; aux < numCadastro; aux++)
        {
            if(strcmp(auxCurso[aux].modalidade,modalidade)==0)
            {
                if(modalidadeCadastrada==0)
                {
                    puts("_________________________________________________________________________________________________");
                    printf("\t%-5s\t\t%-25s\t\t%-5s\t\t%-15s\t\n", "[CIC]", "[NOME COMPLETO DO CURSO]", "[SIGLA]","[MODALIDADE]");

                }
                modalidadeCadastrada=1;

                puts("_________________________________________________________________________________________________");
                printf("\t%-5d\t\t%-25s\t\t%-5s\t\t%-15s\t\n",auxCurso[aux].cic,auxCurso[aux].nomeCurso, auxCurso[aux].sigla, auxCurso[aux].modalidade);
            }
        }
        if(modalidadeCadastrada ==0)
        {
            system("cls");
            printf("Nenhum curso da modalidade %s foi cadastrado.", modalidade);
        }else{
        puts("_________________________________________________________________________________________________");
        }

        printf("\nPressione Esc para voltar ao Menu...");
        do
            esc=getch();
        while(esc!=27);
        system("cls");
    }
}
//Síntese
//Objetivo: Apagar cadastro
//Parâmetro: Posição do cadastro, quantidade de cadastros, nome do arquivo
//Retorno: nenhum
void apagaCurso(int posicao,int numCadastro, char *nomeArq)
{
    //Declarações
    int aux;
    FILE *arquivo, *temporario;
    char nomeTemp[] = "temp.bin";
    cadastro auxCurso[numCadastro],auxiliar[numCadastro], curso;
    //Instruções
//coloca posicao no final
    lerArquivo(auxCurso,numCadastro,nomeArq);
    for(aux=posicao; aux<numCadastro; aux++)
    {
        auxCurso[aux]= auxCurso[aux+1];
    }
    //escrever em  novo arquivo dados atuais sem a ultima posicao
    temporario = fopen(nomeTemp, "wb");
    if(temporario == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        fwrite(auxCurso,sizeof(cadastro),numCadastro-1,temporario);
        if(fclose(temporario)!=0)
        {
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
        else
        {
            if(remove(nomeArq) != 0)
            {
                perror("\nERRO AO REMOVER ARQUIVO ANTIGO.\n");       //excluir arquivo antigo
            }
            else
            {
                if(rename(nomeTemp,nomeArq)!=0)               //renomeia novo arquivo
                {
                    perror("\nERRO AO RENOMEAR NOVO ARQUIVO.\n");
                }
                else
                {
                    printf("Curso Excluído!\nPressione qualquer tecla para voltar...");
                }
            }
        }
    }
    getch();
}
//Síntese
//Objetivo: Escrever no arquivo dados da memória
//Parâmetros: Dados dos cursos cadastrados, quantidade de cadastros, nome do arquivo
//Retorno:nenhum
void escreverArquivo(cadastro curso,int numCadastro,char *nomeArq)
{
    //Declarações
    FILE *arquivo;
    //Instruções
    arquivo = fopen(nomeArq, "ab+");
    if(arquivo == NULL)
    {
        system("cls");
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        fwrite(&curso,sizeof(cadastro),1,arquivo);
        if(fclose(arquivo)!=0)
        {
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
    }
}
//Síntese
//Objetivo: Ordenar alfabeticamente os cursos  cadastrados
//Parâmetro: Dados dos curso cadastrado,posicao do curso que será ordenado e quantidade de cursos
//Retorno: nenhum
void ordemAlfabetica(cadastro *auxCurso, int aux,int numCadastro)
{
    //Declarações
    cadastro auxTroca[numCadastro];
    //copia vetor para auxiliar
    strcpy(auxTroca[aux].nomeCurso,auxCurso[aux].nomeCurso);
    auxTroca[aux].cic=auxCurso[aux].cic;
    strcpy(auxTroca[aux].modalidade,auxCurso[aux].modalidade);
    strcpy(auxTroca[aux].sigla,auxCurso[aux].sigla);
    //troca
    strcpy(auxCurso[aux].nomeCurso,auxCurso[aux+1].nomeCurso);
    auxCurso[aux].cic=auxCurso[aux+1].cic;
    strcpy(auxCurso[aux].modalidade,auxCurso[aux+1].modalidade);
    strcpy(auxCurso[aux].sigla,auxCurso[aux+1].sigla);
    //troca
    strcpy(auxCurso[aux+1].nomeCurso,auxTroca[aux].nomeCurso);
    auxCurso[aux+1].cic=auxTroca[aux].cic;
    strcpy(auxCurso[aux+1].modalidade,auxTroca[aux].modalidade);
    strcpy(auxCurso[aux+1].sigla,auxTroca[aux].sigla);
}
//Síntese
//Objetivo:Ler tamamho do arquiva
//Parâmetros: Quantidade de cadastros, nome do arquivo
//Retorno:nenhum
void tamanhoArquivo (int *numCadastro,char *nomeArq)
{
    //Declarações
    int tamanho =0;
    FILE *arquivo;
    //Instruções
    arquivo = fopen(nomeArq,"ab+");
    if(arquivo == NULL)
    {
        system("cls");
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        fseek(arquivo, 0, SEEK_END);
        tamanho = ftell(arquivo)/sizeof(cadastro);
        *numCadastro = tamanho;
        fseek(arquivo,0,SEEK_SET);
        if(fclose(arquivo)!=0)
        {
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
    }
}
//Síntese
//Objetivo:Ler dados do arquivo para a memória
//Parâmetros: Vetor para amazenar dados, quantidade de cadastros e nome do arquivo.
//Retorno:nenhum
void lerArquivo (cadastro *auxCurso, int numCadastro,char *nomeArq)
{
    //Declarações
    FILE *arquivo;
    //Instruções
    arquivo = fopen(nomeArq,"ab+");
    if(arquivo == NULL)
    {
        system("cls");
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        fseek(arquivo,0,SEEK_SET);
        fread(auxCurso,sizeof(cadastro),numCadastro,arquivo);
        if(fclose(arquivo)!=0)
        {
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
    }
}
//Síntese
//Objetivo:Apagar arquivo
//Parâmetros: Nome do arquivo
//Retorno:nenhum
void apagarArquivo(char *nomeArq)
{
    //Declarações
    char resposta,esc;
    FILE *arquivo;
    //Instruções
    printf("Apagar arquivo '%s'? ('S' para CONFIRMAR a exclusão ou 'N' para CANCELAR exclusão)\n", nomeArq);
    do
        resposta =toupper(getch());
    while(resposta!='S' && resposta!='N');
    system("cls");
    if(resposta =='N')
    {
        puts("...CANCELADA EXCLUSÃO!!...\n\n");
        printf("\nPressione Esc para voltar ao Menu...");
        do
            esc = getch();
        while(esc!=27);
        system("cls");
    }
    else
    {
        if(remove(nomeArq)!=0)
        {
            system("cls");
            printf("\nERRO AO REMOVER ARQUIVO ANTIGO.\n");
        }
        else
        {
            printf("...Arquivo %s foi excluído e criado outro vazio...\n", nomeArq);
            printf("\nPressione Esc para voltar ao Menu...");
            do
                esc = getch();
            while(esc!=27);
            system("cls");
        }
    }
}
//Síntese
//Objetivo: Salvar novamente dados na memória em arquivo antes de encerrar o programa
//Parâmetros: Nome do arquivo e quantidade de cadastros
//Retorno:nenhum
void terminar(char *nomeArq, int numCadastro)
{
    //Declarações
    FILE *arquivo;
    int aux;
    cadastro auxCurso[numCadastro];
    //Instruções
    lerArquivo(auxCurso,numCadastro,nomeArq);
    arquivo = fopen(nomeArq,"wb+");
    if(arquivo==NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO.\n");
    }
    else
    {
        fwrite(auxCurso,sizeof(cadastro),numCadastro,arquivo);

        if(fclose(arquivo)!=0)
        {
            printf("\nERRO AO FECHAR ARQUIVO.\n");
        }
    }
}
//Síntese
//objectivo: Tirar substituir barra n ('\n') pelo terminador barra zero ('\0') em um string
//Parâmetros: string
//Retorno: nenhum
void tiraBarraN(char *string)
{
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
}
//Síntese
//objectivo: Validar a entrada de dados para codigo do curso, que deve conter apenas numeros inteiros
//Parâmetros: codigo do curso, tamanho maximo do codigo do curso
//Retorno: -1 quando não for um número inteiro ou um numero quando for numero inteiro.
int numeroInteiro (char *codigo, int maximoCic)
{
    //declarações
    int aux, soma,resultado=0;
    //instruções
    for(aux=0; aux<strlen(codigo)-1; aux++)
    {
        if(codigo[aux]>= '0' && codigo[aux]<='9')
        {
            soma = codigo[aux]-'0';                    //'0' corresponde a 48 e '9' coreesponde a 51 na tabela ascii
            resultado = (resultado*10)+soma;
        }
        else
        {
            return -1;
        }
    }
    return resultado;
}
//Síntese
//Objetivo: Apresentar mensagem se nenhum curso tiver sido cadastrado
//Parâmetros: nenhum
//Retorno: nenhum
void mensagemNenhumCurso ()
{
    //Declarações
    char esc;
    //Instruções
    puts("Nenhum curso foi cadastrado.\nPressione Esc para voltar ao Menu...");
    do
        esc=getch();
    while(esc!=27);
    system("cls");
}
//Síntese
//Objetivo:validar sigla, deve ser somente numero e letra
//Parâmetros: sigla
//Retorno:nenhum
void validaSigla (char *sigla)
{
    //Declarações
int aux = 0;
//Instruções

while(aux<strlen(sigla)){
     tiraBarraN(sigla);
if(sigla[aux]>='0' && sigla[aux]<='9'|| sigla[aux]>='A'&&sigla[aux]<='Z'||sigla[aux]>='a' && sigla[aux]<='z')
{
aux++;
}else
{
    printf("...SIGLA INVÁLIDA...\nDigite novamente Sigla da Escola (evite espaços e caracteres especiais)\n\t..... ");
    fflush(stdin);
    fgets(sigla,MAXIMO+1,stdin);
system("cls");
    aux=0;
}

}
tiraBarraN(sigla);
}
//Síntese
//Objetivo: validar nome do curso, deve ser somente numero e letra e aceita somente um espaço entre as palavras
//Parâmetros: nome do curso
//Retorno:nenhum
void validaNome (char *nome)
{
    //Declarações
int aux = 0;
//Instruções
while(aux<strlen(nome)){
        tiraBarraN(nome);
   while(nome[0]==' '||nome[strlen(nome)-1]==' '|| nome[aux]==' '&&nome[aux+1]==' ')
   {
       printf("...NOME INVÁLIDO...\nDigite novamente Nome Completo do Curso (evite espaços e caracteres especiais)\n\t..... ");

    fflush(stdin);
    fgets(nome,MAXNOME+1,stdin);
    tiraBarraN(nome);
    system("cls");
   }

    if(nome[aux]>='0' && nome[aux]<='9'|| nome[aux]>='A'&&nome[aux]<='Z'||nome[aux]>='a' && nome[aux]<='z'|| nome[aux]==' ')
{
aux++;
}else
{
    printf("...NOME INVÁLIDO...\nDigite novamente Nome Completo do Curso (evite espaços e caracteres especiais)\n\t..... ");

    fflush(stdin);
    fgets(nome,MAXNOME+1,stdin);
system("cls");
    aux=0;
}

}
tiraBarraN(nome);
}
//Síntese
//Objetivo:limpar string
//Parâmetros:string
//Retorno: nenhum
void limpaString(char *string, int tamanho)
{
    //Declarações
    int aux;
    //Instruções
    for (aux = 0; aux < tamanho; aux++) {
    string[aux] = '\0';
}
}
