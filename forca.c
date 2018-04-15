#include <stdio.h> //biblioteca padrao, tem comandos basicos de entrada e saida
#include <time.h> //usada para gerar numeros aleatorios
#include <stdlib.h> //usada Para Comandos System(" ");
#include <ctype.h> //usada para funcoes de caracteres
#include <string.h> //contem operacoes com strings

void menu(); //exibe o menu
void sair(); //sai do jogo
void initialize(int a); //cria a string de testes utilizada no jogo
void display(); //imprime a string de testes
int entrada(); //l� a letra fornecida pelo usuario
int check_palpite (int a); //verifica se a letra pertence a palavra
int check_vitoria (void); //verifica se a pessoa ganhou
void enforcado(void); //imprime o boneco, dependendo da quantidade de erros
void viveu(); //imagem da vitoria
void morreu(); //imagem da derrota
void alfabeto(); //imprime string com letras do alfabeto
void reset_valores(); //reseta os valores das variaveis para que se possa jogar novamente
int novamente(int a); //pergunta se a pessoa deseja jogar novamente
void dica(int a); //imprime uma dica da palavra
int mecanismo_jogo(int a); //mecanismo do jogo
int jogar(void); //jogo
void limpa_buffer(); //limpa o buffer

// Variaveis globais
int erros=0;
char palpite = '0', teste[21];

char palavras[][21] = {
"Cachorro","Gato", "Baleia Azul", "Elefante", "Ornitorrinco",/*0-4*/
"William Bonner","Madonna","Aristoteles","Santos Dumont","Clarice Lispector",/*5-9*/
"Bangladesh","Alemanha","Madagascar","Noruega","Irlanda"/*10-14*/};

char dicas[][50] = {
"Melhor amigo do homem","Seus bigodes fazem cocegas","O animal mais ruidoso do mundo",
"Maior mamifero terrestre","Mamifero que bota ovos",/*0-4*/
"Ancora famoso de jornal brasileiro","Rainha do pop","Famoso filosofo grego",
"Inventor do relogio de pulso","Famosa por seus livros e contos",/*5-9*/
"A lingua mais falada nesse pais e o bengali","O sobrenome mais popular nesse pais e Muller",
"Pais onde habitam os lemures","Pais conhecido por exportar bacalhau","Pais dos duendes"/*10-14*/};

char alfa[] = {"abcdefghijklmnopqrstuvwxyz"};

//funcao principal
int main()
{
    menu();
}

// Menu Principal
void menu()
{
    int c;
    system("cls");
    printf("\nJOGO DA FORCA\n"
           "\nDigite a opcao desejada\n"
           "1. Jogar\n"
           "2. Sair\n");
    scanf("%d", &c);

    switch (c)
    {
        case 1 :
            jogar();
            break;
        case 2 :
            sair();
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            menu();
    }

    limpa_buffer();
}

//sair do jogo
void sair()
{
    int c;
    system("cls");
    printf("\nDeseja realmente sair?\n"
           "1. Sim\n"
           "2. Nao\n");
    scanf("%d", &c);

    switch (c)
    {
        case 1 :
            system ("cls");
            printf("\nObrigado por jogar\n");
            system("pause");
            exit(0);
            break;
        case 2 :
            menu();
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            sair();
    }

    limpa_buffer();
}

//Jogo
int jogar(void)
{
    int a, novojogo;
    srand ( time(NULL) );

    while(1)
    {
        a = rand()%15;
        system("cls");
        initialize(a); //cria a string dos '_ _ _'
        mecanismo_jogo(a);
        novojogo = novamente(a);
        if(novojogo) //chama o menu se for falso
            menu();
        reset_valores();
    }
    return 0;
}

//Cria a String da palavra que vai ser usada na forca.
void initialize(int a)
{
    int i;
    system("cls");
    for (i=0; palavras[a][i] != '\0'; i++)
    {
        if (palavras[a][i] == ' ')
            teste[i] = palavras[a][i];
        else
            teste[i] = '_';
    }
}

//Mecanismo do jogo da forca.
int mecanismo_jogo(int a)
{
    while (erros<6)
    {
        printf("\n\tVoce pode errar %d vezes.\n", 6-erros);
        enforcado();
        display();
        alfabeto();
        dica(a);

        if (entrada())
        {
            system("cls");
            continue; //faz somente com que a iteracao atual pare, pulando pra proxima
        }
        check_palpite(a);
        if (!(check_vitoria()))
            return 0;
        system("cls");
    }

    enforcado();
    return 0;
}

//Ao final do jogo, possibilita uma nova partida.
int novamente(int a)
{
    int c;
    system ("cls");
    if (erros == 6)
    {
        morreu();
        printf("\n\nVoce Perdeu!\n\n");
        printf("A palavra era: %s\n\n", palavras[a]);
    }
    else
    {
        viveu();
        printf("\n\nParabens!\n\n"
               "Voce venceu \n\n");
        printf("A palavra era: %s\n\n", palavras[a]);
    }

    printf("\nVoce deseja jogar de novo?\n");
    printf("1. Sim\n"
           "2. Nao\n");
    scanf("%d",&c);

    switch (c)
    {
        case 1 :
            reset_valores();
            return 0;
            break;
        case 2 :
            reset_valores();
            return 1;
            break;
        default :
            printf ("\nOpcao invalida! Digite uma opcao valida\n");
            system("pause");
            novamente(a);
    }

    limpa_buffer();
}

//Reseta os Valores para que se possa jogar novamente
void reset_valores(void)
{
    int a;
    erros=0;
    palpite = '0';
    for (a=0; teste[a]!= '\0'; a++)
    {
        teste[a] = '\0';
    }
    memmove(alfa, "abcdefghijklmnopqrstuvwxyz", 27); //copia a string alfa completa pra memoria novamente
}

//Imprime o Boneco da Forca para cada numero de erros.
void enforcado(void)
{
    switch (erros)
    {
        case 0:
            printf ("_________     \n"
                    "|       |     \n"
					"|             \n"
                    "|             \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 1:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|             \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 2:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|       ||    \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 3:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||    \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 4:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|             \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 5:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|       /     \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        case 6:
            printf ("_________     \n"
                    "|       |     \n"
					"|      (oo)   \n"
					"|      /||\\  \n"
					"|       /\\   \n"
					"|     ______  \n"
					"|     |    |  \n"
					"|     |    |  \n");
            break;
        system ("cls");
    }
}

//Mostra o estado do jogo.
void display(void)
{
    int k;
    printf("\n");
    for (k=0; teste[k] != '\0'; k++)
    {
        putchar(teste[k]);
        printf(" ");
    }
    printf("\n");
}

//Mostra o alfabeto e retira as letras ja utilizadas, substituindo-as por '-'.
void alfabeto (void)
{
    int i;
    printf("\n");
	for (i=0; alfa[i] != '\0'; i++)
	{
		if (palpite == alfa[i])
			alfa[i] = '-';
        putchar (alfa[i]);
		printf(" ");
    }
    printf("\n\n");
}

//Imprime na Tela a dica para a palavra
void dica(int a)
{
    if(a <= 4)
        printf("DICA: \nAnimal");
    else if(a <= 9)
        printf("DICA: \nPessoa");
    else if(a <= 14)
        printf("DICA: \nLugar");
    printf("\n%s",dicas[a]);
    printf("\n\n\n");
}

//Le o palpite, com o cuidado de descartar entradas invalidas.
int entrada(void)
{
    char op;
    printf("Digite uma letra: ");
    scanf("%c", &op);
    palpite = op;

    if (palpite == '\n')
        return 1;
    limpa_buffer();
    if(!isalpha(palpite)) //isalpha verifica se o caracter e alfabetico
        return 1;
    palpite = tolower(palpite); //minusculas
    return 0;
}

// Checa o palpite. Se certo, substitui o respectivo '_' pela letra correspondente.
//Se errado, adiciona um a variavel erros*/
int check_palpite (int a)
{
    int i;
    for (i=0; palavras[a][i] != '\0'; i++)
    {
        if (palpite == palavras[a][i] || toupper(palpite)==palavras[a][i]) //maiscula
            teste[i] = palavras[a][i];
    }
    if (!(strchr(alfa, palpite))) //strchr procura a primeira ocorrencia do caractere na string apontada pelo argumento
        return 1;
    if((!(strchr(palavras[a], palpite))) && (!(strchr(palavras[a], toupper(palpite)))))
        erros++;
    return 0;
}

//Verifica se a Pessoa venceu.
int check_vitoria (void)
{
    int x, y;
    for(x=0, y=0; teste[x] != '\0'; x++)
    {
        if (teste[x] == '_')
            continue;
        else
            y++;
    }
    if(x == y)
    {
        display();
        return 0;
    }
    return 1;
}

//Figura para casos de vitoria.
void viveu()
{
    printf ("_________            \n"
            "|       |            \n"
            "|                    \n"
	        "|                    \n"
	        "|                    \n"
	        "|     ______  (oo)   \n"
	        "|     |    |  /||\\  \n"
            "|     |    |   /\\   \n");
}

//Animacao para o caso de derrota.
void morreu()
{
    system("cls");
    printf ("_________      \n"
            "|       |      \n"
            "|       |      \n"
			"|      (xx)    \n"
			"|      /||\\   \n"
			"|       /\\    \n"
            "|     |\\  /|  \n"
			"|     |    |   \n");
}

// Limpa Qualquer Caractere que esteja na tela e funciona como system("pause")
void limpa_buffer()
{
    char x;
    do {
        x = getchar();
    }while ((x != '\n')&&(x != EOF));
}
