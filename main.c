#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define n 50
//preprocessor statements

int count = 0;
FILE * file;
char * filename;

typedef struct{ //structre for listing tasks
    char task[100];
    bool done;
}TASK;
TASK list[n];

void menu();
void task_add();
void task_display();
void marfile(int);
void task_mark();
void delfile();
void task_delete();
//function declarations

int main(int argc , char *argv[]){
    int m_work;
    if(argv[1] == NULL){
        filename = "tasklist.txt";
    }else{
        filename = argv[1];
    }
    do{
        menu();
        printf("your choice: ");
        scanf("%d",&m_work);
        switch (m_work) {
            case 1:
                task_add();
                break;
            case 2:
                task_display();
                break;
            case 3:
                task_mark();
                break;
            case 4:
                task_delete();
                break;
            case 5:
                puts("exited.\n");
                break;
            default:
                puts("Invalid choice. Please try again.\n");
                break;
        }
    }while(m_work != 5);
    return 0;
}

void menu(){
    // for displaying available commands
    puts("-----------MENU-----------");
    puts("1 . add task");
    puts("2 . display task");
    puts("3 . mark completed task");
    puts("4 . delete task");
    puts("5 . exit");
    puts("--------------------------\n");
}

void task_add(){
    //for m_work = 1
    if(count < n){
        file = fopen(filename,"a");
        if(file == NULL){
            perror("error opening the file");
            exit(1);
        }
        printf("enter task: ");
        scanf(" %[^\n]",list[count].task);
        list[count].done = false;
        count++;
        fprintf(file,"%d. %s\n",count,list[count-1].task);
        fclose(file);
        puts("task added");
    }else{
        puts("no tasks can be added");
    }
}

void task_display(){
    //for m_work = 2
    puts("--------------------------\n");
    if(count > 0){
        puts("current tasks are:");
        int sn = 1;
        for(int i = 0 ; i < count ; i++){
            printf("%d. [%c] %s\n",sn,(list[i].done)?'/':' ',list[i].task);
            sn++;
        }
    }else{
        puts("no tasks added\n");
    }
    puts("--------------------------\n");
}

void marfile(int t){
    // marking completion in file funtion
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        perror("error opening the file");
        exit(1);
    }
    char t_filename[] = "t_tasklist.txt";
    FILE *t_file = fopen(t_filename,"w");
    int sn = 1;
    for(int i = 1;i<=count;i++){
        if(list[i-1].done == true){
            fprintf(t_file,"%d. %s [completed]\n",sn,list[i-1].task);
        }else{
            fprintf(t_file,"%d. %s\n",sn,list[i-1].task);
        }
            sn++;
    }
    fclose(file);
    fclose(t_file);
    remove(filename);
    rename(t_filename,filename);
}

void task_mark(){
    //for m_work = 3
    task_display();
    if(count > 0){
        int t;
        printf("enter task number to mark as completed: ");
        scanf("%d",&t);
        if(t >= 1 && t <= count){
            list[t-1].done = true;
            marfile(t);
            puts("task marked as completed");
        }else{
            puts("task number invalid");
        }
    }
}

void delfile(){
    // deletion in file funtion
    file = fopen(filename,"r");
    if(file == NULL){
        perror("error opening the file");
        exit(1);
    }
    char t_filename[] = "t_tasklist.txt";
    FILE *t_file = fopen(t_filename,"w");
    int sn = 1;
    for(int i = 1;i<=count;i++){
        if(list[i-1].done == true){
            fprintf(t_file,"%d. %s [completed]\n",sn,list[i-1].task);
        }else{
            fprintf(t_file,"%d. %s\n",sn,list[i-1].task);
        }
            sn++;
    }
    fclose(file);
    fclose(t_file);
    remove(filename);
    rename(t_filename,filename);
}

void task_delete(){
    // for m_work = 4
    task_display();
    if(count > 0){
        int t,pos;
        printf("enter task number to delete: ");
        scanf("%d",&t);
        if(t >= 1 && t <= count){
            for(int i = t-1 ; i < count - 1 ; i++){
                list[i] = list[i+1];
            }
            puts("task deleted");
            count--;
            delfile();
        }else{
            puts("task number invalid");
        }
    }
}

/* this application is proudly presented to you by A.YuvaKarthik */