namespace FinanceApi.Structs
{
    public struct Expense
    {
        public int id { get; set; }
        public int id_usuario { get; set; }
        public string descricao { get; set; }
        public decimal valor { get; set; }
        public string data_vencimento { get; set; }
        public bool pago { get; set; }
    }

    public struct ExpenseResult
    {
        public Expense? Expense { get; set; }
        public string? ErrorMessage { get; set; }
    }

}