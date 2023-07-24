//
// Created by Admin on 07.06.2023.
//
#include "BDModel.h"
#include "Observing.h"
#include "StringTools.h"

#ifndef LABWORK_12_BBOYDRAGON_INSERTOBSERVER_H
#define LABWORK_12_BBOYDRAGON_INSERTOBSERVER_H


class InsertObserver : public IObserver {
private:

    std::vector<std::string> ParseValue(std::string request) {
        std::vector<std::string> values;
        std::string value;
        int index = 0;
        for (int i = 0; i < request.size(); i++) {
            if (request[i] == ',') {
                value = request.substr(index, i - index);
                values.push_back(value);
                index = i + 1;
            }
        }
        value = request.substr(index, request.size() - index);
        values.push_back(value);
        return values;
    }

    BDModel *_model;


    void ParseValueByType(std::string &valueForType, DataTable *table, int j) {
        if (table->GetTypes()[j].second == EInteger) {
            IValue *value = new IntegerValue(std::stoi(valueForType));
            table->GetColons()[table->GetTypes()[j].first].push_back(value);
            value = nullptr;
        } else if (table->GetTypes()[j].second == EDouble) {
            auto value = new DoubleValue(std::stod(valueForType));
            table->GetColons()[table->GetTypes()[j].first].push_back(value);
            value = nullptr;
        } else if (table->GetTypes()[j].second == EFloat) {
            auto value = new FloatValue(std::stof(valueForType));
            table->GetColons()[table->GetTypes()[j].first].push_back(value);
            value = nullptr;
        } else if (table->GetTypes()[j].second == EBool) {
            if (valueForType == "true") {
                valueForType = "1";
            } else if (valueForType == "false") {
                valueForType = "0";
            }
            auto value = new BooleanValue(std::stoi(valueForType));
            table->GetColons()[table->GetTypes()[j].first].push_back(value);
            value = nullptr;
        } else if (table->GetTypes()[j].second == EVarChar) {
            auto value = new VarcharValue(valueForType);
            table->GetColons()[table->GetTypes()[j].first].push_back(value);
            value = nullptr;

        }
    }

public:
    InsertObserver(BDModel &model) {
        _model = &model;
    }

    InsertObserver() {}

    void Update(SQLModel &model) override {
        std::string tmp = model.find("insert into");
        if (tmp != "null") {
            bool check = false;
            for (auto tab: _model->GetTables()) {
                if (tmp.find(tab.second.GetName()) != std::string::npos) {
                    DataTable *curTab = &tab.second;
                    curTab->SetSize(curTab->GetSize() + 1);
                    std::string WRRequest = tmp;
                    std::transform(WRRequest.begin(), WRRequest.end(), WRRequest.begin(), tolower);
                    if (WRRequest.find("values") != std::string::npos) {
                        if (tmp[WRRequest.find("values") - 2] ==
                            tmp[tmp.rfind(curTab->GetName()) + curTab->GetName().size() - 1]) { ;
                            std::vector<std::string> values = ParseValue(
                                    tmp.substr(tmp.find('(') + 1, tmp.find(')') - tmp.find('(') - 1));
                            SpaceDelete(values);
                            std::string check_value;
                            for (int j = 0; j < values.size(); j++) {
                                if (curTab->GetTypes()[j].first == curTab->GetPrimaryKey()) {
                                    for (int k = 0; k < curTab->GetColons()[curTab->GetPrimaryKey()].size(); k++) {
                                        curTab->GetColons()[curTab->GetPrimaryKey()][k]->PutInColumn(
                                                check_value);
                                        if (check_value == ' ' + values[j]) {
                                            std::cout << "primary key is not unique" << std::endl;
                                            exit(0);
                                        }
                                        check_value.clear();
                                    }
                                }
                                ParseValueByType(values[j], curTab, j);
                            }
                        } else {
                            std::vector<std::string> columns = ParseValue(
                                    tmp.substr(tmp.find('(') + 1, tmp.find(')') - tmp.find('(') - 1));
                            SpaceDelete(columns);
                            std::vector<std::string> values = ParseValue(
                                    tmp.substr(tmp.rfind('(') + 1, tmp.rfind(')') - tmp.rfind('(') - 1));
                            SpaceDelete(values);
                            for (int i = 0; i < columns.size(); i++) {
                                CheckQuestionMark(columns[i]);
                            }
                            std::string check_value;
                            for (int k = 0; k < curTab->GetTypes().size(); k++) {
                                for (int j = 0; j < columns.size(); j++) {
                                    if (columns[j] == curTab->GetTypes()[k].first) {
                                        if (columns[j] ==
                                            curTab->GetPrimaryKey()) {
                                            for (int m = 0; m <
                                                            curTab->GetColons()[curTab->GetPrimaryKey()].size(); m++) {
                                                curTab->GetColons()[curTab->GetPrimaryKey()][m]->PutInColumn(
                                                        check_value);
                                                if (check_value == ' ' + values[j]) {
                                                    std::cout << "primary key is not unique" << std::endl;
                                                    exit(0);
                                                } else {
                                                    check_value.clear();
                                                }
                                            }
                                            ParseValueByType(values[j], curTab, k);
                                        } else {
                                            check_value.clear();
                                            ParseValueByType(values[j], curTab, k);
                                        }
                                    }
                                }
                            }
                            for (int i = 0; i < curTab->GetTypes().size(); i++) {
                                if (curTab->GetColons()[curTab->GetTypes()[i].first].size() < curTab->GetSize()) {
                                    if (&curTab->GetCanBeNull()[curTab->GetTypes()[i].first]) {
                                        std::cout << "not null" << std::endl;
                                        exit(0);
                                    } else
                                        curTab->GetColons()[curTab->GetTypes()[i].first].emplace_back(new NullValue);
                                }
                            }
                        }
                    }
                    _model->GetTables()[tab.first] = *curTab;
                }
            }

        } else {
        }
    };
};


#endif //LABWORK_12_BBOYDRAGON_INSERTOBSERVER_H
