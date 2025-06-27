#pragma once

#include "my_type.h"

extern int stack[10];

class ComponentBase {
public :
	ComponentBase(const int id, const char* name) : id(id), name(name) {}
	
	virtual bool isValid() { return true;}
	virtual const char* getFailResult() const { return "PASS"; }
	const char* getName() const 
	{
		return name;
	}
	int getId() const
	{
		return id;
	}
private :
	const int id;
	const char* name;
};



class Sedan : public ComponentBase {
public:
    Sedan() : ComponentBase(SEDAN, "SEDAN") {}
	bool isValid() 
	{
		if (stack[CarType_Q] != SEDAN) return true;

		if (stack[brakeSystem_Q] == CONTINENTAL)
		{
			return false;
		}
		return true;
	}
	const char* getFailResult() const
	{
		return "Sedan에는 Continental제동장치 사용 불가";
	}
};

class Sub : public ComponentBase {
public:
	Sub() : ComponentBase(SUV, "SUV") {}
	bool isValid()
	{
		if (stack[CarType_Q] != SUV) return true;
		if (stack[Engine_Q] == TOYOTA)
		{
			return false;
		}
		return true;
	}
	const char* getFailResult() const
	{
		return "SUV에는 TOYOTA엔진 사용 불가";
	}
};


class Truck : public ComponentBase {
public:
	Truck() : ComponentBase(TRUCK, "TRUCK") {}
	bool isValid()
	{
		if (stack[CarType_Q] != TRUCK) return true;
		if (stack[Engine_Q] == WIA)
		{
			return false;
		}
		else if (stack[brakeSystem_Q] == MANDO)
		{
			return false;
		}
		return true;
	}
	const char* getFailResult() const
	{
		if (stack[Engine_Q] == WIA)
		{
			return "Truck에는 WIA엔진 사용 불가";
		}
		else if (stack[brakeSystem_Q] == MANDO)
		{
			return "Truck에는 Mando제동장치 사용 불가";
		}
		return "PASS";
	}
};

class CarFactory {
public:
	static ComponentBase& getInstance(int id) {
		static ComponentBase* Instance[NUM_CAR] = {
			new Sedan,
			new Sub,
			new Truck,
		};

		return *Instance[id - 1];

	}
};

class Gm : public ComponentBase {
public:
	Gm() : ComponentBase(GM, "GM") {}
};

class Toyota : public ComponentBase {
public:
	Toyota() : ComponentBase(TOYOTA, "TOYOTA") {}
};

class Wia : public ComponentBase {
public:
	Wia() : ComponentBase(WIA, "WIA") {}

};

class BedEngine : public ComponentBase {
public:
	BedEngine() : ComponentBase(BAD_ENGINE, "고장난 엔진") {}
};

class EngineFactory {
public:
	static ComponentBase& getInstance(int id) {
		static ComponentBase* Instance[NUM_ENGINE] = {
			new Gm,
			new Toyota,
			new Wia,
			new BedEngine,
		};

		return *Instance[id -1];

	}
};


class Mando : public ComponentBase {
public:
	Mando() : ComponentBase(MANDO, "MANDO") {}
};

class Continental : public ComponentBase {
public:
	Continental() : ComponentBase(CONTINENTAL, "CONTINENTAL") {}
};

class BoschB : public ComponentBase {
public:
	BoschB() : ComponentBase(BOSCH_B, "BOSCH") {}
	bool isValid()
	{
		if (stack[brakeSystem_Q] == BOSCH_B) return true;
		if (stack[SteeringSystem_Q] != BOSCH_S)
		{
			return false;
		}
		return true;
	}
	const char* getFailResult() const
	{
		return "Bosch제동장치에는 Bosch조향장치 이외 사용 불가";
	}
};

class BrakeSystemFactory {
public:
	static ComponentBase& getInstance(int id) {
		static ComponentBase* Instance[NUM_BRAKE_SYSTEM] = {
			new Mando,
			new Continental,
			new BoschB,
		};

		return *Instance[id -1];
	}
};

class BoschS : public ComponentBase {
public:
	BoschS() : ComponentBase(BOSCH_S, "BOSCH") {}
};

class Mobis : public ComponentBase {
public:
	Mobis() : ComponentBase(MOBIS, "MOBIS") {}
};

class SteeringSystemFactory {
public:
	static ComponentBase& getInstance(int id) {
		static ComponentBase* Instance[NUM_STEERING_SYSTEM] = {
			new BoschS,
			new Mobis,
		};

		return *Instance[id -1];
	}
};
