#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <time.h>
#include <stdlib.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


int main() {

    escolhepalavra();
    cabecalho();

    do {
        desenhaforca();
        chuta();
    } while (!ganhou() && !enforcou());
    verificavitoria();


    return 0;
}

///Inicialização de funções

void cabecalho() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual seu chute? ");
    scanf(" %c", &chute);
    chutes[chutesdados] = toupper(chute);
    chutesdados++;
}

int jachutou(char letra) {
    int achou = 0;
    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n", (erros>= 1 ? '(' : ' '), (erros>= 1 ? '_' : ' '),(erros>= 1 ? ')' : ' '));
    printf(" |      %c%c%c   \n",  (erros>= 2 ? '\\' : ' '), (erros>= 2 ? '|' : ' '),(erros>= 3 ? '/' : ' '));
    printf(" |       %c     \n",   (erros>= 4 ? '|' : ' '));
    printf(" |      %c %c   \n",   (erros>= 5 ? '/' : ' '), (erros>= 6 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); i++) {
        int achou = jachutou(palavrasecreta[i]);

        if (achou) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra(){
   FILE* f;
   f = fopen("palavras.txt", "r");

   if(f == 0){
    printf("Arquivo corrompido. Tente novamente.\n");
    exit(1);
   }

   int qtdpalavras;
   fscanf(f, "%d", &qtdpalavras);

   srand(time(0));
   int randomico = rand() % qtdpalavras;

   for (int i = 0; i <=  randomico; i++)
   {
       fscanf(f, "%s", palavrasecreta);
   }

   fclose(f);
}

int ganhou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); j++) {
            if (chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }

    return erros;
}

int enforcou() {

    return chuteserrados() >= 6;
}

void verificavitoria() {
    if (enforcou()) {
        printf("Você perdeu!!\n");

        printf("     _          \n");
        printf("   _| |         \n");
        printf(" _| | |         \n");
        printf("| | | |         \n");
        printf("| | | | __      \n");
        printf("| | | |/  \\    \n");
        printf("|       /\\     \n");
        printf("|      /  \\/   \n");
        printf("|      \\  /\\  \n");
        printf("|       \\/ /   \n");
        printf(" \\        /    \n");
        printf("  |     /       \n");
        printf("  |    |        \n");

        printf("A palavra secreta era %s.\n", palavrasecreta);
    } else if (ganhou()) {
        printf("Parabéns, você ganhou!!\n");

        printf("     ___________      \n");
        printf("    '._==_==_=_.'     \n");
        printf("    .-\\:      /-.    \n");
        printf("   | (|:.     |) |    \n");
        printf("    '-|:.     |-'     \n");
        printf("      \\::.    /      \n");
        printf("       '::. .'        \n");
        printf("         ) (          \n");
        printf("       _.' '._        \n");
        printf("      `\"\"\"\"\"\"\"`     \n");

        printf("A palavra secreta é %s.\n\n", palavrasecreta);
    }
    adicionapalavra();
}

void adicionapalavra(){
  char quer;
  printf("Você deseja adicionar uma nova palavra no jogo? (S/N) ");
  scanf(" %c", &quer);

  if(quer == 'S'){
    char novapalavra[TAMANHO_PALAVRA];
    printf("Qual a nova palavra? ");
    scanf("%s", novapalavra);

    FILE *f;

    f = fopen("palavras.txt", "r+");

        if(f == 0){
          printf("Erro ao abrir o arquivo.\n");
          exit(1);
        }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
  else printf("Saindo do programa. Obrigado por jogar...\n");
}