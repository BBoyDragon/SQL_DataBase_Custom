#pragma once
#include "SQLModel.h"

class IObserver{
public:
    virtual void Update(SQLModel& model) = 0;
};

 class IObservable{
public:
    virtual void AddObserver(IObserver* observer) =0;
    virtual void RemoveObserver(IObserver* observer) =0;
    virtual void Notify()=0;
};