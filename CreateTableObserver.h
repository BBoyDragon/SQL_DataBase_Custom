

#ifndef LABWORK_12_BBOYDRAGON_CREATETABLEOBSERVER_H
#define LABWORK_12_BBOYDRAGON_CREATETABLEOBSERVER_H

#include "iostream"

#include "StringTools.h"

#include "string"
#include "Observing.h"
#include "DataTable.h"
#include "BDModel.h"

class CreateTableObserver : public IObserver {
private:

    void CheckPrimaryKey(std::string& request, DataTable& table, std::string& column_name) {
        if (request.find("primary key") != std::string::npos) {
            table.SetPrimaryKey( column_name);
            return;
        }
    }
    void CheckForeignKey(std::string& request, DataTable& table, std::string& columnName) {
        if (request.find("foreign key") != std::string::npos) {
            table.GetForeignKey().columnName = columnName;
            request.erase(0, request.find("references") + 10);
            std::string foreignTable = request.substr(0, request.find('('));
            SpaceDelete(foreignTable);
            request.erase(0, request.find('(') + 1);
            std::string foreignColumn = request.substr(0, request.find(')'));
            table.GetForeignKey().foreignTableName = foreignTable;
            table.GetForeignKey().foreignColumnName = foreignColumn;
            table.GetForeignKey().columnName = columnName;
            return;
        }
    }

    void CheckType(std::string& columnType, std::string& columnName, DataTable& table) {
        if (columnType.find("integer") != std::string::npos) {
            table.GetTypes().emplace_back(columnName, EInteger);
        } else if (columnType.find("varchar") != std::string::npos) {
            table.GetTypes().emplace_back(columnName, EVarChar);
        } else if (columnType.find("float") != std::string::npos) {
            table.GetTypes().emplace_back(columnName, EFloat);
        } else if (columnType.find("double") != std::string::npos) {
            table.GetTypes().emplace_back(columnName, EDouble);
        } else if (columnType.find("bool") != std::string::npos) {
            table.GetTypes().emplace_back(columnName, EBool);
        } else {
            std::cout << "invalid request" << '\n';
            //mistake_ = true;
            return;
        }
        CheckQuestionMark(table.GetTypes().back().first);
    }

    void CheckNull(std::string& request, DataTable table, std::string& columnName) {
        if (request.find("not null") != std::string::npos) {
            table.GetCanBeNull()[columnName] = true;
        }
    }

    BDModel* _model;

public:


    CreateTableObserver(BDModel& model){
        _model=&model;
    }

    CreateTableObserver() {}

     void Update(SQLModel &model) override {
        std::string tmp= model.find("create table");
        if (tmp!="null") {
            DataTable data = DataTable();
            tmp.erase(0, 13);
            std::string a;
            a=std::string_view(tmp.data(), tmp.find('(') - 1);
            data.SetName(a);
            CheckQuestionMark(data.GetName());

            std::string meta;
            meta = std::string_view(tmp.data() + tmp.find('(') + 1,tmp.rfind(')') - tmp.find('(') - 1);
            std::vector<std::string> column_types;
            Split(meta, ',', column_types);

            std::string columnName;
            std::string columnType;
            for (int i = 0; i < column_types.size(); i++) {
                columnType = column_types[i].substr(column_types[i].find(' ') + 1);
                columnName = std::string_view(column_types[i].data(), column_types[i].find(' '));


                column_types[i].erase(0, columnName.size() + 1);
                CheckQuestionMark(columnName);

                std::transform(columnType.begin(),columnType.end(),columnType.begin(), tolower);

                CheckType(columnType, columnName, data);
                column_types[i].erase(0, column_types[i].find(' ') + 1);
                columnType.erase(0, columnType.find(' ') + 1);
                if (!columnType.empty()) {
                    CheckPrimaryKey(columnType, data, columnName);
                    CheckForeignKey(columnType,data,columnName);
                    CheckNull(columnType, data, columnName);
                }
            }
            _model->GetTables()[data.GetName()]=data;
        }
    };
};


#endif //LABWORK_12_BBOYDRAGON_CREATETABLEOBSERVER_H
