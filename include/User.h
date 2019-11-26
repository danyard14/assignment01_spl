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
    // constructors
    User(std::string& name);
    User( User &other);

    //distructor
    virtual ~User();

    // regular methods
    void addToHistory(Watchable* watchable);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s) = 0;
    virtual bool userWatched(Watchable* watchable)=0;
    virtual User& cloneUser(std::string newName)=0;

    //getters
    std::string getName();
    std::vector<Watchable*> get_history() const;

    // rule of 5 stuff
    User& operator=(const User& other);

protected:
    //fields
    std::vector<Watchable*> history;

    // setters
    void setName(std::string nameToSet);

private:
    // fields
    std::string name;


    // new fields

};


class LengthRecommenderUser : public User {
public:
    // constructors
    LengthRecommenderUser( std::string& name);
    LengthRecommenderUser( LengthRecommenderUser &other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual LengthRecommenderUser& cloneUser(std::string newName);

    // regular methods
    bool userWatched(Watchable* watchable);

protected:

private:
    // fields
    double avg;

};


class RerunRecommenderUser : public User {
public:
    // constructors
    RerunRecommenderUser( std::string& name);
    RerunRecommenderUser( RerunRecommenderUser &other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual RerunRecommenderUser& cloneUser(std::string newName);

    // regular methods
    bool userWatched(Watchable* watchable) override;

private:
};



class GenreRecommenderUser : public User {
public:
    // constructors
    GenreRecommenderUser( std::string& name);
    GenreRecommenderUser( GenreRecommenderUser &other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual GenreRecommenderUser& cloneUser(std::string newName);

    // regular methods
    bool userWatched(Watchable* watchable) override;


private:
};

#endif