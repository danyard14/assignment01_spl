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
    sess.createUser(*this);
}

DeleteUser::DeleteUser (std::string userName) : userName(userName), BaseAction() {

}
std::string DeleteUser::getUserName() const {
    return userName;
}
void DeleteUser :: act(Session &sess) {
    sess.deleteUser(*this);
}

ChangeActiveUser::ChangeActiveUser (std::string userName) : userName(userName), BaseAction() {

}
std::string ChangeActiveUser::getUserName() const {
    return userName;
}
void ChangeActiveUser::act(Session &sess) {
    sess.changeActiveUser(*this);
}

PrintActionsLog::PrintActionsLog():BaseAction(){
}

std::string PrintActionsLog::toString() const {
    if(this->getStatus()==ERROR){
        return "PrintActionLog "+ this->getStatus() + this->getErrorMsg();
    }
    else{
        return "PrintActionLog " + this->getStatus();
    }
}

void PrintActionsLog::act(Session &sess) {
    sess.printActionLog();
}
