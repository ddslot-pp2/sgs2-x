#include "mysql_connector.h"
#include "../../../core/src/locale/string_helper.h"

namespace mysql_connector
{
    static sql::Driver* g_driver = nullptr;

     thread_local std::shared_ptr<sql::Connection> connection;
     thread_local std::shared_ptr<sql::Statement>  statement;

    void make_connection(std::wstring ip, std::wstring id, std::wstring password, std::wstring schema)
    {
        std::lock_guard<std::mutex> lock(driver_lock);
        if (!g_driver)
        {
            g_driver = get_driver_instance();
        }

        //ip = L"tcp://" + ip;

        //sql::Driver* driver = get_driver_instance();
        //std::shared_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "root", "1111"));

        sql::SQLString _ip = "tcp://127.0.0.1:3306";
        sql::SQLString _id = core::wstring_to_string(id);
        sql::SQLString _password = core::wstring_to_string(password);

        std::shared_ptr<sql::Connection> con(g_driver->connect(_ip, _id, _password));
        //std::shared_ptr<sql::Connection> con(g_driver->connect("tcp://127.0.0.1:3306", "root", "1111"));

        if (schema != L"")
        {
            con->setSchema(core::wstring_to_string(schema).c_str());
        }

        if (con)
        {
            connection = con;
        }
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
}
