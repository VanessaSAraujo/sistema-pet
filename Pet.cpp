#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> //para a fun��o isdigit

#define MAX_EMPLOYEE 15
#define PASSWORD_LENGTH 10
#define CPF_LENGTH 11

typedef struct {
    char name[50];
    int age;
    char address[100];
    char email[50];
    char cpf[CPF_LENGTH + 1]; // +1 para o caractere nulo de termina��o
    int phoneNumber;
} People;

typedef struct {
    char petName[50];    
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
    char password[PASSWORD_LENGTH + 1];    
} Employee;

int validarCPF(const char *cpf) {
    int i;
    for (i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit(cpf[i])) {
            return 0; // Se encontrar algum caractere que n�o � d�gito, retorna falso
        }
    }
    return (i == CPF_LENGTH); // Retorna verdadeiro se tiver o comprimento correto
}

void cadastrarTutor() {
    TutorRegister newTutorRegister;
    
    do {
        printf("CPF (11 n�meros): ");
        scanf("%s", newTutorRegister.people.cpf);

        if (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf)) {
            printf("CPF inv�lido. Insira 11 n�meros v�lidos.\n");
        }
    } while (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf));
    printf("Nome: ");
    scanf("%s", newTutorRegister.people.name);
    printf("Idade: ");
    scanf("%d", &newTutorRegister.people.age);
    printf("Endere�o Completo: ");
    scanf("%s", newTutorRegister.people.address);
    printf("E-mail: ");
    scanf("%s", newTutorRegister.people.email);
    printf("Telefone: ");
    scanf("%d", &newTutorRegister.people.phoneNumber);  
       

    FILE *file = fopen("tutor.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s %.2lf %s\n",
            newTutorRegister.people.name, newTutorRegister.people.age, newTutorRegister.people.address,
            newTutorRegister.people.email, newTutorRegister.people.cpf, newTutorRegister.people.phoneNumber);

    fclose(file);

    printf("Tutor cadastrado com sucesso!\n");
}



void cadastrarPet() {
    Pet newPet;
    
    printf("Nome: ");
    scanf("%s", newPet.name);
    printf("Idade: ");
    scanf("%d", &newPet.age);
    printf("Ra�a: ");
    scanf("%s", newPet.breed);
   
       

    FILE *file = fopen("pet.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s %.2lf %s\n",
            newPet.name, newPet.age, newPet.breed);

    fclose(file);

    printf("Tutor cadastrado com sucesso!\n");
}



void cadastrarFuncionario() {
    Employee newEmployee;
    
    do {
        printf("CPF (11 n�meros): ");
        scanf("%s", newEmployee.people.cpf);

        if (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf)) {
            printf("CPF inv�lido. Insira 11 n�meros v�lidos.\n");
        }
    } while (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf));
    printf("Nome: ");
    scanf("%s", newEmployee.people.name);
    printf("Idade: ");
    scanf("%d", &newEmployee.people.age);
    printf("Endere�o Completo: ");
    scanf("%s", newEmployee.people.address);
    printf("E-mail: ");
    scanf("%s", newEmployee.people.email);
    printf("Telefone: ");
    scanf("%d", &newEmployee.people.phoneNumber);
    printf("Cargo: ");
    scanf("%s", newEmployee.role);
    printf("Sal�rio: ");
    scanf("%lf", &newEmployee.salary);
    printf("Senha (max %d caracteres): ", PASSWORD_LENGTH);
    scanf("%s", newEmployee.password);

    FILE *file = fopen("funcionarios.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s %.2lf %s\n",
            newEmployee.people.name, newEmployee.people.age, newEmployee.people.address,
            newEmployee.people.email, newEmployee.people.cpf, newEmployee.people.phoneNumber,
            newEmployee.role, newEmployee.salary, newEmployee.password);

    fclose(file);

    printf("Funcion�rio cadastrado com sucesso!\n");
}

void telaDeLogin(){
     
     char password[PASSWORD_LENGTH + 1];
     char cpf[CPF_LENGTH + 1];
     
     printf("Digite seu CPF: ");
     scanf("%s", cpf);
     printf("Digite sua senha: ");
     scanf("%s", password);
     }

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
                 cadastrarFuncionario();
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
