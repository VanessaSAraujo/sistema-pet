#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TUTOR 100
#define MAX_EMPLOYEE 15

typedef struct {
    char name[50];
    int age;
    char address[50];
    char email[50];
    int cpf;
    int telephone;
} People;

typedef struct {
    char petName[50];
    char species[50];
    char breed[50];
    int age;
} Pet;

typedef struct {
    People people;
    Pet pet;
} TutorRegister;

typedef struct {
    People people;
 	char role[50];
    double salary;
} Employee;


void mainMenu() {
    int choice;
    int c; // Vari�vel para limpar o buffer de entrada

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Login do Funcion�rio\n");
        printf("2. Cadastro de Funcion�rio\n");
        printf("3. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &choice);

		if (scanf("%d", &choice) != 1) {
            printf("Entrada inv�lida. Tente novamente.\n");
            system("pause");

            // Limpa o buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
            continue; // Retorna ao in�cio do loop para solicitar uma nova entrada
        }
        
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (choice != 3);
}

int main() {
	mainMenu();
	return 0;
}
	