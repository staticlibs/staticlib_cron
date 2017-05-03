# Copyright 2016, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

# toolchain setup
set ( STATICLIB_TOOLCHAIN linux_amd64_gcc CACHE STRING "toolchain triplet" )
if ( NOT DEFINED STATICLIB_CMAKE )
    set ( STATICLIB_CMAKE ${CMAKE_CURRENT_LIST_DIR}/../../cmake CACHE INTERNAL "" )    
endif ( )
set ( CMAKE_TOOLCHAIN_FILE ${STATICLIB_CMAKE}/toolchains/${STATICLIB_TOOLCHAIN}.cmake CACHE INTERNAL "" )

# project
project ( staticlib_cron_test CXX C )
include ( ${STATICLIB_CMAKE}/staticlibs_common.cmake )
staticlib_enable_deplibs_cache ( )

# dependencies
if ( NOT DEFINED STATICLIB_DEPS )
    set ( STATICLIB_DEPS ${CMAKE_CURRENT_LIST_DIR}/../../ CACHE INTERNAL "" )    
endif ( )
staticlib_add_subdirectory ( ${STATICLIB_DEPS}/staticlib_config )
staticlib_add_subdirectory ( ${STATICLIB_DEPS}/staticlib_support )
staticlib_add_subdirectory ( ${STATICLIB_DEPS}/staticlib_pimpl )
staticlib_add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/../../staticlib_cron )
set ( ${PROJECT_NAME}_DEPS 
        staticlib_config
        staticlib_cron )
staticlib_pkg_check_modules ( ${PROJECT_NAME}_DEPS_PC REQUIRED ${PROJECT_NAME}_DEPS )

# tests
set ( ${PROJECT_NAME}_TEST_INCLUDES ${${PROJECT_NAME}_DEPS_PC_INCLUDE_DIRS} )
set ( ${PROJECT_NAME}_TEST_LIBS ${${PROJECT_NAME}_DEPS_PC_LIBRARIES} )
set ( ${PROJECT_NAME}_TEST_OPTS ${${PROJECT_NAME}_DEPS_PC_CFLAGS_OTHER} )
staticlib_enable_testing ( ${PROJECT_NAME}_TEST_INCLUDES ${PROJECT_NAME}_TEST_LIBS ${PROJECT_NAME}_TEST_OPTS )
# ccronexpr_test
if ( TARGET CronExpression_test )
    add_executable ( ccronexpr_test 
        ${CMAKE_CURRENT_LIST_DIR}/../ccronexpr/ccronexpr_test.c
        ${CMAKE_CURRENT_LIST_DIR}/../ccronexpr/ccronexpr.c )
    target_include_directories ( ccronexpr_test BEFORE PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../ccronexpr )
    set_target_properties ( ccronexpr_test PROPERTIES FOLDER "test" )
    if ( DEFINED CMAKE_MEMORYCHECK_COMMAND )
        add_test ( ccronexpr_test
                ${CMAKE_MEMORYCHECK_COMMAND} ${CMAKE_MEMORYCHECK_COMMAND_OPTIONS} 
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ccronexpr_test )
    else ( )
        add_test ( ccronexpr_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ccronexpr_test )
    endif ( )
endif ( )
