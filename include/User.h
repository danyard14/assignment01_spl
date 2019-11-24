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
    User(const std::string& name);
    User(const User &other);
    //virtual Watchable* getRecommendation(Session& s) = 0;
    virtual ~User();
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    User& operator=(const User& other);
protected:
    std::vector<Watchable*> history;
private:
    const std::string name;

    // new fields
    double avg;
};



class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(const LengthRecommenderUser &other);
    virtual Watchable* getRecommendation(Session& s);

private:
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser(const RerunRecommenderUser &other);
    //virtual Watchable* getRecommendation(Session& s);
private:
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser(const GenreRecommenderUser &other);
    //virtual Watchable* getRecommendation(Session& s);
private:
};

#endif