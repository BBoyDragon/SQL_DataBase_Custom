
#include "DataTable.h"
enum Types{
    EInteger,
    EVarChar,
    EBool,
    EFloat,
    EDouble,
    Null

};

class IVisitor {
public:
    virtual bool Compare(std::string &stringValue, const class IntegerValue *value) { return false; }

    virtual bool Compare(std::string &stringValue, const class DoubleValue *value) { return false; }

    virtual bool Compare(std::string &stringValue, const class VarcharValue *value) { return false; }

    virtual bool Compare(std::string &stringValue, const class BooleanValue *value) { return false; }

    virtual bool Compare(std::string &stringValue, const class FloatValue *value) { return false; }

    virtual bool CompareLess(std::string &stringValue, const IntegerValue *value) { return false; }

    virtual bool CompareLess(std::string &stringValue, const DoubleValue *value) { return false; }

    virtual bool CompareLess(std::string &stringValue, const VarcharValue *value) { return false; }

    virtual bool CompareLess(std::string &stringValue, const BooleanValue *value) { return false; }

    virtual bool CompareLess(std::string &stringValue, const FloatValue *value) { return false; }

    virtual bool CompareMore(std::string &stringValue, const IntegerValue *value) { return false; }

    virtual bool CompareMore(std::string &stringValue, const DoubleValue *value) { return false; }

    virtual bool CompareMore(std::string &stringValue, const VarcharValue *value) { return false; }

    virtual bool CompareMore(std::string &stringValue, const BooleanValue *value) { return false; }

    virtual bool CompareMore(std::string &stringValue, const FloatValue *value) { return false; }

    virtual void Update(std::string &stringValue, IntegerValue *value) { return; }

    virtual void Update(std::string &stringValue, DoubleValue *value) { return; }

    virtual void Update(std::string &stringValue, VarcharValue *value) { return; }

    virtual void Update(std::string &stringValue, BooleanValue *value) { return; }

    virtual void Update(std::string &stringValue, FloatValue *value) { return; }

    IVisitor() = default;

};

class IValue {
private:

public:
    bool is_null_ = false;

    virtual Types Type() = 0;

    virtual void PutInColumn(std::string& output) = 0;

    virtual bool Accept(class IVisitor *visitor, std::string stringValue) = 0;

    virtual bool AcceptLessComp(class IVisitor *visitor, std::string stringValue) = 0;

    virtual bool AcceptMoreComp(class IVisitor *visitor, std::string stringValue) = 0;

    virtual void Update(class IVisitor *visitor, std::string stringValue) = 0;

    IValue() = default;
};


class VarcharValue : public IValue {
public:
    std::string value_;

    Types Type() override { return EVarChar; };

    void PutInColumn(std::string& output) override{
        output += " " + value_;
    };

    bool Accept(class IVisitor *visitor, std::string stringValue) override {
        return visitor->Compare(stringValue, this);
    }

    bool AcceptLessComp(class IVisitor *visitor, std::string stringValue) override {
        return visitor->CompareLess(stringValue, this);
    }

    bool AcceptMoreComp(class IVisitor *visitor, std::string stringValue) override {
        return visitor->CompareMore(stringValue, this);
    }

    void Update(class IVisitor *visitor, std::string stringValue) override {
        visitor->Update(stringValue, this);
    }

    VarcharValue(std::string value) : value_(value) {}

};


class IntegerValue : public IValue {
public:
    int value_;

    void PutInColumn(std::string& output) override{
        output += " " + std::to_string(value_);
    };

    bool Accept(class IVisitor *visitor, std::string stringValue) override {
        return visitor->Compare(stringValue, this);
    }

    bool AcceptLessComp(class IVisitor *visitor, std::string stringValue) override {
        return visitor->CompareLess(stringValue, this);
    }

    bool AcceptMoreComp(class IVisitor *visitor, std::string stringValue) override {
        return visitor->CompareMore(stringValue, this);
    }

    void Update(class IVisitor *visitor, std::string stringValue) override {
        visitor->Update(stringValue, this);
    }

    Types Type() override {
        return EInteger;
    };

    explicit IntegerValue(int value) : value_(value) {}

};


class DoubleValue : public IValue {
public:
    double value_;

    void PutInColumn(std::string& output) override{
        std::string temp = std::to_string(value_);
        temp = temp.substr(0, temp.find('.') + 2);
        output += " " + temp;
    };

    bool Accept(class IVisitor *visitor, std::string string_value) override {
        return visitor->Compare(string_value, this);
    }

    bool AcceptLessComp(class IVisitor *visitor, std::string string_value) override {
       return visitor->CompareLess(string_value, this);
    }

    bool AcceptMoreComp(class IVisitor *visitor, std::string string_value) override {
       return visitor->CompareMore(string_value, this);
    }

    void Update(class IVisitor *visitor, std::string string_value) override {
        visitor->Update(string_value, this);
    }

    explicit DoubleValue(double value) : value_(value) {}

    Types Type() override {
        return EDouble;
    }

};


class FloatValue : public IValue {
public:

    void PutInColumn(std::string& output) override{
        std::string temp = std::to_string(value_);
        temp = temp.substr(0, temp.find('.') + 2);
        output += " " + temp;
    };

    bool Accept(class IVisitor *visitor, std::string string_value) override {
       return visitor->Compare(string_value, this);
    };

    bool AcceptLessComp(class IVisitor *visitor, std::string string_value) override {
       return visitor->CompareLess(string_value, this);
    };

    bool AcceptMoreComp(class IVisitor *visitor, std::string string_value) override {
        return visitor->CompareMore(string_value, this);
    };

    void Update(class IVisitor *visitor, std::string string_value) override {
        visitor->Update(string_value, this);
    };

    float value_;

    Types Type() override {
        return EFloat;
    };


    explicit FloatValue(float value) : value_(value) {}

    FloatValue() = default;

};

class BooleanValue : public IValue {
public:
    bool value_;

    void PutInColumn(std::string& output) override{
        output += " " + std::to_string(value_);
    };
    bool Accept(class IVisitor *visitor, std::string string_value) override {
        return visitor->Compare(string_value, this);
    };

    bool AcceptLessComp(class IVisitor *visitor, std::string string_value) override {
        return  visitor->CompareLess(string_value, this);
    };

    bool AcceptMoreComp(class IVisitor *visitor, std::string string_value) override {
        return visitor->CompareMore(string_value, this);
    };

    void Update(class IVisitor *visitor, std::string string_value) override {
        visitor->Update(string_value, this);
    };

    Types Type() override {
        return EBool;
    };

    explicit BooleanValue(bool value):value_(value){};


};

class NullValue : public IValue {
public:
    std::string value = "null";
    void PutInColumn(std::string& output) override{
        output += " " + value;
    };

    bool Accept(class IVisitor *visitor, std::string string_value) override { return false; }

    bool AcceptLessComp(class IVisitor *visitor, std::string string_value) override { return false; }

    bool AcceptMoreComp(class IVisitor *visitor, std::string string_value) override { return false; }

    void Update(class IVisitor *visitor, std::string string_value) override { return; }


    Types Type() override {
        return Null;
    };

    NullValue(){
        is_null_= true;
    };


    ~NullValue() = default;
};


class VisitorInteger : public IVisitor {
public:
    bool Compare(std::string &string_value, const IntegerValue *value) override {
        return std::stoi(string_value) == value->value_;
    }

    bool CompareLess(std::string &string_value, const IntegerValue *value) override {
        return std::stoi(string_value) < value->value_;
    };

    bool CompareMore(std::string &string_value, const IntegerValue *value) override {
        return std::stoi(string_value) > value->value_;
    };

    void Update(std::string &string_value, IntegerValue *value) override {
        value->value_ = std::stoi(string_value);
    };

    VisitorInteger() = default;
};


class VisitorDouble : public IVisitor {
public:


    bool Compare(std::string &string_value, const DoubleValue *value) override {
        return std::stod(string_value.substr(0, string_value.find('.') + 2)) == value->value_;
    };

    bool CompareLess(std::string &string_value, const DoubleValue *value) override {
        return std::stod(string_value.substr(0, string_value.find('.') + 2)) < value->value_;
    };

    bool CompareMore(std::string &string_value, const DoubleValue *value) override {
        return std::stod(string_value.substr(0, string_value.find('.') + 2)) > value->value_;
    };

    void Update(std::string &string_value, DoubleValue *value) override {
        value->value_ = std::stod(string_value.substr(0, string_value.find('.') + 2));
    };
};

class VisitorVarchar : public IVisitor {
public:

    bool Compare(std::string &string_value, const VarcharValue *value) override{
        return string_value == value->value_;
    };

    void Update(std::string &string_value, VarcharValue *value) override{
        value->value_ = string_value;
    };

};


class VisitorBoolean : public IVisitor {
protected:


    bool Compare(std::string& string_value, const BooleanValue* value) override{
        if (string_value == "true" && value->value_) {
            return true;
        }
        if (string_value == "false" && !value->value_) {
            return true;
        }
        return false;
    };

    void Update(std::string& string_value, BooleanValue* value) override{
        if (string_value == "true") {
            value->value_ = true;
        } else {
            value->value_ = false;
        }
    };


};


class VisitorFloat : public IVisitor {
protected:

    bool Compare(std::string& string_value, const FloatValue* value) override{
        return std::stof(string_value.substr(0, string_value.find('.') + 2)) == value->value_;
    };

    bool CompareLess(std::string& string_value, const FloatValue* value) override{
        return std::stof(string_value.substr(0, string_value.find('.') + 2)) < value->value_;
    };

    bool CompareMore(std::string& string_value, const FloatValue* value) override{
        return std::stof(string_value.substr(0, string_value.find('.') + 2)) > value->value_;
    };

    void Update(std::string& string_value, FloatValue* value) override{
        value->value_ = std::stof(string_value.substr(0, string_value.find('.') + 2));
    };
};
