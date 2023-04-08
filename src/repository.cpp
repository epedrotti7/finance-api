#include "headers/repository.h"
#include <iostream>
#include <mysql/mysql.h>

Json::Value get_users(MYSQL *connection)
{
    std::string query = "SELECT * FROM usuarios";
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection) << std::endl;
        return "";
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (!result)
    {
        std::cerr << "Erro ao obter o resultado: " << mysql_error(connection) << std::endl;
        return "";
    }

    MYSQL_ROW row;
    MYSQL_FIELD *field;
    Json::Value usuarios_json;
    Json::Value usuarios;
    int num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        Json::Value usuario;
        for (int i = 0; i < num_fields; ++i)
        {
            field = mysql_fetch_field_direct(result, i);
            usuario[field->name] = row[i] ? row[i] : "";
        }
        usuarios.append(usuario);
    }

    usuarios_json["users"] = usuarios;

    mysql_free_result(result);
    return usuarios_json;
}