#ifdef _DEBUG

#include "gmock/gmock.h"
#include "my_type.h"
#include "component.h"

extern int stack[10];


TEST(CarFactoryTest, SedanValidCase) {
    stack[CarType_Q] = SEDAN;
    stack[brakeSystem_Q] = BOSCH_B;

    ComponentBase& sedan = CarFactory::getInstance(SEDAN);
    EXPECT_TRUE(sedan.isValid());
    EXPECT_STREQ(sedan.getFailResult(), "PASS");
}

TEST(CarFactoryTest, SedanInvalidBrakeSystem) {
    stack[CarType_Q] = SEDAN;
    stack[brakeSystem_Q] = CONTINENTAL;

    ComponentBase& sedan = CarFactory::getInstance(SEDAN);
    EXPECT_FALSE(sedan.isValid());
    EXPECT_STREQ(sedan.getFailResult(), "Sedan���� Continental������ġ ��� �Ұ�");
}

TEST(CarFactoryTest, TruckInvalidEngine) {
    stack[CarType_Q] = TRUCK;
    stack[Engine_Q] = WIA;
    stack[brakeSystem_Q] = MANDO;

    ComponentBase& truck = CarFactory::getInstance(TRUCK);
    EXPECT_FALSE(truck.isValid());
    EXPECT_STREQ(truck.getFailResult(), "Truck���� WIA���� ��� �Ұ�");
}

TEST(CarFactoryTest, TruckInvalidBrake) {
    stack[CarType_Q] = TRUCK;
    stack[Engine_Q] = GM;  // WIA �ƴ�
    stack[brakeSystem_Q] = MANDO;

    ComponentBase& truck = CarFactory::getInstance(TRUCK);
    EXPECT_FALSE(truck.isValid());
    EXPECT_STREQ(truck.getFailResult(), "Truck���� Mando������ġ ��� �Ұ�");
}

TEST(BrakeSystemFactoryTest, BoschBInvalidSteering) {
    stack[brakeSystem_Q] = BOSCH_B;
    stack[SteeringSystem_Q] = MOBIS;

    ComponentBase& boschB = BrakeSystemFactory::getInstance(BOSCH_B);
    EXPECT_FALSE(boschB.isValid());
    EXPECT_STREQ(boschB.getFailResult(), "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�");
}

TEST(BrakeSystemFactoryTest, BoschBValid) {
    stack[brakeSystem_Q] = BOSCH_B;
    stack[SteeringSystem_Q] = BOSCH_S;

    ComponentBase& boschB = BrakeSystemFactory::getInstance(BOSCH_B);
    EXPECT_TRUE(boschB.isValid());
    EXPECT_STREQ(boschB.getFailResult(), "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�");
}



#include "step.h"

TEST(StepCarTypeTest, ValidInput) {
    StepCarType step;
    EXPECT_TRUE(step.checkAnswer(1));
    EXPECT_TRUE(step.checkAnswer(2));
    EXPECT_TRUE(step.checkAnswer(3));
    EXPECT_FALSE(step.checkAnswer(0));
    EXPECT_FALSE(step.checkAnswer(4));
}

TEST(StepCarTypeTest, FindFailComponentSedanInvalid) {
    StepCarType step;

    stack[CarType_Q] = 1;   // Sedan
    stack[brakeSystem_Q] = CONTINENTAL;  // �߸��� ����

    ComponentBase* failComponent = step.findFailComponent();
    ASSERT_NE(failComponent, nullptr);
    EXPECT_STREQ(failComponent->getFailResult(), "Sedan���� Continental������ġ ��� �Ұ�");
}

TEST(StepCarTypeTest, FindNoFailComponentSedanValid) {
    StepCarType step;

    stack[CarType_Q] = 1;   // Sedan
    stack[brakeSystem_Q] = BOSCH_B;

    ComponentBase* failComponent = step.findFailComponent();
    EXPECT_EQ(failComponent, nullptr);
}

TEST(StepEngineTest, ValidInput) {
    StepEngine step;
    EXPECT_TRUE(step.checkAnswer(1));
    EXPECT_TRUE(step.checkAnswer(2));
    EXPECT_TRUE(step.checkAnswer(3));
    EXPECT_TRUE(step.checkAnswer(4));
    EXPECT_FALSE(step.checkAnswer(-1));
    EXPECT_FALSE(step.checkAnswer(5));
}


TEST(StepBrakeSystemTest, ValidInput) {
    StepBrakeSystem step;
    EXPECT_TRUE(step.checkAnswer(1));
    EXPECT_TRUE(step.checkAnswer(2));
    EXPECT_TRUE(step.checkAnswer(3));
    EXPECT_FALSE(step.checkAnswer(0));
    EXPECT_FALSE(step.checkAnswer(4));
}


TEST(StepSteeringSystemTest, ValidInput) {
    StepSteeringSystem step;
    EXPECT_TRUE(step.checkAnswer(1));
    EXPECT_TRUE(step.checkAnswer(2));
    EXPECT_FALSE(step.checkAnswer(0));
    EXPECT_FALSE(step.checkAnswer(3));
}


TEST(StepRunTest, IsValidCheckFailTruckEngine) {

    stack[CarType_Q] = 3; // Truck
    stack[Engine_Q] = 3;  // WIA
    stack[brakeSystem_Q] = BOSCH_B;
    stack[SteeringSystem_Q] = BOSCH_S;

    StepRunTest stepRun;

    bool isValid = true;
    ComponentBase* failObj = nullptr;
    for (int step = 0; step < Run_Test; ++step) {
        if (step == 0) {
            StepCarType stepCar;
            failObj = stepCar.findFailComponent();
        }
        else if (step == 1) {
            StepEngine stepEngine;
            failObj = stepEngine.findFailComponent();
        }
        else if (step == 2) {
            StepBrakeSystem stepBrake;
            failObj = stepBrake.findFailComponent();
        }
        else if (step == 3) {
            StepSteeringSystem stepSteering;
            failObj = stepSteering.findFailComponent();
        }

        if (failObj) break;
    }

    ASSERT_NE(failObj, nullptr);
    EXPECT_TRUE(strstr(failObj->getFailResult(), "Truck") != nullptr);
}


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

