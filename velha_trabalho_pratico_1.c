#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define dim 3

int matriz [dim][dim];

void escolha();
void novamente();
void escolha_simb(char *jog1, char *jog2);
int menu();
void inicializa_velha();
void mostra_velha();
int jogada_usuario(int lin,int col,char jog);
void jog_pc(int nivel);
char player_vs_player();
char basico();
char medio();
char dificil();
void pega_jogada(char jog);
void pc_basico(char jog);
void pc_medio(char jog);
void pc_dificil(char jog); //funcao implementada parcialmente
int verifica_ganhador(char jog);
void limpa_buffer();
void sair();

void main()
{
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
        menu();
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
    int c;
    system("cls");
    printf("Voce deseja jogar de novo?\n"
           "1. Sim\n"
           "2. Nao\n");
    scanf("%d",&c);
    limpa_buffer();
    switch (c)
    {
    case 1 :
        menu();
        break;
    case 2 :
        printf("Obrigado por jogar\n");
        exit(0);
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
    system("cls");
    printf("Escolha o simbolo dos jogadores\n"
           "(escolha entre X ou O)\n");
    printf("\nJogador 1: ");
    scanf("%c",&j1);
    limpa_buffer();
    printf("\nJogador 2: ");
    scanf("%c",&j2);
    limpa_buffer();
    if(j1 == 'x' && j2 == 'o' || j1 == 'o' && j2 == 'x')
    {
        *jog1 = j1;
        *jog2 = j2;
    }
    else
    {
        printf("\nDigite um simbolo valido\n");
        system("pause");
        escolha_simb(&j1,&j2);
    }
}

int menu()
{
    int op;
    char simb1,simb2;
    system("cls");
    printf("1. Jogador X PC\n"
           "2. Jogador X Jogador\n"
           "Escolha contra quem voce quer jogar: ");
    scanf("%d",&op);
    limpa_buffer();
    switch (op)
    {
    case 1:
        jog_pc(op);
        break;
    case 2:
        player_vs_player();
        break;
    default:
        printf ("Opcao invalida! Digite uma opcao valida\n");
        system("pause");
        menu();
        break;
    }
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
    int jogadas=0,empate=0;

    inicializa_velha();
    escolha_simb(&simb1,&simb2);
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
        novamente();
    }
    else if(jogadas%2==0)
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o '%c' ganhou!",simb2);
        system("pause");
        novamente();
    }
    else
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o '%c' ganhou!",simb1);
        system("pause");
        novamente();
    }
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
    // if(jogada_usuario(linha,coluna,jog))
    // {
    //     printf("Jogada Invalida");
    //     pega_jogada(jog);
    // }
}

int verifica_ganhador(char jog)
{
    int i,j;
    //verifica as colunas
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

void jog_pc(int nivel)
{
    int opnivel;
    system("cls");
    printf("1. Basico\n"
           "2. Intermediario\n"
           "3. Avancado\n"
           "Escolha o nivel do jogo: ");
    scanf("%d",&opnivel);
    switch (opnivel)
    {
    case 1:
        basico();
        break;
    case 2:
        medio();
        break;
    case 3:
        dificil();
        break;
    default:
        printf ("Opcao invalida! Digite uma opcao valida\n");
        system("pause");
        jog_pc(opnivel);
        break;
    }
}

char basico()
{
    int jogadas=0,empate=0;

    inicializa_velha();
    system("cls");
    mostra_velha();
    while(2)
    {
        pega_jogada('X');
        jogadas++;
        putchar(matriz[2][2]);
        system("cls");
        mostra_velha();
        if(verifica_ganhador('X'))
            break;
        else if(jogadas==9)
        {
            empate=1;
            break;
        }
        pc_basico('O');
        jogadas++;
        system("cls");
        mostra_velha();
        if(verifica_ganhador('O'))
            break;
    }
    if(empate)
    {
        system("cls");
        mostra_velha();
        printf("\nDeu velha!");
        system("pause");
        novamente();
    }
    else if(jogadas%2==0)
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o 'O' ganhou!");
        system("pause");
        novamente();
    }
    else
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o 'X' ganhou!");
        system("pause");
        novamente();
    }
}

void pc_basico(char jog)
{
    int y, x;
    for(x=0; x<3; x++)
    {
        for(y=0; y<3; y++)
            if(matriz[x][y]==' ') break;
        if(matriz[x][y]==' ') break;
    }
    matriz[x][y] = 'O';
}

void pc_medio(char jog)
{
    int y, x;

    srand ( time(NULL) );

    do {
        x=rand()%3;
        y=rand()%3;
    } while(matriz[x][y]!=' ');
        matriz[x][y]='X';
        --x, --y;
}

char medio()
{
   char simb1=' ',simb2=' ';
    int jogadas=0,empate=0;

    inicializa_velha();
    system("cls");
    mostra_velha();
    while(2){
        pega_jogada('O');
        jogadas++;
        putchar(matriz[2][2]);
        system("cls");
        mostra_velha();
        if(verifica_ganhador('O'))
            break;
        else if(jogadas==9)
        {
            empate=1;
            break;
        }
        pc_medio('X');
        jogadas++;
        system("cls");
        mostra_velha();
        if(verifica_ganhador('X'))
            break;
    }
    if(empate)
    {
        system("cls");
        mostra_velha();
        printf("\nDeu velha!");
        system("pause");
        novamente();
    }
    else if(jogadas%2==0)
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o 'X' ganhou!");
        system("pause");
        novamente();
    }
    else{
        system("cls");
        mostra_velha();
        printf("\nParabens o 'O' ganhou!");
        system("pause");
        novamente();
    }
}

char dificil()
{
    int jogadas=0,empate=0;
    inicializa_velha();
    system("cls");
    mostra_velha();
    while(2)
    {
        pega_jogada('X');
        jogadas++;
        putchar(matriz[2][2]);
        system("cls");
        mostra_velha();
        if(verifica_ganhador('X'))
            break;
        else if(jogadas==9)
        {
            empate=1;
            break;
        }
        pc_dificil('O');
        jogadas++;
        system("cls");
        mostra_velha();
        if(verifica_ganhador('O'))
            break;
    }
    if(empate)
    {
        system("cls");
        mostra_velha();
        printf("\nDeu velha!");
        system("pause");
        novamente();
    }
    else if(jogadas%2==0)
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o 'O' ganhou!");
        system("pause");
        novamente();
    }
    else
    {
        system("cls");
        mostra_velha();
        printf("\nParabens o 'X' ganhou!");
        system("pause");
        novamente();
    }
}

//funcao implementada parcialmente
void pc_dificil(char jog)
{
    if(matriz[0][0]=='X' && matriz[1][0]=='X')
    {
        matriz[2][0]='O';
        --matriz[2][0];
    }
    if(matriz[0][0]=='X' &&matriz[0][1]=='X')
    {
        matriz[0][2]='O';
        --matriz[0][2];
    }
    if(matriz[0][2]=='X' && matriz[0][1]=='X')
    {
        matriz[0][0]='O';
        --matriz[0][0];
    }
    if(matriz[0][2]=='X' && matriz[1][2]=='X')
    {
        matriz[2][2]='O';
        --matriz[2][2];
    }
    if(matriz[1][2]=='X' && matriz[2][2]=='X')
    {
        matriz[0][2]='O';
        --matriz[0][2];
    }
    if(matriz[2][2]=='X' && matriz[2][1]=='X')
    {
        matriz[2][0]='O';
        --matriz[2][0];
    }
    if(matriz[2][0]=='X' && matriz[2][1]=='X')
    {
        matriz[2][2]='O';
        --matriz[2][2];
    }
    if(matriz[1][0]=='X' && matriz[2][0]=='X')
    {
        matriz[0][0]='O';
        --matriz[0][0];
    }
    if(matriz[0][0]=='X' && matriz[0][2]=='X')
    {
        matriz[0][1]='O';
        --matriz[0][1];
    }
    if(matriz[0][2]=='X' && matriz[2][2]=='X')
    {
        matriz[1][2]='O';
        matriz[1][2];
    }
    if(matriz[2][2]=='X' && matriz[2][0]=='X')
    {
        matriz[2][1]='O';
        matriz[2][1];
    }
    if(matriz[2][0]=='X' && matriz[0][0]=='X')
    {
        matriz[1][0]='O';
        matriz[1][0];
    }

    if(matriz[0][0]=='X' && matriz[1][1]=='X') //Diagonal
    {
        matriz[2][2]='O';
        --matriz[2][2];
    }
    if(matriz[1][1]=='X' && matriz[2][2]=='X') //Diagonal
    {
        matriz[0][0]='O';
        --matriz[0][0];
    }
    if(matriz[0][0]=='X' && matriz[2][2]=='X') //Diagonal
    {
        matriz[1][1]='O';
        --matriz[1][1];
    }
    if(matriz[2][0]=='X' && matriz[1][1]=='X') //Diagonal
    {
        matriz[0][2]='O';
        matriz[0][2];
    }
    if(matriz[0][2]=='X' && matriz[1][1]=='X') //Diagonal
    {
        matriz[2][0]='O';
        --matriz[2][0];
    }
    if(matriz[2][0]=='X' && matriz[0][2]=='X') //Diagonal
    {
        matriz[1][1]='O';
        --matriz[1][1];
    }
}
