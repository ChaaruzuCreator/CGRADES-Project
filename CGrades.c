#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "Color.h"

#define MAX_STUDENTS 50
#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    int grade;              // New: grade level (e.g., 1-12)
    char section[20];       // New: section label (e.g., "A", "BSEMC-1B")
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

static void printStudentTable(void) {
    printf(" "GRN"%-4s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-25s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-5s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-8s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-6s"HAGGANGDITO" "RED"|"HAGGANGDITO" "GRN"%-7s"HAGGANGDITO"\n",
           "ID", "Name", "Grade", "Section", "Quiz1", "Quiz2", "Quiz3",
           "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
    printf(RED" -----+---------------------------+-------+----------+--------+--------+--------+--------+--------+--------+--------+--------+---------\n"HAGGANGDITO);

    for (int i = 0; i < studentCount; i++) {
        printf(" "GRN"%-4d"HAGGANGDITO" "RED"|"HAGGANGDITO" %-25s "RED"|"HAGGANGDITO" %-5d "RED"|"HAGGANGDITO" %-8s "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %7.2f\n",
               students[i].id,
               students[i].name,
               students[i].grade,
               students[i].section,
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
}
//===========================================================================================================================

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
        fprintf(file, "Grade: %d\n", students[i].grade);
        fprintf(file, "Section: %s\n", students[i].section);
        fprintf(file, "Quiz 1:      %.2f\n", students[i].quiz1);
        fprintf(file, "Quiz 2:      %.2f\n", students[i].quiz2);
        fprintf(file, "Quiz 3:      %.2f\n", students[i].quiz3);
        fprintf(file, "Activity 1:  %.2f\n", students[i].activity1);
        fprintf(file, "Activity 2:  %.2f\n", students[i].activity2);
        fprintf(file, "Activity 3:  %.2f\n", students[i].activity3);
        fprintf(file, "Examination: %.2f\n", students[i].examination);
        fprintf(file, "Project:     %.2f\n", students[i].project);
        fprintf(file, "Average:     %.2f\n", students[i].average);
        if (i < studentCount - 1) {
            fprintf(file, "");
        }
        fprintf(file, "\n================\n");
    }
    fclose(file);
}

//===========================================================================================================================

void loadFromFile() {
    FILE* file = fopen("Student Records\\students.txt", "r");
    if (file == NULL) {
        return;
    }
    char line[256];
    fscanf(file, "Total Students: %d\n\n", &studentCount);
    for (int i = 0; i < studentCount; i++) {
        students[i].grade = 0;
        students[i].section[0] = '\0';

        fscanf(file, "\nID: %d\n", &students[i].id);
        fscanf(file, "Name: ");
        fgets(students[i].name, MAX_NAME, file);
        students[i].name[strcspn(students[i].name, "\n")] = 0;

        // Optional grade/section (newer files)
        long posAfterName = ftell(file);
        if (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "Grade:", 6) == 0) {
                sscanf(line, "Grade: %d", &students[i].grade);
                if (fgets(line, sizeof(line), file) && strncmp(line, "Section:", 8) == 0) {
                    // Trim newline
                    char *p = strchr(line, '\n');
                    if (p) *p = '\0';
                    // Copy after prefix
                    const char *sec = line + 8; // after "Section:"
                    while (*sec == ' ') sec++;
                    strncpy(students[i].section, sec, sizeof(students[i].section) - 1);
                    students[i].section[sizeof(students[i].section) - 1] = '\0';
                }
            } else {
                // Not grade line; rewind to let numeric fields parse as before
                fseek(file, posAfterName, SEEK_SET);
            }
        } else {
            // EOF unexpectedly
            break;
        }

        fscanf(file, "Quiz 1: %f\n", &students[i].quiz1);
        fscanf(file, "Quiz 2: %f\n", &students[i].quiz2);
        fscanf(file, "Quiz 3: %f\n", &students[i].quiz3);
        fscanf(file, "Activity 1: %f\n", &students[i].activity1);
        fscanf(file, "Activity 2: %f\n", &students[i].activity2);
        fscanf(file, "Activity 3: %f\n", &students[i].activity3);
        fscanf(file, "Examination: %f\n", &students[i].examination);
        fscanf(file, "Project: %f\n", &students[i].project);
        fscanf(file, "Average: %f\n", &students[i].average);

        // Consume until separator line (backward/forward compatible)
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "================", 16) == 0) break;
        }
    }
    fclose(file);
}

void calculateAverage(Student* s) {
    s->average = (s->quiz1 + s->quiz2 + s->quiz3 + s->activity1 + s->activity2 + s->activity3 + s->examination + s->project) / 8.0;
}

//===========================================================================================================================

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf(RED"Cannot add more students!\n"HAGGANGDITO);
        return;
    }
    
    Student s;
    int candidateId = 1;
    while (candidateId <= MAX_STUDENTS) {
        int used = 0;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].id == candidateId) {
                used = 1;
                break;
            }
        }
        if (!used) {
            break;
        }
        candidateId++;
    }
    if (candidateId > MAX_STUDENTS) {
        printf(RED"Cannot assign new ID. Roster is full.\n"HAGGANGDITO);
        return;
    }
    s.id = candidateId;
    s.grade = 0;
    s.section[0] = '\0';
    s.quiz1 = 0;
    s.quiz2 = 0;
    s.quiz3 = 0;
    s.activity1 = 0;
    s.activity2 = 0;
    s.activity3 = 0;
    s.examination = 0;
    s.project = 0;

    printf(BCYN"=== ADDING NEW STUDENT ===\n\n"HAGGANGDITO);
    
    printf(HYEL"Enter student name (0 to exit)"HAGGANGDITO": ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    if (strlen(s.name) == 0 || strcmp(s.name, "0") == 0) {
        system("cls");
        return;
    }

    
    do {
        printf(HYEL"Enter grade level (1-12)"HAGGANGDITO": ");
        if (scanf("%d", &s.grade) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            s.grade = 0;
        }
        getchar(); 
        if (s.grade < 1 || s.grade > 12) {
            printf(RED"Please enter a valid grade between 1 and 12.\n"HAGGANGDITO);
        }
    } while (s.grade < 1 || s.grade > 12);

    printf(HYEL"Enter section"HAGGANGDITO": ");
    fgets(s.section, sizeof(s.section), stdin);
    s.section[strcspn(s.section, "\n")] = 0;

    system("cls");

    char recordChoice;
    int continueAdding = 1;
    
    while (continueAdding) {
    printf(UGRN"\nSTUDENT:"HAGGANGDITO " %s " RED"|"HAGGANGDITO " Grade: %d " RED"|"HAGGANGDITO " Section: %s\n\n", s.name, s.grade, s.section);
        
        // Calculate current average
        float currentAvg = (s.quiz1 + s.quiz2 + s.quiz3 + s.activity1 + s.activity2 + s.activity3 + s.examination + s.project) / 8.0;
        
        // Print table header
        printf(RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-7s\n", 
               "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
        printf(RED"+--------+--------+--------+--------+--------+--------+--------+--------+---------\n"HAGGANGDITO);
        
        // Print scores
        printf(RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %7.2f\n",
               s.quiz1, s.quiz2, s.quiz3, s.activity1, s.activity2, s.activity3, s.examination, s.project, currentAvg);
        
        printf(BCYN"\nWhat should you record?\n\n"HAGGANGDITO);

        printf(YEL"[1]"HAGGANGDITO" Quiz 1  "YEL"[4]"HAGGANGDITO" Activity 1  "YEL"[7]"HAGGANGDITO" Examination\n");
        printf(YEL"[2]"HAGGANGDITO" Quiz 2  "YEL"[5]"HAGGANGDITO" Activity 2  "YEL"[8]"HAGGANGDITO" Project\n");
    printf(YEL"[3]"HAGGANGDITO" Quiz 3  "YEL"[6]"HAGGANGDITO" Activity 3  "YEL"[9]"HAGGANGDITO" "UWHT BHWHT"Information\n\n"HAGGANGDITO);

        printf(YEL"[Y]"HAGGANGDITO GRN" Finish and Save\n"HAGGANGDITO);
        printf(YEL"[N]"HAGGANGDITO HRED" Cancel\n\n"HAGGANGDITO);
        printf(HYEL"Choose: "HAGGANGDITO);
        scanf(" %c", &recordChoice);
        getchar();
        system("cls");
        
        switch (recordChoice) {
            case '1':
            case 1:
                printf(BCYN"=== ENTERING QUIZ 1 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Quiz 1 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.quiz1);
                while (s.quiz1 < 0 || s.quiz1 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Quiz 1 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.quiz1);
                }
                printf(GRN "Quiz 1 saved: %.2f\n" HAGGANGDITO, s.quiz1);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '2':
            case 2:
                printf(BCYN"=== ENTERING QUIZ 2 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Quiz 2 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.quiz2);
                while (s.quiz2 < 0 || s.quiz2 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Quiz 2 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.quiz2);
                }
                printf(GRN "Quiz 2 saved: %.2f\n" HAGGANGDITO, s.quiz2);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '3':
            case 3:
                printf(BCYN"=== ENTERING QUIZ 3 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Quiz 3 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.quiz3);
                while (s.quiz3 < 0 || s.quiz3 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Quiz 3 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.quiz3);
                }
                printf(GRN "Quiz 3 saved: %.2f\n" HAGGANGDITO, s.quiz3);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '4':
            case 4:
                printf(BCYN"=== ENTERING ACTIVITY 1 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Activity 1 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.activity1);
                while (s.activity1 < 0 || s.activity1 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Activity 1 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.activity1);
                }
                printf(GRN "Activity 1 saved: %.2f\n" HAGGANGDITO, s.activity1);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '5':
            case 5:
                printf(BCYN"=== ENTERING ACTIVITY 2 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Activity 2 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.activity2);
                while (s.activity2 < 0 || s.activity2 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Activity 2 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.activity2);
                }
                printf(GRN "Activity 2 saved: %.2f\n" HAGGANGDITO, s.activity2);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '6':
            case 6:
                printf(BCYN"=== ENTERING ACTIVITY 3 ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Activity 3 score (0-100): "HAGGANGDITO);
                scanf("%f", &s.activity3);
                while (s.activity3 < 0 || s.activity3 > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Activity 3 score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.activity3);
                }
                printf(GRN "Activity 3 saved: %.2f\n" HAGGANGDITO, s.activity3);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '7':
            case 7:
                printf(BCYN"=== ENTERING EXAMINATION ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Examination score (0-100): "HAGGANGDITO);
                scanf("%f", &s.examination);
                while (s.examination < 0 || s.examination > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Examination score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.examination);
                }
                printf(GRN "Examination saved: %.2f\n" HAGGANGDITO, s.examination);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case '8':
            case 8:
                printf(BCYN"=== ENTERING PROJECT ===\n\n"HAGGANGDITO);
                printf(HYEL"Name: "HAGGANGDITO"%s\n", s.name);
                printf(HYEL"Enter Project score (0-100): "HAGGANGDITO);
                scanf("%f", &s.project);
                while (s.project < 0 || s.project > 100) {
                    printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                    printf(HYEL"Enter Project score (0-100): "HAGGANGDITO);
                    scanf("%f", &s.project);
                }
                printf(GRN "Project saved: %.2f\n" HAGGANGDITO, s.project);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                getchar();
                system("cls");
                break;
                
            case 'Y':
            case 'y':
                continueAdding = 0;
                break;
                
            case '9':
            case 9: {
                char buffer[MAX_NAME];
                char sectionBuf[sizeof(s.section)];
                int newGrade;

                printf(BCYN"=== EDIT STUDENT INFORMATION ===\n\n"HAGGANGDITO);

                printf(HYEL"Name ("HAGGANGDITO"%s"HYEL"):"HAGGANGDITO" ", s.name);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if (strlen(buffer) > 0) {
                    strncpy(s.name, buffer, MAX_NAME);
                    s.name[MAX_NAME - 1] = '\0';
                }

                while (1) {
                    printf(HYEL"Grade ("HAGGANGDITO"%d"HYEL"): "HAGGANGDITO, s.grade);
                    if (scanf("%d", &newGrade) == 1 && newGrade >= 1 && newGrade <= 12) {
                        s.grade = newGrade;
                        break;
                    }
                    printf(RED"Please enter a grade between 1 and 12.\n"HAGGANGDITO);
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF) {}
                }
                getchar();

                printf(HYEL"Section ("HAGGANGDITO"%s"HYEL"): "HAGGANGDITO, s.section);
                fgets(sectionBuf, sizeof(sectionBuf), stdin);
                sectionBuf[strcspn(sectionBuf, "\n")] = 0;
                if (strlen(sectionBuf) > 0) {
                    strncpy(s.section, sectionBuf, sizeof(s.section));
                    s.section[sizeof(s.section) - 1] = '\0';
                }

                printf(GRN"\nInformation updated.\n"HAGGANGDITO);
                printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
                getchar();
                system("cls");
                break;
            }
                
            case 'N':
            case 'n':
                printf(YEL "Cancelled. Student not added.\n" HAGGANGDITO);
                printf(UWHT"Press Enter to continue..."HAGGANGDITO);
                getchar();
                system("cls");
                return;
                
            default:
                printf(RED "Invalid choice! Please try again.\n" HAGGANGDITO);
                break;
        }
    }
    
    calculateAverage(&s);
    int insertIndex = studentCount;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].id > s.id) {
            insertIndex = i;
            break;
        }
    }
    for (int i = studentCount; i > insertIndex; --i) {
        students[i] = students[i - 1];
    }
    students[insertIndex] = s;
    studentCount++;

    printf(GRN "Student added successfully! ID: %d\n" HAGGANGDITO, s.id);
    saveToFile();
    
    printf(BCYN"\n STUDENT: %s | Grade: %d | Section: %s\n\n"HAGGANGDITO, s.name, s.grade, s.section);
    
    // Print table header
        printf(RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-7s\n", 
           "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
    printf(RED"+--------+--------+--------+--------+--------+--------+--------+--------+---------\n"HAGGANGDITO);
    
    // Print scores
        printf(RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %7.2f\n",
           s.quiz1, s.quiz2, s.quiz3, s.activity1, s.activity2, s.activity3, s.examination, s.project, s.average);
    
    printf(BCYN"\nYou can Edit this again\n"HAGGANGDITO);
    printf(UWHT"\nPress Enter to continue: "HAGGANGDITO);
    getchar();
    system("cls");
}

//===========================================================================================================================

void showAllStudents() {
    if (studentCount == 0) {
        printf(RED"No students found.\n"HAGGANGDITO);
        return;
    }
    
    while (1) {
        printf(BHCYN"=== ALL STUDENTS RECORDS ===\n\n"HAGGANGDITO);
        printStudentTable();
        
        printf(YEL"\n[1]"HAGGANGDITO GRN" Search Student by ID\n"HAGGANGDITO);
        printf(YEL"[0]"HAGGANGDITO HRED" Back to Main Menu\n\n"HAGGANGDITO);
        printf(HYEL"Choose: "HAGGANGDITO);
        
        int choice;
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1) {
            int searchAgain = 1;
            while (searchAgain) {
                int id;
                printf(HYEL"\nEnter student ID (0 to exit) : "HAGGANGDITO);
                scanf("%d", &id);
                getchar();
                if (id == 0) {
                    break;
                }
                
                int found = 0;
                for (int i = 0; i < studentCount; i++) {
                    if (students[i].id == id) {
                        system("cls");
                        printf(BCYN"\n=== STUDENT DETAILS ===\n\n"HAGGANGDITO);
                        printf(CYN"ID: "HAGGANGDITO"%d\n", students[i].id);
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        if (students[i].grade > 0) printf(CYN"Grade: "HAGGANGDITO"%d\n", students[i].grade);
                        if (students[i].section[0] != '\0') printf(CYN"Section: "HAGGANGDITO"%s\n", students[i].section);
                        printf(CYN"Quiz 1: "HAGGANGDITO"%.2f\n", students[i].quiz1);
                        printf(CYN"Quiz 2: "HAGGANGDITO"%.2f\n", students[i].quiz2);
                        printf(CYN"Quiz 3: "HAGGANGDITO"%.2f\n", students[i].quiz3);
                        printf(CYN"Activity 1: "HAGGANGDITO"%.2f\n", students[i].activity1);
                        printf(CYN"Activity 2: "HAGGANGDITO"%.2f\n", students[i].activity2);
                        printf(CYN"Activity 3: "HAGGANGDITO"%.2f\n", students[i].activity3);
                        printf(CYN"Examination: "HAGGANGDITO"%.2f\n", students[i].examination);
                        printf(CYN"Project: "HAGGANGDITO"%.2f\n", students[i].project);
                        printf(CYN"Average: "HAGGANGDITO"%.2f\n", students[i].average);
                        printf(UWHT"\nPress Enter to continue...\n"HAGGANGDITO);
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
            printf(UWHT"Press Enter to continue..."HAGGANGDITO);
            getchar();
        }
    }
}

//===========================================================================================================================

void editStudent() {
    if (studentCount == 0) {
        printf(RED"No students to edit.\n"HAGGANGDITO);
        return;
    }
    printf(BCYN"=== REEDIT A STUDENT ===\n\n"HAGGANGDITO);
    printStudentTable();
    printf("\n");

    int id;
    printf(HYEL"Enter student ID to edit (0 to exit): "HAGGANGDITO);
    scanf("%d", &id);
    getchar();
    system("cls");
    if (id == 0) {
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            int editChoice;
            int continueEditing = 1;
            
         while (continueEditing) {
          
          float currentAvg = (students[i].quiz1 + students[i].quiz2 + students[i].quiz3 +
                     students[i].activity1 + students[i].activity2 + students[i].activity3 +
                     students[i].examination + students[i].project) / 8.0f;

          printf(UGRN"\nSTUDENT:"HAGGANGDITO " %s " RED"|"HAGGANGDITO " Grade: %d " RED"|"HAGGANGDITO " Section: %s\n\n",
              students[i].name, students[i].grade, students[i].section);

          printf(RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-6s "RED"|"HAGGANGDITO" %-7s\n",
              "Quiz1", "Quiz2", "Quiz3", "Act1", "Act2", "Act3", "Exam", "Proj", "Average");
          printf(RED"+--------+--------+--------+--------+--------+--------+--------+--------+---------\n"HAGGANGDITO);
          printf(RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %6.2f "RED"|"HAGGANGDITO" %7.2f\n",
              students[i].quiz1, students[i].quiz2, students[i].quiz3,
              students[i].activity1, students[i].activity2, students[i].activity3,
              students[i].examination, students[i].project, currentAvg);

          printf(BCYN"\nWhat do you want to edit?\n\n"HAGGANGDITO);
          printf(YEL"[1]"HAGGANGDITO" Quiz 1  "YEL"[4]"HAGGANGDITO" Activity 1  "YEL"[7]"HAGGANGDITO" Examination  "RED"|"HAGGANGDITO"   "YEL"[9]"HAGGANGDITO" Name\n");
          printf(YEL"[2]"HAGGANGDITO" Quiz 2  "YEL"[5]"HAGGANGDITO" Activity 2  "YEL"[8]"HAGGANGDITO" Project      "RED"|"HAGGANGDITO"   "YEL"[10]"HAGGANGDITO" Grade\n");
          printf(YEL"[3]"HAGGANGDITO" Quiz 3  "YEL"[6]"HAGGANGDITO" Activity 3                   "RED"|"HAGGANGDITO"   "YEL"[11]"HAGGANGDITO" Section\n\n");
        
          printf(YEL"[0]"HAGGANGDITO GRN" Finish and Save\n\n"HAGGANGDITO);
          printf(HYEL"Choose: "HAGGANGDITO);
                scanf("%d", &editChoice);
                system("cls");
                
                switch (editChoice) {
                    case 1:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Quiz 1: "HAGGANGDITO"%.2f\n", students[i].quiz1);
                        printf(HYEL"Enter new Quiz 1 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].quiz1);
                        while (students[i].quiz1 < 0 || students[i].quiz1 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Quiz 1 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].quiz1);
                        }
                        printf(GRN "Quiz 1 updated: %.2f\n" HAGGANGDITO, students[i].quiz1);
                        break;
                        
                    case 2:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Quiz 2: "HAGGANGDITO"%.2f\n", students[i].quiz2);
                        printf(HYEL"Enter new Quiz 2 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].quiz2);
                        while (students[i].quiz2 < 0 || students[i].quiz2 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Quiz 2 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].quiz2);
                        }
                        printf(GRN "Quiz 2 updated: %.2f\n" HAGGANGDITO, students[i].quiz2);
                        break;
                        
                    case 3:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Quiz 3: "HAGGANGDITO"%.2f\n", students[i].quiz3);
                        printf(HYEL"Enter new Quiz 3 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].quiz3);
                        while (students[i].quiz3 < 0 || students[i].quiz3 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Quiz 3 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].quiz3);
                        }
                        printf(GRN "Quiz 3 updated: %.2f\n" HAGGANGDITO, students[i].quiz3);
                        break;
                        
                    case 4:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Activity 1: "HAGGANGDITO"%.2f\n", students[i].activity1);
                        printf(HYEL"Enter new Activity 1 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].activity1);
                        while (students[i].activity1 < 0 || students[i].activity1 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Activity 1 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].activity1);
                        }
                        printf(GRN "Activity 1 updated: %.2f\n" HAGGANGDITO, students[i].activity1);
                        break;
                        
                    case 5:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Activity 2: "HAGGANGDITO"%.2f\n", students[i].activity2);
                        printf(HYEL"Enter new Activity 2 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].activity2);
                        while (students[i].activity2 < 0 || students[i].activity2 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Activity 2 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].activity2);
                        }
                        printf(GRN "Activity 2 updated: %.2f\n" HAGGANGDITO, students[i].activity2);
                        break;
                        
                    case 6:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Activity 3: "HAGGANGDITO"%.2f\n", students[i].activity3);
                        printf(HYEL"Enter new Activity 3 score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].activity3);
                        while (students[i].activity3 < 0 || students[i].activity3 > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Activity 3 score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].activity3);
                        }
                        printf(GRN "Activity 3 updated: %.2f\n" HAGGANGDITO, students[i].activity3);
                        break;
                        
                    case 7:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Examination: "HAGGANGDITO"%.2f\n", students[i].examination);
                        printf(HYEL"Enter new Examination score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].examination);
                        while (students[i].examination < 0 || students[i].examination > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Examination score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].examination);
                        }
                        printf(GRN "Examination updated: %.2f\n" HAGGANGDITO, students[i].examination);
                        break;
                        
                    case 8:
                        printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(CYN"Current Project: "HAGGANGDITO"%.2f\n", students[i].project);
                        printf(HYEL"Enter new Project score (0-100): "HAGGANGDITO);
                        scanf("%f", &students[i].project);
                        while (students[i].project < 0 || students[i].project > 100) {
                            printf(RED"Invalid score! Please enter a score between 0 and 100.\n"HAGGANGDITO);
                            printf(HYEL"Enter new Project score (0-100): "HAGGANGDITO);
                            scanf("%f", &students[i].project);
                        }
                        printf(GRN "Project updated: %.2f\n" HAGGANGDITO, students[i].project);
                        break;
                    case 9:
                        printf(CYN"Current Name: "HAGGANGDITO"%s\n", students[i].name);
                        printf(HYEL"Enter new name: "HAGGANGDITO);
                        getchar();
                        fgets(students[i].name, MAX_NAME, stdin);
                        students[i].name[strcspn(students[i].name, "\n")] = 0;
                        printf(GRN "Name updated to: %s\n" HAGGANGDITO, students[i].name);
                        break;
                    case 10:
                        do {
                            printf(CYN"Current Grade: "HAGGANGDITO"%d\n", students[i].grade);
                            printf(HYEL"Enter new grade level (1-12): "HAGGANGDITO);
                            if (scanf("%d", &students[i].grade) != 1) {
                                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                                students[i].grade = 0;
                            }
                            if (students[i].grade < 1 || students[i].grade > 12) {
                                printf(RED"Please enter a valid grade between 1 and 12.\n"HAGGANGDITO);
                            }
                        } while (students[i].grade < 1 || students[i].grade > 12);
                        printf(GRN "Grade updated to: %d\n" HAGGANGDITO, students[i].grade);
                        break;
                    case 11:
                        printf(CYN"Current Section: "HAGGANGDITO"%s\n", students[i].section);
                        printf(HYEL"Enter new section: "HAGGANGDITO);
                        getchar();
                        fgets(students[i].section, sizeof(students[i].section), stdin);
                        students[i].section[strcspn(students[i].section, "\n")] = 0;
                        printf(GRN "Section updated to: %s\n" HAGGANGDITO, students[i].section);
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
            printf(GRN "Student updated successfully!\n\n" HAGGANGDITO);
                printf(CYN"Name: "HAGGANGDITO"%s\n", students[i].name);
                printf(CYN"Quiz 1: "HAGGANGDITO"%.2f\n", students[i].quiz1);
                printf(CYN"Quiz 2: "HAGGANGDITO"%.2f\n", students[i].quiz2);
                printf(CYN"Quiz 3: "HAGGANGDITO"%.2f\n", students[i].quiz3);
                printf(CYN"Activity 1: "HAGGANGDITO"%.2f\n", students[i].activity1);
                printf(CYN"Activity 2: "HAGGANGDITO"%.2f\n", students[i].activity2);
                printf(CYN"Activity 3: "HAGGANGDITO"%.2f\n", students[i].activity3);
                printf(CYN"Examination: "HAGGANGDITO"%.2f\n", students[i].examination);
                printf(CYN"Project: "HAGGANGDITO"%.2f\n", students[i].project);
                printf(CYN"Average: "HAGGANGDITO"%.2f\n", students[i].average);
            printf(UWHT"\nPress Enter to continue..."HAGGANGDITO);
            getchar();
            system("cls");
            return;
        }
    }
    printf(RED"Student not found.\n"HAGGANGDITO);
}

//===========================================================================================================================

void deleteStudent() {
    if (studentCount == 0) {
        printf(RED"No students to delete.\n"HAGGANGDITO);
        return;
    }
    printf(BCYN"=== DELETE STUDENT ===\n\n"HAGGANGDITO);
    printStudentTable();
    printf("\n");
    
    int id;
    printf(HYEL"Enter student ID to delete: "HAGGANGDITO);
    scanf("%d", &id);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf(GRN"\nStudent deleted successfully.\n\n"HAGGANGDITO);
            saveToFile();
            return;
        }
    }
    system("cls");
    printf(RED"Student not found.\n\a"HAGGANGDITO);
    
}

//===========================================================================================================================

int main() {
    int choice;
    
    enableANSI();  // Enable ANSI color support once
    system("mode con: cols=160 lines=45"); // Set console size
    loadFromFile();
    
    while (1) {
        const char *banner =
        "\n"
BHRED"       .::    "HAGGANGDITO BHYEL"  .::::  "HAGGANGDITO BHGRN" .:::::::    "HAGGANGDITO BHCYN"       .:       "HAGGANGDITO BHBLU" .:::::    "HAGGANGDITO BHMAG" .::::::::"HAGGANGDITO BHWHT"   .:: ::  \n"HAGGANGDITO
BHRED"    .::   .:: "HAGGANGDITO BHYEL".:    .::"HAGGANGDITO BHGRN" .::    .::  "HAGGANGDITO BHCYN"      .: ::     "HAGGANGDITO BHBLU" .::   .:: "HAGGANGDITO BHMAG" .::      "HAGGANGDITO BHWHT" .::    .::\n"HAGGANGDITO
BHRED"   .::        "HAGGANGDITO BHYEL"::       "HAGGANGDITO BHGRN" .::    .::  "HAGGANGDITO BHCYN"     .:  .::    "HAGGANGDITO BHBLU" .::    .::"HAGGANGDITO BHMAG" .::      "HAGGANGDITO BHWHT"  .::      \n"HAGGANGDITO
BHRED"   .::        "HAGGANGDITO BHYEL"::       "HAGGANGDITO BHGRN" .: .::      "HAGGANGDITO BHCYN"    .::   .::   "HAGGANGDITO BHBLU" .::    .::"HAGGANGDITO BHMAG" .::::::  "HAGGANGDITO BHWHT"    .::    \n"HAGGANGDITO
BHRED"   .::        "HAGGANGDITO BHYEL"::   .:::"HAGGANGDITO BHGRN" .::  .::    "HAGGANGDITO BHCYN"   .:::::: .::  "HAGGANGDITO BHBLU" .::    .::"HAGGANGDITO BHMAG" .::      "HAGGANGDITO BHWHT"       .:: \n"HAGGANGDITO
BHRED"    .::   .:: "HAGGANGDITO BHYEL".::    .:"HAGGANGDITO BHGRN" .::    .::  "HAGGANGDITO BHCYN"  .::       .:: "HAGGANGDITO BHBLU" .::   .:: "HAGGANGDITO BHMAG" .::      "HAGGANGDITO BHWHT" .::    .::\n"HAGGANGDITO
BHRED"      .::::   "HAGGANGDITO BHYEL" .:::::  "HAGGANGDITO BHGRN" .::      .::"HAGGANGDITO BHCYN" .::         .::"HAGGANGDITO BHBLU" .:::::    "HAGGANGDITO BHMAG" .::::::::"HAGGANGDITO BHWHT"   .:: ::  \n"HAGGANGDITO
"\n"
BHRED"\t                         |--- BY BSEMC 1-B ---|                           "HAGGANGDITO;
                                                          
    puts(banner);
    printf(BCYN"\n WELCOME TO THE CGRADE SYSTEM BOOK!!\n\n"HAGGANGDITO);
        printf(YEL"  [1]"HAGGANGDITO" Add Student\n");
        printf(YEL"  [2]"HAGGANGDITO" Show All Students\n");
        printf(YEL"  [3]"HAGGANGDITO" Edit Student\n");
        printf(YEL"  [4]"HAGGANGDITO" Delete Student\n");
        printf(YEL"  [0]"HAGGANGDITO" Exit\n\n");
        
        printf(HYEL" Enter choice: "HAGGANGDITO);
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
                printf(GRN"\n Proposed by: EMC/1/B\n"HAGGANGDITO);
                printf(HRED" Leader:"HAGGANGDITO HWHT"  Charles Vincent Razon\n"HAGGANGDITO);
                printf(HBLU" Members:"HAGGANGDITO HWHT" John Jerick Borlio\n"HAGGANGDITO);
                printf(HWHT"          Gabriel Yam-id Abria\n"HAGGANGDITO);
                printf(HWHT"          Takumi Yoshiga\n"HAGGANGDITO);
                printf(HWHT"          Mark Denver Gerona Abenes\n"HAGGANGDITO);
                printf(GRN"\n Di pa approved by (T-T):\n"HAGGANGDITO);
                printf(HWHT" Genalyn D. Villafuerte\n"HAGGANGDITO);
                printf(HWHT" EMC Faculty\n\n"HAGGANGDITO);
                printf(BHMAG"THANK YOU FOR USING CGRADES. Goodbye!\n"HAGGANGDITO);
                printf(HBLK"\nPress Enter to exit...");
                getchar();
                return 0;
            default:
                printf(RED" NOTIFICATION:" " Invalid choice! \n\a");
        }
      
    }
    
    return 0;
}
