#include "crow.h"
#include "headers/database.h"
#include "headers/repository.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>

int main()
{
    MYSQL *connection = connect_to_database();
    if (!connection)
    {
        return 1;
    }

    crow::SimpleApp app;

    CROW_ROUTE(app, "/usuarios")
        .methods("GET"_method)([](const crow::request &req)
                               {
        MYSQL *connection = connect_to_database();
        Json::Value usuarios_json = get_users(connection);
        mysql_close(connection);

        Json::StreamWriterBuilder writer;
        std::string response_body = Json::writeString(writer, usuarios_json);

        crow::response res(response_body);
        res.set_header("Content-Type", "application/json");
        return res; });

    CROW_ROUTE(app, "/expenses/<int>")
        .methods("GET"_method)([](const crow::request &req, int user_id)
                               {
        MYSQL *connection = connect_to_database();
        Json::Value expenses_json = get_expenses(connection, user_id);
        mysql_close(connection);

        Json::StreamWriterBuilder writer;
        std::string response_body = Json::writeString(writer, expenses_json);

        crow::response res(response_body);
        res.set_header("Content-Type", "application/json");
        return res; });

    app.port(8080).multithreaded().run();

    mysql_close(connection);
    return 0;
}