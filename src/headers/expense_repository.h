#ifndef EXPENSE_REPOSITORY_H
#define EXPENSE_REPOSITORY_H

#include "database.h"
#include "expense.h"
#include <jsoncpp/json/json.h>
#include <vector>

class ExpenseRepository
{
public:
    ExpenseRepository(Database &db);
    Json::Value get_expenses(int user_id);
    bool save_expense(int user_id, const Expense &expense);
    Json::Value get_expense(int user_id, int expense_id);

private:
    Database &database;
    Expense from_mysql_row(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields);
};

#endif // EXPENSE_REPOSITORY_H
