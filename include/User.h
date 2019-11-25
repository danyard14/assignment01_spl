#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    User(std::string& name);
    User( User &other);
    virtual Watchable* getRecommendation(Session& s) = 0;
    virtual ~User();
    std::string getName();
    std::vector<Watchable*> get_history() const;
    User& operator=(const User& other);
    virtual User& cloneUser(std::string newName)=0;
    void addToHistory(Watchable* watchable);
    virtual bool userWatched(Watchable* watchable)=0;
protected:
    std::vector<Watchable*> history;
    void setName(std::string nameToSet);
private:
    std::string name;
    // new fields

};



class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser( std::string& name);
    LengthRecommenderUser( LengthRecommenderUser &other);
    virtual Watchable* getRecommendation(Session& s);
    virtual LengthRecommenderUser& cloneUser(std::string newName);
    double getAverageWatchTime();
    bool userWatched(Watchable* watchable);

protected:

private:
    double avg;

};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser( std::string& name);
    RerunRecommenderUser( RerunRecommenderUser &other);
    virtual Watchable* getRecommendation(Session& s);
    virtual RerunRecommenderUser& cloneUser(std::string newName);
    bool userWatched(Watchable* watchable) override;


private:
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser( std::string& name);
    GenreRecommenderUser( GenreRecommenderUser &other);
    virtual Watchable* getRecommendation(Session& s);
    virtual GenreRecommenderUser& cloneUser(std::string newName);
    bool userWatched(Watchable* watchable) override;


private:
};

#endif