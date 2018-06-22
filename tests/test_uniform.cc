#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cassert>

#include <time.h>

#include "ql/openql.h"
#include "ql/utils.h"

// a simple first test
// the x gates serve to separate the cnot gates wrt dependences
// this creates big bundles with 7 x gates
// and small bundles with just a cnot
// after uniform scheduling, one or more x gates
// should have been moved next to the cnot
// those will move that do not have operands that overlap those of the cnot
void
test_0( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_0_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.0",starmon);

    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 0,2);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 6,3);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 1,4);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// just as the previous one
// but then more of the same
void
test_1( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_1_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.1",starmon);

    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 0,2);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 6,3);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 1,4);

    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 2,5);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 3,1);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 4,6);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 2,0);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 3,6);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 4,1);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 5,2);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 1,3);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 6,4);
    for (int j=0; j<7; j++)
        k.gate("x", j);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// big bundles with x gates
// alternated with cnot bundles
// these cnots were chosen to be mutually independent
// so will be going all 3 in one bundle
// the single independent x will be moved with it
void
test_2( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_2_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.2",starmon);

    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 0,2);
    k.gate("cnot", 6,3);
    k.gate("cnot", 1,4);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 2,5);
    k.gate("cnot", 3,1);
    k.gate("cnot", 4,6);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 2,0);
    k.gate("cnot", 3,6);
    k.gate("cnot", 4,1);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 5,2);
    k.gate("cnot", 1,3);
    k.gate("cnot", 6,4);
    for (int j=0; j<7; j++)
        k.gate("x", j);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// again big bundles with x gates
// alternated with cnot bundles;
// these cnots were chosen to be largely dependent
// this already creates smaller bundles but more of them
void
test_3( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_3_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.3",starmon);

    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 6,3);
    k.gate("cnot", 0,2);
    k.gate("cnot", 1,3);
    k.gate("cnot", 1,4);
    k.gate("cnot", 0,3);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 2,5);
    k.gate("cnot", 3,1);
    k.gate("cnot", 2,0);
    k.gate("cnot", 3,6);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 4,1);
    k.gate("cnot", 3,0);
    k.gate("cnot", 4,6);
    for (int j=0; j<7; j++)
        k.gate("x", j);
    k.gate("cnot", 3,5);
    k.gate("cnot", 5,2);
    k.gate("cnot", 6,4);
    k.gate("cnot", 5,3);
    for (int j=0; j<7; j++)
        k.gate("x", j);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// as with test 3 but now without the big x bundles
// just the cnots in lexicographic order
// the worst you can imagine,
// creating the smallest bundles
void
test_4( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_4_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.4",starmon);

    for (int j=0; j<7; j++)
        k.gate("x", j);

    k.gate("cnot", 0,2);
    k.gate("cnot", 0,3);
    k.gate("cnot", 1,3);
    k.gate("cnot", 1,4);
    k.gate("cnot", 2,0);
    k.gate("cnot", 2,5);
    k.gate("cnot", 3,0);
    k.gate("cnot", 3,1);
    k.gate("cnot", 3,5);
    k.gate("cnot", 3,6);
    k.gate("cnot", 4,1);
    k.gate("cnot", 4,6);
    k.gate("cnot", 5,2);
    k.gate("cnot", 5,3);
    k.gate("cnot", 6,3);
    k.gate("cnot", 6,4);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

void
test_5( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_5_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.5",starmon);

    // empty kernel

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// code with a lot of preps at the start, meas at the end and some work in the middle
// all is equally critical so gain here
void
test_6( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_6_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.6",starmon);

    k.gate("prepz", 0);
    k.gate("prepz", 1);
    k.gate("prepz", 2);
    k.gate("prepz", 3);
    k.gate("prepz", 4);
    k.gate("prepz", 5);
    k.gate("prepz", 6);

    k.gate("t", 0);
    k.gate("t", 1);
    k.gate("t", 2);
    k.gate("t", 3);
    k.gate("t", 4);
    k.gate("t", 5);
    k.gate("t", 6);

    k.gate("measz", 0);
    k.gate("measz", 1);
    k.gate("measz", 2);
    k.gate("measz", 3);
    k.gate("measz", 4);
    k.gate("measz", 5);
    k.gate("measz", 6);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

// code with a lot of preps at the start
void
test_7( std::string scheduler, std::string scheduler_uniform)
{
    // create and set platform
    ql::quantum_platform starmon("starmon","test_cfg_none_s7.json");
    ql::set_platform(starmon);

    // create program
    ql::quantum_program prog(("test_7_" + scheduler + "_uniform_" + scheduler_uniform), 7, starmon);
    ql::quantum_kernel k("kernel7.7",starmon);

    k.gate("prepz", 0);
    k.gate("prepz", 1);
    k.gate("prepz", 2);
    k.gate("prepz", 3);
    k.gate("prepz", 4);
    k.gate("prepz", 5);
    k.gate("prepz", 6);

    k.gate("h", 0);	// qubit 0 critical
    k.gate("t", 0);
    k.gate("h", 0);
    k.gate("t", 0);

    k.gate("h", 2);	// qubit 2 loaded
    k.gate("t", 2);

    k.gate("h", 4);	// qubit 4 medium loaded

    for (int j=0; j<7; j++)	// all qubits some load at the end
        k.gate("x", j);

    prog.add(k);

    ql::options::set("scheduler", scheduler);
    ql::options::set("scheduler_uniform", scheduler_uniform);
    prog.compile( );
}

int main(int argc, char ** argv)
{
    // ql::utils::logger::set_log_level("LOG_DEBUG");
    ql::utils::logger::set_log_level("LOG_INFO");

    test_0("ALAP", "no");
    test_0("ALAP", "yes");
    test_1("ALAP", "no");
    test_1("ALAP", "yes");
    test_2("ALAP", "no");
    test_2("ALAP", "yes");
    test_3("ALAP", "no");
    test_3("ALAP", "yes");
    test_4("ALAP", "no");
    test_4("ALAP", "yes");
    test_5("ALAP", "no");
    test_5("ALAP", "yes");
    test_6("ALAP", "no");
    test_6("ALAP", "yes");
    test_7("ALAP", "no");
    test_7("ALAP", "yes");

    return 0;
}
