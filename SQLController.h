#pragma once
#include "vector"
#include "string"
#include "StringTools.h"
#include "Observing.h"

class SQLController: public IObservable{
private:
    std::vector<IObserver*> _observers;
    SQLModel _model;
public:

    void UpdateSQLModel(std::string request){
        _model.clean();
        request= DeleteSpace(request);
        for (int i = 0; i < request.size(); i++) {
            if (request[i] == ';') {
                _model.add(request.substr(0, i));
                request.erase(0, i + 1);
                i = 0;
            }
        }
        Notify();
    }


    void AddObserver(IObserver* observer) override{
        _observers.emplace_back(observer);
    }
    virtual void RemoveObserver(IObserver* observer) override {
        //delete
    }
    virtual void Notify() override{
        for (auto& observer : _observers) {
            observer->Update(_model);
        }
    }


};

