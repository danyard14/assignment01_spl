//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Action.h"
#include "../include/Session.h"

// constructors
BaseAction::BaseAction() {
    status = PENDING;
}
CreateUser::CreateUser (std::string userName, std::string reccomendAlgo) : userName(userName), reccomendAlgo(reccomendAlgo), BaseAction() {}
ChangeActiveUser::ChangeActiveUser (std::string userName) : userName(userName), BaseAction() {}
DeleteUser::DeleteUser (std::string userName) : userName(userName), BaseAction() {}
DuplicateUser::DuplicateUser(std::string originalUserName, std::string newUserName) : originalUserName(originalUserName), newUserName(newUserName) {}
PrintContentList::PrintContentList() : BaseAction() {}
PrintWatchHistory::PrintWatchHistory () : BaseAction() {}
PrintActionsLog::PrintActionsLog():BaseAction(){}

// base action methods
void BaseAction::complete() {
    status = COMPLETED;
}
void  BaseAction::error(const std::string &msg) {
    status = ERROR;
    errorMsg = msg;
}
// getters
ActionStatus BaseAction::getStatus() const {
    return status;
}
std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}
// setters
void BaseAction::setStatus(ActionStatus stats) {
    status = stats;
}
void BaseAction::setErrorMsg(std::string msg) {
    errorMsg = msg;
}

// create user methods
void CreateUser :: act(Session &sess) {
    std::string ret = sess.createUser(*this);
    if (ret == "")
        complete();
    else {
        setStatus(ERROR);
        setErrorMsg(ret);
    }
}
std::string CreateUser::toString() const {
    std::string ret = "CreateUser ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}
// getters
std::string CreateUser::getUserName() const { return userName; }
std::string CreateUser::getUserRecAlgo() const { return reccomendAlgo; }

// change active user methods
void ChangeActiveUser::act(Session &sess) {
    std::string ret = sess.changeActiveUser(*this);
    if (ret == "")
        complete();
    else {
        error(ret);
    }
}
std::string ChangeActiveUser::toString() const {
    std::string ret = "ChangeActiveUser ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}
// getters
std::string ChangeActiveUser::getUserName() const { return userName; }

// delete user methods
void DeleteUser::act(Session &sess) {
    std::string ret = sess.deleteUser(*this);
    if (ret == "")
        complete();
    else {
        error(ret);
    }
}
std::string DeleteUser::toString() const {
    std::string ret = "DeleteUser ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}
// getters
std::string DeleteUser::getUserName() const {
    return userName;
}

// duplicate user methods
void DuplicateUser::act(Session &sess) {
    std::string ret = sess.duplicateUser(*this);
    if (ret == "")
        complete();
    else {
        error(ret);
    }
}
std::string DuplicateUser::toString() const {
    std::string ret = "DuplicateUser ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}

// getters
std::string DuplicateUser:: getOriginUserName() const{
    return originalUserName;
}
std::string DuplicateUser::getNewUserName() const {
    return newUserName;
}

// print content list methods
void PrintContentList::act(Session &sess) {
    sess.printContentList(*this);
    complete();
}
std::string PrintContentList::toString() const {
    std::string ret = "PrintContentList ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}

// print watch history methods
void PrintWatchHistory::act (Session& sess) {
    sess.printWatchHistory();
    complete();
}
std::string PrintWatchHistory::toString() const {
    std::string ret = "PrintWatchHistory ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}

// print actions log
void PrintActionsLog::act(Session &sess) {
    sess.printActionLog();
    complete();
}
std::string PrintActionsLog::toString() const {
    std::string ret = "PrintActionLog ";
    ActionStatus status = getStatus();
    if(status == COMPLETED) {
        ret += "COMPLETED";
        return ret;
    }
    else if (status == ERROR) {
        ret += "ERROR: ";
        ret += getErrorMsg();
        return ret;
    }
    else {
        ret += "PENDING";
        return ret;
    }
}




Watch::Watch(int id) : id(id) {}
void Watch::act(Session &sess) {
    sess.watchContentById(*this);
    complete();
}

int Watch::getContentId() { return id; }

std::string Watch::toString() const {

    return "Watch"+getStatus();
}
