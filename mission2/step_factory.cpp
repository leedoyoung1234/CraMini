#include "step.h"
#include "step_factory.h"

StepBase& StepFactory::getInstance(QuestionType stpe) {
    static StepBase* Instance[NUM_QUESTION] = {
        new StepCarType,
        new StepEngine,
        new StepBrakeSystem,
        new StepSteeringSystem,
        new StepRunTest,
    };

    return *Instance[stpe];
}
