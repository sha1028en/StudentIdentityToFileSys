# 개선됀 StudentIdentity

### 기존의 있던 StudentIdentity 에서 파일IO를 추가하여 학생을 관리한다.
### 기능으로는 저장 / 불러오기 / 학생 추가 / 수정 / 삭제 / 검색 이 있다.
### 파일 IO를 통해 프로그램을 종료 했더라도, 다시 이어서 관리 할 수 있다.


## 상수
```
    INIT_STUDENT_NAME_REAR    21
    INIT_STUDENT_GENDER_REAR  5

```
## INIT_STUDENT_NAME_REAR
#### 학생 이름의 길이이다.  null을 위해 20자리만 사용한다.

## INIT_STUDENT_GENDER_REAR  5
#### 학생 성별의 길이이다.


## 학생 정보 구조체
```
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

Student* studentHead    = NULL;
Student* studentCurrent = NULL;

```

## personName
    * 학생 이름을 담고 있다.
    * 20자리까지 사용한다. (나머지 1자리는 null)

## personId
    * 학생 학번을 담고 있다.

## personGender
    * 학생 성별을 담고 있다. 
    * 4자리만 사용한다 (나머지 1자리는 null)

## pointJava, pointAndroid, pointKotlin, pointReactNeative, pointJSP
    * 학생 별 과목 점수이다.

## pointTotal, pointAvg, pointGrade
    * 학생 별 총점 / 평균 / 등급이다.
    * 등급은 pointAvg를 기준으로 계산한다.

## StudentIdentity *prevNode, StudentIdentity *nextNode;
    * 이중연결 리스트를 위한 구조.
    * 각각 전의 학생 / 다음 학생을 가리킨다.

## Student* studentHead, Student* studentCurrent
    * 이중연결 리스트를 위한 구조.
    * studentHead는 불변이다.
    * studentCurrent는 커서( Cursor )의 역활을 한다.
    * 애지간한 학생 참조는 studentCurrent으로 한다.




## 맴버 함수
```
    readStudentByFile()
    writeStudentByFile()
    initStudentHead()

    appendNewStudent();
    updateStudent(Student* node)
    deleteStudentByCurrent()
    selectStudent(char* name)

```


#### readStudentByFile()
    * 키보드로 문자열을 입력받아 값을 읽어온다.
    * 읽어온 값을 StudentIdentity 구조체끼리 연결한다
    * 실패할 경우 오류 메세지를 던져준다.

#### writeStudentByFile()
    * 현재 학생 정보를 저장한다.
    * 저장할 파일명을 입력받아 저장을 시도한다.
    * 파일이 없으면 새로 생성, 있으면 덮어쓴다.
    * 실패할 경우 오류 메세지를 던져준다

#### initStudentHead()
    * 리스트의 처음 위치할 장로를 할당하여 studentHead에 담아둔다.


#### appendNewStudent()
    * 현재 studentCurrent 뒤에 새로운 StudentIdentity 를 추가한다
    * 해당 학생의 정보는 키보드로 입력 받는다.

#### updateStudent(Student* node)
    * node 가 가리키는 위치의 StudentIdenttity 를 갱신한다
    * 해당 학생의 정보를 키보드로 입력 받는다.

#### deleteStudentByCurrent()
    * 현재 studentCurrent가 가리키는 위치의 학생의 정보를 완전히 밀어버린다.
    * 해당 StudentIdentity는 어느것도 담고 있지 않고, 어느것도 가리키고 있지 않게 됀다...

#### selectStudent(char* name)
    * 각 학생들의 이름을 name하고 비교한다.
    * 일치할 경우 해당 학생의 신상 정보를 표시
    * 없다면, 못찾았다는 메세지를 표시.
