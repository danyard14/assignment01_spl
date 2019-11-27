//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Action.h"
#include "../include/Session.h"

// constructors
BaseAction::BaseAction() { status = PENDING; }
CreateUser::CreateUser (std::string userName, std::string reccomendAlgo) : userName(userName), reccomendAlgo(reccomendAlgo), BaseAction() {}
ChangeActiveUser::ChangeActiveUser (std::string userName) : userName(userName), BaseAction() {}
DeleteUser::DeleteUser(std::string userName) : userName(userName), BaseAction() {}
DuplicateUser::DuplicateUser(std::string originalUserName, std::string newUserName) : originalUserName(originalUserName), newUserName(newUserName) {} //TODO:: need to add base()?
PrintContentList::PrintContentList() : BaseAction() {}
PrintWatchHistory::PrintWatchHistory () : BaseAction() {}
PrintActionsLog::PrintActionsLog():BaseAction() {}

// copy constructors
//BaseAction::BaseAction(const BaseAction &other) : status(other.status), errorMsg(other.errorMsg) {}
//CreateUser::CreateUser (const CreateUser &other) : userName(other.userName), reccomendAlgo(other.reccomendAlgo), BaseAction(other) {}
//ChangeActiveUser::ChangeActiveUser (const ChangeActiveUser &other) : userName(other.userName), BaseAction(other) {}
//DeleteUser::DeleteUser (const DeleteUser &other) : userName(userName), BaseAction(other) {}
//DuplicateUser::DuplicateUser(const DuplicateUser &other) : originalUserName(originalUserName), newUserName(newUserName), BaseAction(other) {}
//PrintContentList::PrintContentList(const PrintContentList &other) : BaseAction(other) {}
//PrintWatchHistory::PrintWatchHistory (const PrintWatchHistory &other) : BaseAction(other) {}
//PrintActionsLog::PrintActionsLog(const PrintActionsLog &other):BaseAction(other){}

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
    else
        error(ret);
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

CreateUser &CreateUser::cloneAction() {
    CreateUser* action = new CreateUser(this->getUserName(),this->reccomendAlgo);
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// change active user methods
void ChangeActiveUser::act(Session &sess) {
    std::string ret = sess.changeActiveUser(*this);
    if (ret == "")
        complete();
    else
        error(ret);
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

ChangeActiveUser &ChangeActiveUser::cloneAction() {
    ChangeActiveUser* action = new ChangeActiveUser(this->getUserName());
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//ChangeActiveUser &ChangeActiveUser::cloneAction(){
//    ChangeActiveUser* actionClone = new ChangeActiveUser(*this);
//    return *actionClone;
//}

// delete user methods
//void DeleteUser::act(Session &sess) {
//    std::string ret = sess.deleteUser(*this);
//    if (ret == "")
//        complete();
//    else
//        error(ret);
//}
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
std::string DeleteUser::getUserName() const { return userName; }

DeleteUser &DeleteUser::cloneAction() {
    DeleteUser* action = new DeleteUser(this->getUserName());
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//DeleteUser &DeleteUser::cloneAction(){
//    DeleteUser* actionClone = new DeleteUser(*this);
//    return *actionClone;
//}

// duplicate user methods
void DuplicateUser::act(Session &sess) {
    std::string ret = sess.duplicateUser(*this);
    if (ret == "")
        complete();
    else
        error(ret);
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

DuplicateUser &DuplicateUser::cloneAction() {
    DuplicateUser* action = new DuplicateUser(this->originalUserName, this->getNewUserName());
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//DuplicateUser &DuplicateUser::cloneAction(){
//    DuplicateUser* actionClone = new DuplicateUser(*this);
//    return *actionClone;
//}

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

PrintContentList &PrintContentList::cloneAction() {
    PrintContentList* action = new PrintContentList();
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//PrintContentList &PrintContentList::cloneAction(){
//    PrintContentList* actionClone = new PrintContentList(*this);
//    return *actionClone;
//}

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

PrintWatchHistory &PrintWatchHistory::cloneAction() {
    PrintWatchHistory* action = new PrintWatchHistory();
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//PrintWatchHistory &PrintWatchHistory::cloneAction(){
//    PrintWatchHistory* actionClone = new PrintWatchHistory(*this);
//    return *actionClone;
//}

// watch content methods
void Watch::act(Session &sess) {
    std::string ret = sess.watchContentById(*this);
    if (ret == "")
        complete();
    else
        error(ret);
}
std::string Watch::toString() const {
    std::string ret = "Watch ";
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
int Watch::getContentId() { return id; }

Watch &Watch::cloneAction() {
    Watch* action = new Watch(this->id);
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//Watch &Watch::cloneAction(){
//    Watch* actionClone = new Watch(*this);
//    return *actionClone;
//}

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

PrintActionsLog &PrintActionsLog::cloneAction() {
    PrintActionsLog* action = new PrintActionsLog();
    action->setStatus(this->getStatus());
    action->setErrorMsg(this->getErrorMsg());
    return *action;
}

// return new Action of type createuser
//PrintActionsLog &PrintActionsLog::cloneAction(){
//    PrintActionsLog* actionClone = new PrintActionsLog(*this);
//    return *actionClone;
//}