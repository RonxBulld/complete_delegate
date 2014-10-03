#include "delegate.h"

delegate(void, th, (int i), (i));

void Call(th delegate_method)
{
	delegate_method(123);
}
