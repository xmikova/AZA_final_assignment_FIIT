# CMakeList.txt : CMake project for AZA_final_assignment_Mikova, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (AZA_final_assignment_Mikova "AZA_final_assignment_Mikova.h"
        AZA_task1_Mikova.cpp
        AZA_task2_Mikova.cpp
        AZA_task3_Mikova.cpp
        AZA_task4_Mikova.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AZA_final_assignment_Mikova PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
