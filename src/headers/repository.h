#pragma once

#include <jsoncpp/json/json.h>
#include <mysql/mysql.h>
#include <string>

Json::Value get_users(MYSQL *connection);
