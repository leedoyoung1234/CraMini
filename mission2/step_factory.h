#pragma once
#include "my_type.h"
class StepBase;
class StepFactory {
public:
    static StepBase& getInstance(QuestionType stpe);
};
