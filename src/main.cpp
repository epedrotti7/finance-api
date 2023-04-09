#include "crow.h"
#include "headers/database.h"
#include "headers/expense_repository.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>

int main()
{
    Database db;
    ExpenseRepository expense_repository(db);

    crow::SimpleApp app;

    // Buscar despesa
    CROW_ROUTE(app, "/despesas/<int>")
        .methods("GET"_method)([&](const crow::request &req, int user_id)
                               {
            Json::Value expenses_json = expense_repository.get_expenses(user_id);

            Json::StreamWriterBuilder writer;
            std::string response_body = Json::writeString(writer, expenses_json);

            crow::response res(response_body);
            res.set_header("Content-Type", "application/json");
            return res; });

    // Criar despesa
    CROW_ROUTE(app, "/despesas/<int>")
        .methods("POST"_method)([&](const crow::request &req, int user_id)
                                {
         Json::CharReaderBuilder reader_builder;
        Json::Value json_req;
        std::string errs;

        std::istringstream body_stream(req.body);
        if (!Json::parseFromStream(reader_builder, body_stream, &json_req, &errs)) {
            crow::response res(400);
            res.write("Invalid JSON");
            return res;
        }

        if (!json_req.isMember("descricao") || !json_req.isMember("valor") ||
            !json_req.isMember("data_vencimento") || !json_req.isMember("pago") ||
            !json_req["valor"].isNumeric()) {
            crow::response res(400);
            res.write("Missing or invalid fields");
            return res;
        }

        Expense new_expense;
        new_expense.descricao = json_req["descricao"].asString();
        new_expense.valor = json_req["valor"].asDouble();
        new_expense.data_vencimento = json_req["data_vencimento"].asString();
        new_expense.pago = json_req["pago"].asBool();

        bool success = expense_repository.save_expense(user_id, new_expense);

        if (!success) {
            crow::response res(500);
            res.write("Failed to save expense");
            return res;
        }

        crow::response res(201);
        res.write("Expense saved successfully");
        return res; });

    // Buscar uma única despesa
    CROW_ROUTE(app, "/despesas/<int>/buscar/<int>")
        .methods("GET"_method)([&](const crow::request &req, int user_id, int expense_id)
                               {
        Json::Value expense_json = expense_repository.get_expense(user_id, expense_id);

        Json::StreamWriterBuilder writer;
        std::string response_body = Json::writeString(writer, expense_json);

        crow::response res(response_body);
        res.set_header("Content-Type", "application/json");
        return res; });

    app.port(8080).multithreaded().run();

    return 0;
}
