#include "mysql_connector.h"
#include "../../../core/src/locale/string_helper.h"

namespace mysql_connector
{
    static sql::Driver* g_driver = nullptr;

     thread_local std::shared_ptr<sql::Connection> connection;
     thread_local std::shared_ptr<sql::Statement>  statement;

    void make_connection(std::wstring hostname, int port, std::wstring username, std::wstring password, std::wstring schema)
    {
        std::lock_guard<std::mutex> lock(driver_lock);

        if (!g_driver)
        {
            g_driver = get_driver_instance();
        }

        auto to_string = core::wstring_to_string;

        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = to_string(hostname);
        connection_properties["userName"] = to_string(username);
        connection_properties["password"] = to_string(password);
        connection_properties["schema"] = to_string(schema);
        connection_properties["port"] = port;
        //connection_properties["OPT_RECONNECT"] = true;

        connection.reset(g_driver->connect(connection_properties));

        make_statement();
    }

    void make_statement()
    {
        statement.reset(connection->createStatement());
    }

    std::shared_ptr<sql::Connection> get_connection()
    {
        return connection;
    }

    std::shared_ptr<sql::Statement> get_statement()
    {
        return statement;
    }

    std::shared_ptr<sql::ResultSet> execute_query(const std::string& query)
    {
        try
        {
            std::shared_ptr<sql::ResultSet> res(statement->executeQuery(query));
            return res;
        }
        catch (sql::SQLException &e) 
        {

            return nullptr;
        }
    }

    void execute(const std::string& query)
    {
        try
        {
            statement->executeQuery(query);
        }
        catch (sql::SQLException &e)
        {

        }
    }
}
