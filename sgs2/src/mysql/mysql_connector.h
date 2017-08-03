#ifndef __MYSQL_CONNECTOR_H
#define __MYSQL_CONNECTOR_H

#include <mutex>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace mysql_connector
{
    void make_connection(std::wstring hostname, int port, std::wstring username, std::wstring password, std::wstring schema);
    void make_statement();

    std::shared_ptr<sql::Connection> get_connection();
    std::shared_ptr<sql::Statement>  get_statement();

    std::unique_ptr<sql::ResultSet> execute_query(const std::string& query);

    static std::mutex driver_lock;
}

#endif
