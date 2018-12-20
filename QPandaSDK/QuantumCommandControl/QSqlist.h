#ifndef  _Q_SQLITE_H
#define  _Q_SQLITE_H

#include "sqlite3/sqlite3.h"
#include <iostream>
#include <vector>
#include <mutex>
namespace QSqlite 
{
#define DB_SUBVECTOR     std::vector<std::string>
#define DB_VECTOR        std::vector<DB_SUBVECTOR>

    std::mutex _G_sqlMutex;
    class QSQLite
    {
    public:
         DB_VECTOR mResutVector;

        ~QSQLite();

        inline static QSQLite * getIntance(std::string &sDBPath) 
        {
            static QSQLite  pSqlite(sDBPath); //=new QSQLite;// ;

            return &pSqlite;

        }

        bool execSQL(std::string sSQL,char * cpMError) noexcept;



    private:
        QSQLite(std::string & sDBPath);
        QSQLite();
        static int callback(void *data, int argc, char **argv, char **azColName)  noexcept;
        static int callbackCheckTable(void* pHandle, int iRet, char** szSrc, char** szDst)  noexcept;
        bool checkTable();
        bool createTable();
        sqlite3 * pDB;

    };

    QSQLite::QSQLite()
    {
        string sDBPath = "Cloud.db";
        int rc = sqlite3_open(sDBPath.c_str(),&pDB);
    }

    QSQLite::QSQLite(std::string& sDBPath)
    {

        int rc = sqlite3_open(sDBPath.c_str(),&pDB);
        
        if (rc!= SQLITE_OK)
        {
            cout << "sqlite open fail" << endl;
        }
        else
        {
            cout << "sqlite open success" << endl;
        }
    }

    QSQLite::~QSQLite()
    {
        sqlite3_close(pDB);
    }


    bool QSQLite::execSQL(std::string sSQL, char * cpMError) noexcept
    {
        if ((nullptr== pDB)||(0 == sSQL.size()))
        {
            return false;
        }
        if (!checkTable())
        {
            return false;
        }
        int rc =sqlite3_exec(pDB, sSQL.c_str(), callback, (void *)&this->mResutVector, &cpMError);

        if (rc != SQLITE_OK)
        {
            return false;
        }
        return true;
    }
    bool QSQLite::createTable()
    {
        if (nullptr == pDB)
        {
            return false;
        }
        int tableNum = 0;
        string sql = "CREATE TABLE CloudTask(ID INT PRIMARY KEY,TaskID TEXT,TaskSta INT);";
        int rc = sqlite3_exec(pDB, sql.c_str(), nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK)
        {
            return false;
        }
        else
        {
            cout << "create table success" << endl;
            return true;
        }

    }
    bool QSQLite::checkTable()
    {
        if (nullptr == pDB)
        {
            return false;
        }
        int tableNum = 0;
        string sql = "select count(*) from sqlite_master where type='table' and name = 'CloudTask'";
        int rc = sqlite3_exec(pDB, sql.c_str(), callbackCheckTable, &tableNum, nullptr);
        if (rc != SQLITE_OK)
        {
            return false;
        }

        if (tableNum < 1)
        {
            return createTable();
        }
        return true;
    }


    int QSQLite::callbackCheckTable(void* pHandle, int iRet, char** szSrc, char** szDst) noexcept
    {
        //... 
        if (1 == iRet)
        {
            int iTableExist = atoi(*(szSrc));  
            if (pHandle != nullptr)
            {
                int* pRes = (int*)pHandle;
                *pRes = iTableExist;
            }
            
        }

        return 0;
    }

    int QSQLite::callback(void *data, int argc, char **argv, char **azColName) noexcept
    {
        DB_VECTOR * pResutVector = (DB_VECTOR *)data;
        if (0 != pResutVector->size())
        {
            pResutVector->clear();
            
        }

        for (int i = 0; i < argc; i++)
        {
            std::cout<<(argv[i] ? argv[i] : "NULL")<<' ';
        }
        std::cout << std::endl;

        return 0;
    }
}
#endif // ! _Q_SQLITE_H

