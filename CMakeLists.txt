cmake_minimum_required(VERSION 3.9)
project(kingofnewyork)

set(CMAKE_CXX_STANDARD 17)

add_executable(kingofnewyork main.cpp diceroller.cpp player.cpp game.cpp helper.cpp common.cpp card.cpp tile.cpp map.cpp borough.cpp rolldicestrategy.cpp resolvedicestrategy.cpp movestrategy.cpp buycardsstrategy.cpp subject.cpp gameview.cpp stateview.cpp)

target_link_libraries(kingofnewyork stdc++fs)
