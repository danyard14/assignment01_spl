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

    std::string getUserName() const;
    std::string getUserRecAlgo() const;

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
    DeleteUser(std::string userName);
    virtual void act(Session & sess);
    virtual std::string toString() const;

    std::string getUserName() const;
private:
    std::string userName;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string originUserName, std::string newUserName);
    virtual void act(Session & sess);
    virtual std::string toString() const;

    std::string getOriginUserName() const;

private:
    std::string originUserName;
    std::string newUserName;
};

class PrintContentList : public BaseAction {
public:
    PrintContentList();
    virtual void act (Session& sess);
    virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
    PrintWatchHistory();
    virtual void act (Session& sess);
    virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch(int id);
    virtual void act(Session& sess);
    virtual std::string toString() const;

    int getContentId();
private:
    int id;
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