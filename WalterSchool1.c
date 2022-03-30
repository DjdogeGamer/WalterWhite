#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SCHOOL_SIDE 5

// Funcao que imprime o estado atual do mapa
void imprimirMapa(char matriz[SCHOOL_SIDE][SCHOOL_SIDE], int x, int y, int itens)
{
  for (int i = 0; i < SCHOOL_SIDE; i++)
  {
    for (int j = 0; j < SCHOOL_SIDE; j++)
    {
      // Caso o walter nao esteja na posicao, printa ela normalemnte
      if (i != x || j != y)
      {
        printf("%c ", matriz[i][j]);
      }
      // Sobrescreve com W caso o Walter esteja na posição
      else if (i == x && j == y)
      {
        printf("W ");
      }
    }
    printf("\n");
  }
  printf("\nItens: %d/4\n\n", itens);
}

// Funcao que popula o mapa
void popularMapa(char escola[][SCHOOL_SIDE])
{
  escola[0][0] = '5';
  escola[0][3] = '1';
  escola[0][4] = '1';
  escola[1][4] = '1';
  escola[1][3] = '2';
  escola[2][3] = '2';
  escola[2][4] = '2';
  escola[3][3] = '3';
  escola[4][3] = '3';
  escola[3][4] = '4';
  escola[4][4] = '4';
}

// Funcao que checa se o movimento e possivel e altera os valores de walter caso sim
void handleDirection(int *x, int *y, char dir)
{
  switch (dir)
  {
  case 'w':
    if (*x - 1 >= 0)
    {
      *x = *x - 1;
    }
    break;
  case 'a':
    if (*y - 1 >= 0)
    {
      *y = *y - 1;
    }
    break;
  case 's':
    if (*x + 1 < SCHOOL_SIDE)
    {
      *x = *x + 1;
    }
    break;
  case 'd':
    if (*y + 1 < SCHOOL_SIDE)
    {
      *y = *y + 1;
    }
    break;
  }
}

int main(void)
{
  char escola[SCHOOL_SIDE][SCHOOL_SIDE];

  printf("Walter: Jesse, vou pegar os produtos químicos\n\n");

  // Inicializa todas as posições com valor zero
  for (int i = 0; i < SCHOOL_SIDE; i++)
  {
    for (int j = 0; j < SCHOOL_SIDE; j++)
    {
      escola[i][j] = '_';
    }
  }

  popularMapa(escola);

  int walter_x = 0, walter_y = 0; // Guarda a posição do Walter
  char direction;
  int itens = 0, itens_unicos[4]; // Numero de itens/set de itens
  int policia = 0, vitoria = 0;   // Condicoes de encerramento

  // Inicia itens unicos com valores zerados
  for (int i = 0; i < 4; i++)
  {
    itens_unicos[i] = 0;
  }

  // Executa o programa até o Walter ser preso ou vencer
  do
  {
    // Começa mostrando o mapa e o mostra novamente a cada movimento
    imprimirMapa(escola, walter_x, walter_y, itens);

    scanf("%c", &direction);
    getchar();

    // Manda pra funcao que atualiza a posicao do walter se possivel
    handleDirection(&walter_x, &walter_y, direction);

    // Executa caso Walter passe por cima de uma posicao ocupada
    if (escola[walter_x][walter_y] != '_')
    {
      switch (escola[walter_x][walter_y])
      {
      case '1':
        if (itens_unicos[0] == 0)
        {
          itens_unicos[0] = 1;
          itens++;
          escola[walter_x][walter_y] = '_';
        }
        else
        {
          printf("Walter foi preso!\n");
          policia = 1;
        }
        break;
      case '2':
        if (itens_unicos[1] == 0)
        {
          itens_unicos[1] = 2;
          itens++;
          escola[walter_x][walter_y] = '_';
        }
        else
        {
          printf("Walter foi preso!\n");
          policia = 1;
        }
        break;
      case '3':
        if (itens_unicos[2] == 0)
        {
          itens_unicos[2] = 3;
          itens++;
          escola[walter_x][walter_y] = '_';
        }
        else
        {
          printf("Walter foi preso!\n");
          policia = 1;
        }
        break;
      case '4':
        if (itens_unicos[3] == 0)
        {
          itens_unicos[3] = 4;
          itens++;
          escola[walter_x][walter_y] = '_';
        }
        else
        {
          printf("Walter foi preso!\n");
          policia = 1;
        }
        break;
      case '5':
        if (itens < 4)
        {
          printf("Volte e pegue todos os produtos!\n");
        }
        else
        {
          printf("Parabens, voce pegou tudo\n");
          vitoria = 1;
        }
        break;
      }
    }
  } while (policia == 0 && vitoria == 0);

  return 0;
}