Complete Delegate
=================

A gadget of complete delegate


How to use
=================

1.Include head file:
#include "delegate.h"

2.Declare function prototype
delegate(return-value-type,delegate-name,(Formal parameters),(The actual parameters);
e.g.
delegate(void, th, (int i), (i));

3.To instantiate delegate
delegate-name delegate-instant(&class-name, &member-function-name);
or
delegate-name delegate-instant(&function-name);
e.g.
th delegate_0(&t, &A::p);
or
th delegate_0(&disp);

4.Call
delegate-instant(The actual parameters);
e.g.
delegate_0(123);
