#include <unistd.h>
#include "cft_test_runner.h"
#include "cft_worker_manager.h"

//#define CHILD_PROCS_COUNT 5

int main(int argc, char **argv)
{
    return(test_runner());
}
