cmake_minimum_required(VERSION 3.23)
project(labwork_12_BBoyDragon)

set(CMAKE_CXX_STANDARD 20)

#include_directories(.)

add_executable(labwork_12_BBoyDragon
        BDController.cpp
        BDController.h
        BDModel.cpp
        BDModel.h
        Main.cpp
        SQLModel.h
        SQLController.h
        Visiting.h
        Observing.h
        StringTools.h
        CreateTableObserver.h
        CreateTableObserver.cpp
        DataTable.h
        DataTable.cpp
        JsonController.cpp
        JsonController.h
        InsertObserver.cpp
        InsertObserver.h
        )
