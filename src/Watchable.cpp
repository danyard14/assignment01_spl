//
// Created by danyard@wincs.cs.bgu.ac.il on 21/11/2019.
//
#include "../include/Watchable.h"
#include "../include/Session.h"

// constractor
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length), tags(tags) {

}
int Watchable::getLength() const {
    return length;
}
std::string Watchable::printTags() const {
    std::string ret = "[";
    for (auto &tag : tags) {
        ret += tag + ", ";
    }
    return ret.substr(0, ret.length() - 3) + "]";
}

Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags) : name(name), Watchable(id, length, tags) {

}
Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,
                 const std::vector<std::string> &tags) : seriesName (seriesName), season (season), episode(episode), nextEpisodeId(id + 1), Watchable(id, length, tags) {
}

// destractor
Watchable::~Watchable() {
    tags.clear();
}
// copy constructor
Watchable::Watchable(const Watchable &other) : id(other.id), length(other.length), tags(other.tags) {

}
Movie::Movie(const Movie &other) : name(other.name), Watchable(other) {

}
Episode::Episode(const Episode &other) : seriesName(other.seriesName), season(other.season), episode(other.episode), nextEpisodeId(other.nextEpisodeId), Watchable(other) {

}

std::string Movie::toString() const {
    std:std::string movieName = this -> name ;
    std::string movieLength = std::to_string(this->getLength());
    std::string tags = this->printTags();

    std::string ret = movieName + " " + movieLength + " " + tags;
    return ret;
}



std::string Episode::toString() const {
    std:std::string seriesName = this -> seriesName ;
    std::string numOfSeason = std::to_string(season);
    std::string numOfEpisode = std::to_string(episode);
    std::string episodeLength = std::to_string(this->getLength());
    std::string tags = this->printTags();
    (Watchable)this.
    if (season < 10)
        numOfSeason = "0" + numOfSeason;
    if (episode < 10)
        numOfEpisode = "0" + numOfEpisode;

    std::string ret = seriesName + " S" + numOfSeason + "E" + numOfEpisode + " " + episodeLength + " minutes " + tags;

    return ret;
};