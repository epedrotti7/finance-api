using System.Collections.Generic;
using System.Threading.Tasks;
using FinanceApi.Structs;
using FinanceApi.Database;
using Microsoft.Extensions.Logging;
using MySql.Data.MySqlClient;

namespace FinanceApi.Repositories
{
    public interface IExpenseRepository
    {
        Task<List<Expense>> ListExpensesByUserId(int userId);
        Task<ExpenseResult> GetExpense(int userId, int expenseId);
    }

    public class ExpenseRepository : IExpenseRepository
    {
        private readonly ILogger<ExpenseRepository> _logger;
        private readonly Connection _connection;

        public ExpenseRepository(ILogger<ExpenseRepository> logger, Connection connection)
        {
            _logger = logger;
            _connection = connection;
        }

        public async Task<List<Expense>> ListExpensesByUserId(int userId)
        {
            List<Expense> expenses = new List<Expense>();

            using MySqlConnection connection = _connection.GetConnection();

            string query = "SELECT id, usuario_id, descricao, valor, data_vencimento, pago FROM despesas WHERE usuario_id = @userId";
            using MySqlCommand command = new MySqlCommand(query, connection);
            command.Parameters.AddWithValue("@userId", userId);

            using MySqlDataReader? reader = await command.ExecuteReaderAsync() as MySqlDataReader;
            while (await reader?.ReadAsync())
            {
                Expense expense = new Expense
                {
                    id = reader.GetInt32("id"),
                    id_usuario = reader.GetInt32("usuario_id"),
                    descricao = reader.GetString("descricao"),
                    valor = reader.GetDecimal("valor"),
                    data_vencimento = reader.GetString("data_vencimento"),
                    pago = reader.GetBoolean("pago")
                };

                expenses.Add(expense);
            }

            return expenses;
        }

        public async Task<ExpenseResult> GetExpense(int userId, int expenseId)
        {

            using MySqlConnection connection = _connection.GetConnection();

            string query = "SELECT * FROM despesas WHERE usuario_id = @userId AND id = @expenseId";
            using MySqlCommand command = new MySqlCommand(query, connection);
            command.Parameters.AddWithValue("@userId", userId);
            command.Parameters.AddWithValue("@expenseId", expenseId);

            using MySqlDataReader? reader = await command.ExecuteReaderAsync() as MySqlDataReader;
            var read = await reader?.ReadAsync();

            if (!read)
            {
                return new ExpenseResult { ErrorMessage = "Despesa nao encontrada" };
            }

            Expense expense = new Expense
            {
                id = reader.GetInt32("id"),
                id_usuario = reader.GetInt32("usuario_id"),
                descricao = reader.GetString("descricao"),
                valor = reader.GetDecimal("valor"),
                data_vencimento = reader.GetString("data_vencimento"),
                pago = reader.GetBoolean("pago")
            };

            return new ExpenseResult { Expense = expense };
        }

    }
}
