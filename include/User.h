#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>

class Watchable;
class Session;

class User{
public:
    // constructors
    User(std::string& name);
    User( User &other);
    User(User&& other);
    User& operator=(const User& other);

    // distructor
    virtual ~User();

    // regular methods
    virtual void addToHistory(Watchable* watchable);
    bool userWatched(Watchable* watchable);
    std::pair <std::string, int> getMaxFromMap(std::map<std::string,int>* genreMap);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s) = 0;
    virtual User& cloneUser(std::string newName)=0;

    //getters
    std::string getName();
    std::vector<Watchable*> get_history() const;

protected:
    //fields
    std::vector<Watchable*> history;

    // setters
    void setName(std::string nameToSet);

private:
    // fields
    std::string name;
};


class LengthRecommenderUser : public User {
public:
    // constructors
    LengthRecommenderUser(std::string& name);
    LengthRecommenderUser(LengthRecommenderUser &other);
    LengthRecommenderUser(LengthRecommenderUser &&other);
    LengthRecommenderUser& operator=(const LengthRecommenderUser& other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual LengthRecommenderUser& cloneUser(std::string newName);
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
    RerunRecommenderUser(RerunRecommenderUser &&other);
    RerunRecommenderUser& operator=(const RerunRecommenderUser& other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual RerunRecommenderUser& cloneUser(std::string newName);

    // getters
    int getLastRecIndex();

private:
    int lastRecIndex;
};



class GenreRecommenderUser : public User {
public:
    // constructors
    GenreRecommenderUser( std::string& name);
    GenreRecommenderUser( GenreRecommenderUser &other);
    GenreRecommenderUser& operator=(const GenreRecommenderUser& other);

    // virtual methods
    virtual Watchable* getRecommendation(Session& s);
    virtual GenreRecommenderUser& cloneUser(std::string newName);

private:
};

#endif