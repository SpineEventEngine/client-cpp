find_package(Doxygen)
set(DOXYGEN_JAVADOC_AUTOBRIEF TRUE)
doxygen_add_docs(docs ${SOURCE_LIB_FILES} ${SOURCE_HEADER_FILES})
