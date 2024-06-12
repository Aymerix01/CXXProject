
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.hpp *.cpp)

add_library(src ${SOURCES} )
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC pugixml sfml-graphics sfml-audio)