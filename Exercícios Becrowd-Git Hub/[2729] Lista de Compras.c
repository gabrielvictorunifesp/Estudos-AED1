/*
Valentina é uma mulher muito dedicada e costuma trabalhar até tarde todos os dias. Para economizar tempo, 
ela faz a lista de compras do mercado em um aplicativo e costuma anotar cada item na mesma hora que percebe a falta dele em casa.

O problema é que o aplicativo não exclui itens duplicados e como Valentina é distraída, 
anota o mesmo item mais de uma vez e a lista acaba ficando extensa. Sua tarefa como programadora e amiga de Valentina é melhorar o aplicativo de notas desenvolvendo um código 
que exclua os itens duplicados da lista de compras e que os ordene alfabeticamente.

Entrada
A primeira linha de entrada contém um inteiro N (N < 100) que indica a quantidade de casos de teste que vem a seguir, ou melhor, 
a quantidade de listas de compras que Valentina quer organizar. Cada lista de compra consiste de uma única linha que contém de 1 a 1000 itens ou palavras compostas apenas 
de letras minúsculas (de 1 a 20 letras), sem acentos e separadas por um espaço.

Saída
A saída contém N linhas, cada uma representando uma das listas de compras de Valentina, sem itens repetidos e em ordem alfabética.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 21

// Estrutura para representar um nó da lista
typedef struct Node {
    char item[MAX_LENGTH];
    struct Node *next;
} Node;

// Função para adicionar um novo nó à lista
void insert(Node **head, char *item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->item, item);
    newNode->next = *head;
    *head = newNode;
}

// Função para remover duplicatas da lista
void removeDuplicates(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        while (temp->next != NULL) {
            if (strcmp(current->item, temp->next->item) == 0) {
                Node *duplicate = temp->next;
                temp->next = temp->next->next;
                free(duplicate);
            } else {
                temp = temp->next;
            }
        }
        current = current->next;
    }
}

// Função para ordenar a lista alfabeticamente
void sortList(Node *head) {
    Node *current = head;
    Node *index = NULL;
    char temp[MAX_LENGTH];
    
    if (head == NULL) return;
    
    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->item, index->item) > 0) {
                strcpy(temp, current->item);
                strcpy(current->item, index->item);
                strcpy(index->item, temp);
            }
            index = index->next;
        }
        current = current->next;
    }
}

// Função para imprimir a lista
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s ", current->item);
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

int main() 
{
    int N;
    scanf("%d", &N); // Lendo o número de casos de teste

    // Iterando sobre os casos de teste
    for (int i = 0; i < N; i++) {
        Node *head = NULL; // Cabeça da lista para cada caso de teste

        // Lendo a lista de compras
        char item[MAX_LENGTH];
        while (scanf("%s", item) != EOF) {
            insert(&head, item); // Adicionando cada item à lista
        }

        // Removendo duplicatas da lista
        removeDuplicates(head);
        
        // Ordenando a lista alfabeticamente
        sortList(head);

        // Imprimindo a lista ordenada e sem itens duplicados
        printList(head);

        // Liberando a memória alocada pela lista
        freeList(head);
    }

    return 0;
}
