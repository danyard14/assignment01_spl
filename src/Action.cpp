//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Action.h"
#include "../include/Session.h"

BaseAction :: BaseAction() {
    status = PENDING;
}

void CreateUser :: act(Session &sess) {
    std::string msg = createUserAct(sess);


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


