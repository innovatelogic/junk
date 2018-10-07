# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

# This module is shared by multiple languages; use include blocker.
if(__COMPILER_CRAY)
  return()
endif()
set(__COMPILER_CRAY 1)

include(Compiler/CMakeCommonCompilerMacros)
