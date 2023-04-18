using FinanceApi.Database;
using FinanceApi.Structs;
using FinanceApi.Repositories;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace FinanceApi
{
    public class Startup
    {
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddSingleton<Connection>(_ =>
            {
                string connectionString = "server=127.0.0.1;port=3306;database=finances;user=finance;password=finance";
                return new Connection(connectionString);
            });
            services.AddScoped<IExpenseRepository, ExpenseRepository>();

            services.AddControllers();
        }

        public void Configure(IApplicationBuilder app,
         IWebHostEnvironment env,
         ILogger<Startup> logger,
         ILogger<Connection> connectionLogger,
         Connection connection)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.UseRouting();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapGet("/despesas/{userId}", async context =>
                {
                    int userId = int.Parse(context.Request.RouteValues["userId"].ToString());
                    var expenseRepository = context.RequestServices.GetService<IExpenseRepository>();
                    var expenses = await expenseRepository.ListExpensesByUserId(userId);
                    var response = new { despesas = expenses };

                    await context.Response.WriteAsJsonAsync(response);
                });
            });

            connectionLogger.LogInformation("Conexão estabelecida com sucesso");
        }
    }
}
