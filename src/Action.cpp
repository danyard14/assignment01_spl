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
CreateUser::CreateUser (std::string userName, std::string reccomendAlgo) : userName(userName), reccomendAlgo(reccomendAlgo), BaseAction() {
}

std::string CreateUser::getName() const { return userName;}
std::string CreateUser::getRecAlgo() const { return reccomendAlgo;}





// function "act" of create user
void CreateUser :: act(Session &sess) {
    sess.makeNewUser(*this);

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


