#include "headers/expense_repository.h"
#include <iostream>
#include <mysql/mysql.h>

ExpenseRepository::ExpenseRepository(Database &db) : database(db) {}

Json::Value ExpenseRepository::get_expenses(int user_id)
{
    MYSQL *connection = database.create_connection();
    if (!connection)
    {
           return Json::Value(Json::objectValue);
    }

    std::string query = "SELECT * FROM despesas WHERE usuario_id = " + std::to_string(user_id);
    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection) << std::endl;
           return Json::Value(Json::objectValue);
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (!result)
    {
        std::cerr << "Erro ao obter o resultado: " << mysql_error(connection) << std::endl;
           return Json::Value(Json::objectValue);
    }

    MYSQL_ROW row;
    MYSQL_FIELD *field;
    Json::Value despesas_json;
    Json::Value despesas;
    int num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        Expense despesa = from_mysql_row(row, result->fields, num_fields);
        Json::Value despesa_json;
        despesa_json["id"] = despesa.id;
        despesa_json["usuario_id"] = despesa.usuario_id;
        despesa_json["descricao"] = despesa.descricao;
        despesa_json["valor"] = despesa.valor;
        despesa_json["data_vencimento"] = despesa.data_vencimento;
        despesa_json["pago"] = despesa.pago;
        despesas.append(despesa_json);
    }

    if (!despesas)
    {
        Json::Value empty_array(Json::arrayValue);
        despesas_json["despesas"] = empty_array;
    }
    else
    {
        despesas_json["despesas"] = despesas;
    }

    mysql_free_result(result);
    mysql_close(connection);
    return despesas_json;
}

bool ExpenseRepository::save_expense(int user_id, const Expense &expense)
{
    MYSQL *connection = database.create_connection();
    if (!connection)
    {
        return false;
    }

    std::string query = "INSERT INTO despesas (usuario_id, descricao, valor, data_vencimento, pago) VALUES (" +
                        std::to_string(user_id) + ", " + "'" + expense.descricao + "', " + std::to_string(expense.valor) + ", " + "'" +
                        expense.data_vencimento + "', " + (expense.pago ? "1" : "0") + ")";

    if (mysql_query(connection, query.c_str()))
    {
        std::cerr << "Erro ao executar a query: " << mysql_error(connection) << std::endl;
        return false;
    }

    mysql_close(connection);
    return true;
}

Json::Value ExpenseRepository::get_expense(int user_id, int expense_id)
{
    MYSQL *connection = database.create_connection();
    if (!connection)
    {
        return "";
    }

    std::string query = "SELECT * FROM despesas WHERE usuario_id = " + std::to_string(user_id) + " AND id = " + std::to_string(expense_id);
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
    Json::Value despesa_json;
    int num_fields = mysql_num_fields(result);

    if ((row = mysql_fetch_row(result)))
    {
        Expense despesa = from_mysql_row(row, result->fields, num_fields);
        despesa_json["id"] = despesa.id;
        despesa_json["usuario_id"] = despesa.usuario_id;
        despesa_json["descricao"] = despesa.descricao;
        despesa_json["valor"] = despesa.valor;
        despesa_json["data_vencimento"] = despesa.data_vencimento;
        despesa_json["pago"] = despesa.pago;
    }

    mysql_free_result(result);
    mysql_close(connection);
    return despesa_json;
}

Expense ExpenseRepository::from_mysql_row(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields)
{
    Expense despesa;
    for (int i = 0; i < num_fields; ++i)
    {
        std::string field_name = fields[i].name;
        if (field_name == "id")
        {
            despesa.id = std::stoi(row[i]);
            // Continuação do arquivo expense_repository.cpp
        }
        else if (field_name == "usuario_id")
        {
            despesa.usuario_id = std::stoi(row[i]);
        }
        else if (field_name == "descricao")
        {
            despesa.descricao = row[i];
        }
        else if (field_name == "valor")
        {
            despesa.valor = std::stod(row[i]);
        }
        else if (field_name == "data_vencimento")
        {
            despesa.data_vencimento = row[i];
        }
        else if (field_name == "pago")
        {
            despesa.pago = std::stoi(row[i]) != 0;
        }
    }
    return despesa;
}
