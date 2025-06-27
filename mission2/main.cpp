#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include "step.h"

#define CLEAR_SCREEN "\033[H\033[2J"

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


void displayMenuEngine()
{
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}



void displayMenuBrakeSystem()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}



void displayMenuSteeringSystem()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}


void displayMenuRunTest()
{
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
    printf("1. RUN\n");
    printf("2. Test\n");
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
            StepBase::delay(800);
            continue;
        }
        StepBase& stepObj = StepFactory::getInstance(step);

        if (true == stepObj.checkAnswer(answer))
        {
            if (answer == 0)
            {
                step = stepObj.goBack(step, answer);
            }
            else
            {
                step = stepObj.execute(answer);
            }
        }
        else
        {
            stepObj.processFail();
            StepBase::delay(800);
            continue;
        }
    }
}
#endif

