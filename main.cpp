#include <iostream>
using namespace std;
#include "delegate.h"

delegate_m(void, th, int);
delegate_m(bool, Event, void);
extern void Call(th delegate_method);

class A
{
public:
	void p(int i)
	{
		cout << "[class]delegate print:" << i << endl;
	}
};

void p(int i)
{
	cout << "[func]delegate print:" << i << endl;
}

int main()
{
	A t;
	th delegate_0(&t, &A::p);
	Call(delegate_0);
	delegate_0 = &p;
	delegate_0(7890);
	Call(&p);
	Call({&t, &A::p});
	delegate_0(789);
	Call([](int v)
	{
		cout << "[lambda]delegate print:" << v << endl;
	});
	delegate_0 = [](int v)
	{
		cout << "[lambda2]delegate print:" << v << endl;
	};
	Call(delegate_0);
	Event e = [](void)->bool{return true;};
	return 0;
}