#include<iostream>

using namespace std;

template<class k, class e>
class dictionary {
public:
	virtual void ascend(void) const = 0;

	virtual pair<k e> *get(const K&) const = 0;

	virtual void insert(const pair<k, e>&) = 0;

	virtual void Delete(const k&) = 0;
};

class baseclass {
public:
	virtual void print(void) const{
		cout << "base class\n";
	};
};

class baseclass2 {
public:
	virtual void print(void) = 0;
};

class dervclass: public baseclass {
public:
	virtual void print(void) const {
		cout << "derived class\n";
	};
};

/*						---						*/
class polygons {
protected:
	double area;
	virtual void calcarea() = 0;
public:
	polygons() {};
	~polygons() {};
	void printarea() const;
};

class triangle: public polygons {
private:
	double sa;
	double sb;
	double sc;
	virtual void calcArea();
public:
	triangle(double sa, double sb, double sc);
};
/*						---						*/

int main(void) {
	baseclass *objptr = new baseclass;
	objptr->print();
	delete objptr;

	// baseclass2 *objptr2 = new baseclass2; 추상 class는 object를 갖을 수 없다.
	// objptr2->print();
	// delete objptr2;

	objptr = new dervclass;
	objptr->print();
	delete objptr;
}