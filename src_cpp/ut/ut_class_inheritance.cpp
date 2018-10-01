#include <gtest/gtest.h>

void foo_A(class A &a);

class A
{
public:
	void pub_func() {}
protected:
	void prot_func() {}
private:
	void priv_func() {}

public:
	int pub_a;
protected:
	int prot_b;
private:
	int priv_c;

	friend void foo_A(A &a);
};

void foo_A(A &a)
{
	a.priv_c = 0;
}
class B : public A
{
public:
	void UpdateBase()
	{
		pub_a = 0;
		prot_b = 0;
		//priv_c = 0;

		pub_func();
		prot_func();
		//priv_func();
	}
};

class C : public A
{
public:
	void UpdateBase()
	{
		pub_a = 0;
		prot_b = 0;
		//priv_c = 0;

		pub_func();
		prot_func();
	//	priv_func();
	}
};

class CC : protected C
{
public:
	void UpdateBase()
	{
		pub_a = 0;
		prot_b = 0;
		//priv_c = 0; // error

		pub_func();    // OK
		prot_func();   // OK 
		//priv_func(); // error
	}
};

void foo_CC()
{
	CC obj;
	obj.UpdateBase(); // OK
	//obj.pub_a = 0; // error 
	//obj.pub_func(); // error
}

class D : private A
{
public:
	void UpdateBase()
	{
		pub_a = 0;    // OK
		prot_b = 0;   // OK
		//priv_c = 0; // error

		pub_func();    // OK
		prot_func();   // OK 
		//priv_func(); // error
	}
};

class DD : public D
{
public:
	void UpdateBase()
	{
		D::UpdateBase(); // OK

		//pub_a = 0;    // error
		//prot_b = 0;   // error
		//priv_c = 0; // error

		//pub_func();   // error
		//prot_func();  // error
		//priv_func(); // error
	}
};

void foo_DD()
{
	DD obj;
	obj.UpdateBase();
}

TEST(CPP_Class, Inheritance)
{
	CC obj;
	obj.UpdateBase();
}


class Point
{
public:
	int x, y;
public:
	//Point() {};
	
	void print() { std::cout << x << ' ' << y << std::endl; }
	//Point(int x1, int y1) { x = x1; y = y1; }

	// Copy constructor
	//Point(const Point &p2) { x = p2.x; y = p2.y; }

//	int getX() { return x; }
	//int getY() { return y; }
};

class T {
public:
	int x;

	T() = default;
};

#pragma warning (disable: 4700)

TEST(CPP_Class, CopyCtor)
{
	/*T t;
	T *p_t = new T;

	T c = T();
	T *p_c = new T();

	T d{};
	T dd = T{};

	std::cout << t.x << std::endl;
	std::cout << p_t->x << std::endl;

	std::cout << c.x << std::endl;
	std::cout << p_c->x << std::endl;

	std::cout << d.x << std::endl;
	std::cout << dd.x << std::endl;

	//Point p1;
	//Point p2;

	//p1.getX();
	//p2.getY();
	//p1.print();
	//p2.print();
	//Point p1(10, 15); // Normal constructor is called here
	//Point p2 = p1; // Copy constructor is called here
	*/
}
