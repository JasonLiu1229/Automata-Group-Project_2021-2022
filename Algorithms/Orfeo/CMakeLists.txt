cmake_minimum_required(VERSION 3.0.0)
project(Automata VERSION 0.4.0)

#include(CTest)
#enable_testing()

set(DFA_sources
        Test_files/DFA_test.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(NFA_sources
        Test_files/NFA_test.cpp
        DFA.cpp
        NFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(SSC_sources
        Test_files/SSC_test.cpp
        DFA.cpp
        NFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(MSSC_sources
        Test_files/MSSC_test.cpp
        ENFA.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(PA_sources
        Test_files/Product_test.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(RE_sources
        Test_files/REGEX_test.cpp
        RE.cpp
        ENFA.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(TFA_sources
        Test_files/TFA_test.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp
)

set(MACRO_sources
        Test_files/MACRO_test.cpp
        RE.cpp
        ENFA.cpp
        DFA.cpp
        Node.cpp
        transition.cpp
        transitionNFA.cpp   
)

add_executable(DFA ${DFA_sources})

add_executable(NFA ${NFA_sources})

add_executable(SSC ${SSC_sources})

add_executable(MSSC ${MSSC_sources})

add_executable(PA ${PA_sources})

add_executable(RE ${RE_sources})

add_executable(TFA ${TFA_sources})

add_executable(MACRO ${MACRO_sources})

#install( TARGETS  DESTINATION ${PROJECT_SOURCE_DIR}/debug )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)