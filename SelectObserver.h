
#include "BDModel.h"
#include "Observing.h"
#include "StringTools.h"
#include "WhereSubController.h"
#ifndef LABWORK_12_BBOYDRAGON_SELECTOBSERVER_H
#define LABWORK_12_BBOYDRAGON_SELECTOBSERVER_H


class SelectObserver : public IObserver{

private:

    BDModel *_model;

public:
    SelectObserver(BDModel &model) {
        _model = &model;
    }

    SelectObserver() {}

    void Update(SQLModel &model) override {
        std::string tmp = model.find("select");
        if (tmp != "null") {

            if (tmp.find("join") != std::string::npos) {
                std::string leftTable;
                std::string rightTable;
                leftTable = tmp.substr(tmp.find("from") + 5,tmp.find("join") - tmp.find("from")
                                            - 6);
                if(leftTable.find("left") != std::string::npos){
                    leftTable = leftTable.substr(0, leftTable.find("left") - 1);
                }
                if(leftTable.find("right") != std::string::npos){
                    leftTable = leftTable.substr(0, leftTable.find("right") - 1);
                }
                rightTable = tmp.substr(tmp.find("join") + 5,tmp.find("on") - tmp.find("join")- 6);
                std::cout << leftTable << " " << rightTable << std::endl;
                CheckQuestionMark(leftTable);
                CheckQuestionMark(rightTable);
                DataTable* left = &_model->GetTables()[leftTable];
                DataTable* right = &_model->GetTables()[rightTable];

                //create.JoinTable(request, left, right);
                return;
            } else {
                std::string nameTable;
                if (tmp.find("where") == std::string::npos) {
                    nameTable = tmp.substr(tmp.find("from") + 5, tmp.size() - (tmp.find("from") + 5));
                    tmp.erase(0, 7);
                    CheckQuestionMark(nameTable);
                    DataTable *data = &_model->GetTables()[nameTable];
                    std::transform(tmp.begin(), tmp.end(),tmp.begin(), tolower);
                    if (tmp.find('*') != std::string::npos && tmp.find("where") == std::string::npos) {
                        //table->PrintTable();
                        return;
                    } else if (tmp.find('*') != std::string::npos && tmp.find("where") != std::string::npos) {
                        WhereSubController whereController(tmp, data, Eselect);
                        return;
                    }
                    if (tmp.find("where") == std::string::npos) {
                        std::string colonName = tmp.substr(0, tmp.find("from"));
                        std::vector<std::string> colons;
                        Split(colonName, ',', colons);
                        SpaceDelete(colons);
                        //table->PrintTable(colons);
                    } else {
                        WhereSubController whereController(tmp, data, Eselect);
                    }

                } else {
                    nameTable = tmp.substr(tmp.find("from") + 5, tmp.find("where") - tmp.find("from") - 6);
                    tmp.erase(0, 7);
                    CheckQuestionMark(nameTable);
                    DataTable *data = &_model->GetTables()[nameTable];

                    std::transform(tmp.begin(), tmp.end(),tmp.begin(), tolower);
                    if (tmp.find('*') != std::string::npos && tmp.find("where") == std::string::npos) {
                        //table->PrintTable();
                        return;
                    } else if (tmp.find('*') != std::string::npos && tmp.find("where") != std::string::npos) {
                        WhereSubController whereController(tmp, data, Eselect);
                        return;
                    }
                    if (tmp.find("where") == std::string::npos) {
                        std::string colonName = tmp.substr(0, tmp.find("from"));
                        std::vector<std::string> colons;
                        Split(colonName, ',', colons);
                        SpaceDelete(colons);
                        //table->PrintTable(colons);
                    } else {
                        WhereSubController whereController(tmp, data, Eselect);
                    }
                }
            }
        }
    };
};


#endif //LABWORK_12_BBOYDRAGON_SELECTOBSERVER_H
