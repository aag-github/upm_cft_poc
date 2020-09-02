#include <unistd.h>
#include "cft_test_runner.h"
#include "cft_worker_manager.h"
#include "et.h"

int main(int argc, char **argv)
{
    if (argc > 1) {
        et_set_filter(argv[1]);
    }

    return(test_runner());
}
