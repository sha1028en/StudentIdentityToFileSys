
#include <stdio.h>
#include <stdlib.h>
#include "student_identity_dll.h"



enum ActionList { END, READ_FILE, SHOW, EDIT, WRITE_FILE };
enum EditStudentActionList { EXIT, PREV, NEXT, INSERT, MODIFY, DELETE, SEARCH };

void getStringByAddress(char* informationString, char* inputAddr);


void editStudent();
void showStudentByIndex(Student* current);




int main() {

    int isLoop = 0;
    int action = 0;
    initStudentHead();      // student HeadNode init_...

    while(!isLoop && studentHead != NULL){


        system("cls");
        puts("===============================");
        puts("=     ���� ���� ���α׷�      =");
        puts("===============================\n");

        puts("1. ���� ���α׷� ���� ��������");
        puts("2. ���� ���α׷� ��Ȳ ����");
        puts("3. ���� ���α׷� ����");
        puts("4. ���� ���α׷� ���� ����");
        puts("0. ���� ���α׷� ����");
        printf("-> ");
        scanf("%d", &action);
        getchar();      // remove "Enter"


        switch(action){
            case READ_FILE:     puts("1. ���� ���α׷� ���� ��������");
                                readStudentByFile(); break;

            case SHOW:          puts("2. ���� ���α׷� ��Ȳ ����");
                                showAllStudent(); break;


            case EDIT:          puts("3. ���� ���α׷� ����");
                                editStudent(); break;

            case WRITE_FILE:    puts("4. ���� ���α׷� ���� ����");
                                writeStudentByFile(); break;

            case END:           isLoop = 1;
                                break;

            default: puts("�߸��� ���� �Է� �ϼ̾��!");
        }
    }

    return 0;
}




/*********** CASE EDIT: ****************/
void editStudent(){

    studentCurrent = studentHead->nextNode;
    char bufString[INIT_STUDENT_NAME_REAR] = "";

    int action = 0;
    int isLoop = 0;

    while(!isLoop){

        system("cls");
        puts("===============================");
        puts("=     ���� ���� ���α׷�      =");
        puts("===============================\n");


        if( studentCurrent != NULL ){

            showStudentByIndex(studentCurrent);

        }

        puts("1. ���� ����");
        puts("2. ���� ����");
        puts("3. ���� ���");
        puts("4. ���� ����");
        puts("5. ���� ����");
        puts("6. ���� �˻�");
        puts("0. ���ư���");
        printf("-> ");
        scanf("%d", &action);
        getchar();      // remove "Enter"


        // DIDNT HAVE CHILD.
        if(studentCurrent == NULL) {

            switch(action){
                case PREV:
                case NEXT:
                case MODIFY:
                case DELETE:
                case SEARCH:    continue;;

                case INSERT:    appendNewStudent();
                                break;
                case EXIT:      break;

                default: ;
            }
        }


        switch(action){
            case PREV:          if( studentCurrent->prevNode != NULL ){
                                    studentCurrent = studentCurrent->prevNode;
                                } break;

            case NEXT:          if( studentCurrent->nextNode != NULL){
                                    studentCurrent = studentCurrent->nextNode;
                                } break;

            case INSERT:        appendNewStudent();
                                break;

            case MODIFY:        studentCurrent = updateStudent(studentCurrent);
                                break;

            case DELETE:        deleteStudentByCurrent();
                                break;


            case SEARCH:        getStringByAddress("Enter name... ", bufString);
                                selectStudent(bufString);
                                break;

            case EXIT:          isLoop = 1;
                                break;

            default: puts("�߸��� ���� �Է� �ϼ̾��!");
        }
    }
}
