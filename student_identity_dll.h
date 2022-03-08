#include <stdio.h>
#include <stdlib.h>
#include <String.h>

#define INIT_STUDENT_NAME_REAR    20
#define INIT_STUDENT_GENDER_REAR  5


typedef struct StudentIdentity {

    char    personName[INIT_STUDENT_NAME_REAR];
    int     personId;
    char    personGender[INIT_STUDENT_GENDER_REAR];

    int     pointJava;
    int     pointAndroid;
    int     pointKotlin;
    int     pointReactNeative;
    int     pointJSP;
    int     pointTotal;
    double  pointAvg;
    char    pointGrade;

    struct  StudentIdentity *prevNode;
    struct  StudentIdentity *nextNode;

} Student;

void waitEnter();
void inputStudentIdentityByAddress(Student* node);
void showStudentByIndex(Student* current);
int isEqualsStudentId(int toEqualsId);
void clearBuffer();
char getGrade(double inputValue);


Student* studentHead    = NULL;
Student* studentCurrent = NULL;

/********* studentHead __INIT__ ********/

void initStudentHead(){

    studentHead = (Student* ) calloc(1, sizeof(Student ));

    if ( studentHead == NULL){
        puts("CANT allocate Student");
        waitEnter();
    }
}

/********** Rear Append **********/

void appendNodeRear(Student* node){

    Student* p = studentHead;



    while(p->nextNode != NULL){
        p = p->nextNode;            // find to last node
    }

    p->nextNode = node;             // append node

    // point to append node
    if(p != studentHead){
        node->prevNode = p;         // link to prevNode
    }

    return;
}

/****** Add Child by studentCurrent's Pos ******/

void appendNodeByCurrent(Student* node){

    Student* head = studentHead;
    Student* current = studentCurrent;


    // blank
    if( head->nextNode == NULL){
        appendNodeRear(node);
        return;
    }

    // front
    if( current->prevNode == NULL ){

        node->nextNode = head->nextNode;
        node->nextNode->prevNode = node;        // (node.next가 참조하는 곳의 prevNode)
        head->nextNode = node;


    // rear
    } else if( current->nextNode == NULL){

        node->prevNode = current;
        current->nextNode = node;
        // node->nextNode = NULL;      use malloc(), need this.

    // between
    } else if (current->nextNode != NULL && current->prevNode != NULL ) {

        node->nextNode = current->nextNode;
        node->nextNode->prevNode = node;

        current->nextNode = node;
        node->prevNode = current;

    // failed!
    } else {

        puts("__ERROR OCCUR__");
    }


    return;
}

/************* Read File to load Student **************/

void readStudentByFile(){

    Student* student = NULL;
    FILE* inStream = NULL;

    int readFileResult = 0;
    int readFileCount = 0;
    int isLoop = 0;
    char studentFileName[30] = "";


    printf("읽을 파일 이름을 입력하세요 >> ");
    scanf("%s", studentFileName);

    inStream = fopen(studentFileName, "r");

    if( inStream == NULL ){
        puts("__CANT READ FILE__");
        printf("%s\n", studentFileName );
        isLoop = 1;
    }

    while(!isLoop){

        student = (Student* ) calloc(1, sizeof(Student));
        readFileResult  = fscanf(inStream, "%s %d %s %d %d %d %d %d %d %lf %c",
                 student->personName, &student->personId, student->personGender,
                 &student->pointJava, &student->pointAndroid, &student->pointKotlin, &student->pointReactNeative, &student->pointJSP,
                 &student->pointTotal, &student->pointAvg, &student->pointGrade);

        if(readFileResult == EOF){

            free(student);
            break;
        }
        appendNodeRear(student);
        readFileCount++;



        printf("%s %d %s %d %d %d %d %d %d %lf %c\n",
                 student->personName, student->personId, student->personGender,
                 student->pointJava, student->pointAndroid, student->pointKotlin, student->pointReactNeative, student->pointJSP,
                 student->pointTotal, student->pointAvg, student->pointGrade);
    }
    fclose(inStream);
}

/************ Write File for save Student **************/

void writeStudentByFile(){

    Student* p = studentHead;
    FILE* oStream = NULL;

    int writeFileResult = 0;
    char studentFileName[30] = "";


    printf("저장할 파일 이름을 입력하세요 >> ");
    scanf("%s", studentFileName);

    oStream = fopen(studentFileName, "w+");

    if( oStream == NULL ){
        puts("__CANT WRITE FILE__");
        printf("%s\n", studentFileName);
        return;
    }

    while( p->nextNode != NULL ){
        p = p->nextNode;

        writeFileResult = fprintf(oStream, "%s %d %s %d %d %d %d %d %d %lf %c\n",
                 p->personName, p->personId, p->personGender,
                 p->pointJava, p->pointAndroid, p->pointKotlin, p->pointReactNeative, p->pointJSP,
                 p->pointTotal, p->pointAvg, p->pointGrade);

        if(writeFileResult == EOF) {
            printf("\"%s\" ERROR OCCUR!\n", studentFileName);
            break;
        }
    }
    fclose(oStream);

    return;
}


/******** SELECT * FROM StudentIdentity WHERE personName == toSelectName *********/

Student* selectStudent(char* toSelectName){

    Student* p = studentHead;


    while( p->nextNode != NULL){

        p = p->nextNode;
        if(stricmp(toSelectName, p->personName) == 0) {
            system("cls");
            showStudentByIndex(p);
            waitEnter();
            return p;
        }
    }

    puts("검색 대상이 없어요!");
    waitEnter();
    return NULL;
}


/********** UPDATE Child *************/

Student* updateStudent(Student* node){

    if(node == NULL){
        puts("CANT FIND TO GO");
        getchar();
        return NULL;
    }


    inputStudentIdentityByAddress(node);
    showStudentByIndex(node);
    waitEnter();


    return node;
}


/*********** Not DROP, just DELETE ************/

Student* deleteStudent(Student* node){

    if(node == NULL){
        puts("CANT FIND TO GO");
        getchar();
        return NULL;
    }

    strncpy(node->personName, "", strlen(node->personName));
    node->personId = 0;
    strncpy(node->personGender, "", strlen(node->personGender));


    node->pointJava         = 0;
    node->pointAndroid      = 0;
    node->pointKotlin       = 0;
    node->pointReactNeative = 0;
    node->pointJSP          = 0;
    node->pointTotal        = 0;
    node->pointAvg          = 0.0;
    node->pointGrade        = 0;

    return node;
}


/***** DROP by studentCurrent's Pos *****/
void deleteStudentByCurrent(){

    Student* current = studentCurrent;
    Student* head = studentHead;


    // get Pos.
    if(studentCurrent->nextNode != NULL){

        studentCurrent = studentCurrent->nextNode;

    } else if(studentCurrent->nextNode == NULL && studentCurrent->prevNode != NULL ){

        studentCurrent = studentCurrent->prevNode;

    } else {
        studentCurrent = NULL;

    }

    // front
    if( current->nextNode != NULL && current->prevNode == NULL ){

        current->nextNode->prevNode = NULL;
        head->nextNode = current->nextNode;

    // between
    } else if ( current->nextNode != NULL && current->prevNode != NULL ){

        current->nextNode->prevNode = current->prevNode;
        current->prevNode->nextNode = current->nextNode;

    // rear
    } else if ( current->nextNode == NULL && current->prevNode != NULL ){

        current->prevNode->nextNode = NULL;

    } else {

        studentHead->nextNode = NULL;

    }
    return;
}


/************ Add new Child *************/

Student* appendNewStudent(){

    Student* node = (Student* ) calloc(1, sizeof(Student ));

    if (node == NULL){

        puts("__CANT ALLOWCATE__");
        getchar();
        return NULL;
    }

    inputStudentIdentityByAddress(node);
    appendNodeByCurrent(node);
    showStudentByIndex(node);
    waitEnter();

    return node;
}


/************ Internal Func. *************/

void inputStudentIdentityByAddress(Student* node){
    int isTie = 1;


    if(node == NULL){
        return;
    }

    puts("Enter Name");
    scanf("%s", node->personName);
    clearBuffer();
    puts("Enter Gender");
    scanf("%s", node->personGender);
    clearBuffer();


    while(isTie){
        printf(" isTie : %d\n", isTie);
        puts("Enter Id");
        scanf("%d", &node->personId);
        clearBuffer();
        isTie = isEqualsStudentId(node->personId);
    }


    puts("Enter Java point");
    scanf("%d", &node->pointJava);
    puts("Enter Android point");
    scanf("%d", &node->pointAndroid);
    puts("Enter Kotlin point");
    scanf("%d", &node->pointKotlin);
    puts("Enter React point");
    scanf("%d", &node->pointReactNeative);
    puts("Enter JSP point");
    scanf("%d", &node->pointJSP);


    node->pointTotal =  node->pointJava +
                        node->pointAndroid +
                        node->pointKotlin +
                        node->pointReactNeative +
                        node->pointJSP;

    node->pointAvg = node->pointTotal / 5.0;
    node->pointGrade = getGrade(node->pointAvg);

    return;
}


int isEqualsStudentId(int toEqualsId){

    Student* p = studentHead;
    int resultValue = 0;


    while(p->nextNode != NULL){
        p = p->nextNode;
        printf("\n%d : %d", p->personId, resultValue);

        // is Tie???? Y = 1 N = 0
        if(p->personId == toEqualsId) {

            resultValue = 1;
            break;
        }
    }


    return resultValue;
}


void waitEnter(){
    printf(" ");
    getchar();
    getchar();
}


/********* Print to Node's member ***********/

void showStudentByIndex(Student* current){

    if (current != NULL){

        puts("===============================");
        printf("%13s [%s]\n", "이름", current->personName);
        printf("%13s [%d]\n", "학번", current->personId);
        printf("%13s [%s]\n", "성별", current->personGender);
        printf("%13s [%d]\n", "자바", current->pointJava);
        printf("%13s [%d]\n", "안드로이드", current->pointAndroid);
        printf("%13s [%d]\n", "코틀린", current->pointKotlin);
        printf("%13s [%d]\n", "리액트", current->pointReactNeative);
        printf("%13s [%d]\n", "자바스크립트", current->pointJSP);
        printf("%13s [%d]\n", "총점", current->pointTotal);
        printf("%13s [%.2lf]\n", "평균", current->pointAvg);
        printf("%13s [%c]\n", "등급", current->pointGrade);
        puts("===============================");
    }
    return;
}


/********* Print ALL Students member ***********/

void showAllStudent(){

    Student* p = studentHead;

    puts("========================================================================================");
    puts("이름\t학번\t성별\t\t\t\t\t\t총점\t평균\t등급");
    puts("========================================================================================");

    while( p->nextNode != NULL) {

        p = p->nextNode;
        printf("%s\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%.2lf\t%c\n",
            p->personName, p->personId, p->personGender,
            p->pointJava, p->pointAndroid, p->pointKotlin, p->pointReactNeative, p->pointJSP,
            p->pointTotal, p->pointAvg, p->pointGrade);

    }
    getchar();
    getchar();
    return;
}


void clearBuffer(){

    while( getchar() != '\n' );
}
