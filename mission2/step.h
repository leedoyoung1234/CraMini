#pragma once

#include "component.h"
#include "step_factory.h"

extern int stack[10];


class StepBase {

public:
    StepBase(int numComponent) : numComponent(numComponent) {}
    virtual  bool checkAnswer(int answer) = 0;
    virtual  void processFail() = 0;
    virtual  QuestionType execute(int answer) = 0;
    virtual  ComponentBase* getComponent(int id) { return nullptr;  }

    ComponentBase* findFailComponent() 
    { 
        for (int id = 1; id < numComponent; ++id)
        {
            ComponentBase* componentObj = getComponent(id);
            if (false == componentObj->isValid())
            {
                return componentObj;
            }

        }

        return nullptr;
    }

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
private :
    int numComponent;
};



class StepCarType : public StepBase {
public:
    StepCarType() : StepBase(NUM_CAR) {}
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

    ComponentBase* getComponent(int id) 
    { 
        return &CarFactory::getInstance(id);
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
    StepEngine() : StepBase(NUM_ENGINE) {}
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

    ComponentBase* getComponent(int id)
    {
        return &EngineFactory::getInstance(id);
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
    StepBrakeSystem() : StepBase(NUM_BRAKE_SYSTEM) {}
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
    ComponentBase* getComponent(int id)
    {
        return &BrakeSystemFactory::getInstance(id);
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
    StepSteeringSystem() : StepBase(NUM_STEERING_SYSTEM) {}
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

    ComponentBase* getComponent(int id)
    {
        return &SteeringSystemFactory::getInstance(id);
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
    StepRunTest() : StepBase(0) {}
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
    bool isValid = true;
    ComponentBase* failObj = nullptr;

    int isValidCheck()
    {  
        isValid = true;
        failObj = nullptr;
        for (int step = 0; step < Run_Test; ++step)
        {
            StepBase&  stepObj =StepFactory::getInstance((QuestionType)step);
            failObj = stepObj.findFailComponent();
            if(failObj)
            {
                printf("%s\n", failObj->getName());
                break; 
            }
        }
        if (failObj)
        {
            return false;
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
        isValidCheck();
        if (false == isValid)
        {
            printf("자동차 부품 조합 테스트 결과 : FAIL\n");
            printf("%s\n", failObj->getFailResult());
        }
        else
        {
            printf("자동차 부품 조합 테스트 결과 : PASS\n");
        }

    }
};

