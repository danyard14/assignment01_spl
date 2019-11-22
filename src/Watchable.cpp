//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Watchable.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length) {
    this -> tags = tags;
}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) : name(name), Watchable(id, length, tags) {
}

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : seriesName (seriesName), season (season), episode(episode), Watchable(id, length, tags) {

        //TODO: implement Next episode
}
