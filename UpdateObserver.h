
#include "BDModel.h"
#include "Observing.h"
#include "StringTools.h"
#include "WhereSubController.h"
#ifndef LABWORK_12_BBOYDRAGON_UPDATEOBSERVER_H
#define LABWORK_12_BBOYDRAGON_UPDATEOBSERVER_H


class UpdateObserver: public IObserver{

private:

    BDModel *_model;

public:
    UpdateObserver(BDModel &model) {
        _model = &model;
    }

    UpdateObserver() {}

    void Update(SQLModel &model) override {
        std::string tmp = model.find("update");
        if (tmp != "null") {
            std::string nameTable;
            tmp.erase(0, 7);
            nameTable = tmp.substr(0, tmp.find(' '));
            if (nameTable[0] == '"') {
                nameTable = nameTable.substr(1, nameTable.size() - 2);
            }
            DataTable* data =&_model->GetTables()[nameTable];
            std::transform(tmp.begin(), tmp.end(),tmp.begin(), tolower);
            if (tmp.find("where") == std::string::npos) {
                std::cout << "Update Error" << std::endl;
            }
             WhereSubController(tmp, data, Eupdate);



        }
    };


};


#endif //LABWORK_12_BBOYDRAGON_UPDATEOBSERVER_H
