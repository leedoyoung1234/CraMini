#ifdef REFACTO_CLASS

#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA
};

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS
};

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}



void selectCarType(int answer)
{
    stack[CarType_Q] = answer;
    if (answer == 1)
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Engine_Q] = answer;
    if (answer == 1)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[brakeSystem_Q] = answer;
    if (answer == 1)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 3)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[SteeringSystem_Q] = answer;
    if (answer == 1)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == 2)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
}

int isValidCheck()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        return false;
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        return false;
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        return false;
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
    }
    else
    {
        if (stack[Engine_Q] == 4)
        {
            printf("������ ���峪�ֽ��ϴ�.\n");
            printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        }
        else
        {
            if (stack[CarType_Q] == 1)
                printf("Car Type : Sedan\n");
            if (stack[CarType_Q] == 2)
                printf("Car Type : SUV\n");
            if (stack[CarType_Q] == 3)
                printf("Car Type : Truck\n");
            if (stack[Engine_Q] == 1)
                printf("Engine : GM\n");
            if (stack[Engine_Q] == 2)
                printf("Engine : TOYOTA\n");
            if (stack[Engine_Q] == 3)
                printf("Engine : WIA\n");
            if (stack[brakeSystem_Q] == 1)
                printf("Brake System : Mando");
            if (stack[brakeSystem_Q] == 2)
                printf("Brake System : Continental\n");
            if (stack[brakeSystem_Q] == 3)
                printf("Brake System : Bosch\n");
            if (stack[SteeringSystem_Q] == 1)
                printf("SteeringSystem : Bosch\n");
            if (stack[SteeringSystem_Q] == 2)
                printf("SteeringSystem : Mobis\n");

            printf("�ڵ����� ���۵˴ϴ�.\n");
        }
    }
}

void testProducedCar()
{
    if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
    }
    else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
    }
    else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
    }
    else
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
    }
}

bool checkAnswerCarType(int answer)
{
    if (answer >= 1 && answer <= 3)
    {
        return true;
    }
    return false;
}

void processFailCarType()
{
    printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
}


QuestionType executeCarType(int answer)
{
    selectCarType(answer);
    delay(800);
    return Engine_Q;
}

void displayMenuCarType()
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}


bool checkAnswerEngine(int answer)
{
    if (answer >= 0 && answer <= 4)
    {
        return true;
    }
    return false;
}

void processFailEngine()
{
    printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
}


QuestionType executeEngine(int answer)
{
    selectEngine(answer);
    delay(800);
    return brakeSystem_Q;;
}

void displayMenuEngine()
{
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}


bool checkAnswerBrakeSystem(int answer)
{
    if (answer >= 0 && answer <= 3)
    {
        return true;
    }
    return false;
}

void processFailBrakeSystem()
{
    printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
}


QuestionType executeBrakeSystem(int answer)
{
    selectbrakeSystem(answer);
    delay(800);
    return SteeringSystem_Q;;
}

void displayMenuBrakeSystem()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}



bool checkAnswerSteeringSystem(int answer)
{
    if (answer >= 0 && answer <= 2)
    {
        return true;
    }
    return false;
}

void processFailSteeringSystem()
{
    printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
}


QuestionType executeSteeringSystem(int answer)
{
    selectSteeringSystem(answer);
    delay(800);
    return Run_Test;
}

void displayMenuSteeringSystem()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}


bool checkAnswerRunTest(int answer)
{
    if (answer >= 0 && answer <= 2)
    {
        return true;
    }
    return false;
}

void processFailRunTest()
{
    printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
}


QuestionType executeRunTest(int answer)
{
    if (answer == 1)
    {
        runProducedCar();
        delay(2000);
    }
    else if (answer == 2)
    {
        printf("Test...\n");
        delay(1500);
        testProducedCar();
        delay(2000);
    }
    return Run_Test;
}

void displayMenuRunTest()
{
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}


bool checkAnswer(QuestionType step, int answer)
{
    if (step == CarType_Q) return checkAnswerCarType(answer);
    else if (step == Engine_Q) return checkAnswerEngine(answer);
    else if (step == brakeSystem_Q) return checkAnswerBrakeSystem(answer);
    else if (step == SteeringSystem_Q) return checkAnswerSteeringSystem(answer);
    else if (step == Run_Test) return checkAnswerRunTest(answer);
    return true;
}

void processFail(QuestionType step)
{
    if (step == CarType_Q) return processFailCarType();
    else if (step == Engine_Q) return processFailEngine();
    else if (step == brakeSystem_Q) return processFailBrakeSystem();
    else if (step == SteeringSystem_Q) return processFailSteeringSystem();
    else if (step == Run_Test) return processFailRunTest();
}

QuestionType execute(QuestionType step, int answer)
{
    if (step == CarType_Q) return executeCarType(answer);
    else if (step == Engine_Q) return executeEngine(answer);
    else if (step == brakeSystem_Q) return executeBrakeSystem(answer);
    else if (step == SteeringSystem_Q) return executeSteeringSystem(answer);
    else if (step == Run_Test) return executeRunTest(answer);
    return step;
}

void displayMenu(QuestionType step)
{
    printf(CLEAR_SCREEN);
    if (step == CarType_Q) return displayMenuCarType();
    else if (step == Engine_Q) return displayMenuEngine();
    else if (step == brakeSystem_Q) return displayMenuBrakeSystem();
    else if (step == SteeringSystem_Q) return displayMenuSteeringSystem();
    else if (step == Run_Test) return displayMenuRunTest();

    printf("===============================\n");
}


QuestionType goBack(QuestionType step, int answer)
{

    // ó������ ���ư���
    if (step == Run_Test)
    {
        return CarType_Q;
    }

    // �������� ���ư���
    if (step >= 1)
    {
        return QuestionType(step - 1);
    }

    return step;
}


int main()
{
    char buf[100];
    QuestionType step = CarType_Q;

    while (1)
    {

        displayMenu(step);

        printf("INPUT > ");
        fgets(buf, sizeof(buf), stdin);

        // ���� ���๮�� ����
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("���̹���\n");
            break;
        }

        // ���ڷ� �� ������� Ȯ��
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

        // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
        if (*checkNumber != '\0')
        {
            printf("ERROR :: ���ڸ� �Է� ����\n");
            delay(800);
            continue;
        }

        if (true == checkAnswer(step, answer))
        {
            if (answer == 0)
            {
                step = goBack(step, answer);
            }
            else
            {
                step = execute(step, answer);
            }
        }
        else
        {
            processFail(step);
            delay(800);
            continue;
        }
    }
}
#endif

#endif