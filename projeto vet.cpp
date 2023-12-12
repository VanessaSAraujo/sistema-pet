#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_EMPLOYEE 15
#define PASSWORD_LENGTH 10
#define CPF_LENGTH 11
#define MAX_CONSULTAS 20

typedef struct {
    char name[50];
    int age;
    char address[100];
    char email[50];
    char cpf[CPF_LENGTH + 1];
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
    char historicoConsultas[MAX_CONSULTAS][100];
    int numConsultas;
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
            return 0;
        }
    }
    return (i == CPF_LENGTH);
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

    newTutorRegister.numConsultas = 0; // Inicializa o n�mero de consultas
    
    FILE *file = fopen("tutor.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s %s %s %d\n",
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
    printf("Ra�a: ");
    scanf("%s", newPet.breed);

    FILE *file = fopen("pet.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "%s %d %s\n",
            newPet.petName, newPet.age, newPet.breed);

    fclose(file);

    printf("Pet cadastrado com sucesso!\n");
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

    fprintf(file, "Nome: %s \nIdade: %d  \nEndere�o: %s \nEmail: %s \nCPF: %s \nTelefone: %d \nCargo: %s \nSal�rio: %.2lf \nSenha: %s\n\n\n\n",
            newEmployee.people.name, newEmployee.people.age, newEmployee.people.address,
            newEmployee.people.email, newEmployee.people.cpf, newEmployee.people.phoneNumber,
            newEmployee.role, newEmployee.salary, newEmployee.password);

    fclose(file);

    printf("Funcion�rio cadastrado com sucesso!\n");
}

void prontuarioAnimal(TutorRegister *tutor) {
    int opcao;
    do {
        printf("\n=== PRONTU�RIO ANIMAL ===\n");
        printf("1. Agendamento de consultas\n");
        printf("2. Controle de vacinas\n");
        printf("3. Informacoes medicas do animal\n");
        printf("4. Consultas agendadas\n");
        printf("5. Hist�rico de consultas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Agendamento de consultas
                printf("Opcao 1: Agendamento de consultas\n");
                // Implemente a l�gica para agendar consultas aqui
                break;
            case 2:
                // Controle de vacinas
                printf("Opcao 2: Controle de vacinas\n");
                // Implemente a l�gica para controle de vacinas aqui
                break;
            case 3:
                // Informacoes medicas do animal
                printf("Opcao 3: Informacoes medicas do animal\n");
                // Implemente a l�gica para informa��es m�dicas aqui
                break;
            case 4:
                // Consultas agendadas
                printf("Opcao 4: Consultas agendadas\n");
                // Implemente a l�gica para consultar consultas agendadas aqui
                break;
            case 5:
                // Hist�rico de consultas
                printf("Opcao 5: Historico de consultas\n");
                // Implemente a l�gica para consultar o hist�rico de consultas aqui
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void telaDeLogin() {
    char password[PASSWORD_LENGTH + 1];
    char cpf[CPF_LENGTH + 1];

    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    printf("Digite sua senha: ");
    scanf("%s", password);
}

void mainMenu() {
    int choice;
    int c;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Login do Funcion�rio\n");
        printf("2. Cadastro de Funcion�rio\n");
        printf("3. Prontu�rio Animal\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inv�lida. Tente novamente.\n");
            // Limpa o buffer de entrada
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (choice) {
            case 1:
                // Login do Funcion�rio
                telaDeLogin();
                break;
            case 2:
                // Cadastro de Funcion�rio
                cadastrarFuncionario();
                break;
            case 3:
                // Prontu�rio Animal
                prontuarioAnimal(NULL); // Aqui voc� precisa passar um TutorRegister v�lido
                break;
            case 4:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}

