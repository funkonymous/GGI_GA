###############################################################################
cmake_minimum_required (VERSION 2.8)
project (GreibachCrammaticalInferenceAccelerated)

###############################################################################

# for rdm
#set(CMAKE_EXPORT_COMPILE_COMMANDS=1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o3")

set(EXECUTABLE_OUTPUT_PATH bin)

###############################################################################


include_directories(
  ${PROJECT_SOURCE_DIR}/MainProgram
  ${PROJECT_SOURCE_DIR}/GeneticAlgorithm
  ${PROJECT_SOURCE_DIR}/GreibachImplementation
  ${PROJECT_SOURCE_DIR}/DataManipulation
  ${PROJECT_SOURCE_DIR}/DataSets
)

#add_library(ggi ${GGI_ACCEL_SOURCE_FILES})

file(COPY DataSets DESTINATION bin)
###############################################################################
#
add_executable(GGI_ACCEL
    MainProgram/main.cpp

    DataManipulation/datautilities.h
    DataManipulation/dataword.h
    DataManipulation/dataword.cpp
    DataManipulation/enumterminalsmap.h
    DataManipulation/enumterminalsmap.cpp
    DataManipulation/database.h
    DataManipulation/database.cpp
)


# Xcode and Visual working directories
#set_target_properties(GGI_ACCEL
#    PROPERTIES
#    XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
#    PROJECT_LABEL "Greibach Grammatical Inference (GA - Accelerated)"
#    FOLDER "ExecutableFolder"
#)
#create_target_launcher(ap WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/GGI_ACCEL/")
#create_default_target_launcher(GGI_ACCEL WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/GGI_ACCEL/")

###############################################################################

SOURCE_GROUP(datasets REGULAR_EXPRESSION ".*/.dat$" )

###############################################################################


