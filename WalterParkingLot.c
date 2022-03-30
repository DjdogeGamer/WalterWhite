#include <stdio.h>

#define LINE 3
#define COLUMN 10

// Funcao que imprime o estado atual do mapa
void imprimirMapa(char matriz[LINE][COLUMN], int x, int y)
{
    for (int i = 0; i < LINE; i++)
    {
        for (int j = 0; j < COLUMN; j++)
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
}

// Funcao que imprime o objetivo
void imprimirObj(int has_car)
{
    printf("\nObjetivo: ");

    if (has_car == 0)
    {
        printf("pegue o seu carro\n\n");
    }
    else
    {
        printf("saia do estacionamento\n\n");
    }
}

// Funcao que popula o mapa
void popularMapa(char estacionamento[LINE][COLUMN])
{
    estacionamento[0][0] = 'P';
    estacionamento[0][3] = '1';
    estacionamento[0][4] = '2';
    estacionamento[0][5] = '3';
    estacionamento[0][6] = '4';
    estacionamento[0][7] = '5';
    estacionamento[0][8] = '6';
    estacionamento[0][9] = '7';
    estacionamento[2][9] = 'S';
}

// Verifica se a posicao que Walter esta tentando acessar e outro carro
int isAnotherCar(char pos)
{
    if (pos == '_' || pos == 'P' || pos == 'S' || pos == '5')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Funcao que checa se o movimento e possivel e altera os valores de walter caso sim
void handleDirection(char matrix[LINE][COLUMN], int *x, int *y, char dir)
{
    switch (dir)
    {
    case 'w':
        // Não deixa o walter andar até a posicao ocupada por um carro
        if (*x - 1 >= 0 && isAnotherCar(matrix[*x - 1][*y]) == 0)
        {
            *x = *x - 1;
        }
        break;
    case 'a':
        if (*y - 1 >= 0 && isAnotherCar(matrix[*x][*y - 1]) == 0)
        {
            *y = *y - 1;
        }
        break;
    case 's':
        if (*x + 1 < LINE && isAnotherCar(matrix[*x + 1][*y]) == 0)
        {
            *x = *x + 1;
        }
        break;
    case 'd':
        if (*y + 1 < COLUMN && isAnotherCar(matrix[*x][*y + 1]) == 0)
        {
            *y = *y + 1;
        }
        break;
    }
}

int main(void)
{
    char estacionamento[LINE][COLUMN];

    printf("Walter: Preciso pegar meu carro\n\n");

    // Inicializa todas as posições com valor '_'
    for (int i = 0; i < LINE; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            estacionamento[i][j] = '_';
        }
    }

    popularMapa(estacionamento);

    int walter_x = 0, walter_y = 0; // Guarda a posição do Walter
    char direction;
    int has_car = 0, left = 0; // Condicao de encerramento

    // Executa o programa até o Walter sair com o carro
    do
    {
        // Começa mostrando o mapa e o mostra novamente a cada movimento
        imprimirMapa(estacionamento, walter_x, walter_y);
        imprimirObj(has_car);

        scanf("%c", &direction);
        getchar();

        // Manda pra funcao que atualiza a posicao do walter se possivel
        handleDirection(estacionamento, &walter_x, &walter_y, direction);

        // Walter pega o carro
        if (estacionamento[walter_x][walter_y] == '5')
        {
            has_car = 1;
            estacionamento[walter_x][walter_y] = '_';
        }

        // Caso o Walter vá para a porta
        if (estacionamento[walter_x][walter_y] == 'P')
        {
            printf("Voce nao pode voltar para a escola\n");
        }

        // Quando o Walter tenta sair do estacionamento
        if (estacionamento[walter_x][walter_y] == 'S' && has_car == 0)
        {
            printf("Voce precisa pegar o seu carro para sair\n");
        }
        else if (estacionamento[walter_x][walter_y] == 'S' && has_car == 1)
        {
            printf("Voce venceu\n");
            left = 1;
        }

    } while (left == 0);

    return 0;
}
