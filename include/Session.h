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

    std::string createUser(CreateUser &action);
    std::string changeActiveUser(ChangeActiveUser &action);
    std::string deleteUser(DeleteUser &action);
    std::string duplicateUser(DuplicateUser &action);
    void printContentList(PrintContentList &action);
    void printWatchHistory();
    void printActionLog();
    void addUserToMap(User* user);
    Watchable * getContentAtIndex(int i);
    Watchable * getClosestTimeWatchable(double avg, LengthRecommenderUser* user);

    std::string watchContentById(Watch &action);
    User* getActiveUser();
    bool is_number(const std::string& s);
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    std::string defaultUserString;
};
#endif