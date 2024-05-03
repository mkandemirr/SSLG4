set(headers ${CMAKE_CURRENT_SOURCE_DIR}/include/FileReader.hh 
            ${CMAKE_CURRENT_SOURCE_DIR}/include/OpticalSurfaceMessenger.hh
            ${CMAKE_CURRENT_SOURCE_DIR}/include/MaterialPropertiesTable.hh           
            ${CMAKE_CURRENT_SOURCE_DIR}/include/VMaterialBuilder.hh
            ${CMAKE_CURRENT_SOURCE_DIR}/include/MaterialPropertiesTableMessenger.hh  
            ${CMAKE_CURRENT_SOURCE_DIR}/include/VMaterialFactory.hh
            ${CMAKE_CURRENT_SOURCE_DIR}/include/OpticalSurface.hh 
            ${CMAKE_CURRENT_SOURCE_DIR}/include/ScintillatorBuilder.hh   
            )
            
set(sources ${CMAKE_CURRENT_SOURCE_DIR}/src/FileReader.cc 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/OpticalSurfaceMessenger.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/MaterialPropertiesTable.cc           
            ${CMAKE_CURRENT_SOURCE_DIR}/src/VMaterialBuilder.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/MaterialPropertiesTableMessenger.cc  
            ${CMAKE_CURRENT_SOURCE_DIR}/src/VMaterialFactory.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/OpticalSurface.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ScintillatorBuilder.cc
            
            )

add_library(OPSim ${sources} ${headers})

target_include_directories(OPSim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(OPSim PRIVATE ${Geant4_LIBRARIES})        
