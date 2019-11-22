//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Watchable.h"
#include "../include/Session.h"

Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length), tags(tags) {

}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) : name(name), Watchable(id, length, tags) {

}

std::string Movie::toString() const {
    return this->name ;
}

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : seriesName (seriesName), season (season), episode(episode), nextEpisodeId(id + 1), Watchable(id, length, tags) {
}

std::string Episode::toString() const {
    std:std::string seriesName = this -> seriesName ;
    std::string numOfSeason =std::to_string(season);
    std::string numOfEpisode =std::to_string(episode);
    if (season < 10)
        numOfSeason = "0" + numOfSeason;
    if (episode < 10)
        numOfEpisode = "0" + numOfEpisode;

    std::string toReturn = seriesName + " S" + numOfSeason + "E" + numOfEpisode;

    return toReturn ;
};
