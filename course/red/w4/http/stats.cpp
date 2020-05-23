#include "stats.h"

static std::map<std::string, std::string> m_protocol;

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
        out.method = method;
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
        out.uri = uri;
    }

    if (m_protocol.count(static_cast<std::string>(protocol)) == 0){
        m_protocol[static_cast<std::string>(protocol)] = static_cast<std::string>(protocol);
    }

    out.protocol = m_protocol[static_cast<std::string>(protocol)];

    return out;
}