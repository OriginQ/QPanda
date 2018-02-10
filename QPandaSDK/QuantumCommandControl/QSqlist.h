#ifndef  _Q_SQLITE_H
#define  _Q_SQLITE_H

#include "../include/sqlite3.h"
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
#if 0
        
        if (rc!= SQLITE_OK)
        {
            throw rc;
        }
#endif // 0

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

        int rc =sqlite3_exec(pDB, sSQL.c_str(), callback, (void *)&this->mResutVector, &cpMError);

        if (rc != SQLITE_OK)
        {
            return false;
        }
        return true;
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

