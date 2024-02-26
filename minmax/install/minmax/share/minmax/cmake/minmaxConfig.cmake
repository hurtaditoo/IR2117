# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_minmax_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED minmax_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(minmax_FOUND FALSE)
  elseif(NOT minmax_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(minmax_FOUND FALSE)
  endif()
  return()
endif()
set(_minmax_CONFIG_INCLUDED TRUE)

# output package information
if(NOT minmax_FIND_QUIETLY)
  message(STATUS "Found minmax: 0.0.0 (${minmax_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'minmax' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${minmax_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(minmax_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${minmax_DIR}/${_extra}")
endforeach()
