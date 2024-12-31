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
//S�tese
//Objetivo: Cadastrar curso proficionalizantes.
//Entrada: C�digo de identifica��o do curso, nome completo do curso, sigla da escola que ofertar� o curso, modalidade do curso.
//Sa�da: Lista de cursos cadastrados.
int main()
{
    //Declara��es
    int numCadastro;
    cadastro curso;
    char escolha;
    FILE *arquivo;
    char nomeArq[]="cursos.bin";
    //Instru��es
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
//S�ntese
//Objetivo: Cadastrar cursos
//Par�metros: C�digo de identifica��o do curso, nome completo do curso, sigla da escola que ofertar� o curso, modalidade do curso, n�mero de cadastros, arquivo e nome do arquivo.
//Retorno: nenhum
void cadastraCurso(cadastro *curso, int numCadastro, FILE *arquivo,char *nomeArq)
{
    //Instru��es
    cadastraCic(&curso->cic,numCadastro,arquivo,nomeArq);
    cadastraNome(curso->nomeCurso);
    cadastraSigla(curso->sigla);
    cadastraModalidade(curso->modalidade);
}
//S�ntese
//Objetivo: Cadastrar c�digo de indentifica��o de curso
//Par�metros: C�digo de identifica��o do curso, n�mero de cadastros, arquivo e nome do arquivo.
//Retorno: nenhum
void cadastraCic(int *cic, int numCadastro,FILE *arquivo,char *nomeArq)
{
    //Declara��es
    int aux;
    const int maximoCic =5;
    cadastro auxCurso;
    char codigo[maximoCic];
    //Instru��es
    fflush(stdin);
    printf("...CADASTRANDO...\nC�digo de Identifica��o de Curso (deve ser um n�mero maior que %d): ", MINCIC);
    fgets(codigo,maximoCic+2,stdin);
    *cic=numeroInteiro(codigo,maximoCic);
    system("cls");
    do
    {
        aux=0;
        while(*cic<=MINCIC||*cic ==-1)
        {
            fflush(stdin);
            printf("...C�DIGO INV�LIDO...\nDigite novamente o C�digo de Identifica��o de Curso (deve ser um n�mero maior que %d): ", MINCIC);
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
                        printf("...C�DIGO J� CADASTRADO...\nDigite novamente o C�digo de Identifica��o de Curso (deve ser um n�mero maior que %d): ", MINCIC);
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
//S�ntese
//Objetivo: Cadastrar nome do curso.
//Par�metros: Nome completo do curso.
//Retorno: nenhum
void cadastraNome(char *nomeCurso)
{
    //Declara��es
    int aux=0;
    char auxNome[MAXNOME+1];
    //Instru��es
limpaString(nomeCurso,MAXNOME);
limpaString(auxNome,MAXNOME);
    printf("...CADASTRANDO...\nNome Completo do Curso (evite espa�os e caracteres especiais)\n\t..... ");
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
//S�ntese
//Objetivo: Cadastrar sigla da escola que fornecer� o curso
//Par�metros: Sigla da escola.
//Retorno: nenhum
void cadastraSigla(char *sigla)
{
//Declara��es
    int aux =0;
//Instru��es
limpaString(sigla,MAXIMO);
    fflush(stdin);
    printf("...CADASTRANDO...\nSigla da Escola (evite espa�os e caracteres especiais)\n\t..... ");
    fgets(sigla, MAXIMO+1, stdin);
    system("cls");
    validaSigla(sigla);

    for(aux=0; aux<strlen(sigla); aux++)
    {
        sigla[aux] = toupper(sigla[aux]);
    }
}
//S�ntese
//Objetivo: Cadastrar modalidade do curso.
//Par�metros:Modalidade do curso.
//Retorno: nenhum
void cadastraModalidade(char *modalidade)
{
    //Declara��es
    char modal;
//Instru��es
    do
    {
        limpaString(modalidade,MAXMODAL);
        puts("...CADASTRANDO...\nModalidade do Curso\n\nPresencial.......(P)\nSemipresencial.......(S)\nDist�ncia.......(D)");
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
            strcpy(modalidade, "Dist�ncia");
            break;
        default:
            system("cls");
        }
    }
    while(modal != 'P'&&modal != 'S'&&modal != 'D');
}
//S�ntese
//Objetivo: Listar cursos cadastrados
//Par�metros: Quantidade de cadastro e nome do arquivo.
//Retorno: nenhum
void listarTodos(int numCadastro,char *nomeArq)
{
    //Declara��es
    int aux, esc,ordem,cont;
    cadastro auxCurso[numCadastro];
    //Instru��es
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
//S�ntese
//Objetivo: Editar cursos
//Par�metros: Quantidade de cadastros, nome do arquivo
//Retorno: nenhum
void editarCurso(int numCadastro,char *nomeArq)
{
    //Declara��es
    int busca, posicao =-1,esc,aux;
    const int maximoCic =5;
    char escolha;
    FILE *arquivo;
    cadastro auxCurso[numCadastro];
    cadastro edita;
    char codigo[maximoCic];
    //Instru��es
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
            printf("...EDITANDO...\nC�digo de Identifica��o do curso que ser� editado (0 para voltar ao Menu): ");
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
                printf("...Cadastro n�o encontado...\nPressione Esc para voltar ao menu...");
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
//S�ntese
//Objetivo: Pesquisar cursos e apresentar na tela
//Par�metros: Quantidade de cadastros e nome do arquivo
//Retorno: nenhum
void pesquisarCurso(int numCadastro,char *nomeArq)
{
    //Declara��es
    char escolha, modalidade[MAXMODAL],ordem,esc;
    int aux,cont, modalidadeCadastrada=0;
    cadastro auxCurso[numCadastro];
    //Instru��es
    lerArquivo(auxCurso,numCadastro,nomeArq);
    puts("...PESQUISANDO...\nModalidade do Curso\n\nPresencial.......(P)\nSemipresencial.......(S)\nDist�ncia.......(D)\n\nPressione Esc para voltar ao Menu...");
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
            strcpy(modalidade, "Dist�ncia");
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
//S�ntese
//Objetivo: Apagar cadastro
//Par�metro: Posi��o do cadastro, quantidade de cadastros, nome do arquivo
//Retorno: nenhum
void apagaCurso(int posicao,int numCadastro, char *nomeArq)
{
    //Declara��es
    int aux;
    FILE *arquivo, *temporario;
    char nomeTemp[] = "temp.bin";
    cadastro auxCurso[numCadastro],auxiliar[numCadastro], curso;
    //Instru��es
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
                    printf("Curso Exclu�do!\nPressione qualquer tecla para voltar...");
                }
            }
        }
    }
    getch();
}
//S�ntese
//Objetivo: Escrever no arquivo dados da mem�ria
//Par�metros: Dados dos cursos cadastrados, quantidade de cadastros, nome do arquivo
//Retorno:nenhum
void escreverArquivo(cadastro curso,int numCadastro,char *nomeArq)
{
    //Declara��es
    FILE *arquivo;
    //Instru��es
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
//S�ntese
//Objetivo: Ordenar alfabeticamente os cursos  cadastrados
//Par�metro: Dados dos curso cadastrado,posicao do curso que ser� ordenado e quantidade de cursos
//Retorno: nenhum
void ordemAlfabetica(cadastro *auxCurso, int aux,int numCadastro)
{
    //Declara��es
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
//S�ntese
//Objetivo:Ler tamamho do arquiva
//Par�metros: Quantidade de cadastros, nome do arquivo
//Retorno:nenhum
void tamanhoArquivo (int *numCadastro,char *nomeArq)
{
    //Declara��es
    int tamanho =0;
    FILE *arquivo;
    //Instru��es
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
//S�ntese
//Objetivo:Ler dados do arquivo para a mem�ria
//Par�metros: Vetor para amazenar dados, quantidade de cadastros e nome do arquivo.
//Retorno:nenhum
void lerArquivo (cadastro *auxCurso, int numCadastro,char *nomeArq)
{
    //Declara��es
    FILE *arquivo;
    //Instru��es
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
//S�ntese
//Objetivo:Apagar arquivo
//Par�metros: Nome do arquivo
//Retorno:nenhum
void apagarArquivo(char *nomeArq)
{
    //Declara��es
    char resposta,esc;
    FILE *arquivo;
    //Instru��es
    printf("Apagar arquivo '%s'? ('S' para CONFIRMAR a exclus�o ou 'N' para CANCELAR exclus�o)\n", nomeArq);
    do
        resposta =toupper(getch());
    while(resposta!='S' && resposta!='N');
    system("cls");
    if(resposta =='N')
    {
        puts("...CANCELADA EXCLUS�O!!...\n\n");
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
            printf("...Arquivo %s foi exclu�do e criado outro vazio...\n", nomeArq);
            printf("\nPressione Esc para voltar ao Menu...");
            do
                esc = getch();
            while(esc!=27);
            system("cls");
        }
    }
}
//S�ntese
//Objetivo: Salvar novamente dados na mem�ria em arquivo antes de encerrar o programa
//Par�metros: Nome do arquivo e quantidade de cadastros
//Retorno:nenhum
void terminar(char *nomeArq, int numCadastro)
{
    //Declara��es
    FILE *arquivo;
    int aux;
    cadastro auxCurso[numCadastro];
    //Instru��es
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
//S�ntese
//objectivo: Tirar substituir barra n ('\n') pelo terminador barra zero ('\0') em um string
//Par�metros: string
//Retorno: nenhum
void tiraBarraN(char *string)
{
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
}
//S�ntese
//objectivo: Validar a entrada de dados para codigo do curso, que deve conter apenas numeros inteiros
//Par�metros: codigo do curso, tamanho maximo do codigo do curso
//Retorno: -1 quando n�o for um n�mero inteiro ou um numero quando for numero inteiro.
int numeroInteiro (char *codigo, int maximoCic)
{
    //declara��es
    int aux, soma,resultado=0;
    //instru��es
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
//S�ntese
//Objetivo: Apresentar mensagem se nenhum curso tiver sido cadastrado
//Par�metros: nenhum
//Retorno: nenhum
void mensagemNenhumCurso ()
{
    //Declara��es
    char esc;
    //Instru��es
    puts("Nenhum curso foi cadastrado.\nPressione Esc para voltar ao Menu...");
    do
        esc=getch();
    while(esc!=27);
    system("cls");
}
//S�ntese
//Objetivo:validar sigla, deve ser somente numero e letra
//Par�metros: sigla
//Retorno:nenhum
void validaSigla (char *sigla)
{
    //Declara��es
int aux = 0;
//Instru��es

while(aux<strlen(sigla)){
     tiraBarraN(sigla);
if(sigla[aux]>='0' && sigla[aux]<='9'|| sigla[aux]>='A'&&sigla[aux]<='Z'||sigla[aux]>='a' && sigla[aux]<='z')
{
aux++;
}else
{
    printf("...SIGLA INV�LIDA...\nDigite novamente Sigla da Escola (evite espa�os e caracteres especiais)\n\t..... ");
    fflush(stdin);
    fgets(sigla,MAXIMO+1,stdin);
system("cls");
    aux=0;
}

}
tiraBarraN(sigla);
}
//S�ntese
//Objetivo: validar nome do curso, deve ser somente numero e letra e aceita somente um espa�o entre as palavras
//Par�metros: nome do curso
//Retorno:nenhum
void validaNome (char *nome)
{
    //Declara��es
int aux = 0;
//Instru��es
while(aux<strlen(nome)){
        tiraBarraN(nome);
   while(nome[0]==' '||nome[strlen(nome)-1]==' '|| nome[aux]==' '&&nome[aux+1]==' ')
   {
       printf("...NOME INV�LIDO...\nDigite novamente Nome Completo do Curso (evite espa�os e caracteres especiais)\n\t..... ");

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
    printf("...NOME INV�LIDO...\nDigite novamente Nome Completo do Curso (evite espa�os e caracteres especiais)\n\t..... ");

    fflush(stdin);
    fgets(nome,MAXNOME+1,stdin);
system("cls");
    aux=0;
}

}
tiraBarraN(nome);
}
//S�ntese
//Objetivo:limpar string
//Par�metros:string
//Retorno: nenhum
void limpaString(char *string, int tamanho)
{
    //Declara��es
    int aux;
    //Instru��es
    for (aux = 0; aux < tamanho; aux++) {
    string[aux] = '\0';
}
}
