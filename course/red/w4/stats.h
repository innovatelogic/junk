#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <string>
#include <array>
#include <vector>

using namespace std;

enum class EHttpMethods : size_t
{
    Get = 0,
    Post,
    Put,
    Delete,
    MAX
};

enum class EUri : size_t
{
    Main = 0,
    Order,
    Product,
    Basket,
    Help,
    MAX
};

static const std::string STR_METHOD_GET = "GET";
static const std::string STR_METHOD_POST = "POST";
static const std::string STR_METHOD_PUT = "PUT";
static const std::string STR_METHOD_DELETE = "DELETE";
static const std::string STR_METHOD_UNKNOWN = "UNKNOWN";

static const std::string STR_URI_MAIN = "/";
static const std::string STR_URI_ORDER = "/order";
static const std::string STR_URI_PRODUCT = "/product";
static const std::string STR_URI_BASKET = "/basket";
static const std::string STR_URI_HELP = "/help";
static const std::string STR_URI_UNKNOWN = "unknown";


std::map<std::string, std::string> m_protocol;

class Stats 
{
   
public:
    Stats()
    {
        m_protocol.clear();

        m_methods_stats[STR_METHOD_GET] = 0;
        m_methods_stats[STR_METHOD_POST] = 0;
        m_methods_stats[STR_METHOD_PUT] = 0;
        m_methods_stats[STR_METHOD_DELETE] = 0;
        m_methods_stats[STR_METHOD_UNKNOWN] = 0;

        m_uri_stats[STR_URI_MAIN] = 0;
        m_uri_stats[STR_URI_ORDER] = 0;
        m_uri_stats[STR_URI_PRODUCT] = 0;
        m_uri_stats[STR_URI_BASKET] = 0;
        m_uri_stats[STR_URI_HELP] = 0;
        m_uri_stats[STR_URI_UNKNOWN] = 0;

        m_methods_array[static_cast<int>(EHttpMethods::Get)] = &(m_methods_stats.at(STR_METHOD_GET));
        m_methods_array[static_cast<int>(EHttpMethods::Post)] = &m_methods_stats.at(STR_METHOD_POST);
        m_methods_array[static_cast<int>(EHttpMethods::Put)] = &m_methods_stats.at(STR_METHOD_PUT);
        m_methods_array[static_cast<int>(EHttpMethods::Delete)] = &m_methods_stats.at(STR_METHOD_DELETE);
        m_methods_array[static_cast<int>(EHttpMethods::MAX)] = &m_methods_stats.at(STR_METHOD_UNKNOWN);

        m_uris_array[static_cast<int>(EUri::Main)] = &m_uri_stats.at(STR_URI_MAIN);
        m_uris_array[static_cast<int>(EUri::Order)] = &m_uri_stats.at(STR_URI_ORDER);
        m_uris_array[static_cast<int>(EUri::Product)] = &m_uri_stats.at(STR_URI_PRODUCT);
        m_uris_array[static_cast<int>(EUri::Basket)] = &m_uri_stats.at(STR_URI_BASKET);
        m_uris_array[static_cast<int>(EUri::Help)] = &m_uri_stats.at(STR_URI_HELP);
        m_uris_array[static_cast<int>(EUri::MAX)] = &m_uri_stats.at(STR_URI_UNKNOWN);
    }

    void AddMethod(string_view method)
    {
        if (method == STR_METHOD_GET)
         {
            (*m_methods_array[static_cast<int>(EHttpMethods::Get)])++;
        } 
        else if (method == STR_METHOD_POST) 
        {
           (*m_methods_array[static_cast<int>(EHttpMethods::Post)])++;
        }
        else if (method == STR_METHOD_PUT) 
        {
           (*m_methods_array[static_cast<int>(EHttpMethods::Put)])++;
        }
        else if (method == STR_METHOD_DELETE)
        {
            (*m_methods_array[static_cast<int>(EHttpMethods::Delete)])++;
        }
        else
        {
            (*m_methods_array[static_cast<int>(EHttpMethods::MAX)])++;
        }
    }

    void AddUri(string_view uri)
    {
        if (uri == STR_URI_MAIN) {
            (*m_uris_array[static_cast<int>(EUri::Main)])++;
        } else if (uri == STR_URI_ORDER) {
            (*m_uris_array[static_cast<int>(EUri::Order)])++;
        } else if (uri == STR_URI_PRODUCT) {
            (*m_uris_array[static_cast<int>(EUri::Product)])++;
        } else if (uri == STR_URI_BASKET) {
            (*m_uris_array[static_cast<int>(EUri::Basket)])++;
        } else if (uri == STR_URI_HELP) {
            (*m_uris_array[static_cast<int>(EUri::Help)])++;
        } else {
            (*m_uris_array[static_cast<int>(EUri::MAX)])++;
        }
    }

    const map<string_view, int>& GetMethodStats() const { return m_methods_stats; }
    const map<string_view, int>& GetUriStats() const { return m_uri_stats; }

    //static std::map<std::string, std::string> m_protocol;

private:
    std::map<string_view, int> m_methods_stats;
    std::map<string_view, int> m_uri_stats;
    
    std::array<int*, static_cast<int>(EHttpMethods::MAX) + 1> m_methods_array;
    std::array<int*, static_cast<int>(EUri::MAX) + 1> m_uris_array;
};

std::vector<std::string_view> split_str(std::string_view str)
{
    vector<std::string_view> out;

    //std::cout << str << std::endl;

    size_t pos = str.find_first_not_of(" ");
    const size_t pos_end = str.npos;

    while (true)
    {
        size_t space = str.find(' ', pos);

        out.push_back(space == pos_end
            ? str.substr(pos)
            : str.substr(pos, space - pos));

            //std::cout << out[out.size() - 1] << " ";

        if (space == pos_end){
            break;
        }
        pos = space + 1;
    }

    //std::cout << endl;

    //std::cout << "out: " << out.size() << " " << out[0] << ' ' << out[1] << ' ' << out[2] << std::endl;

    return out;
}

HttpRequest ParseRequest(string_view line)
{
    HttpRequest out;

    std::vector<std::string_view> r = split_str(line);

    std::string_view method = r[0];
    std::string_view uri = r[1];
    std::string_view protocol = r[2];

    //std::cout << "AddMethod" << r[0] << ' ' << r[1] << ' ' << r[2] << std::endl;

    if (method == STR_METHOD_GET) {
        out.method = STR_METHOD_GET;
    } else if (method == STR_METHOD_POST) {
        out.method = STR_METHOD_POST;
    }
    else if (method == STR_METHOD_PUT) {
       out.method = STR_METHOD_PUT;
    }
    else if (method == STR_METHOD_DELETE){
        out.method = STR_METHOD_DELETE;
    } else {
        out.method = STR_METHOD_UNKNOWN;
    }

    if (uri == STR_URI_MAIN) {
        out.uri = STR_URI_MAIN;
    } else if (uri == STR_URI_ORDER) {
        out.uri = STR_URI_ORDER;
    } else if (uri == STR_URI_PRODUCT) {
        out.uri = STR_URI_PRODUCT;
    } else if (uri == STR_URI_BASKET) {
        out.uri = STR_URI_BASKET;
    } else if (uri == STR_URI_HELP) {
        out.uri = STR_URI_HELP;
    } else {
        out.uri = STR_URI_UNKNOWN;
    }

    if (m_protocol.count(static_cast<std::string>(protocol)) == 0){
        m_protocol[static_cast<std::string>(protocol)] = static_cast<std::string>(protocol);
    }

    out.protocol = m_protocol[static_cast<std::string>(protocol)];

    return out;
}