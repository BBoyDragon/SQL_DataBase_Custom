
#include "string"
#include "vector"
#include "DataTable.h"
#include "regex"
#include "StringTools.h"

#ifndef LABWORK_12_BBOYDRAGON_WHERESUBCONTROLLER_H
#define LABWORK_12_BBOYDRAGON_WHERESUBCONTROLLER_H
enum RequestType {
    Edelete,
    Eupdate,
    Eselect
};


struct Action {
    std::string colon;
    std::string operation;
    std::string val;
};

class WhereSubController {
private:
    std::vector<std::vector<std::string>> _finalResult;


    bool Accept(Types type, Action &operation, int line, DataTable *data) {
        IVisitor *visitor;
        bool result;
        switch (type) {
            case EInteger:
                visitor = new VisitorInteger();
                break;
            case EDouble:
                visitor = new VisitorDouble();
                break;
            case EFloat:
                visitor = new VisitorFloat();
                break;
            case EBool:
                visitor = new VisitorBoolean();
                break;
            case EVarChar:
                visitor = new VisitorVarchar();
                break;
        }
        result = data->GetColons()[operation.colon][line]->Accept(visitor, operation.val);
        delete visitor;
        return result;


    }

    bool AcceptLess(Types type, Action &operation, int line, DataTable *data) {
        IVisitor *visitor;
        bool result;
        switch (type) {
            case EInteger:
                visitor = new VisitorInteger();
                break;
            case EDouble:
                visitor = new VisitorDouble();
                break;
            case EFloat:
                visitor = new VisitorFloat();
                break;
            case EBool:
                visitor = new VisitorBoolean();
                break;
            case EVarChar:
                visitor = new VisitorVarchar();
                break;
        }
        result = data->GetColons()[operation.colon][line]->AcceptLessComp(visitor, operation.val);
        delete visitor;
        return result;
    }

    bool AcceptMore(Types type, Action &operation, int line, DataTable *data) {
        IVisitor *visitor;
        bool result;
        switch (type) {
            case EInteger:
                visitor = new VisitorInteger();
                break;
            case EDouble:
                visitor = new VisitorDouble();
                break;
            case EFloat:
                visitor = new VisitorFloat();
                break;
            case EBool:
                visitor = new VisitorBoolean();
                break;
            case EVarChar:
                visitor = new VisitorVarchar();
                break;
        }
        result = data->GetColons()[operation.colon][line]->AcceptMoreComp(visitor, operation.val);
        delete visitor;
        return result;


    }

    void UpdateCell(Types type,const std::string& colonName,int row,DataTable* data,const std::string& value) {
        IVisitor *visitor;
        switch (type) {
            case EInteger:
                visitor = new VisitorInteger();
                break;
            case EDouble:
                visitor = new VisitorDouble();
                break;
            case EFloat:
                visitor = new VisitorFloat();
                break;
            case EBool:
                visitor = new VisitorBoolean();
                break;
            case EVarChar:
                visitor = new VisitorVarchar();
                break;
        }
        data->GetColons()[colonName][row]->Update(visitor, value);
        delete visitor;
    }

    Action LogicalActionInfo(std::string &request) {
        std::regex logicalX(R"(("?\w+"?)\s*(=|>|<|!=)\s*("?\w+"?))");
        std::smatch logicalMatch;
        std::regex_search(request, logicalMatch, logicalX);
        std::string colon = logicalMatch[1];
        std::string val = logicalMatch[3];
        std::string operation = logicalMatch[2];
        CheckQuestionMark(colon);
        CheckQuestionMark(val);
        Action action;
        action.colon = colon;
        action.operation = operation;
        action.val = val;
        return action;
    }

    bool CheckOperation(Action &action, int line, DataTable *data) {
        for (int i = 0; i < data->GetTypes().size(); ++i) {
            if (data->GetTypes()[i].first == action.colon) {
                if (action.operation == "=") {
                    return Accept(data->GetTypes()[i].second, action, line, data);
                } else if (action.operation == ">") {
                    return AcceptMore(data->GetTypes()[i].second, action, line, data);
                } else if (action.operation == "<") {
                    return AcceptLess(data->GetTypes()[i].second, action, line, data);
                }
            }
        }
        return false;
    }

    void CheckData(std::vector<int> &lines, DataTable *data) {
        bool IsOr = false;
        bool IsAnd = true;
        Action action;
        for (int i = 0; i < data->GetSize(); ++i) {
            for (auto &str: _finalResult) {
                for (auto &leter: str) {
                    action = LogicalActionInfo(leter);
                    IsAnd = IsAnd && CheckOperation(action, i, data);
                }
                IsOr = IsOr || IsAnd;
                IsAnd = true;
            }
            if (IsOr) {
                lines.push_back(i);
            }
            IsOr = false;
        }

    }

    void AndOrInfo(std::string &request) {
        std::vector<std::string> result;
        std::regex orX("OR", std::regex_constants::icase);
        std::sregex_token_iterator orExp(request.begin(), request.end(), orX, -1);
        std::sregex_token_iterator end;
        while (orExp != end) {
            std::string expression = *orExp;
            std::regex andX("AND", std::regex_constants::icase);
            std::sregex_token_iterator andExp(expression.begin(), expression.end(), andX, -1);
            std::sregex_token_iterator andEnd;
            while (andExp != andEnd) {
                std::string and_expression = *andExp;
                SpaceDelete(and_expression);
                result.push_back(and_expression);
                ++andExp;
            }
            _finalResult.push_back(result);
            result.clear();
            ++orExp;
        }
    }


    void ParseDelete(std::string &request, DataTable *data) {
        AndOrInfo(request);
        std::vector<int> delete_row;
        CheckData(delete_row, data);
        for (int i = 0; i < delete_row.size(); ++i) {
            data->Delete(delete_row[i] - i);
        }
    };

    void ParseUpdate(std::string& request, DataTable* table) {
        std::vector<std::string> colons;
        request.erase(0, request.find("set") + 3);
        std::string colonName = request.substr(0, request.find("where"));
        Split(colonName, ',', colons);
        SpaceDelete(colons);
        std::vector<std::string> values;
        for (auto& i : colons) {
            values.push_back(i.substr(i.find("=") + 2, i.size()));
            CheckQuestionMark(values.back());
            i.erase(i.find("=") - 1, i.size());
        }
        request.erase(0, request.find("where") + 5);
        AndOrInfo(request);
        std::vector<int> updateRow;
        CheckData(updateRow, table);
        for (int i = 0; i < updateRow.size(); ++i) {
            for (int j = 0; j < colons.size(); ++j) {
                for (int k = 0; k < table->GetTypes().size(); ++k) {
                    if (table->GetTypes()[k].first == colons[j]) {
                        UpdateCell(table->GetTypes()[k].second, colons[j], updateRow[i], table, values[j]);
                        break;
                    }
                }
            }
        }
    }



    void ParseSelect(std::string& request, DataTable* data) {
        if (request.find('*') != std::string::npos) {
            request.erase(0, request.find("where") + 6);
            AndOrInfo(request);
            std::vector<int> selectRow;
            CheckData(selectRow, data);
            std::vector<std::string> printRow(data->GetSize());
            for (int i = 0; i < selectRow.size(); ++i) {
                for (int j = 0; j < data->GetTypes().size(); j++) {
                    for (int k = 0; k < data->GetSize(); k++) {
                        if (selectRow[i] == k) {
                            data->GetColons()[data->GetTypes()[j].first][k]->PutInColumn(printRow[k]);
                        }
                    }
                }
            }
            for (int i = 0; i < data->GetTypes().size(); ++i) {
                std::cout << data->GetTypes()[i].first << " ";
            }
            std::cout << "\n";
            for (auto& i : printRow) {
                if (i[0] != '\0') {
                    std::cout << i << "\n";
                }
            }
        } else {
            std::vector<std::string> Colons;
            std::string column_name = request.substr(0, request.find("from"));
            Split(column_name, ',', Colons);
            SpaceDelete(Colons);
            request.erase(0, request.find("where") + 6);
            AndOrInfo(request);
            std::vector<int> selectRow;
            CheckData(selectRow, data);
            std::vector<std::string> printRow(data->GetSize());
            for (int i = 0; i < data->GetTypes().size(); ++i) {
                for (int j = 0; j < Colons.size(); ++j) {
                    if (data->GetTypes()[i].first == Colons[j]) {
                        for (int k = 0; k < selectRow.size(); ++k) {
                            data->GetColons()[data->GetTypes()[i].first][selectRow[k]]->PutInColumn(printRow[selectRow[k]]);
                        }
                    }
                }
            }

            for (int i = 0; i < Colons.size(); ++i) {
                std::cout << Colons[i] << " ";
            }
            std::cout << "\n";
            for (auto& i : printRow) {
                if (i[0] != '\0') {
                    std::cout << i << "\n";
                }
            }
        }
    }


public:
    WhereSubController(std::string &request, DataTable *data, RequestType type) {
        switch (type) {
            case Edelete:
                ParseDelete(request, data);
                break;
            case Eupdate:
                ParseUpdate(request, data);
                break;
            case Eselect:
                ParseSelect(request, data);
                break;
            default:
                break;
        }
    }
};


#endif //LABWORK_12_BBOYDRAGON_WHERESUBCONTROLLER_H
