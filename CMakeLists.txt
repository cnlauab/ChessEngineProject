# CMakeList.txt : CMake project for ChessEngineProject, include source and define
# project specific logic here.
#
set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required (VERSION 3.8)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ChessEngineProject")

# Add source to this project's executable.
add_executable (ChessEngineProject "ChessEngineProject.cpp" "ChessEngineProject.h" "BoardRenderer.cpp" "BoardRenderer.h" "Position.h" "Position.cpp" "State.cpp" "State.h" "Parser.cpp" "Parser.h" "Move.cpp" "Move.h" "Validator.cpp" "Validator.h" "MoveGenerator.cpp" "MoveGenerator.h" "ChessUtil.h" "ChessUtil.cpp" "LegalChecker.cpp" "LegalChecker.h" "Debug.cpp" "Debug.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ChessEngineProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
