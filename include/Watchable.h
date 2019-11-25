#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);
    Watchable(const Watchable &other);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    std::string printLengthAndTags() const;
    virtual Watchable* getNextWatchable(Session& sess);
    int getContentId() const;
    std::string printTags() const;
    virtual int getLength();
private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    Movie(const Movie &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(const Episode &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session& sess) const;
    void setNextWatchableId(long nextId);
    long getNextWatchableId();
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif