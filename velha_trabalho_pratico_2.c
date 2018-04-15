/**********************************************************************/
/**                        PROJETO 2                                 **/
/**               IMPLEMENTAÇÃO DO JOGO DA VELHA                     **/
/** JOGO POR FERNANDA BATISTA DE OLIVEIRA E TATIANE PORTELA MEDEIROS **/
/**                       TADS - 2016                                **/
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define dim 3

int matriz [dim][dim];
int cpartida=0;

typedef struct Velha
{
    int partida; //número da partida (Ex: primeira(1), segunda(2), terceira(3), ….,partida)
    char JogVelha[3][3]; // Tabuleiro do jogo. Armazenará as jogadas
    char resultado; // Resultado da Partida: X, 0 ou V(equivale a Velha - empate)
} Partida;

void escolha();
void sair();
void novamente();
void escolha_simb(char *jog1, char *jog2);
void inicializa_velha();
void mostra_velha();
int jogada_usuario(int lin,int col,char jog);
char player_vs_player();
void pega_jogada(char jog);
int verifica_ganhador(char jog);
void limpa_buffer();
void pega_simb(char *jog1, char *jog2);
int abbin(char *nomearq, Partida jogo);
Partida* umapartida(char *nomearq, int partida);
void exibetudo(int partida);

void main()
{
    FILE *f=fopen("partidas.dat","wb");
    fclose(f);

    escolha();
}

void escolha()
{
    int op;
    char simb1, simb2;
    system("cls");
    printf("JOGO DA VELHA\n"
           "1. Jogar\n"
           "2. Sair\n"
           "Escolha sua opcao: ");
    scanf("%d",&op);
    limpa_buffer();
    system("cls");
    switch (op)
    {
    case 1:
        player_vs_player();
        break;
    case 2:
        sair();
        break;
    default:
        printf ("Opcao invalida! Digite uma opcao valida\n");
        system("pause");
        escolha();
        break;
    }
}

void sair()
{
    int c;
    system("cls");
    printf("Deseja realmente sair?\n"
           "1. Sim\n"
           "2. Nao\n");
    scanf("%d", &c);
    limpa_buffer();
    switch (c)
    {
    case 1 :
        system ("cls");
        printf("Obrigado por jogar\n");
        system("pause");
        exit(0);
        break;
    case 2 :
        escolha();
        break;
    default :
        printf ("Opcao invalida! Digite uma opcao valida\n");
        system("pause");
        sair();
    }
}

void novamente()
{
    int c, npartida, t;
    Partida *Jogo;
    system("cls");
    printf("O que voce deseja fazer?\n"
           "1. Jogar novamente\n"
           "2. Sair\n"
           "3. Mostrar uma das partidas realizadas\n"
           "4. Mostrar todas as partidas realizadas\n");
    scanf("%d",&c);
    limpa_buffer();
    switch (c)
    {
    case 1 :
        player_vs_player();
        break;
    case 2 :
        sair();
        break;
    case 3 :
        system("cls");
        printf("\nQual partida deseja procurar?\n");
        scanf("%d",&npartida);
        limpa_buffer();
        Jogo = umapartida("partidas.dat",npartida);

        if(Jogo->partida>0)
        {
            printf("Partida de numero: %d\n",Jogo->partida);

            printf("Jogador ganhador: %c\n",Jogo->resultado);
            printf("\n");
            for(t=0; t<dim; t++)
            {
                printf("\t %c | %c | %c\n", Jogo->JogVelha[t][0], Jogo->JogVelha[t][1],Jogo->JogVelha[t][2]);
                if(t!=2)
                    printf("\t---|---|---\n");
            }
            printf("\n\n");
            while(!kbhit());
        }
        free(Jogo);
        novamente();
        break;
    case 4 :
        exibetudo(cpartida);
        novamente();
        break;
    default :
        printf ("Opcao invalida! Digite uma opcao valida\n");
        system("pause");
        novamente();
    }
}

void escolha_simb(char *jog1, char *jog2)
{
    char j1,j2;
    char nome1[20],nome2[20];
    FILE *jogador;

    if((jogador = fopen("jogadores.txt", "w"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        exit(0);
    }

    system("cls");
    printf("Jogador 1");
    printf("\nDigite o nome: ");
    gets(nome1);
    fprintf(jogador,"%s;", nome1);
    printf("Digite o simbolo (X ou O): ");
    scanf("%c",&j1);
    j1 = toupper(j1);
    *jog1 = j1;
    fprintf(jogador,"%c;", *jog1);
    limpa_buffer();
    printf("\nJogador 2");
    printf("\nDigite o nome: ");
    gets(nome2);
    fprintf(jogador,"%s;", nome2);
    printf("Digite o simbolo (X ou O): ");
    scanf("%c",&j2);
    j2 = toupper(j2);
    *jog2 = j2;
    fprintf(jogador,"%c.", *jog2);
    limpa_buffer();

    fclose(jogador);
}

void inicializa_velha()
{
    int i, j;
    for(i=0; i<dim; i++)
    {
        for(j=0; j<dim; j++)
        {
            matriz[i][j] = ' ';
        }
    }
}

void mostra_velha()
{
    int t;
    printf("\n\n");
    for(t=0; t<dim; t++)
    {
        printf("\t %c | %c | %c\n", matriz[t][0], matriz[t][1],matriz[t][2]);
        if(t!=2)
            printf("\t---|---|---\n");
    }
    printf("\n\n");
}

int jogada_usuario(int lin,int col,char jog)
{
    if(col<0||col>dim||lin<0||lin>dim)
    {
        printf("Jogada Invalida");
        pega_jogada(jog);
        return 1;
    }
    else if(matriz[lin][col]==' ')
    {
        matriz[lin][col]=jog;
        return 0;
    }
    else
    {
        printf("Posicao ja preenchida");
        pega_jogada(jog);
        return 2;
    }
}

char player_vs_player()
{
    char simb1=' ',simb2=' ';
    int jogadas=0,empate=0, i=0, j=0;
    Partida jogo, *pj;

    inicializa_velha();

    cpartida++;
    if (cpartida == 1)
    {
        escolha_simb(&simb1,&simb2);
    }
    else
    {
        pega_simb(&simb1,&simb2);
    }

    system("cls");
    mostra_velha();
    while(2)
    {
        pega_jogada(simb1);
        jogadas++;
        putchar(matriz[2][2]);
        system("cls");
        mostra_velha();
        if(verifica_ganhador(simb1))
            break;
        else if(jogadas==9)
        {
            empate=1;
            break;
        }
        pega_jogada(simb2);
        jogadas++;
        system("cls");
        mostra_velha();
        if(verifica_ganhador(simb2))
            break;
    }
    if(empate)
    {
        system("cls");
        mostra_velha();
        printf("\nDeu velha!");
        system("pause");
        jogo.resultado='V';
    }
    else if(jogadas%2==0)
    {
        jogo.resultado=simb2;
        system("cls");
        mostra_velha();
        printf("\nParabens o '%c' ganhou!",simb2);
        system("pause");
    }
    else
    {
        jogo.resultado=simb1;
        system("cls");
        mostra_velha();
        printf("\nParabens o '%c' ganhou!",simb1);
        system("pause");
    }
    for(i=0; i<dim; i++)
    {
        for(j=0; j<dim; j++)
        {
            jogo.JogVelha[i][j]=matriz[i][j];
        }

    }
    jogo.partida=0;

    abbin("partidas.dat",jogo);

    novamente();
}

void pega_jogada(char jog)
{
    int linha,coluna;
    printf("\nVez do %c!",jog);
    printf("\nQual a sua jogada (ex: 2 1):");
    scanf("%i%i",&linha,&coluna);
    limpa_buffer();
    --linha;
    --coluna;
    if(jogada_usuario(linha,coluna,jog))
    {
        /*printf("Jogada Invalida");
        pega_jogada(jog);*/
    }
}

int verifica_ganhador(char jog)
{
    int i,j;
    //verifica as coluna
    for(i=0; i<dim; i++)
    {
        for(j=0; j<dim; j++)
        {
            if(jog!=matriz[i][j])
            {
                j=1;
                break;
            }

        }
        if(j!=1) return 1;
    }
    //verifica as linhas
    for(i=0; i<dim; i++)
    {
        for(j=0; j<dim; j++)
        {
            if(jog!=matriz[j][i])
            {
                j=1;
                break;
            }

        }
        if(j!=1) return 1;
    }
    //verifica a diagonal principal
    for(i=0; i<dim; i++)
    {
        if(jog!=matriz[i][i])
        {
            i=1;
            break;
        }
    }
    if(i!=1)
    {
        return 1;
    }
    //verifica a diagonal secundaria
    for(i=0; i<dim; i++)
    {
        if(jog!=matriz[i][2-i])
        {
            i=1;
            break;
        }
    }
    if(i!=1)
    {
        return 1;
    }
    return 0;
}

void limpa_buffer()
{
    char x;
    do
    {
        x = getchar();
    }
    while ((x != '\n')&&(x != EOF));
}


void pega_simb(char *jog1, char *jog2)
{
    char j1,j2, buff[20];
    int aux=0, i=0;

    FILE *jogador;

    if((jogador = fopen("jogadores.txt", "r"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        exit(0);
    }

    fread(buff,20,1,jogador);

    for(i=0; i<strlen(buff); i++)
    {
        if(buff[i] == 'X' || buff[i] == 'O' )
        {
            if(aux==0)
            {
                j1=buff[i];
            }
            else
                j2 = buff[i];
            aux++;
        }
    }

    *jog1 = j1;
    *jog2 = j2;

    fclose(jogador);
}

int abbin(char *nomearq, Partida jogo)
{
    FILE *partidas;

    if((partidas = fopen("partidas.dat", "r + b"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        fopen("partidas.dat","w + b");
    }

    fseek(partidas, sizeof(Partida),SEEK_END);
    jogo.partida=ftell(partidas)/sizeof(Partida);
    fclose(partidas);
    if((partidas = fopen("partidas.dat", "a + b"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        exit(0);
    }

    fwrite(&jogo, sizeof(Partida),1,partidas);
    fclose(partidas);
    return 1;
}

Partida* umapartida(char nomearq[], int partida)
{
    FILE *partidas;
    Partida* mostra=malloc(sizeof(Partida));
    int x;
    mostra->partida=0;

    if((partidas = fopen(nomearq, "rb"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        exit(0);
    }

    fseek(partidas, sizeof(Partida),SEEK_END);
    x=ftell(partidas)/sizeof(Partida);

    if(partida<=0||partida>x)
    {
        fclose(partidas);
        return mostra;
    }
    rewind(partidas);
    fseek(partidas, sizeof(Partida)*(partida-1),SEEK_SET);
    fread(mostra,sizeof(Partida),1,partidas);

    fclose(partidas);

    return mostra;

}

void exibetudo(int partida)
{
    FILE *partidas;
    Partida *mostra;
    int t,i,j,reg, x=0, o=0;

    if((partidas = fopen("partidas.dat", "rb"))== NULL)
    {
        printf("O arquivo nao pode ser aberto!");
        exit(0);
    }
    fseek(partidas,sizeof(Partida),SEEK_END);
    reg = ftell(partidas)/sizeof(Partida);

    rewind(partidas);

    for(i=0; i<reg; i++)
    {
        mostra = umapartida("partidas.dat",i+1);
        if(mostra->partida==0)
        {
            free(mostra);
            break;
        }
        printf("Partida de numero: %d\n",mostra->partida);
        printf("Jogador ganhador: %c\n",mostra->resultado);
        if(mostra->resultado == 'X')
        {
            x++;
        }
        else if(mostra->resultado == 'O')
        {
            o++;
        }
        for(j=0; j<dim; j++)
        {
            printf("\t %c | %c | %c\n", mostra->JogVelha[j][0], mostra->JogVelha[j][1],mostra->JogVelha[j][2]);
            if(j!=2)
                printf("\t---|---|---\n");
        }
        printf("\n\n");
        free(mostra);
    }
    fclose(partidas);


    partidas = fopen("jogadores.txt", "r");
    char  nome1[10], nome2[10], jog1[1], jog2[1];
    fscanf(partidas, "%10[^; ]; %1[^; ]; %10[^; ]; %1[^; ]",nome1,jog1,nome2,jog2);
    if(x > o)
        printf("O vencedor da competicao e %s!!!!\n", nome1);
    else if(x != o)

        printf("O vencedor da competicao e %s!!!!\n", nome2);
    else
        printf("A competicao ainda esta empatada! \n");
    fclose(partidas);

    printf("\nPressione qulquer letra para continuar... ");
    while(!kbhit());
}
