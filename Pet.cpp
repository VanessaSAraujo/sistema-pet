#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> //para a função isdigit
#include <windows.h>

#define MAX_TUTORS 50
#define MAX_EMPLOYEE 15
#define PASSWORD_LENGTH 10
#define CPF_LENGTH 11

int tutorCount = 0;

void mainMenu();
void menuFuncionario();
void fazerLogin();
void cadastrarPet();
void prontuarioAnimal();

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
    int tutorID;
} Pet;

typedef struct {
    People people;
    int tutorID;
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

int obterUltimoID() {
    FILE *file = fopen("tutor.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tutores.\n");
        return 0; // Retorna 0 se o arquivo não puder ser aberto
    }

    int maxID = 0;
    TutorRegister tutor;

    // Lê todas as informações de cada tutor do arquivo
    while (fscanf(file, "Nome: %[^\n] Idade: %d Endereço: %[^\n] E-mail: %[^\n] CPF: %[^\n] Telefone: %d Id: %d",
                  tutor.people.name, &tutor.people.age, tutor.people.address,
                  tutor.people.email, tutor.people.cpf, &tutor.people.phoneNumber, &tutor.tutorID) == 7) {
        if (tutor.tutorID > maxID) {
            maxID = tutor.tutorID; // Atualiza o máximo ID encontrado
        }
    }

    fclose(file);
    return maxID + 1; // Retorna o novo ID a ser atribuído
}


void cadastrarTutor() {
    TutorRegister newTutorRegister;
    // Obtém o último ID do tutor do arquivo
    int ultimoID = obterUltimoID();
    
    if (tutorCount >= MAX_TUTORS) {
        printf("Limite de tutores alcançado. Não é possível cadastrar mais tutores.\n");
        return;
    }else {
    	
    	newTutorRegister.tutorID = ultimoID + 1;
    	
	    do {
	        printf("CPF (11 números): ");
	        scanf("%s", newTutorRegister.people.cpf);
	
	        if (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf)) {
	            printf("CPF inválido. Insira 11 números válidos.\n");
	        }
	    } while (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validarCPF(newTutorRegister.people.cpf));
	    fflush(stdin);
        printf("Nome: ");
	    //fflush(stdin);
	    gets(newTutorRegister.people.name);
	    fflush(stdin);
	    printf("Idade: ");       
	    scanf("%d", &newTutorRegister.people.age);
        fflush(stdin);
	    printf("Endereço Completo: ");        
	    gets(newTutorRegister.people.address);
	    fflush(stdin);
	    printf("E-mail: ");
	    scanf("%s", newTutorRegister.people.email);
	    fflush(stdin);
	    printf("Telefone: ");
	    scanf("%d", &newTutorRegister.people.phoneNumber); 
        fflush(stdin);
		
	    FILE *file = fopen("tutor.txt", "a");
	    if (file == NULL) {
	        printf("Erro ao abrir o arquivo.\n");
	        return;
	    }
	    
		fprintf(file, "Nome: %s\nIdade: %d\nEndereço: %s\nE-mail: %s\nCPF: %s \nTelefone: %d\nId: %d\n",
                newTutorRegister.people.name, newTutorRegister.people.age, newTutorRegister.people.address,
                newTutorRegister.people.email, newTutorRegister.people.cpf, newTutorRegister.people.phoneNumber, newTutorRegister.tutorID);

        fclose(file);
        printf("Tutor cadastrado com sucesso! ID do Tutor: %d\n", newTutorRegister.tutorID);
    }
}

TutorRegister obterTutor(int tutorID) {
    FILE *file = fopen("tutor.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tutores.\n");
        // Retorna um tutor com ID inválido para indicar erro
        TutorRegister invalidTutor;
        invalidTutor.tutorID = -1;
        return invalidTutor;
    }
    
    TutorRegister tutor;
    int found = 0; // Flag para indicar se o tutor foi encontrado

    // Lê todas as informações de cada tutor do arquivo
    while (fscanf(file, "Nome: %[^\n] Idade: %d Endereço: %[^\n] E-mail: %[^\n] CPF: %[^\n] Telefone: %d Id: %d\n",
                  tutor.people.name, &tutor.people.age, tutor.people.address,
                  tutor.people.email, tutor.people.cpf, &tutor.people.phoneNumber, &tutor.tutorID) == 7) {
        if (tutor.tutorID == tutorID) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        return tutor; // Retorna o tutor correspondente ao ID
    } else {
        // Se não encontrar o tutor, retorna um tutor com ID inválido para indicar erro
		TutorRegister invalidTutor;
        invalidTutor.tutorID = -1;
        return invalidTutor;
    }
}	

void cadastrarPet() {
    Pet newPet;
    
    fflush(stdin);
    printf("Nome: ");
    gets(newPet.petName);
    fflush(stdin);
    printf("Idade: ");
    scanf("%d", &newPet.age);
    fflush(stdin);
    printf("Raça: ");
    gets(newPet.breed);
    fflush(stdin);
    printf("ID do Tutor: ");
    scanf("%d", &newPet.tutorID);
    fflush(stdin);
       
	// Verifica se o tutorID existe
    TutorRegister tutor = obterTutor(newPet.tutorID);
    if (tutor.tutorID != -1) {
        FILE *file = fopen("pet.txt", "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de pets.\n");
            return;
        }

    	fprintf(file,"Nome: %s\nIdade: %d\nRaça: %s\nID do Tutor: %d\n",
            newPet.petName, newPet.age, newPet.breed, newPet.tutorID);

    	fclose(file);

    	printf("Pet cadastrado com sucesso!\n");
	} else {	
		printf("Tutor com o ID informado não foi encontrado.\n");
    }
}

int verificarPetDoTutor(int tutorID, const char *petName) {
    FILE *file = fopen("pet.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pets.\n");
        return 0; // Indica erro
    }

    Pet pet;
    int encontrado = 0; // Flag para indicar se o pet foi encontrado

    while (fscanf(file, "Nome: %[^\n]\nIdade: %d\nRaça: %[^\n]\nID do Tutor: %d\n",
                  pet.petName, &pet.age, pet.breed, &pet.tutorID) == 4) {

        // Verifica se o pet pertence ao tutor com base no ID do tutor e no nome do pet
        if (pet.tutorID == tutorID && strcmp(pet.petName, petName) == 0) {
            encontrado = 1; // Pet encontrado
            break;
        }
    }

    fclose(file);

    return encontrado;
}

int contarPetsCadastrados() {
    FILE *file = fopen("pet.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pets.\n");
        return 0;
    }

    char line[100]; // Ajuste o tamanho conforme necessário para acomodar as linhas do arquivo
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Se encontrar uma linha com "Nome:", considera como um pet cadastrado
        if (strstr(line, "Nome:") != NULL) {
            count++;
        }
    }

    fclose(file);
    return count;
}


void fazerLoginProntuario(){
     
    int tutorID;
    char petName[50];
    int petCount = contarPetsCadastrados();
     
    if (petCount == 0) {
        printf("Não há pets cadastrados. Impossível acessar o prontuário.\n");
        return;
    } else {
	    printf("Digite o ID do Tutor: ");
	    scanf("%d", &tutorID);
	         
	    printf("Digite o nome do Pet: ");
	    scanf("%s", petName);
	    
	    int petEncontrado = verificarPetDoTutor(tutorID, petName);
	    
	    if (petEncontrado) {
	        printf("Acesso permitido ao prontuário do pet %s do tutor ID %d.\n", petName, tutorID);
	        prontuarioAnimal();
	        // Coloque aqui o código para exibir o prontuário do pet
	    } else {
	        printf("O pet %s não pertence ao tutor ID %d ou não foi encontrado.\n", petName, tutorID);
	    }
    } 

}

void prontuarioAnimal(){
	int choice;
    int c; // Variável para limpar o buffer de entrada

	system("cls");
    do {
        printf("\n=== PRONTUÁRIO ANIMAL ===\n");
        printf("1. Agendamento de consultas\n");
        printf("2. Controle de vacinas\n");
        printf("3. Informacoes medicas do animal\n");
        printf("4. Consultas agendadas\n");
        printf("5. Histórico de consultas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");

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
                //Agendamento de Consultas
                break;
            case 2:
            	system("cls");
                // Controle de vacinas
                break;
            case 3:
            	// Informacoes medicas do animal
            	break;
            case 4:
            	// Consultas agendadas
            	break;
            case 5:
            	//Histórico de Consultas
            	break;
            case 0:                 
                printf("Deslogando...\n");
                system("cls");
				menuFuncionario();             
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);
}

int contarFuncionarios() {
    FILE *file = fopen("funcionarios.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char line[100]; // Ajuste o tamanho conforme necessário para acomodar as linhas do arquivo
    int count = 0;
    char cpfsEncontrados[MAX_EMPLOYEE][CPF_LENGTH + 1]; // Array para armazenar CPFs únicos
    memset(cpfsEncontrados, 0, sizeof(cpfsEncontrados)); // Inicializa o array com zeros

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentCPF[CPF_LENGTH + 1];
        sscanf(line, "CPF: %s", currentCPF);

        // Verifica se o CPF já foi contado
        int cpfJaContado = 0;
        for (int i = 0; i < MAX_EMPLOYEE; i++) {
            if (strcmp(cpfsEncontrados[i], currentCPF) == 0) {
                cpfJaContado = 1;
                break;
            }
        }

        if (!cpfJaContado) {
            // Se o CPF não estiver no array, conta como funcionário único
            for (int i = 0; i < MAX_EMPLOYEE; i++) {
                if (cpfsEncontrados[i][0] == '\0') {
                    strcpy(cpfsEncontrados[i], currentCPF);
                    count++;
                    break;
                }
            }
        }
    }

    fclose(file);
    return count;
}

void cadastrarFuncionario() {
    Employee newEmployee;
    int numFuncionarios = contarFuncionarios();
    
    if (numFuncionarios >= MAX_EMPLOYEE) {
        printf("Limite de funcionários atingido. Não é possível cadastrar mais funcionários.\n");
        return;
    }else {
	    do {
	        printf("CPF (11 números): ");
	        scanf("%s", newEmployee.people.cpf);
	
	        if (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf)) {
	            printf("CPF inválido. Insira 11 números válidos.\n");
	        }
	    } while (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validarCPF(newEmployee.people.cpf));
	    fflush(stdin);
	    printf("Nome: ");
	    gets(newEmployee.people.name);
	    printf("Idade: ");
	    scanf("%d", &newEmployee.people.age);
	    printf("Endereço Completo: ");
	    gets(newEmployee.people.address);
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
                cadastrarPet();
                break;
            case 2:
            	system("cls");
                cadastrarTutor();
                break;
            case 3:
            	system("cls");
            	fazerLoginProntuario();
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
