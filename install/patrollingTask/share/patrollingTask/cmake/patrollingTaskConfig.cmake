# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_patrollingTask_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED patrollingTask_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(patrollingTask_FOUND FALSE)
  elseif(NOT patrollingTask_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(patrollingTask_FOUND FALSE)
  endif()
  return()
endif()
set(_patrollingTask_CONFIG_INCLUDED TRUE)

# output package information
if(NOT patrollingTask_FIND_QUIETLY)
  message(STATUS "Found patrollingTask: 0.0.0 (${patrollingTask_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'patrollingTask' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${patrollingTask_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(patrollingTask_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${patrollingTask_DIR}/${_extra}")
endforeach()
