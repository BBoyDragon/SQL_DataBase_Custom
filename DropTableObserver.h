
#include "BDModel.h"
#include "Observing.h"
#include "StringTools.h"

#ifndef LABWORK_12_BBOYDRAGON_DROPTABLEOBSERVER_H
#define LABWORK_12_BBOYDRAGON_DROPTABLEOBSERVER_H


class DropTableObserver:public IObserver {
private:

    BDModel *_model;

public:
    DropTableObserver(BDModel &model) {
        _model = &model;
    }

    DropTableObserver() {}

    void Update(SQLModel &model) override {
        std::string tmp = model.find("drop table");
        if (tmp != "null") {
            std::string name_table;
            if (tmp.find('"') != std::string::npos) {
                name_table = tmp.substr(tmp.find('"') + 1, tmp.rfind('"') - tmp.find('"') - 1);
            } else {
                name_table =tmp.substr(tmp.rfind(' ') + 1, tmp.size() - tmp.rfind(' ') - 1);
            }
            _model->GetTables().erase(name_table);
        }
    };

};


#endif //LABWORK_12_BBOYDRAGON_DROPTABLEOBSERVER_H
