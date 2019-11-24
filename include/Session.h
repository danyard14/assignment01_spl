#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "../include/Action.h"

#include "../include/json.hpp"
#include "fstream"

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    Session(const Session &other);
    ~Session();
    void start();
    void addAction(BaseAction* action);

    void deleteUser(DeleteUser& action);
    void changeActiveUser(ChangeActiveUser& action);

private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
};
#endif