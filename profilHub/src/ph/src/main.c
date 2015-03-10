#include <errors.h>
#include <launcher.h>
#include <strstuff.h>

int
main(int argc, const char** argv, const char** env)
{
	M_LAUNCHER(l, "/tmp/a.out -to -the -rap -mobile -lets -go");
	if (!launcher_add_task(&l, E_VALGRIND_MEMCHECK, NULL))
		return M_ERROR_INT(1, "could not create task\n", 0);
	if (!launcher_launch(&l))
		return M_ERROR_INT(1, "could not execute tasks\n", 0);
	M_LAUNCHER_DESTROY(l);
	return 0;
	(void)argc;
	(void)argv;
	(void)env;
}
