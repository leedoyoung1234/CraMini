#pragma once

#include "my_type.h"

extern int stack[10];


class StepBase {

public:
    virtual  bool checkAnswer(int answer) = 0;
    virtual  void processFail() = 0;
    virtual  QuestionType execute(int answer) = 0;

    QuestionType goBack(QuestionType step, int answer)
    {

        // 처음으로 돌아가기
        if (step == Run_Test)
        {
            return CarType_Q;
        }

        // 이전으로 돌아가기
        if (step >= 1)
        {
            return QuestionType(step - 1);
        }

        return step;
    }

    static void delay(int ms)
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

    static int stack[10];
};



class StepCarType : public StepBase {
public:
    bool checkAnswer(int answer)
    {
        if (answer >= 1 && answer <= 3)
        {
            return true;
        }
        return false;
    }

    void processFail()
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
    }


    QuestionType execute(int answer)
    {
        selectCarType(answer);
        delay(800);
        return Engine_Q;
    }
private :
    void selectCarType(int answer)
    {
        stack[CarType_Q] = answer;
        if (answer == 1)
            printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
        if (answer == 2)
            printf("차량 타입으로 SUV을 선택하셨습니다.\n");
        if (answer == 3)
            printf("차량 타입으로 Truck을 선택하셨습니다.\n");
    }
};

class StepEngine : public StepBase {
public:

    bool checkAnswer(int answer)
    {
        if (answer >= 0 && answer <= 4)
        {
            return true;
        }
        return false;
    }

    void processFail()
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
    }


    QuestionType execute(int answer)
    {
        selectEngine(answer);
        delay(800);
        return brakeSystem_Q;;
    }

private:
    void selectEngine(int answer)
    {
        stack[Engine_Q] = answer;
        if (answer == 1)
            printf("GM 엔진을 선택하셨습니다.\n");
        if (answer == 2)
            printf("TOYOTA 엔진을 선택하셨습니다.\n");
        if (answer == 3)
            printf("WIA 엔진을 선택하셨습니다.\n");
    }

};

class StepBrakeSystem : public StepBase {
public:

    bool checkAnswer(int answer)
    {
        if (answer >= 0 && answer <= 3)
        {
            return true;
        }
        return false;
    }

    void processFail()
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
    }


    QuestionType execute(int answer)
    {
        selectbrakeSystem(answer);
        delay(800);
        return SteeringSystem_Q;;
    }

private:
    void selectbrakeSystem(int answer)
    {
        stack[brakeSystem_Q] = answer;
        if (answer == 1)
            printf("MANDO 제동장치를 선택하셨습니다.\n");
        if (answer == 2)
            printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
        if (answer == 3)
            printf("BOSCH 제동장치를 선택하셨습니다.\n");
    }
};


class StepSteeringSystem : public StepBase {
public:

    bool checkAnswer(int answer)
    {
        if (answer >= 0 && answer <= 2)
        {
            return true;
        }
        return false;
    }

    void processFail()
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
    }


    QuestionType execute(int answer)
    {
        selectSteeringSystem(answer);
        delay(800);
        return Run_Test;
    }

private:
    void selectSteeringSystem(int answer)
    {
        stack[SteeringSystem_Q] = answer;
        if (answer == 1)
            printf("BOSCH 조향장치를 선택하셨습니다.\n");
        if (answer == 2)
            printf("MOBIS 조향장치를 선택하셨습니다.\n");
    }
};


class StepRunTest : public StepBase {
public:

    bool checkAnswer(int answer)
    {
        if (answer >= 0 && answer <= 2)
        {
            return true;
        }
        return false;
    }

    void processFail()
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
    }


    QuestionType execute(int answer)
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

private:
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
            printf("자동차가 동작되지 않습니다\n");
        }
        else
        {
            if (stack[Engine_Q] == 4)
            {
                printf("엔진이 고장나있습니다.\n");
                printf("자동차가 움직이지 않습니다.\n");
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

                printf("자동차가 동작됩니다.\n");
            }
        }
    }

    void testProducedCar()
    {
        if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Sedan에는 Continental제동장치 사용 불가\n");
        }
        else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("SUV에는 TOYOTA엔진 사용 불가\n");
        }
        else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 WIA엔진 사용 불가\n");
        }
        else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Truck에는 Mando제동장치 사용 불가\n");
        }
        else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        }
        else
        {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }
    }
};


class StepFactory {
public :
    static StepBase& getInstance(QuestionType stpe) {
        static StepBase* Instance[NumQuestion] = {
            new StepCarType,
            new StepEngine,
            new StepBrakeSystem,
            new StepSteeringSystem,
            new StepRunTest,
        };

        return *Instance[stpe];
    
    }
};