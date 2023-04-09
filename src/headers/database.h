#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <string>

class Database
{
public:
    Database();
    ~Database();
    MYSQL *create_connection();

private:
    MYSQL *connection;
    std::string host;
    std::string user;
    std::string password;
    std::string db_name;
};

#endif // DATABASE_H
