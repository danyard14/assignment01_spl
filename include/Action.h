#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
    BaseAction();
    BaseAction(const BaseAction &other);
    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;

    void setStatus(ActionStatus status);
    void setErrorMsg(std::string errorMsg);

protected:
    void complete();
    void error(const std::string& errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};

class CreateUser : public BaseAction {
public:
    CreateUser (std::string userName, std::string reccomendAlgo);
    virtual void act(Session& sess);
    virtual std::string toString() const;
    
    std::string getName() const;
    std::string getRecAlgo() const;

private:
    std::string userName;
    std::string reccomendAlgo;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser (std::string userName);
    virtual void act(Session& sess);
    virtual std::string toString() const;

    std::string getUserName() const;
private:
    std::string userName;
};

class DeleteUser : public BaseAction {
public:
    virtual void act(Session & sess);
    DeleteUser(std::string userName);
    virtual std::string toString() const;

    std::string getUserName() const;
private:
    std::string userName;
};


class DuplicateUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
};

class PrintContentList : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    virtual void act(Session& sess);
    virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
};
#endif