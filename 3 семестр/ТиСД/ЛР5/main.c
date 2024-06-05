#include "head.h"

int main(void)
{
	int rc;
	setbuf(stdout, NULL);
	
    int general_action;
    if ((rc = read_general_action(&general_action)))
	{
        return rc;
	}

	if (general_action == 1)
        rc = compare_turns();
	
	if (general_action == 2)
        rc = solution_problem();
    
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}