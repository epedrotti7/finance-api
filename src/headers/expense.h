#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

struct Expense {
    int id;
    int usuario_id;
    std::string descricao;
    double valor;
    std::string data_vencimento;
    bool pago;
};

#endif // EXPENSE_H
