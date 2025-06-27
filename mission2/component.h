#pragma once

#include "my_type.h"

class ComponentBase {
public :
	ComponentBase(const int id, const char* name) : id(id), name(name) {}
	
	virtual bool isValid() = 0;
	virtual const char* getTestResult() const = 0;
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

/*
enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK
};
*/

class Sedan : public ComponentBase {
public:
    Sedan() : ComponentBase(SEDAN, "SEDAN") {}
	bool isValid() 
	{
		return true;
	}
	const char* getTestResult() const 
	{
		return "PASS\n";
	}
};

class Sub : public ComponentBase {
public:
	Sub() : ComponentBase(SUV, "SUV") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class Truck : public ComponentBase {
public:
	Truck() : ComponentBase(TRUCK, "TRUCK") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

/*

enum Engine
{
	GM = 1,
	TOYOTA,
	WIA
};

*/

class Gm : public ComponentBase {
public:
	Gm() : ComponentBase(GM, "GM") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class Toyota : public ComponentBase {
public:
	Toyota() : ComponentBase(TOYOTA, "TOYOTA") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class Wia : public ComponentBase {
public:
	Wia() : ComponentBase(WIA, "WIA") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

/*
enum BrakeSystem
{
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};
*/

class Mando : public ComponentBase {
public:
	Mando() : ComponentBase(MANDO, "MANDO") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class Continental : public ComponentBase {
public:
	Continental() : ComponentBase(CONTINENTAL, "CONTINENTAL") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class BoschB : public ComponentBase {
public:
	BoschB() : ComponentBase(BOSCH_B, "BOSCH_B") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};


/*
enum SteeringSystem
{
	BOSCH_S = 1,
	MOBIS
};
*/
class BoschS : public ComponentBase {
public:
	BoschS() : ComponentBase(BOSCH_S, "BOSCH_S") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

class Mobis : public ComponentBase {
public:
	Mobis() : ComponentBase(MOBIS, "MOBIS") {}
	bool isValid()
	{
		return true;
	}
	const char* getTestResult() const
	{
		return "PASS\n";
	}
};

