#include "iostream"
#include "vector"
#include "string"

class SQLModel{
private:
    std::vector<std::string>_requests;
public:
    void add(std::string request){

        _requests.push_back(request);
    }
    void clean(){
        _requests.clear();
    }
    std::string find(std::string f){
        for(int i=0;i<_requests.size();i++){
            std::transform(_requests[i].begin(), _requests[i].end(),_requests[i].begin(), tolower);
            if (_requests[i].find(f) != std::string::npos) {
                return _requests[i];
            }
        }
        return "null";
    }


};