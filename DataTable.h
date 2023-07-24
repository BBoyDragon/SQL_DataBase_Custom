
#pragma once
#include "vector"
#include "string"
#include "iostream"
#include "unordered_map"
#include "Visiting.h"
struct ForeignKey {
    std::string foreignTableName = " ";
    std::string columnName = " ";
    std::string foreignColumnName = " ";
};

class DataTable {
private:
    std::vector<std::pair<std::string,Types>>_colonTypes;
    std::unordered_map<std::string,std::vector<IValue*>> _colons;
    std::string _name;

    std::string _primaryKey;
    ForeignKey _foreignKey;

    std::unordered_map<std::string, bool> _canBeNull;
    int _size=0;
public:

    void SetSize(int size){
        _size=size;
    }
    int GetSize(){
        return _size;
    }

    std::unordered_map<std::string,bool>& GetCanBeNull(){
        return _canBeNull;
    }

    ForeignKey& GetForeignKey(){
        return _foreignKey;
    }

    std::string& GetName(){
        return _name;
    }
    void SetName(std::string t){
        _name=t;
    }
    std::string& GetPrimaryKey(){
        return _primaryKey;
    }
    void SetPrimaryKey(std::string t){
        _primaryKey=t;
    }

    std::unordered_map<std::string,std::vector<IValue*>>& GetColons(){
        return _colons;
    }

    std::vector<std::pair<std::string,Types>>& GetTypes(){
        return _colonTypes;
    }



    void Delete() {
        for (auto &colon: _colons) {
            for (auto &value: colon.second) {
                delete value;
            }
        }
        _colons.clear();
        _size=0;
    }
    void Delete(int row) {
        for (auto& i : _colons) {
            delete i.second[row];
            i.second.erase(i.second.begin() + row);
        }
        _size--;
    }


};

