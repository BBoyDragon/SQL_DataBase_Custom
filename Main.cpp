#include "iostream"
#include "BDController.h"
#include "SQLController.h"

int main() {
    BDController bdController;
    SQLController sqlController;

    sqlController.AddObserver(&bdController.GetCreateTableObserver());
    sqlController.AddObserver(&bdController.GetInsertObserver());
    sqlController.AddObserver(&bdController.GetDropTableObserver());
    sqlController.AddObserver(&bdController.GetDeleteFromObserver());
    sqlController.AddObserver(&bdController.GetUodateObserver());
    sqlController.AddObserver(&bdController.GetSelectObserver());

    sqlController.UpdateSQLModel("create table use (\n"
                                 "    Age integer PRIMARY KEY NOT NULL,\n"
                                 "    name varchar(255),\n"
                                 "    www float,\n"
                                 "    qqq double,\n"
                                 "    bbb bool\n"
                                 "    );");

    sqlController.UpdateSQLModel("insert into use  values (19, Ivan, 1.2, 1.2, true);");

    sqlController.UpdateSQLModel("insert into use (name, Age, www, qqq, bbb) values (Ivan, 18, 1.2, 1.2, false);");

    sqlController.UpdateSQLModel("update use set name = ANANAS where Age = 19;");

    sqlController.UpdateSQLModel("select * from use where Age = 19;");

    sqlController.UpdateSQLModel("delete from use where Age = 19;");

    sqlController.UpdateSQLModel("drop table use;");
}