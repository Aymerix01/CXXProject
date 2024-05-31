add_executable(simpleGame
  Source/Game.cpp 
  Source/Main.cpp
 "Include/Deck.h" "Include/Player.h" "Include/Card.h" "Source/Player.cpp" "Source/Deck.cpp" "Source/Card.cpp")

target_include_directories(simpleGame
 PRIVATE
  Include
)

target_link_libraries(simpleGame PUBLIC sfml-graphics)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})