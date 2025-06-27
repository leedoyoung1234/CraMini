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
        printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
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
            printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
        if (answer == 2)
            printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
        if (answer == 3)
            printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
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
        printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
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
            printf("GM ������ �����ϼ̽��ϴ�.\n");
        if (answer == 2)
            printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
        if (answer == 3)
            printf("WIA ������ �����ϼ̽��ϴ�.\n");
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
        printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
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
            printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
        if (answer == 2)
            printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
        if (answer == 3)
            printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
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
            printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
        if (answer == 2)
            printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
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
        isValidCheck();
        if (false == isValid)
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
            printf("%s\n", failObj->getFailResult());
        }
        else
        {
            printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
        }

    }
};

