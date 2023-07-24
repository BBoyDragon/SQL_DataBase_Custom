
#include "BDModel.h"
#include "Observing.h"
#include "StringTools.h"
#include "WhereSubController.h"
#ifndef LABWORK_12_BBOYDRAGON_DELETEFROMOBSERVER_H
#define LABWORK_12_BBOYDRAGON_DELETEFROMOBSERVER_H


class DeleteFromObserver: public IObserver {
private:

    BDModel *_model;


public:
    DeleteFromObserver(BDModel &model) {
        _model = &model;
    }

    DeleteFromObserver() {}

    void Update(SQLModel &model) override {
        std::string tmp = model.find("delete from");
        if (tmp != "null") {
            std::string name_table;
            tmp.erase(0, 12);
            name_table = tmp.substr(0, tmp.find(' '));
            tmp.erase(0, tmp.find(' ') + 1);
            if (name_table[0] == '"') {
                name_table = name_table.substr(1, name_table.size() - 2);
            }

            DataTable* curTab=&_model->GetTables()[name_table];
            if(curTab== nullptr){
                std::cout << "don't find table" << std::endl;
            }

            std::transform(tmp.begin(), tmp.end(),tmp.begin(), tolower);
            if (tmp.find("where") == std::string::npos) {
                curTab->Delete();
            }else {
                tmp.erase(0, tmp.find("where") + 6);
                WhereSubController where(tmp,curTab , Edelete);
            }

        }
    };
};


#endif //LABWORK_12_BBOYDRAGON_DELETEFROMOBSERVER_H
