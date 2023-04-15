#include "headers/database.h"
#include <iostream>

Database::Database()
{
    // host = "172.27.192.1";
    host = "127.0.0.1";
    user = "finance";
    password = "finance";
    db_name = "finances";
}

Database::~Database() {}

MYSQL *Database::create_connection()
{
    MYSQL *connection = mysql_init(nullptr);

    if (!mysql_real_connect(connection, host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), 0, nullptr, 0))
    {
        std::cerr << "Erro ao conectar ao banco de dados: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return nullptr;
    }

    return connection;
}
