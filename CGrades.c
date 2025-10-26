#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Color.h"

#define MAX_STUDENTS 50
#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    float quiz1;
    float quiz2;
    float quiz3;
    float activity1;
    float activity2;
    float activity3;
    float examination;
    float project;
    float average;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void saveToFile() {

    system("mkdir \"Student Records\" 2>nul");
    
    FILE* file = fopen("Student Records\\students.txt", "w");
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
        fprintf(file, "Quiz 3: %.2f\n", students[i].quiz3);
        fprintf(file, "Activity 1: %.2f\n", students[i].activity1);
        fprintf(file, "Activity 2: %.2f\n", students[i].activity2);
        fprintf(file, "Activity 3: %.2f\n", students[i].activity3);
        fprintf(file, "Examination: %.2f\n", students[i].examination);
        fprintf(file, "Project: %.2f\n", students[i].project);
        fprintf(file, "Average: %.2f\n", students[i].average);
        if (i < studentCount - 1) {
            fprintf(file, "");
        }
        fprintf(file, "\n================\n");
    }
    fclose(file);
}

void loadFromFile() {
    FILE* file = fopen("Student Records\\students.txt", "r");
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
        fscanf(file, "Quiz 3: %f\n", &students[i].quiz3);
        fscanf(file, "Activity 1: %f\n", &students[i].activity1);
        fscanf(file, "Activity 2: %f\n", &students[i].activity2);
        fscanf(file, "Activity 3: %f\n", &students[i].activity3);
        fscanf(file, "Examination: %f\n", &students[i].examination);
        fscanf(file, "Project: %f\n", &students[i].project);
        fscanf(file, "Average: %f\n", &students[i].average);
        fgets(buffer, sizeof(buffer), file); // Skip empty line
        fgets(buffer, sizeof(buffer), file); // Skip separator line
    }
    fclose(file);
}

void calculateAverage(Student* s) {
    s->average = (s->quiz1 + s->quiz2 + s->quiz3 + s->activity1 + s->activity2 + s->activity3 + s->examination + s->project) / 8.0;
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
    s.quiz3 = 0;
    s.activity1 = 0;
    s.activity2 = 0;
    s.activity3 = 0;
    s.examination = 0;
    s.project = 0;
    
    printf("Enter student name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    system("cls");

    char recordChoice;
    int continueAdding = 1;
    
    while (continueAdding) {
        printf("\nSTUDENT NAME: %s\n\n", s.name);
        
        // Calculate current average
        float currentAvg = (s.quiz1 + s.quiz2 + s.quiz3 + s.activity1 + s.activity2 + s.activity3 + s.examination + s.project) / 8.0;
        
        // Print table header
        printf("| %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-7s\n", 
               "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
        printf("+--------+--------+--------+--------+--------+--------+--------+--------+---------\n");
        
        // Print scores
        printf("| %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %7.2f\n",
               s.quiz1, s.quiz2, s.quiz3, s.activity1, s.activity2, s.activity3, s.examination, s.project, currentAvg);
        
        printf(YELLOW "\nWhat should you record?\n\n" HAGGANGDITO);

        printf("[1] Quiz 1  [4] Activity 1  [7] Examination\n");
        printf("[2] Quiz 2  [5] Activity 2  [8] Project\n");
        printf("[3] Quiz 3  [6] Activity 3  [9] Information\n\n");

        printf("[Y] Finish and Save\n");
        printf("[N] Cancel\n");
        printf("Choose: ");
        scanf(" %c", &recordChoice);
        getchar();
        system("cls");
        
        switch (recordChoice) {
            case '1':
            case 1:
                printf("=== ENTERING QUIZ 1 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Quiz 1 score (0-100): ");
                scanf("%f", &s.quiz1);
                while (s.quiz1 < 0 || s.quiz1 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Quiz 1 score (0-100): ");
                    scanf("%f", &s.quiz1);
                }
                printf(GREEN "Quiz 1 saved: %.2f\n" HAGGANGDITO, s.quiz1);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '2':
            case 2:
                printf("=== ENTERING QUIZ 2 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Quiz 2 score (0-100): ");
                scanf("%f", &s.quiz2);
                while (s.quiz2 < 0 || s.quiz2 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Quiz 2 score (0-100): ");
                    scanf("%f", &s.quiz2);
                }
                printf(GREEN "Quiz 2 saved: %.2f\n" HAGGANGDITO, s.quiz2);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '3':
            case 3:
                printf("=== ENTERING QUIZ 3 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Quiz 3 score (0-100): ");
                scanf("%f", &s.quiz3);
                while (s.quiz3 < 0 || s.quiz3 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Quiz 3 score (0-100): ");
                    scanf("%f", &s.quiz3);
                }
                printf(GREEN "Quiz 3 saved: %.2f\n" HAGGANGDITO, s.quiz3);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '4':
            case 4:
                printf("=== ENTERING ACTIVITY 1 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Activity 1 score (0-100): ");
                scanf("%f", &s.activity1);
                while (s.activity1 < 0 || s.activity1 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Activity 1 score (0-100): ");
                    scanf("%f", &s.activity1);
                }
                printf(GREEN "Activity 1 saved: %.2f\n" HAGGANGDITO, s.activity1);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '5':
            case 5:
                printf("=== ENTERING ACTIVITY 2 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Activity 2 score (0-100): ");
                scanf("%f", &s.activity2);
                while (s.activity2 < 0 || s.activity2 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Activity 2 score (0-100): ");
                    scanf("%f", &s.activity2);
                }
                printf(GREEN "Activity 2 saved: %.2f\n" HAGGANGDITO, s.activity2);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '6':
            case 6:
                printf("=== ENTERING ACTIVITY 3 ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Activity 3 score (0-100): ");
                scanf("%f", &s.activity3);
                while (s.activity3 < 0 || s.activity3 > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Activity 3 score (0-100): ");
                    scanf("%f", &s.activity3);
                }
                printf(GREEN "Activity 3 saved: %.2f\n" HAGGANGDITO, s.activity3);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '7':
            case 7:
                printf("=== ENTERING EXAMINATION ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Examination score (0-100): ");
                scanf("%f", &s.examination);
                while (s.examination < 0 || s.examination > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Examination score (0-100): ");
                    scanf("%f", &s.examination);
                }
                printf(GREEN "Examination saved: %.2f\n" HAGGANGDITO, s.examination);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case '8':
            case 8:
                printf("=== ENTERING PROJECT ===\n");
                printf("Name: %s\n", s.name);
                printf("Enter Project score (0-100): ");
                scanf("%f", &s.project);
                while (s.project < 0 || s.project > 100) {
                    printf("Invalid score! Please enter a score between 0 and 100.\n");
                    printf("Enter Project score (0-100): ");
                    scanf("%f", &s.project);
                }
                printf(GREEN "Project saved: %.2f\n" HAGGANGDITO, s.project);
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                system("cls");
                break;
                
            case 'Y':
            case 'y':
                continueAdding = 0;
                break;
                
            case '9':
            case 9:
                printf("=== EDIT STUDENT NAME ===\n");
                printf("Current Name: %s\n", s.name);
                printf("Enter new name: ");
                fgets(s.name, MAX_NAME, stdin);
                s.name[strcspn(s.name, "\n")] = 0;
                printf(GREEN "Name updated to: %s\n" HAGGANGDITO, s.name);
                printf("\nPress Enter to continue...");
                getchar();
                system("cls");
                break;
                
            case 'N':
            case 'n':
                printf(YELLOW "Cancelled. Student not added.\n" HAGGANGDITO);
                printf("Press Enter to continue...");
                getchar();
                system("cls");
                return;
                
            default:
                printf(RED "Invalid choice! Please try again.\n" HAGGANGDITO);
                break;
        }
    }
    
    calculateAverage(&s);
    students[studentCount] = s;
    studentCount++;

    printf(GREEN "Student added successfully! ID: %d\n" HAGGANGDITO, s.id);
    saveToFile();
    
    printf("\n=== STUDENT: %s ===\n\n", s.name);
    
    // Print table header
    printf("| %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-7s\n", 
           "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
    printf("+--------+--------+--------+--------+--------+--------+--------+--------+---------\n");
    
    // Print scores
    printf("| %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %7.2f\n",
           s.quiz1, s.quiz2, s.quiz3, s.activity1, s.activity2, s.activity3, s.examination, s.project, s.average);
    
    printf("\nYou can Edit this again\n");
    printf("\nPress Enter to continue: ");
    getchar();
    system("cls");
}

void showAllStudents() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }
    
    while (1) {
        system("cls");
        printf("\n=== ALL STUDENTS ===\n\n");
        
        printf("%-4s | %-25s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-7s\n", 
               "ID", "Name", "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
        printf("-----+---------------------------+--------+--------+--------+--------+--------+--------+--------+--------+---------\n");
        
        for (int i = 0; i < studentCount; i++) {
            printf("%-4d | %-25s | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %6.2f | %7.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].quiz1,
                   students[i].quiz2,
                   students[i].quiz3,
                   students[i].activity1,
                   students[i].activity2,
                   students[i].activity3,
                   students[i].examination,
                   students[i].project,
                   students[i].average);
        }
        
        printf("\n[1] Search Student by ID\n");
        printf("[0] Back to Main Menu\n");
        printf("Choose: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1) {
            int searchAgain = 1;
            while (searchAgain) {
                int id;
                printf("\nEnter student ID (0 to exit) : ");
                scanf("%d", &id);
                getchar();
                if (id == 0) {
                    break;
                }
                
                int found = 0;
                for (int i = 0; i < studentCount; i++) {
                    if (students[i].id == id) {
                        system("cls");
                        printf("\n=== STUDENT DETAILS ===\n\n");
                        printf("ID: %d\n", students[i].id);
                        printf("Name: %s\n", students[i].name);
                        printf("Quiz 1: %.2f\n", students[i].quiz1);
                        printf("Quiz 2: %.2f\n", students[i].quiz2);
                        printf("Quiz 3: %.2f\n", students[i].quiz3);
                        printf("Activity 1: %.2f\n", students[i].activity1);
                        printf("Activity 2: %.2f\n", students[i].activity2);
                        printf("Activity 3: %.2f\n", students[i].activity3);
                        printf("Examination: %.2f\n", students[i].examination);
                        printf("Project: %.2f\n", students[i].project);
                        printf("Average: %.2f\n", students[i].average);
                        printf("\nPress Enter to continue...");
                        getchar();
                        found = 1;
                        searchAgain = 0;
                        break;
                    }
                }
                if (!found) {
                    printf(RED "\nStudent not found. Try again.\n" HAGGANGDITO);
                }
            }
        } else if (choice == 0) {
            system("cls");
            break;
        } else {
            printf(RED "Invalid choice!\n" HAGGANGDITO);
            printf("Press Enter to continue...");
            getchar();
        }
    }
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
                printf("Quiz 3: %.2f\n", students[i].quiz3);
                printf("Activity 1: %.2f\n", students[i].activity1);
                printf("Activity 2: %.2f\n", students[i].activity2);
                printf("Activity 3: %.2f\n", students[i].activity3);
                printf("Examination: %.2f\n", students[i].examination);
                printf("Project: %.2f\n", students[i].project);
                
                printf("\nWhat do you want to edit?\n");
                printf("1. Quiz 1\n");
                printf("2. Quiz 2\n");
                printf("3. Quiz 3\n");
                printf("4. Activity 1\n");
                printf("5. Activity 2\n");
                printf("6. Activity 3\n");
                printf("7. Examination\n");
                printf("8. Project\n");
                printf("0. Finish and Save\n");
                printf("Choose: ");
                scanf("%d", &editChoice);
                system("cls");
                
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
                        printf("Current Quiz 3: %.2f\n", students[i].quiz3);
                        printf("Enter new Quiz 3 score (0-100): ");
                        scanf("%f", &students[i].quiz3);
                        while (students[i].quiz3 < 0 || students[i].quiz3 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Quiz 3 score (0-100): ");
                            scanf("%f", &students[i].quiz3);
                        }
                        printf(GREEN "Quiz 3 updated: %.2f\n" HAGGANGDITO, students[i].quiz3);
                        break;
                        
                    case 4:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Activity 1: %.2f\n", students[i].activity1);
                        printf("Enter new Activity 1 score (0-100): ");
                        scanf("%f", &students[i].activity1);
                        while (students[i].activity1 < 0 || students[i].activity1 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Activity 1 score (0-100): ");
                            scanf("%f", &students[i].activity1);
                        }
                        printf(GREEN "Activity 1 updated: %.2f\n" HAGGANGDITO, students[i].activity1);
                        break;
                        
                    case 5:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Activity 2: %.2f\n", students[i].activity2);
                        printf("Enter new Activity 2 score (0-100): ");
                        scanf("%f", &students[i].activity2);
                        while (students[i].activity2 < 0 || students[i].activity2 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Activity 2 score (0-100): ");
                            scanf("%f", &students[i].activity2);
                        }
                        printf(GREEN "Activity 2 updated: %.2f\n" HAGGANGDITO, students[i].activity2);
                        break;
                        
                    case 6:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Activity 3: %.2f\n", students[i].activity3);
                        printf("Enter new Activity 3 score (0-100): ");
                        scanf("%f", &students[i].activity3);
                        while (students[i].activity3 < 0 || students[i].activity3 > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Activity 3 score (0-100): ");
                            scanf("%f", &students[i].activity3);
                        }
                        printf(GREEN "Activity 3 updated: %.2f\n" HAGGANGDITO, students[i].activity3);
                        break;
                        
                    case 7:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Examination: %.2f\n", students[i].examination);
                        printf("Enter new Examination score (0-100): ");
                        scanf("%f", &students[i].examination);
                        while (students[i].examination < 0 || students[i].examination > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Examination score (0-100): ");
                            scanf("%f", &students[i].examination);
                        }
                        printf(GREEN "Examination updated: %.2f\n" HAGGANGDITO, students[i].examination);
                        break;
                        
                    case 8:
                        printf("Name: %s\n", students[i].name);
                        printf("Current Project: %.2f\n", students[i].project);
                        printf("Enter new Project score (0-100): ");
                        scanf("%f", &students[i].project);
                        while (students[i].project < 0 || students[i].project > 100) {
                            printf("Invalid score! Please enter a score between 0 and 100.\n");
                            printf("Enter new Project score (0-100): ");
                            scanf("%f", &students[i].project);
                        }
                        printf(GREEN "Project updated: %.2f\n" HAGGANGDITO, students[i].project);
                        break;
                        
                    case 0:
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
                printf("Quiz 3: %.2f\n", students[i].quiz3);
                printf("Activity 1: %.2f\n", students[i].activity1);
                printf("Activity 2: %.2f\n", students[i].activity2);
                printf("Activity 3: %.2f\n", students[i].activity3);
                printf("Examination: %.2f\n", students[i].examination);
                printf("Project: %.2f\n", students[i].project);
                printf("Average: %.2f\n", students[i].average);
            printf("\nPress Enter to continue: ");
            getchar();
            system("cls");
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
        printf("[4] Edit Student\n");
        printf("[5] Delete Student\n");
        printf("[0] Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        system("cls");
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                showAllStudents();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 0:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
      
    }
    
    return 0;
}
