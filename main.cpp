#include <iostream>
using namespace std;
#include "delegate.h"

delegate_m(void, th, int);
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
	Call(&p);
	Call({&t, &A::p});
	delegate_0(789);
	th delegate_1([](int v)
	{
		cout << "[lambda]delegate print:" << v << endl;
	});
	delegate_1(654);
	return 0;
}