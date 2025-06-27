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
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}


void displayMenuEngine()
{
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}



void displayMenuBrakeSystem()
{
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}



void displayMenuSteeringSystem()
{
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}


void displayMenuRunTest()
{
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
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

        // 엔터 개행문자 제거
        char* context = nullptr;
        strtok_s(buf, "\r", &context);
        strtok_s(buf, "\n", &context);

        if (!strcmp(buf, "exit"))
        {
            printf("바이바이\n");
            break;
        }

        // 숫자로 된 대답인지 확인
        char* checkNumber;
        int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

        // 입력받은 문자가 숫자가 아니라면
        if (*checkNumber != '\0')
        {
            printf("ERROR :: 숫자만 입력 가능\n");
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

