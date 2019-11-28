#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "User.h"

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

class BaseAction{
public:
    BaseAction();
//    BaseAction(const BaseAction &other);

    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
    virtual BaseAction& cloneAction()=0;

    void setStatus(ActionStatus status);
    void setErrorMsg(std::string errorMsg);

//    virtual BaseAction& cloneAction()=0;

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
    CreateUser(std::string userName, std::string reccomendAlgo);
//    CreateUser(const CreateUser &other);

    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual CreateUser& cloneAction();


    std::string getUserName() const;
    std::string getUserRecAlgo() const;

//    virtual CreateUser& cloneAction();

private:
    std::string userName;
    std::string reccomendAlgo;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser(std::string userName);
//    ChangeActiveUser(const ChangeActiveUser &other);
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual ChangeActiveUser& cloneAction();


    std::string getUserName() const;

//    virtual ChangeActiveUser& cloneAction();

private:
    std::string userName;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser(std::string userName);
  //  DeleteUser(DeleteUser &other);
    virtual void act(Session & sess);
    virtual DeleteUser& cloneAction();

    virtual std::string toString() const;

    std::string getUserName() const;

private:
    std::string userName;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string originalUserName, std::string newUserName);
    virtual DuplicateUser& cloneAction();
    //    DuplicateUser(const DuplicateUser &other);
    virtual void act(Session & sess);
    virtual std::string toString() const;

    std::string getNewUserName() const;
    std::string getOriginUserName() const;

//    virtual DuplicateUser& cloneAction();

private:
    std::string newUserName;
    std::string originalUserName;
};

class PrintContentList : public BaseAction {
public:
    PrintContentList();
//    PrintContentList(const PrintContentList &other);

    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual PrintContentList& cloneAction();


//    virtual PrintContentList& cloneAction();

};

class PrintWatchHistory : public BaseAction {
public:
    PrintWatchHistory();
//    PrintWatchHistory(const PrintWatchHistory &other);

    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual PrintWatchHistory& cloneAction();


//    virtual PrintWatchHistory& cloneAction();

};


class Watch : public BaseAction {
public:
    Watch(int id);
//    Watch(const Watch &other);
    virtual Watch& cloneAction();
    virtual void act(Session& sess);
    virtual std::string toString() const;

    int getContentId();

//    virtual Watch& cloneAction();

private:
    int id;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
//    PrintActionsLog(const PrintActionsLog &other);
    virtual PrintActionsLog& cloneAction();
    virtual void act(Session& sess);
    virtual std::string toString() const;

//    virtual PrintActionsLog& cloneAction();

};

class Exit : public BaseAction {
public:
    virtual Exit& cloneAction();
    virtual void act(Session& sess);
    virtual std::string toString() const;

//    virtual Exit& cloneAction();

};
#endif