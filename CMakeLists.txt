cmake_minimum_required(VERSION 3.24)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordManager main.cpp Encryption/Encryption.cpp Encryption/Encryption.h PasswordManager/PasswordManager.cpp PasswordManager/PasswordManager.h dataOperations/dataOperations.cpp dataOperations/dataOperations.h operationsWithPassword/passwordOperations.cpp operationsWithPassword/passwordOperations.h additionalMethods/aditionalMethods.cpp additionalMethods/aditionalMethods.h runProgramme/runProgramme.cpp runProgramme/runProgramme.h runProgramme/runProgramme.cpp password/Password.hpp)
