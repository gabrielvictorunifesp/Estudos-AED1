/*
Luiggy gosta de fazer amizades e sempre está expandindo sua lista de amigos na rede social ListBook. 
O ListBook permite que você inclua seus novos amigos em sua lista de amizade e os indique também para outros amigos da sua rede, tudo isso dinamicamente, 
sem limites de amigos na sua rede. Como Luiggy é seu amigo, ele pediu que você criasse um programa para facilitar a vida dele com esta tarefa. 
Para isso, Luiggy teve a seguinte ideia:

O programa deverá ler a lista atual de amigos de Luiggy;
O programa deverá ler a nova lista de amigos de Luiggy;
O programa deverá ler o nome do amigo atual que receberá a nova lista como indicação de amigos.

Entrada
Você deve ler em uma única linha a lista de amigos de Luiggy L, contendo somente o primeiro nome e separados por um espaço em branco. 
Na segunda linha deve ser informada a nova lista de amigos N. Na última linha, o nome do amigo S da rede que deseja indicar também essa nova lista de amigos N. 
Caso não queira indicar para ninguém a nova lista de amigos, basta digitar na última linha a palavra “nao”.

Saída
Seu programa deverá exibir a nova lista de amigos de Luiggy atualizada. 
Se houver indicação de um amigo da lista, os novos amigos deverão ser inseridos antes do nome do amigo indicado. 
Caso não haja indicação, os novos nomes deverão ser inseridos no fim da lista de amigos de Luiggy.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um nó da lista de amigos
typedef struct Node {
    char name[20];
    struct Node *next;
} Node;

// Função para adicionar um novo amigo à lista
void insert(Node **head, char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);
    newNode->next = *head;
    *head = newNode;
}

// Função para imprimir a lista de amigos
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s ", current->name);
        current = current->next;
    }
    printf("\n");
}

// Função para liberar a memória alocada pela lista
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node *friends = NULL; // Lista de amigos inicial de Luiggy
    char new_friends[20]; // Lista de novos amigos
    char indicating_friend[20]; // Amigo que está indicando a nova lista
    char input[20]; // Buffer para entrada

    // Lendo a lista atual de amigos de Luiggy
    fgets(input, 20, stdin);
    char *token = strtok(input, " ");
    while (token != NULL) {
        insert(&friends, token);
        token = strtok(NULL, " ");
    }

    // Lendo a nova lista de amigos de Luiggy
    fgets(new_friends, 20, stdin);
    new_friends[strlen(new_friends) - 1] = '\0'; // Removendo o caractere de nova linha

    // Lendo o amigo que está indicando a nova lista
    fgets(indicating_friend, 20, stdin);
    indicating_friend[strlen(indicating_friend) - 1] = '\0'; // Removendo o caractere de nova linha

    // Encontrando o amigo que está indicando a nova lista na lista de amigos
    Node *current = friends;
    Node *prev = NULL;
    while (current != NULL && strcmp(current->name, indicating_friend) != 0) {
        prev = current;
        current = current->next;
    }

    // Inserindo os novos amigos antes do amigo indicado, se encontrado
    if (current != NULL) {
        token = strtok(new_friends, " ");
        while (token != NULL) {
            insert(&friends, token);
            token = strtok(NULL, " ");
        }
        prev->next = friends;
    } else if (strcmp(indicating_friend, "nao") != 0) { // Se o amigo não for encontrado e não for "nao"
        token = strtok(new_friends, " ");
        while (token != NULL) {
            insert(&friends, token);
            token = strtok(NULL, " ");
        }
    } else { // Se "nao" for digitado
        token = strtok(new_friends, " ");
        while (token != NULL) {
            insert(&friends, token);
            token = strtok(NULL, " ");
        }
    }

    // Imprimindo a lista de amigos atualizada
    printList(friends);

    // Liberando a memória alocada pela lista
    freeList(friends);

    return 0;
}

