#pragma once


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    NUM_QUESTION
};

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    NUM_CAR

};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BAD_ENGINE,
    NUM_ENGINE
};

enum BrakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    NUM_BRAKE_SYSTEM
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    NUM_STEERING_SYSTEM
};