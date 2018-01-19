#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::NetSSL" for configuration "Release"
set_property(TARGET Poco::NetSSL APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Poco::NetSSL PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libPocoNetSSL.50.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libPocoNetSSL.50.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Poco::NetSSL )
list(APPEND _IMPORT_CHECK_FILES_FOR_Poco::NetSSL "${_IMPORT_PREFIX}/lib/libPocoNetSSL.50.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
