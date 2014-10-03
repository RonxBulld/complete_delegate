#include <iostream>
using namespace std;
#include "delegate.h"

delegate(void, th, (int i), (i));
extern void Call(th delegate_method);

class A
{
public:
	void p(int i)
	{
		cout << "delegate print:" << i << endl;
	}
};

int main()
{
	A t;
	th delegate_0(&t, &A::p);
	Call(delegate_0);
	return 0;
}
