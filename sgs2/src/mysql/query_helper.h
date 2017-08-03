#ifndef __QUERY_HELPER_H
#define __QUERY_HELPER_H

#include <string>

template <typename... Args>
std::string make_query(const std::string& q, Args... args)
{
    auto query = "call " + q + "(";
    recurse(query, args...);

    return query;
}

template <typename Head>
void recurse(std::string& q, Head h)
{
    add_parameter(q, h);
    q = q + ");";
}

template <typename Head, typename... Tail>
void recurse(std::string& q, Head h, Tail... t)
{
    add_parameter(q, h);
    q = q + ",";
    recurse(q, t...);
}

template <typename T>
void add_parameter(std::string& q, T arg)
{
    q = q + std::to_string(arg);
}

template <>
inline void add_parameter(std::string& q, const char* arg)
{
    q = q + "'" + arg + "'";
}

template <>
inline void add_parameter(std::string& q, std::string arg)
{
    q = q + "'" + arg + "'";
}

#endif
