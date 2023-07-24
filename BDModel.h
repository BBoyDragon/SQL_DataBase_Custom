
#pragma once
#include "vector"
#include "string"
#include "iostream"
#include "unordered_map"
#include "DataTable.h"
#ifndef LABWORK_12_BBOYDRAGON_BDMODEL_H
#define LABWORK_12_BBOYDRAGON_BDMODEL_H


class BDModel {
private:
    std::unordered_map<std::string,DataTable> _tables;

public:

    std::unordered_map<std::string,DataTable>& GetTables(){

        return _tables;
    }



};


#endif //LABWORK_12_BBOYDRAGON_BDMODEL_H
