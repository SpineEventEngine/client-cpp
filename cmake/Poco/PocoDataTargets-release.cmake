#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::Data" for configuration "Release"
set_property(TARGET Poco::Data APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Poco::Data PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libPocoData.50.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libPocoData.50.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Poco::Data )
list(APPEND _IMPORT_CHECK_FILES_FOR_Poco::Data "${_IMPORT_PREFIX}/lib/libPocoData.50.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
