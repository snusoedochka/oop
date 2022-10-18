cmake_minimum_required(VERSION 3.21)
project(oop_lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp cell_object.cpp cell_object_view.cpp field_view.cpp field.cpp cells/cell_view.cpp cells/cell.cpp cells/cell_entrance.cpp cells/cell_exit.cpp actors/actor.cpp actors/player.cpp actors/enemy.cpp actors/enemies/acolyte.cpp actions/action_combat.cpp actions/action_shoot_ballistic.cpp actions/action_move.cpp actors/item.cpp game_conditions/exit_condition.cpp game_conditions/player_death_condition.cpp)
