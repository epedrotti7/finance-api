#include "headers/database.h"
#include <iostream>

MYSQL *connect_to_database()
{
    MYSQL *connection;
    connection = mysql_init(nullptr);

    if (!connection)
    {
        std::cerr << "Erro ao inicializar o MySQL: " << mysql_error(connection) << std::endl;
        return nullptr;
    }

    if (!mysql_real_connect(connection, "172.27.192.1", "finance", "finance", "finances", 3306, nullptr, 0))
    {
        std::cerr << "Erro ao conectar ao banco de dados: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return nullptr;
    }

    std::cout << "Conexão bem-sucedida ao banco de dados!" << std::endl;
    return connection;
}
