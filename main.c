#include <stdio.h>
#include <string.h>
#include <time.h>

struct tasks
{
    int id,categ,dd,mm,yy,stat;
    char stat1[50];
    char taskname[50];
}task;

//    FUNCTION VIEW FILE RECORDS
void viewtask(){
    int count = 0;
    printf("\n==================================Task list=====================================");
    printf("\nNo\tID\tCategory\tDeadline\tStatus\t\tTask");
    printf("\n--------------------------------------------------------------------------------\n");
    FILE * ptr = fopen("taskfile.txt", "r");
    while(fscanf(ptr,"%d",&task.id) != EOF){
        fscanf(ptr,"%d",&task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1){
            strcpy(task.stat1 , "Complete");
        }else if (task.stat == 0){
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname,50,ptr);
        printf("%d)\t%d\t%d\t\t%d/%d/%d\t%s\t%s",++count, task.id, task.categ,task.dd,task.mm,task.yy,task.stat1,task.taskname);
    }
    printf("\n");
    fclose(ptr);
}

//    FUNCTION INSERT RECORDS TO THE FILE
void addtask()
{
    FILE *ptr = fopen("taskfile.txt", "a");
    fseek(ptr, 0, SEEK_END);
    //ID
    printf("\nEnter the task ID\n> ");
    scanf("%d", &task.id);
    //category
    do {
        printf("Enter the category\n");
        printf("1. Important\n");
        printf("2. Urgent\n");
        printf("3. Both\n");
        printf("4. Not important & not urgent\n> ");
        scanf("%d", &task.categ);
        if (task.categ <1 || task.categ>4){
            printf("Please choose between 1 and 4!\n");
        }
    }while(task.categ <1 || task.categ>4);
    //deadline

    do{
        printf("Enter task's deadline(day)\n> ");
        scanf("%d", &task.dd);
        if (task.dd <0 || task.dd >31){
            printf("Invalid day input!\n");
        }
    }while (task.dd <0 || task.dd >31);
    do{
        printf("Enter task's deadline(month)\n> ");
        scanf("%d", &task.mm);
        if (task.mm <0 || task.dd >12) {
            printf("Invalid month input!\n");
        }
    }while(task.mm < 0 || task.mm >12);
    do {
        printf("Enter task's deadline(year)\n> ");
        scanf("%d", &task.yy);
        if (task.yy <2022 || task.yy >2050) {
            printf("Invalid year input!\n");
        }
    }while(task.yy <2022|| task.yy >2050);
    //status
    do {
        printf("Enter status\n");
        printf("Complete (1) or Incomplete (0)\n>");
        scanf("%d", &task.stat);
        if (task.stat < 0 || task.stat > 1) {
            printf("Invalid status input!\n");
        }
    }while(task.stat < 0  || task.stat > 1);
    //task name
    printf("Enter task\n> ");
    getchar();
    fgets(task.taskname, 50, stdin);
    printf("ID:%d, category:%d, day:%d, month:%d, year:%d, status:%d, task:%s",task.id,task.categ,task.dd,task.mm,task.yy,task.stat,task.taskname);
    fprintf(ptr,"%d %d %d %d %d %d %s",task.id,task.categ,task.dd,task.mm,task.yy,task.stat,task.taskname);
    fclose(ptr);
}

//    FUNCTION DELETE FILE RECORDS
void deletetask(){
    int i;
    FILE *ptr = fopen("taskfile.txt" ,"r");
    FILE *pptr = fopen("tempfile.txt", "w");

    printf("========Delete task=======\n");
    printf("Enter the ID to delete\n> ");
    scanf("%d", &i);
    while(fscanf(ptr,"%d",&task.id) != EOF) { //Ori file
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr,"%d", &task.stat);
        if (task.stat == 1){
            strcpy(task.stat1 , "Complete");
        }else if (task.stat == 0){
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (i == task.id) {
            printf("Record deleted\n");
            printf("ID:%d\tTask:%s\nStatus:%s\n", i, task.taskname,task.stat1);
            continue;
        }
        fprintf(pptr,"%d %d %d %d %d %d %s",task.id,task.categ,task.dd,task.mm,task.yy,task.stat,task.taskname);
        fflush(stdin);
    }
    fclose(pptr);
    fclose(ptr);
    remove("taskfile.txt");
    rename("tempfile.txt", "taskfile.txt");
}

//    FUNCTION UPDATE TASK RECORDS
int updatetask() {
    int i, choice = 0;
    char trash[100];
    char input[] = "";

    FILE *ptr = fopen("taskfile.txt", "r");
    FILE *pptr = fopen("tempfile.txt", "w");

    printf("========Update file=======\n");
    printf("Enter the ID to update\n> ");
    scanf("%d", &i);
    fflush(stdin);
    while (fscanf(ptr, "%d", &task.id) != EOF) { //Ori file
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr,"%d", &task.stat);
        if (task.stat == 1){
            strcpy(task.stat1 , "Complete");
        }else if (task.stat == 0){
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (i == task.id) {
            printf("Record selected\n");
            printf("ID:%d\tTask:%s\tStatus:%s\n", i, task.taskname,task.stat1);
            printf("Pick an option to update\n");
            printf("    1.Category            \n");
            printf("    2.Day of deadline     \n");
            printf("    3.Month of deadline   \n");
            printf("    4.Year of deadline    \n");
            printf("    5.Task                \n");
            printf("    6.Status              \n");
            printf("    7.Exit                \n> ");

            fgets(input, 5, stdin);
            input[strcspn(input, "\n")] = 0;
            sscanf(input, "%i%s", &choice, trash);

            if (strlen(trash) == 0) {
                switch (choice) {
                    case 1:
                        do {
                            printf("Enter the category\n");
                            printf("1. Important\n");
                            printf("2. Urgent\n");
                            printf("3. Both\n");
                            printf("4. Not important & not urgent\n> ");
                            scanf("%d", &task.categ);
                            if (task.categ <1 || task.categ>4){
                                printf("Please choose between 1 and 4!");
                            }
                        }while(task.categ <1 || task.categ>4);
                        break;
                    case 2:
                        do{
                            printf("Enter task's deadline(day)\n> ");
                            scanf("%d", &task.dd);
                            if (task.dd <0 || task.dd >31){
                                printf("Invalid day input\n");
                            }
                        }while (task.dd <0 || task.dd >31);
                        break;
                    case 3:
                        do{
                            printf("Enter task's deadline(month)\n> ");
                            scanf("%d", &task.mm);
                            if (task.mm <0 || task.dd >12) {
                                printf("Invalid month input\n");
                            }
                        }while(task.mm < 0 || task.mm >12);
                        break;
                    case 4:
                        do {
                            printf("Enter task's deadline(year)\n> ");
                            scanf("%d", &task.yy);
                            if (task.yy <2022 || task.yy >2050) {
                                printf("Invalid year input\n");
                            }
                        }while(task.yy <2022|| task.yy >2050);
                        break;
                    case 5:
                        printf("Enter new task\n> ");
                        scanf("%s[^\n]", task.taskname);
                        break;
                    case 6:
                        do {
                            printf("Enter status\n");
                            printf("Complete (1) or Incomplete (0)\n>");
                            scanf("%d", &task.stat);
                            if (task.stat < 0 || task.stat > 1) {
                                printf("Invalid status input");
                            }
                        }while(task.stat < 0  || task.stat > 1);
                        break;
                    case 7:
                        break;
                    default:
                        printf("Invalid input.\n");
                        break;
                }
            } else {
                printf('Invalid input.\n');
                break;
            }
        }
        fprintf(pptr, "%d %d %d %d %d %d %s", task.id, task.categ, task.dd, task.mm, task.yy, task.stat, task.taskname);
        fflush(stdin);
    }
    fclose(pptr);
    fclose(ptr);
    remove("taskfile.txt");
    rename("tempfile.txt", "taskfile.txt");
}

//    FUNCTION TO SEARCH TASK
void searchtask() {
    int i;
    FILE *ptr = fopen("taskfile.txt", " r");

    printf("========Search task=======");
    printf("\nEnter the ID to search\n> ");
    scanf("%d", &i);
    while (fscanf(ptr, "%d", &task.id) != EOF) {
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1){
            strcpy(task.stat1 , "Complete");
        }else if (task.stat == 0){
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (i == task.id) {
            printf("Task record found!\n");
            printf("id: %d \t category: %d\t Deadline:%d/%d/%d \tState:%s \tTask:%s", task.id, task.categ, task.dd, task.mm, task.yy, task.stat1, task.taskname);
            fflush(stdin);
        }
    }
    fclose(ptr);
    fflush(stdin);
}

//    FUNCTION SORT COMPLETE TASK RECORDS
void sortdone() {
    int count = 0;
    printf("\n==================================Task list=====================================");
    printf("\nNo\tID\tCategory\tDeadline\tStatus\t\tTask");
    printf("\n--------------------------------------------------------------------------------\n");
    FILE *ptr = fopen("taskfile.txt", "r");
    while (fscanf(ptr, "%d", &task.id) != EOF) {
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1) {
            strcpy(task.stat1, "Complete");
        } else if (task.stat == 0) {
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (task.stat == 1){
            printf("%d)\t%d\t%d\t\t%d/%d/%d\t%s\t%s", ++count, task.id, task.categ, task.dd, task.mm, task.yy,task.stat1, task.taskname);
        }
    }
    fclose(ptr);

    FILE *ptr2 = fopen("taskfile.txt", "r");
    while (fscanf(ptr, "%d", &task.id) != EOF) {
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1) {
            strcpy(task.stat1, "Complete");
        } else if (task.stat == 0) {
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (task.stat == 0) {
            printf("%d)\t%d\t%d\t\t%d/%d/%d\t%s\t%s", ++count, task.id, task.categ, task.dd, task.mm, task.yy,task.stat1, task.taskname);
        }
    }
    printf("\n");
    fclose(ptr2);
}

//     FUNCTION SORT INCOMPLETE TASK RECORDS
void sortxdone(){
    int count = 0;
    printf("\n==================================Task list=====================================");
    printf("\nNo\tID\tCategory\tDeadline\tStatus\t\tTask");
    printf("\n--------------------------------------------------------------------------------\n");
    FILE *ptr = fopen("taskfile.txt", "r");
    while (fscanf(ptr, "%d", &task.id) != EOF) {
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1) {
            strcpy(task.stat1, "Complete");
        } else if (task.stat == 0) {
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (task.stat == 0){
            printf("%d)\t%d\t%d\t\t%d/%d/%d\t%s\t%s", ++count, task.id, task.categ, task.dd, task.mm, task.yy,task.stat1, task.taskname);
        }
    }
    fclose(ptr);

    FILE *ptr2 = fopen("taskfile.txt", "r");
    while (fscanf(ptr, "%d", &task.id) != EOF) {
        fscanf(ptr, "%d", &task.categ);
        fscanf(ptr, "%d", &task.dd);
        fscanf(ptr, "%d", &task.mm);
        fscanf(ptr, "%d", &task.yy);
        fscanf(ptr, "%d", &task.stat);
        if (task.stat == 1) {
            strcpy(task.stat1, "Complete");
        } else if (task.stat == 0) {
            strcpy(task.stat1, "Incomplete");
        }
        fgets(task.taskname, 50, ptr);
        if (task.stat == 1) {
            printf("%d)\t%d\t%d\t\t%d/%d/%d\t%s\t%s", ++count, task.id, task.categ, task.dd, task.mm, task.yy,task.stat1, task.taskname);
        }
    }
    printf("\n");
    fclose(ptr2);
}

//    FUNCTION SHOW CURRENT TIME
void showtime(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Current date and time: %d-%02d-%02d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int menu(){
    int choice;
    char trash[100];
    char input[]="";
    do
    {
        printf("=============================================\n");
        printf("=            Task Management System         =\n");
        printf("=============================================\n");
        printf("=           1. View Tasks                   =\n");
        printf("=           2. Add Task                     =\n");
        printf("=           3. Delete Task                  =\n");
        printf("=           4. Update Task                  =\n");
        printf("=           5. Search Task                  =\n");
        printf("=           6. Sort Completed task          =\n");
        printf("=           7. Sort Incomplete task         =\n");
        printf("=           8. Show current date &time      =\n");
        printf("=           9. Exit                         =\n");
        printf("=============================================\n");
        printf("Please enter your choice > ");

        fgets(input, 5, stdin); //get first 5 char input and ignore the rest
        input[strcspn(input, "\n")]= 0; //remove input's \n
        sscanf(input,"%i%s", &choice, trash); //filter user input

        if(strlen(trash) == 0){
            switch (choice) {

                case 1:
                    viewtask();
                    break;
                case 2:
                    addtask();
                    break;
                case 3:
                    deletetask();
                    break;
                case 4:
                    updatetask();
                    break;
                case 5:
                    searchtask();
                    break;
                case 6:
                    sortdone();
                    break;
                case 7:
                    sortxdone();
                    break;
                case 8:
                    showtime();
                    break;
                case 9:
                    printf("Have a nice day! Bye.\n");
                    break;
                default:
                    printf("\nYour choice is wrong\nPlease try again...\n");
                    break;
            }
        }else{
            printf("Invalid input.\n");
            fflush(stdin);
        }
    } while (choice != 9);
    return 0;
}

int main(){
    menu();
    return 0;
}