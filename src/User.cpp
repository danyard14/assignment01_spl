//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/User.h"

User::User(const std::string &name) : name(name){
    // make sure that the initialized vector is made in stack and copy to history by deep copy
    history = std::vector<Watchable*>();
}




std::string User::getName() const {
    return name;
}
std::vector<Watchable*> User::get_history() const {
    return history;
}

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name){

}

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name){

}

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name){

}
