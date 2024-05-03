set(headers 
 ${CMAKE_CURRENT_SOURCE_DIR}/include/EJ426Builder.hh 
 ${CMAKE_CURRENT_SOURCE_DIR}/include/OrganicScintillatorFactory.hh  
 ${CMAKE_CURRENT_SOURCE_DIR}/include/InorganicScintillatorFactory.hh
)  
             
set(sources
 ${CMAKE_CURRENT_SOURCE_DIR}/src/EJ426Builder.cc      
 ${CMAKE_CURRENT_SOURCE_DIR}/src/OrganicScintillatorFactory.cc     
 ${CMAKE_CURRENT_SOURCE_DIR}/src/InorganicScintillatorFactory.cc  
)  

set(libName sslg4) #do not change!

add_library(${libName} ${headers} ${sources})
target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${libName} PRIVATE OPSim ${Geant4_LIBRARIES})

file(GLOB_RECURSE filePathList_data #results variable
                  RELATIVE # keyword to specify relative path
                  ${CMAKE_CURRENT_SOURCE_DIR} # relative to this path
                  data/* # global expression. all files under this directory
                  )
                  
file(GLOB_RECURSE filePathList_macros 
                  RELATIVE 
                  ${CMAKE_CURRENT_SOURCE_DIR} 
                  macros/*
                  )
                  
#message("Relative file path list (relative path is specified with " 
#        "the RELATIVE keyword) : ${filePathList_data}"
#       )

foreach(_filePath ${filePathList_data} ${filePathList_macros})

#message("Copying file from ${CMAKE_CURRENT_SOURCE_DIR}/${_filePath} "
#        "to ${CMAKE_BINARY_DIR}/${libName}/${_filePath}....")

#Copy a file to another location and modify its contents
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${_filePath} #input file path
  ${CMAKE_BINARY_DIR}/${libName}/${_filePath} # output file path, do not change!
  # since macro files read from this path!
  COPYONLY
  )

endforeach()
