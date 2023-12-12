#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> //para a função isdigit

#define MAX_EMPLOYEE 15
#define PASSWORD_LENGTH 10
#define CPF_LENGTH 11

void mainMenu();
void menuFuncionario();
void fazerLogin();

typedef struct {
    char name[50];
    int age;
    char address[100];
    char email[50];
    char cpf[CPF_LENGTH + 1]; // +1 para o caractere nulo de terminação
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
            return 0; // Se encontrar algum caractere que não é dígito, retorna falso
        }
    }
    return (i == CPF_LENGTH); // Retorna verdadeiro se tiver o comprimento correto
}

void cadastrarTutor() {
    TutorRegister newTutorRegister;
    
    do {
        printf("CPF (11 números): ");
        scanf("%s", newTutorRegister.people.cpf);

        if (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf)) {
            printf("CPF inválido. Insira 11 números válidos.\n");
        }
    } while (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf));
    printf("Nome: ");
    scanf("%s", newTutorRegister.people.name);
    printf("Idade: ");
    scanf("%d", &newTutorRegister.people.age);
    printf("Endereço Completo: ");
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
    scanf("%s", newPet.petName);
    printf("Idade: ");
    scanf("%d", &newPet.age);
    printf("Raça: ");
    scanf("%s", newPet.breed);
   
       

    FILE *file = fopen("pet.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s %.2lf %s\n",
            newPet.petName, newPet.age, newPet.breed);

    fclose(file);

    printf("Tutor cadastrado com sucesso!\n");
}



void cadastrarFuncionario() {
    Employee newEmployee;
    
    do {
        printf("CPF (11 números): ");
        scanf("%s", newEmployee.people.cpf);

        if (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf)) {
            printf("CPF inválido. Insira 11 números válidos.\n");
        }
    } while (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf));
    printf("Nome: ");
    scanf("%s", newEmployee.people.name);
    printf("Idade: ");
    scanf("%d", &newEmployee.people.age);
    printf("Endereço Completo: ");
    scanf("%s", newEmployee.people.address);
    fflush(stdin);
    printf("E-mail: ");
    scanf("%s", newEmployee.people.email);
    fflush(stdin);
	printf("Telefone: ");
    scanf("%d", &newEmployee.people.phoneNumber);
    fflush(stdin);
    printf("Cargo: ");
    scanf("%s", newEmployee.role);
    fflush(stdin);
    printf("Salário: ");
    scanf("%lf", &newEmployee.salary);
    fflush(stdin);
    printf("Senha (max %d caracteres): ", PASSWORD_LENGTH);
    scanf("%s", newEmployee.password);
    fflush(stdin);

    FILE *file = fopen("funcionarios.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "Nome: %s \nIdade: %d  \nEndereço: %s \nEmail: %s \nCPF: %s \nTelefone: %d \nCargo: %s \nSalário: %.2lf \nSenha: %s\n\n\n\n",
            newEmployee.people.name, newEmployee.people.age, newEmployee.people.address,
            newEmployee.people.email, newEmployee.people.cpf, newEmployee.people.phoneNumber,
            newEmployee.role, newEmployee.salary, newEmployee.password);

    fclose(file);

    printf("Funcionário cadastrado com sucesso!\n");
}

void menuFuncionario(){
	int choice;
    int c; // Variável para limpar o buffer de entrada

	system("cls");
    do {
        printf("\n=== MENU DO FUNCIONÁRIO ===\n");
        printf("1. Cadastro do Pet\n");
        printf("2. Cadastro do Tutor\n");
        printf("3. Prontuário do Pet\n");
        printf("4. Deslogar\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            system("pause");
            // Limpa o buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
            continue; // Retorna ao início do loop para solicitar uma nova entrada
        }
        
        switch (choice) {
            case 1:
                 system("cls");
                 //cadastro do pet
                break;
            case 2:
            	 system("cls");
                 //cadastro do tutor
                break;
            case 3:
            	//prontuário
            	break;
            case 4:                 
                printf("Deslogando...\n");
                system("cls");
				mainMenu();              
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 4);
}

int validarLogin(const char *inputCPF, const char *inputPassword) {
    FILE *file = fopen("funcionarios.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    Employee employee;
    int loginSuccess = 0;

    //while (fscanf(file, " Nome: %49s Idade: %d Endereço: %99s Email: %49s CPF: %11s Telefone: %d Cargo: %49s Salário: %lf Senha: %10s",
    //O == 9 é pra confirmar que foi feita aleitura de todos os 9 elementos
	while (fscanf(file, "Nome: %49s\nIdade: %d\nEndereço: %99s\nEmail: %49s\nCPF: %s\nTelefone: %d\nCargo: %49s\nSalário: %lf\nSenha: %s\n\n\n\n",
                  employee.people.name, &employee.people.age, employee.people.address, employee.people.email, employee.people.cpf,
                  &employee.people.phoneNumber, employee.role, &employee.salary, employee.password) == 9) {

		//a função strcmp compara duas strng e retorna 0 quando são identicas
        if (strcmp(employee.people.cpf, inputCPF) == 0 && strcmp(employee.password, inputPassword) == 0) {
            loginSuccess = 1;
            break;
        } 
    }

    fclose(file);
	return loginSuccess;
}

void fazerLogin(){
     
    char password[PASSWORD_LENGTH + 1];
    char cpf[CPF_LENGTH + 1];
    //int resultadoLogin;
     
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
         
    printf("Digite sua senha: ");
    scanf("%s", password);
    
    int resultadoLogin = validarLogin(cpf, password);
    
    if (resultadoLogin) {
        printf("Login bem-sucedido!\n");
        menuFuncionario();
    } else {
        printf("CPF ou senha incorretos. Tente novamente.\n");
    }

}

void mainMenu() {
    int choice;
    int c; // Variável para limpar o buffer de entrada

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Login do Funcionário\n");
        printf("2. Cadastro de Funcionário\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            system("pause");
            // Limpa o buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
            continue; // Retorna ao início do loop para solicitar uma nova entrada
        }
        
        switch (choice) {
            case 1:
                 system("cls");
                 fazerLogin();
                break;
            case 2:
            	 system("cls");
                 cadastrarFuncionario();
                break;
            case 3:                 
                printf("Saindo do programa...\n");              
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 3);
}

int main() {
    mainMenu();
    return 0;
}
