//#pragma once
#include "Observing.h"
#include "vector"
#include "string"
#include "BDModel.h"
#include "CreateTableObserver.h"
#include "InsertObserver.h"
#include "DropTableObserver.h"
#include "DeleteFromObserver.h"
#include "UpdateObserver.h"
#include "SelectObserver.h"
class BDController {
private:
    CreateTableObserver _createTable;
    InsertObserver _insert;
    DropTableObserver _drop;
    DeleteFromObserver _delete;
    UpdateObserver _update;
    SelectObserver _select;
    BDModel _model;
public:
    BDController(){
        _createTable= CreateTableObserver(_model);
        _insert= InsertObserver(_model);
        _drop= DropTableObserver(_model);
        _delete=DeleteFromObserver(_model);
        _update= UpdateObserver(_model);
        _select = SelectObserver(_model);
    }

    CreateTableObserver& GetCreateTableObserver(){
        return _createTable;
    }
    InsertObserver& GetInsertObserver(){
        return _insert;
    }
    DropTableObserver& GetDropTableObserver(){
        return _drop;
    }
    DeleteFromObserver& GetDeleteFromObserver(){
        return _delete;
    }
    UpdateObserver& GetUodateObserver(){
        return _update;
    }
    SelectObserver& GetSelectObserver(){
        return _select;
    }


};

