#ifndef _Q_COMMNAD_VECTOR_BASE_H
#define _Q_COMMNAD_VECTOR_BASE_H

#include <sstream>
#include <iostream>

class QCommandVectorBase
{
public:
    
    QCommandVectorBase() {};
    virtual ~QCommandVectorBase() {};

    /*************************************************************************************************************
    Name:        commandAction
    Description: command  action
    Argin:       ssAction  command name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    virtual bool commandAction(std::stringstream & ssAction) = 0;

    /*************************************************************************************************************
    Name:        commandDescription
    Description: command  Description
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    virtual void commandDescription() = 0;
private:

};


#endif // !_Q_COMMNAD_VECTOR_BASE_H

