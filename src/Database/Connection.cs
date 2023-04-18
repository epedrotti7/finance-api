using Microsoft.Extensions.Logging;
using MySql.Data.MySqlClient;

namespace FinanceApi.Database
{
    public class Connection
    {
        private readonly string _connectionString;

        public Connection(string connectionString)
        {
            _connectionString = connectionString;
        }

        public MySqlConnection GetConnection()
        {
            MySqlConnection connection = new MySqlConnection(_connectionString);
            connection.Open();

            return connection;
        }
    }
}
