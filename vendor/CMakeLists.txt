cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(vendor NONE)

include("${CMAKE_CURRENT_LIST_DIR}/cpm-cmake-package-lock/vendor/CPM.cmake")

CPMUsePackageLock("${CMAKE_CURRENT_LIST_DIR}/cpm-cmake-package-lock/cmake/package-lock.cmake")

set(VENDOR_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor")
file(MAKE_DIRECTORY "${VENDOR_INCLUDE_DIR}")

include("${CMAKE_CURRENT_LIST_DIR}/cpm-cmake-package-lock/cmake/common.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cpm-cmake-package-lock/cmake/dependency.cmake")

copy_vendor_package(pqrs_cf_array)
copy_vendor_package(pqrs_cf_dictionary)
copy_vendor_package(pqrs_cf_number)
copy_vendor_package(pqrs_cf_string)
copy_vendor_package(pqrs_hash)
copy_vendor_package(pqrs_hid)
copy_vendor_package(pqrs_osx_iokit_types)
copy_vendor_package(pqrs_osx_kern_return)
copy_vendor_package(ut)
