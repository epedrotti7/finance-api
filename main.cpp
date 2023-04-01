#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/despesa")
    ([]()
     {
        crow::json::wvalue response;
        response["Descricao"] = "Fatal Model";
        return response; 
    });

    CROW_ROUTE(app, "/hello/<int>")
    ([](int count) -> crow::response {
        crow::json::wvalue response;
        if (count > 100) {
            return crow::response(400);
        }
        std::ostringstream os;
        os << count << " bottles of beer!";
        response["message"] = os.str();
        return crow::response(response);
    });

    app.port(8080).multithreaded().run();

    return 0;
}