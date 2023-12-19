#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <windows.h>

#define MAX_TUTORS 50
#define MAX_EMPLOYEE 15
#define PASSWORD_LENGTH 10
#define CPF_LENGTH 11
#define MAX_APPOINTMENTS 60
#define MAX_MEDICAL_HISTORY 60

int tutorCount = 0;

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
    char species[50];
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

typedef struct {
    char date[20];
    char veterinarian[50];
} Appointment;

typedef struct {
    char date[20];
    char details[200];
} MedicalRecord;

typedef struct {
    TutorRegister tutor;
    Pet pet;
    Appointment appointments[MAX_APPOINTMENTS];
    MedicalRecord medicalHistory[MAX_MEDICAL_HISTORY];
    int appointmentCount;
    int medicalRecordCount;
} PetProntuary;

void mainMenu();
void makeLogin(); 
int validateLogin(const char *inputCPF, const char *inputPassword); 
void EmployeeMenu(); 
void viewSchedule(); 
void addDateAgenda();
void registerEmployee(); 
int countEmployees() ;
void animalRecord(int tutorID, const char *petName);
void viewVaccinesTaken(PetProntuary *petProntuary);
void addVaccinesTaken(PetProntuary *petProntuary); 
void viewScheduledConsultations(PetProntuary *petProntuary); 
void addMedicalInformation(PetProntuary *petProntuary); 
void listMedicalInformation (PetProntuary *petProntuary); 
void addScheduledConsultation (PetProntuary *petProntuary); 
void saveScheduledConsultation(PetProntuary *petProntuary, char *dataConsulta, char *nomeVeterinario); 
void loadMedicalHistory(PetProntuary *petProntuary);
void createMedicalHistoryFile(PetProntuary *petProntuary, const char *petName, int tutorID);
void createVaccinesFile(PetProntuary petProntuary, const char petName, int tutorID);
void createAppointmentsFile(PetProntuary *petProntuary, const char *petName, int tutorID);
void makeLoginProntuario(); 
int countPetsRegistered();
int checkPetFromTutor(int tutorID, const char *petName); 
void registerPet(); 
TutorRegister getTutor(int tutorID); 
void registerTutor(); 
int getLastID(); 
int validateCPF(const char *cpf);
void cabecalho ();

void cabecalho () {
    printf("\n\t\t\t ######  ##       #### ##    ## ####  ######     ###    ");
	printf("\n\t\t\t##    ## ##        ##  ###   ##  ##  ##    ##   ## ##   ");
	printf("\n\t\t\t##       ##        ##  ####  ##  ##  ##        ##   ##  ");
	printf("\n\t\t\t##       ##        ##  ## ## ##  ##  ##       ##     ## ");
	printf("\n\t\t\t##       ##        ##  ##  ####  ##  ##       ######### ");
	printf("\n\t\t\t##    ## ##        ##  ##   ###  ##  ##    ## ##     ## ");
	printf("\n\t\t\t ######  ######## #### ##    ## ####  ######  ##     ## ");
	
	printf("\n\n*  ##  ##    ####    ##         ##     ######   ######            ##  ##    ####    ##   ##   ####      ## *");
	printf("\n*  ## ##      ##     ##        ####      ##     ##                ## ##      ##     ### ###    ##      #### *");
	printf("\n*  ####       ##     ##       ##  ##     ##     ##                ####       ##     #######    ##     ##  ## *");
	printf("\n*  ###        ##     ##       ######     ##     ####              ###        ##     ## # ##    ##     ###### *");
	printf("\n*  ####       ##     ##       ##  ##     ##     ##                ####       ##     ##   ##    ##     ##  ## *");
	printf("\n*  ## ##      ##     ##       ##  ##     ##     ##                ## ##      ##     ##   ##    ##     ##  ## *");
	printf("\n*  ##  ##    ####    ######   ##  ##     ##     ######            ##  ##    ####    ##   ##   ####    ##  ## *\n\n\n\n\n\n");
	
}

int validateCPF(const char *cpf) {
    int i;
    for (i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }
    return (i == CPF_LENGTH);
}

int getLastID() {
    FILE *file = fopen("tutor.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tutores.\n");
        return 0;
    }
    int maxID = 0;
    TutorRegister tutor;
    while (fscanf(file, "Nome: %[^\n] Idade: %d Endereço: %[^\n] E-mail: %[^\n] CPF: %[^\n] Telefone: %d Id: %d",
                  tutor.people.name, &tutor.people.age, tutor.people.address,
                  tutor.people.email, tutor.people.cpf, &tutor.people.phoneNumber, &tutor.tutorID) == 7) {
        if (tutor.tutorID > maxID) {
            maxID = tutor.tutorID;
        }
    }
    fclose(file);
    return maxID + 1;
}

void registerTutor() {
    TutorRegister newTutorRegister;
    int lastID = getLastID();
    
    if (tutorCount >= MAX_TUTORS) {
        printf("Limite de tutores alcançado. Não é possível cadastrar mais tutores.\n");
        return;
    }else {
    	newTutorRegister.tutorID = lastID + 1;
	    do {
	        printf("CPF (11 números): ");
	        scanf("%s", newTutorRegister.people.cpf);
	
	        if (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validateCPF(newTutorRegister.people.cpf)) {
	            printf("CPF inválido. Insira 11 números válidos.\n");
	        }
	    } while (strlen(newTutorRegister.people.cpf) != CPF_LENGTH || !validateCPF(newTutorRegister.people.cpf));
	    fflush(stdin);
        printf("Nome: ");
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

TutorRegister getTutor(int tutorID) {
    FILE *file = fopen("tutor.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tutores.\n");
        TutorRegister invalidTutor;
        invalidTutor.tutorID = -1;
        return invalidTutor;
    }
    TutorRegister tutor;
    int found = 0;
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
        return tutor;
    } else {
		TutorRegister invalidTutor;
        invalidTutor.tutorID = -1;
        return invalidTutor;
    }
}	

void registerPet() {
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
    printf("Espécie: ");
    gets(newPet.species);
    fflush(stdin);
    printf("ID do Tutor: ");
    scanf("%d", &newPet.tutorID);
    fflush(stdin);
       
    TutorRegister tutor = getTutor(newPet.tutorID);
    if (tutor.tutorID != -1) {
        FILE *file = fopen("pet.txt", "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de pets.\n");
            return;
        }
    	fprintf(file,"Nome: %s\nIdade: %d\nRaça: %s\nID do Tutor: %d\nEspécie: %s\n",
            newPet.petName, newPet.age, newPet.breed, newPet.tutorID, newPet.species);
    	fclose(file);
		printf("Pet cadastrado com sucesso!\n");
	} else {	
		printf("Tutor com o ID informado não foi encontrado.\n");
    }
}

int checkPetFromTutor(int tutorID, const char *petName) {
    FILE *file = fopen("pet.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pets.\n");
        return 0;
    }
    Pet pet;
    int encontrado = 0;

    while (fscanf(file, "Nome: %[^\n]\nIdade: %d\nRaça: %[^\n]\nID do Tutor: %d\n",
            pet.petName, &pet.age, pet.breed, &pet.tutorID) == 4) {
        if (pet.tutorID == tutorID && strcmp(pet.petName, petName) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(file);

    return encontrado;
}

int countPetsRegistered() {
    FILE *file = fopen("pet.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de pets.\n");
        return 0;
    }
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Nome:") != NULL) {
            count++;
        }
    }
    fclose(file);
    return count;
}

void makeLoginProntuario(){
    int tutorID;
    char petName[50];
    int petCount = countPetsRegistered();
    
    if (petCount == 0) {
        printf("Não há pets cadastrados. Impossível acessar o prontuário.\n");
        return;
    } else {
	    printf("Digite o ID do Tutor: ");
	    scanf("%d", &tutorID);
	    printf("Digite o nome do Pet: ");
	    scanf("%s", petName);
	    int petEncontrado = checkPetFromTutor(tutorID, petName);
	    if (petEncontrado) {
	        printf("Acesso permitido ao prontuário do pet %s do tutor ID %d.\n", petName, tutorID);
            animalRecord(tutorID, petName);
	    } else {
	        printf("O pet %s não pertence ao tutor ID %d ou não foi encontrado.\n", petName, tutorID);
	    }
    } 
}

void createAppointmentsFile(PetProntuary *petProntuary, const char *petName, int tutorID) {
	petProntuary->tutor.tutorID = tutorID;
	strcpy(petProntuary->pet.petName, petName);
    char fileName[50];
    sprintf(fileName, "appointments_%d_%s.txt", petProntuary->tutor.tutorID, petName);
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de agendamentos.\n");
        return;
    }
    fclose(file);
}

void createMedicalHistoryFile(PetProntuary *petProntuary, const char *petName, int tutorID) {
	petProntuary->tutor.tutorID = tutorID;
	strcpy(petProntuary->pet.petName, petName);
    char fileName[50];
    sprintf(fileName, "medical_history_%d_%s.txt", petProntuary->tutor.tutorID, petName);
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Erro ao criar o arquivo do histórico médico.\n");
        return;
    }
    fclose(file);
}

void loadAppointments(PetProntuary *petProntuary) {
    char fileName[50];
    sprintf(fileName, "appointments_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos.\n");
        return;
    }
	while (fscanf(file, "Data: %[^\n] Veterinário: %[^\n]\n", 
        petProntuary->appointments[petProntuary->appointmentCount].date,
        petProntuary->appointments[petProntuary->appointmentCount].veterinarian) == 2) {
        petProntuary->appointmentCount++;
        if (petProntuary->appointmentCount >= MAX_APPOINTMENTS) {
            break;
        }
    }
    fclose(file);
}

void loadMedicalHistory(PetProntuary *petProntuary) {
    char fileName[50];
    sprintf(fileName, "medical_history_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo do histórico médico.\n");
        return;
    }

    while (fgets(petProntuary->medicalHistory[petProntuary->medicalRecordCount].date, sizeof(petProntuary->medicalHistory[petProntuary->medicalRecordCount].date), file) != NULL &&
           fgets(petProntuary->medicalHistory[petProntuary->medicalRecordCount].details, sizeof(petProntuary->medicalHistory[petProntuary->medicalRecordCount].details), file) != NULL) {
        petProntuary->medicalRecordCount++;
        if (petProntuary->medicalRecordCount >= MAX_MEDICAL_HISTORY) {
            break; 
        }
    }
    fclose(file);
}

void saveScheduledConsultation(PetProntuary *petProntuary, char *dataConsulta, char *nomeVeterinario) {
    if (petProntuary->appointmentCount >= MAX_APPOINTMENTS) {
        printf("Limite de consultas agendadas atingido.\n");
        return;
    }
    sprintf(petProntuary->appointments[petProntuary->appointmentCount].date, "Data: %s", dataConsulta);
    sprintf(petProntuary->appointments[petProntuary->appointmentCount].veterinarian, "Veterinário: %s", nomeVeterinario);
    petProntuary->appointmentCount++;
    char fileName[50];
    sprintf(fileName, "appointments_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos para escrita.\n");
        return;
    }
    fprintf(file, "Data: %s\nVeterinário: %s\n\n", dataConsulta, nomeVeterinario);
    fclose(file);
}

void addScheduledConsultation(PetProntuary *petProntuary) {
    printf("=== AGENDAMENTO DE CONSULTA ===\n");

    char veterinarian[50];
    char date[11];
    
    printf("Digite o nome do veterinário:\n");
    fflush(stdin);
    fgets(veterinarian, sizeof(veterinarian), stdin);
    strtok(veterinarian, "\n");
    printf("Digite a data da consulta (formato DD/MM/YYYY):\n");
    fflush(stdin);
    fgets(date, sizeof(date), stdin);
    strtok(date, "\n");

    FILE *agendaFile = fopen("agenda.txt", "r");
    if (agendaFile == NULL) {
        printf("Erro ao abrir o arquivo de agenda.\n");
        return;
    }
    FILE *tempFile = fopen("temp_agenda.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(agendaFile);
        return;
    }
    char line[100]; 
    int consultaAgendada = 0;
    while (fgets(line, sizeof(line), agendaFile) != NULL) {
        char dataAtual[11], vetAtual[50];
        if (sscanf(line, "Data: %s - %s\n", dataAtual, vetAtual) == 2) {
            if (strcmp(dataAtual, date) == 0 && strcmp(vetAtual, veterinarian) == 0) {
                consultaAgendada = 1;
                printf("Consulta agendada com sucesso para %s com o veterinário %s.\n", date, veterinarian);
                saveScheduledConsultation(petProntuary, date, veterinarian);
                continue;
            }
        }
        fprintf(tempFile, "%s", line);
    }

    fclose(agendaFile);
    fclose(tempFile);

    remove("agenda.txt");
    rename("temp_agenda.txt", "agenda.txt");

    if (!consultaAgendada) {
        printf("Data ou veterinário indisponíveis. Consulta não agendada.\n");
    }
}


void listMedicalInformation(PetProntuary *petProntuary) {
    printf("=== INFORMAÇÕES MÉDICAS DO ANIMAL ===\n");

    char fileName[50];
    sprintf(fileName, "medical_history_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Nenhuma informação médica encontrada para este animal.\n");
        return;
    }
    
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void addMedicalInformation(PetProntuary *petProntuary) {
    printf("=== ADICIONAR INFORMAÇÕES MÉDICAS DO ANIMAL ===\n");
    printf("Digite as informações médicas (máximo 200 caracteres):\n");

    char informacoes[200];
    fflush(stdin);
    fgets(informacoes, sizeof(informacoes), stdin);

    if (petProntuary->medicalRecordCount < MAX_MEDICAL_HISTORY) {
        strcpy(petProntuary->medicalHistory[petProntuary->medicalRecordCount].details, informacoes);
        printf("Informações médicas adicionadas com sucesso!\n");
        petProntuary->medicalRecordCount++;
        char fileName[50];
        sprintf(fileName, "medical_history_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);
        FILE *file = fopen(fileName, "a");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo do histórico médico.\n");
            return;
        }
        fprintf(file, "%s\n", informacoes);
        fclose(file);
    } else {
        printf("Limite de registros médicos alcançado. Não é possível adicionar mais informações.\n");
    }
}

void viewScheduledConsultations(PetProntuary *petProntuary) {
    printf("=== CONSULTAS AGENDADAS ===\n");
    char fileName[50];
    sprintf(fileName, "appointments_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Nenhuma consulta agendada encontrada para este animal.\n");
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void addVaccinesTaken(PetProntuary *petProntuary) {
    printf("=== ADICIONAR VACINAS TOMADAS ===\n");

    char nomeVacina[50];
    printf("Digite o nome da vacina:\n");
    fflush(stdin);
    fgets(nomeVacina, sizeof(nomeVacina), stdin);
    strtok(nomeVacina, "\n");

    char dataVacina[11];
    printf("Digite a data da vacina (formato DD/MM/YYYY):\n");
    fflush(stdin);
    fgets(dataVacina, sizeof(dataVacina), stdin);
    strtok(dataVacina, "\n");

    char nomeVeterinario[50];
    printf("Digite o nome do veterinário que aplicou a vacina:\n");
    fflush(stdin);
    fgets(nomeVeterinario, sizeof(nomeVeterinario), stdin);
    strtok(nomeVeterinario, "\n");

    char dataProximaVacina[11];
    printf("Digite a data da próxima vacina (formato DD/MM/YYYY):\n");
    fflush(stdin);
    fgets(dataProximaVacina, sizeof(dataProximaVacina), stdin);
    strtok(dataProximaVacina, "\n");

    char fileName[50];
    sprintf(fileName, "vaccines_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);
    FILE *file = fopen(fileName, "a");

    if (file == NULL) {
       printf("Erro ao abrir o arquivo de vacinas para escrita.\n");
       return;
    }

    fprintf(file, "Nome da Vacina: %s\nData da Vacina: %s\nVeterinário: %s\nPróxima Vacina: %s\n\n", nomeVacina, dataVacina, nomeVeterinario, dataProximaVacina);
    fclose(file);
}

void viewVaccinesTaken(PetProntuary *petProntuary) {
    printf("=== VACINAS TOMADAS ===\n");

    char fileName[50];
    sprintf(fileName, "vaccines_%d_%s.txt", petProntuary->tutor.tutorID, petProntuary->pet.petName);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Nenhuma informação de vacina encontrada para este animal.\n");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}


void animalRecord(int tutorID, const char *petName){
	
	PetProntuary petProntuary;
    petProntuary.appointmentCount = 0;
    petProntuary.medicalRecordCount = 0;
    
    createAppointmentsFile(&petProntuary, petName, tutorID);
    createMedicalHistoryFile(&petProntuary, petName, tutorID);
	loadAppointments(&petProntuary);
	loadMedicalHistory(&petProntuary);
	
	int choice;
    int c;
	
    do {
    	system("cls");
    	cabecalho ();
        printf("\n=== PRONTUÁRIO ANIMAL ===\n");
        printf("1. Agendamento de consultas\n");
        printf("2. Adicionar vacinas tomadas\n");
        printf("3. Visualizar vacinas\n");
        printf("4. Visualizar Informacoes medicas do animal\n");
        printf("5. Adicionar Informacoes medicas do animal\n");
        printf("6. Consultas agendadas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            system("pause");
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
            continue;
        }
        
        switch (choice) {
            case 1:
                system("cls");
                addScheduledConsultation(&petProntuary);
                system("pause");
                break;
            case 2:
            	system("cls");
                addVaccinesTaken(&petProntuary);
                system("pause");
                break;
            case 3:
            	system("cls");
                viewVaccinesTaken(&petProntuary);
                system("pause");
                break;
            case 4:
            	system("cls");
            	listMedicalInformation(&petProntuary);
            	system("pause");
            	break;
            case 5:
            	system("cls");
            	addMedicalInformation(&petProntuary);
            	system("pause");
            	break;
            case 6:
            	system("cls");
   	 			viewScheduledConsultations(&petProntuary);
   	 			system("pause");
            	break;
            case 0:                 
                printf("Deslogando...\n");
                system("pause");
                system("cls");
				return;            
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);
}

int countEmployees() {
    FILE *file = fopen("funcionarios.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    char line[100];
    int count = 0;
    char cpfsEncontrados[MAX_EMPLOYEE][CPF_LENGTH + 1];
    memset(cpfsEncontrados, 0, sizeof(cpfsEncontrados));
    while (fgets(line, sizeof(line), file) != NULL) {
        char currentCPF[CPF_LENGTH + 1];
        sscanf(line, "CPF: %s", currentCPF);
        int cpfJaContado = 0;
        for (int i = 0; i < MAX_EMPLOYEE; i++) {
            if (strcmp(cpfsEncontrados[i], currentCPF) == 0) {
                cpfJaContado = 1;
                break;
            }
        }
        if (!cpfJaContado) {
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

void registerEmployee() {
    Employee newEmployee;
    int numFuncionarios = countEmployees();
    
    if (numFuncionarios >= MAX_EMPLOYEE) {
        printf("Limite de funcionários atingido. Não é possível cadastrar mais funcionários.\n");
        return;
    }else {
	    do {
	        printf("CPF (11 números): ");
	        scanf("%s", newEmployee.people.cpf);
	
	        if (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validateCPF(newEmployee.people.cpf)) {
	            printf("CPF inválido. Insira 11 números válidos.\n");
	        }
	    } while (strlen(newEmployee.people.cpf) != CPF_LENGTH || !validateCPF(newEmployee.people.cpf));
	    fflush(stdin);
	    printf("Nome: ");
	    gets(newEmployee.people.name);
	    printf("Idade: ");
	    scanf("%d", &newEmployee.people.age);
	    fflush(stdin);
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
	
	    fprintf(file, "Nome: %s \nIdade: %d  \nEndereço: %s \nEmail: %s \nCPF: %s \nTelefone: %d \nCargo: %s \nSalário: %.2lf \nSenha: %s\n",
	            newEmployee.people.name, newEmployee.people.age, newEmployee.people.address,
	            newEmployee.people.email, newEmployee.people.cpf, newEmployee.people.phoneNumber,
	            newEmployee.role, newEmployee.salary, newEmployee.password);
	
	    fclose(file);
	
	    printf("Funcionário cadastrado com sucesso!\n");
    }
}

void addDateAgenda() {
    FILE *agendaFile = fopen("agenda.txt", "a");
    if (agendaFile == NULL) {
        printf("Erro ao abrir o arquivo de agenda.\n");
        return;
    }
    char novaData[20];
    char nomeVeterinario[50];
  	printf("Digite a nova data (DD/MM/YYYY): ");
    scanf("%s", novaData);
    fflush(stdin);
    printf("Digite o nome do veterinário disponível: ");
    gets(nomeVeterinario);
    fflush(stdin);
    fprintf(agendaFile, "Data: %s - %s\n", novaData, nomeVeterinario);
    fclose(agendaFile);
}

void viewSchedule() {
    FILE *agendaFile = fopen("agenda.txt", "r");
    if (agendaFile == NULL) {
        printf("Erro ao abrir o arquivo de agenda.\n");
        return;
    }
    printf("\nDatas Disponíveis para Consulta:\n");
    char line[100];
    while (fgets(line, sizeof(line), agendaFile) != NULL) {
        printf("%s", line);
    }
    fclose(agendaFile);
}

void employeeMenu(){
	int choice;
    int c;

    do {
    	system("cls");
    	cabecalho ();
        printf("\n=== MENU DO FUNCIONÁRIO ===\n");
        printf("1. Cadastro do Pet\n");
        printf("2. Cadastro do Tutor\n");
        printf("3. Prontuário do Pet\n");
        printf("4. Visualizar Agenda Vet\n");
        printf("5. Adicionar na Agenda Vet\n");
        printf("0. Deslogar\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            system("pause");
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
        }
        
        switch (choice) {
            case 1:
                system("cls");
                registerPet();
                break;
            case 2:
            	system("cls");
                registerTutor();
                break;
            case 3:
            	system("cls");
            	makeLoginProntuario();
            	break;
            case 4:
                system("cls");
                viewSchedule();
                system("pause");
                break;
            case 5:
                system("cls");
                addDateAgenda();
                break;
            case 0:                 
                printf("Deslogando...\n");
                system("cls");
                return;            
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);
}

int validateLogin(const char *inputCPF, const char *inputPassword) {
    FILE *file = fopen("funcionarios.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    Employee employee;
    int loginSuccess = 0;
    while (fscanf(file, "Nome: %[^\n]\nIdade: %d\nEndereço: %[^\n]\nEmail: %[^\n]\nCPF: %s\nTelefone: %d\nCargo: %[^\n]\nSalário: %lf\nSenha: %[^\n]\n\n",
                  employee.people.name, &employee.people.age, employee.people.address, employee.people.email, employee.people.cpf,
                  &employee.people.phoneNumber, employee.role, &employee.salary, employee.password) == 9) {
        if (strcmp(employee.people.cpf, inputCPF) == 0 && strcmp(employee.password, inputPassword) == 0) {
            loginSuccess = 1;
            break;
        } 
    }
    fclose(file);
    return loginSuccess;
}


void makeLogin(){
     
    char password[PASSWORD_LENGTH + 1];
    char cpf[CPF_LENGTH + 1];
    
    cabecalho (); 
    printf("Digite seu CPF: ");
    scanf("%s", cpf);
    fflush(stdin);
    printf("Digite sua senha: ");
    scanf("%s", password);
    
    int resultadoLogin = validateLogin(cpf, password);
    if (resultadoLogin) {
        printf("Login bem-sucedido!\n");
        employeeMenu();
    } else {
        printf("CPF ou senha incorretos. Tente novamente.\n");
        system("pause");
    }

}

void mainMenu() {
    int choice;
    int c;

    do {
    	system("cls");
    	cabecalho ();
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Login do Funcionário\n");
        printf("2. Cadastro de Funcionário\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            system("pause");
            while ((c = getchar()) != '\n' && c != EOF);
            system("cls");
            continue;
        }
        switch (choice) {
            case 1:
                 system("cls");
                 makeLogin();
                break;
            case 2:
            	 system("cls");
                 registerEmployee();
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
	setlocale(LC_ALL, "Portuguese");
    mainMenu();
    return 0;
}
