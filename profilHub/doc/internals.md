Internals
======

## .ph framework

### Launcher API (under construction)

* *profilHub/src/ph/src/launcher.c*
* *profilHub/src/ph/include/launcher.h*

The launcher API should be used by front-end interfaces in order to execute selected tools and get their results.

Here's a simple example of use:
``` c
#include <errors.h>
#include <launcher.h>

int
main(void)
{
	/* creates a launcher l on the stack, targeting executable /tmp/a.out with arguments "--some-arg" and "-v" */
	M_LAUNCHER(l, "/tmp/a.out --some-arg -v");
	/* creates two different tasks for this launcher */
	/* NULL pointers indicates the use of the default parameters of the tool */
	if (!launcher_add_task(&l, E_VALGRIND_MEMCHECK, NULL) ||
	    !launcher_add_task(&l, E_VALGRIND_HELGRIND, NULL))
		return M_ERROR_INT(1, "could not create task\n", 0);
	/* executes the tasks and gets the results */
	if (!launcher_launch(&l))
		return M_ERROR_INT(1, "could not execute tasks\n", 0);
	/* clears launcher */
	M_LAUNCHER_DESTROY(l);
	return 0;
}
```
