#include "delegate.h"

delegate_m(void, th, int);

void Call(th delegate_method)
{
	delegate_method(123);
}