//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Action.h"
#include "../include/Session.h"

// constructor
BaseAction::BaseAction() {
    status = PENDING;
}

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

CreateUser::CreateUser (std::string userName, std::string reccomendAlgo) : userName(userName), reccomendAlgo(reccomendAlgo), BaseAction() {

}

void CreateUser :: act(Session &sess) {
    sess


    /*
                 if (userMap.find(userName) != userMap.end()) {
                User* user;
                if (reccomendAlgo == "len")
                    user = new LengthRecommenderUser(userName);
                else if (reccomendAlgo == "rer")
                    user = new RerunRecommenderUser(userName);
                else if (reccomendAlgo == "gen")
                    user = new GenreRecommenderUser(userName);
                userMap.insert({userName, user});
                //update action
            }
            else
                //update action
     */
}

DeleteUser::DeleteUser (std::string userName) : userName(userName), BaseAction() {

}
std::string DeleteUser::getUserName() const {
    return userName;
}
void DeleteUser :: act(Session &sess) {
    BaseAction* act = new DeleteUser(userName);
    sess.addAction(act);
    sess.deleteUser(*this);
}
