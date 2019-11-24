//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Action.h"
#include "../include/Session.h"

// constructor general
BaseAction::BaseAction() {
    status = PENDING;
}

// constructor of createUser
// setters
void BaseAction::setStatus(ActionStatus stats) {
    status = stats;
}
void BaseAction::setErrorMsg(std::string msg) {
    errorMsg = msg;
}

// getters
ActionStatus BaseAction::getStatus() const {
    return status;
}
std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

CreateUser::CreateUser (std::string userName, std::string reccomendAlgo) : userName(userName), reccomendAlgo(reccomendAlgo), BaseAction() {}

std::string CreateUser::getName() const { return userName;}
std::string CreateUser::getRecAlgo() const { return reccomendAlgo;}

// function "act" of create user
void CreateUser :: act(Session &sess) {
    std::string ret = sess.createUser(*this);
    if (ret == "")
        complete();
    else {
        setStatus(ERROR);
        setErrorMsg(ret);
    }
}

DeleteUser::DeleteUser (std::string userName) : userName(userName), BaseAction() {

}
std::string DeleteUser::getUserName() const {
    return userName;
}
void DeleteUser :: act(Session &sess) {
    std::string ret = sess.deleteUser(*this);
    if (ret == "")
        complete();
    else {
        error(ret);
    }
}

ChangeActiveUser::ChangeActiveUser (std::string userName) : userName(userName), BaseAction() {

}
std::string ChangeActiveUser::getUserName() const {
    return userName;
}
void ChangeActiveUser::act(Session &sess) {
    std::string ret = sess.changeActiveUser(*this);
    if (ret == "")
        complete();
    else {
        error(ret);
    }
}

PrintActionsLog::PrintActionsLog():BaseAction(){
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

void PrintActionsLog::act(Session &sess) {
    sess.printActionLog();
    complete();
}

PrintContentList::PrintContentList() : BaseAction() {

}
void PrintContentList::act(Session &sess) {
    sess.printContentList(*this);
    complete();
}

void BaseAction::complete() {
    status = COMPLETED;
}

void  BaseAction::error(const std::string &msg) {
    status = ERROR;
    errorMsg = msg;
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