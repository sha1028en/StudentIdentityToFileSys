
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
        puts("=     성적 관리 프로그램      =");
        puts("===============================\n");

        puts("1. 성적 프로그램 파일 가져오기");
        puts("2. 성적 프로그램 현황 보기");
        puts("3. 성적 프로그램 관리");
        puts("4. 성적 프로그램 파일 저장");
        puts("0. 성적 프로그램 종료");
        printf("-> ");
        scanf("%d", &action);
        getchar();      // remove "Enter"


        switch(action){
            case READ_FILE:     puts("1. 성적 프로그램 파일 가져오기");
                                readStudentByFile(); break;

            case SHOW:          puts("2. 성적 프로그램 현황 보기");
                                showAllStudent(); break;


            case EDIT:          puts("3. 성적 프로그램 관리");
                                editStudent(); break;

            case WRITE_FILE:    puts("4. 성적 프로그램 파일 저장");
                                writeStudentByFile(); break;

            case END:           isLoop = 1;
                                break;

            default: puts("잘못됀 값을 입력 하셨어요!");
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
        puts("=     성적 관리 프로그램      =");
        puts("===============================\n");


        if( studentCurrent != NULL ){

            showStudentByIndex(studentCurrent);

        }

        puts("1. 이전 성적");
        puts("2. 다음 성적");
        puts("3. 성적 등록");
        puts("4. 성적 수정");
        puts("5. 성적 삭제");
        puts("6. 성적 검사");
        puts("0. 돌아가기");
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

            default: puts("잘못됀 값을 입력 하셨어요!");
        }
    }
}
