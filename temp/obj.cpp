#include <iostream>
#include <algorithm>
using namespace std;

template <class K, class E>
class Dictonary
{
public:
	virtual void Ascend(void) const = 0;

	virtual pair<K, E> *Get(const K &) const = 0;

	virtual void insert(const pair<K, E> &) = 0;

	virtual void Delete(const K &) = 0;
};

class BaseClass
{
public:
	virtual void print(void) const
	{
		cout << "Base class\n";
	}
};

class DervClass : public BaseClass
{
public:
	virtual void print(void) const
	{
		cout << "Derived class\n";
	}
};

class Polygons
{
protected:
	double area;
	virtual void calcArea() = 0;

public:
	Polygons() {}
	~Polygons() {}
	void printArea() const;
};

class Triangle : public Polygons
{
private:
	double sideA;
	double sideB;
	double sideC;
	virtual void calcArea();

public:
	Triangle(double sideA, double sideB, double sideC);
};

int main(void)
{
	BaseClass *objPtr = new BaseClass;
	objPtr->print();
	delete objPtr;

	objPtr = new DervClass;
	objPtr->print();
	delete objPtr;

	return 0;
}