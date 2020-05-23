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

class Stats 
{
   
public:
    Stats()
    {
        //m_protocol.clear();

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

    

private:
    std::map<string_view, int> m_methods_stats;
    std::map<string_view, int> m_uri_stats;
    
    std::array<int*, static_cast<int>(EHttpMethods::MAX) + 1> m_methods_array;
    std::array<int*, static_cast<int>(EUri::MAX) + 1> m_uris_array;
};

std::vector<std::string_view> split_str(std::string_view str);

HttpRequest ParseRequest(string_view line);