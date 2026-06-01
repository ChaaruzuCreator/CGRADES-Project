#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Color.h"

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MAX_STUDENTS 50
#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    float quiz1;
    float quiz2;
    float activity;
    float average;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void saveToFile() {

    #ifdef _WIN32
    system("mkdir \"Student Records\" 2>nul");
#else
    system("mkdir -p \"Student Records\" 2>/dev/null");
#endif
    
    #ifdef _WIN32
    FILE* file = fopen("Student Records\\students.txt", "w");
#else
    FILE* file = fopen("Student Records/students.txt", "w");
#endif
    if (file == NULL) {
        printf("Error saving data!\n");
        return;
    }
    fprintf(file, "Total Students: %d\n\n", studentCount);
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "\nID: %d\n", students[i].id);  
        fprintf(file, "Name: %s\n", students[i].name);    
        fprintf(file, "Quiz 1: %.2f\n", students[i].quiz1);
        fprintf(file, "Quiz 2: %.2f\n", students[i].quiz2);
        fprintf(file, "Activity: %.2f\n", students[i].activity);
        fprintf(file, "Average: %.2f\n", students[i].average);
        if (i < studentCount - 1) {
            fprintf(file, "");
        }
        fprintf(file, "\n================\n");
    }
    fclose(file);
}

void loadFromFile() {
    #ifdef _WIN32
    FILE* file = fopen("Student Records\\students.txt", "r");
#else
    FILE* file = fopen("Student Records/students.txt", "r");
#endif
    if (file == NULL) {
        return;
    }
    char buffer[100];
    fscanf(file, "Total Students: %d\n\n", &studentCount);
    for (int i = 0; i < studentCount; i++) {
        fscanf(file, "\nID: %d\n", &students[i].id);
        fscanf(file, "Name: ");
        fgets(students[i].name, MAX_NAME, file);
        students[i].name[strcspn(students[i].name, "\n")] = 0;
        fscanf(file, "Quiz 1: %f\n", &students[i].quiz1);
        fscanf(file, "Quiz 2: %f\n", &students[i].quiz2);
        fscanf(file, "Activity: %f\n", &students[i].activity);
        fscanf(file, "Average: %f\n", &students[i].average);
        fgets(buffer, sizeof(buffer), file); 
    }
    fclose(file);
}

void calculateAverage(Student* s) {
    s->average = (s->quiz1 + s->quiz2 + s->activity) / 3.0;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students!\n");
        return;
    }
    
    Student s;
    s.id = studentCount + 1;
    s.quiz1 = 0;
    s.quiz2 = 0;
    s.activity = 0;
    
    printf("Enter student name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    int recordChoice;
    int continueAdding = 1;
    
    while (continueAdding) {
        printf("\nWhat should you record?\n");
        printf("1. Quiz 1\n");
        printf("2. Quiz 2\n");
        printf("3. Activity\n");
        printf("4. Finish and Save\n");
        printf("Choose: ");
        scanf("%d", &recordChoice);
        system(CLEAR_SCREEN);
        
        switch (recordChoice) {
            case 1:
                printf("Name: %s\n", s.name);
                printf("Enter Quiz 1 score (0-100): ");
                scanf("%f", &s.quiz1);
                while (s.quiz1 < 0 || s.quiz1 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Quiz 1 score (0-100): ");
                    scanf("%f", &s.quiz1);
                }
                printf(GREEN "Quiz 1 saved: %.2f\n" HAGGANGDITO, s.quiz1);
                break;
                
            case 2:
                printf("Name: %s\n", s.name);
                printf("Enter Quiz 2 score (0-100): ");
                scanf("%f", &s.quiz2);
                while (s.quiz2 < 0 || s.quiz2 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Quiz 2 score (0-100): ");
                    scanf("%f", &s.quiz2);
                }
                printf(GREEN "Quiz 2 saved: %.2f\n" HAGGANGDITO, s.quiz2);
                break;
                
            case 3:
                printf("Name: %s\n", s.name);
                printf("Enter Activity score (0-100): ");
                scanf("%f", &s.activity);
                while (s.activity < 0 || s.activity > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Activity score (0-100): ");
                    scanf("%f", &s.activity);
                }
                printf(GREEN "Activity saved: %.2f\n" HAGGANGDITO, s.activity);
                break;
                
            case 4:
                continueAdding = 0;
                break;
                
            default:
                printf(RED "Invalid choice! Please try again.\n" HAGGANGDITO);
                break;
        }
    }

    getchar();
    
    calculateAverage(&s);
    students[studentCount] = s;
    studentCount++;

    printf(GREEN"Student added successfully! ID: %d\n"HAGGANGDITO, s.id );
    saveToFile();
            printf("\nName: %s\n", s.name);
            printf("Quiz 1: %.2f\n", s.quiz1);
            printf("Quiz 2: %.2f\n", s.quiz2);
            printf("Activity: %.2f\n", s.activity);
            printf("Average: %.2f\n", s.average);
        printf("\nYou can Edit this again\n");
    printf("\nPress Enter to continue: ");
    getchar();
    system(CLEAR_SCREEN);
}

void showAllStudents() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }
    
    printf("\n=== ALL STUDENTS ===\n");
    for (int i = 0; i < studentCount; i++) {
        printf("\nID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Quiz 1: %.2f\n", students[i].quiz1);
        printf("Quiz 2: %.2f\n", students[i].quiz2);
        printf("Activity: %.2f\n", students[i].activity);
        printf("Average: %.2f\n", students[i].average);
    }
    printf("\nPress Enter to exit: ");
    getchar();
    system(CLEAR_SCREEN);
}

void searchStudent() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }
    
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("\nID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Quiz 1: %.2f\n", students[i].quiz1);
            printf("Quiz 2: %.2f\n", students[i].quiz2);
            printf("Activity: %.2f\n", students[i].activity);
            printf("Average: %.2f\n", students[i].average);
            return;
        }
    }
    printf("Student not found.\n");
}

void editStudent() {
    if (studentCount == 0) {
        printf("No students to edit.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to edit: ");
    scanf("%d", &id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            int editChoice;
            int continueEditing = 1;
            
            while (continueEditing) {
                printf("\n=== Current Information ===\n");
                printf("Name: %s\n", students[i].name);
                printf("Quiz 1: %.2f\n", students[i].quiz1);
                printf("Quiz 2: %.2f\n", students[i].quiz2);
                printf("Activity: %.2f\n", students[i].activity);
                
                printf("\nWhat do you want to edit?\n");
                printf("1. Quiz 1\n");
                printf("2. Quiz 2\n");
                printf("3. Activity\n");
                printf("4. Finish and Save\n");
                printf("Choose: ");
                scanf("%d", &editChoice);
                system(CLEAR_SCREEN);
                
                switch (editChoice) {
                    case 1:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Quiz 1: %.2f\n", students[i].quiz1);
                        printf("Enter new Quiz 1 score (0-100): ");
                        scanf("%f", &students[i].quiz1);
                        while (students[i].quiz1 < 0 || students[i].quiz1 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Quiz 1 score (0-100): ");
                            scanf("%f", &students[i].quiz1);
                        }
                        printf(GREEN "Quiz 1 updated: %.2f\n" HAGGANGDITO, students[i].quiz1);
                        break;
                        
                    case 2:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Quiz 2: %.2f\n", students[i].quiz2);
                        printf("Enter new Quiz 2 score (0-100): ");
                        scanf("%f", &students[i].quiz2);
                        while (students[i].quiz2 < 0 || students[i].quiz2 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Quiz 2 score (0-100): ");
                            scanf("%f", &students[i].quiz2);
                        }
                        printf(GREEN "Quiz 2 updated: %.2f\n" HAGGANGDITO, students[i].quiz2);
                        break;
                        
                    case 3:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Activity: %.2f\n", students[i].activity);
                        printf("Enter new Activity score (0-100): ");
                        scanf("%f", &students[i].activity);
                        while (students[i].activity < 0 || students[i].activity > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Activity score (0-100): ");
                            scanf("%f", &students[i].activity);
                        }
                        printf(GREEN "Activity updated: %.2f\n" HAGGANGDITO, students[i].activity);
                        break;
                        
                    case 4:
                        continueEditing = 0;
                        break;
                        
                    default:
                        printf(RED "Invalid choice! Please try again.\n" HAGGANGDITO);
                        break;
                }
            }
            
            getchar();
            calculateAverage(&students[i]);
            saveToFile();
            printf(GREEN "Student updated successfully!\n" HAGGANGDITO);
                printf("Name: %s\n", students[i].name);
                printf("Quiz 1: %.2f\n", students[i].quiz1);
                printf("Quiz 2: %.2f\n", students[i].quiz2);
                printf("Activity: %.2f\n", students[i].activity);
                printf("Average: %.2f\n", students[i].average);
            printf("\nPress Enter to continue: ");
            getchar();
            system(CLEAR_SCREEN);
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent() {
    if (studentCount == 0) {
        printf("No students to delete.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student deleted successfully.\n");
            saveToFile();
            return;
        }
    }
    printf("Student not found.\n");
}

int main() {
    int choice;
    
    loadFromFile();
    
    while (1) {
    enableANSI();
        const char *banner =
        "\n"
GREEN"\t    .::      .::::   .:::::::          .:       .:::::    .::::::::  .:: ::  \n"
"\t .::   .:: .:    .:: .::    .::       .: ::     .::   .:: .::      .::    .::\n"
"\t.::       .::        .::    .::      .:  .::    .::    .::.::       .::      \n"
"\t.::       .::        .: .::         .::   .::   .::    .::.::::::     .::    \n"
"\t.::       .::   .::::.::  .::      .:::::: .::  .::    .::.::            .:: \n"
"\t .::   .:: .::    .: .::    .::   .::       .:: .::   .:: .::      .::    .::\n"
"\t   .::::    .:::::   .::      .::.::         .::.:::::    .::::::::  .:: ::  \n" HAGGANGDITO
"\n"
"\t                                BY BSEMC 1-B                              ";
                                                         
    puts(banner);
        printf("\n=== STUDENT GRADE SYSTEM ===\n");
        printf("[1] Add Student\n");
        printf("[2] Show All Students\n");
        printf("[3] Search Student\n");
        printf("[4] Edit Student\n");
        printf("[5] Delete Student\n");
        printf("[6] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        system(CLEAR_SCREEN);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                showAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                editStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
      
    }
    
    return 0;
}
