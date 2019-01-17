#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <string_view>
#include "crow/utility.h"

namespace crow
{
    enum class HTTPMethod
    {
#ifndef DELETE
        DELETE = 0,
        GET,
        HEAD,
        POST,
        PUT,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH,
        PURGE,
#endif

        Delete = 0,
        Get,
        Head,
        Post,
        Put,
        Connect,
        Options,
        Trace,
        Patch,
        Purge,


        InternalMethodCount,
        // should not add an item below this line: used for array count
    };

    static constexpr std::string_view strDel("DELETE");
    static constexpr std::string_view strGet("GET");
    static constexpr std::string_view strHead("HEAD");
    static constexpr std::string_view strPost("POST");
    static constexpr std::string_view strPut("PUT");
    static constexpr std::string_view strConnect("CONNECT");
    static constexpr std::string_view strOptions("OPTIONS");
    static constexpr std::string_view strTrace("TRACE");
    static constexpr std::string_view strPatch("PATCH");
    static constexpr std::string_view strPurge("PURGE");

    inline std::string_view method_name(HTTPMethod method)
    {
        switch(method)
        {
            case HTTPMethod::Delete:
                return strDel;
            case HTTPMethod::Get:
                return strGet;
            case HTTPMethod::Head:
                return strHead;
            case HTTPMethod::Post:
                return strPost;
            case HTTPMethod::Put:
                return strPut;
            case HTTPMethod::Connect:
                return strConnect;
            case HTTPMethod::Options:
                return strOptions;
            case HTTPMethod::Trace:
                return strTrace;
            case HTTPMethod::Patch:
                return strPatch;
            case HTTPMethod::Purge:
                return strPurge;
            default:
                return "invalid";
        }
        return "invalid";
    }

    enum class ParamType
    {
        INT,
        UINT,
        DOUBLE,
        STRING,
        PATH,

        MAX
    };

    struct routing_params
    {
        std::vector<int64_t> int_params;
        std::vector<uint64_t> uint_params;
        std::vector<double> double_params;
        std::vector<std::string> string_params;

        void debug_print() const
        {
            std::cerr << "routing_params" << std::endl;
            for(auto i:int_params)
                std::cerr<<i <<", " ;
            std::cerr<<std::endl;
            for(auto i:uint_params)
                std::cerr<<i <<", " ;
            std::cerr<<std::endl;
            for(auto i:double_params)
                std::cerr<<i <<", " ;
            std::cerr<<std::endl;
            for(auto& i:string_params)
                std::cerr<<i <<", " ;
            std::cerr<<std::endl;
        }

        template <typename T>
        T get(unsigned) const;

    };

    template<>
    inline int64_t routing_params::get<int64_t>(unsigned index) const
    {
        return int_params[index];
    }

    template<>
    inline uint64_t routing_params::get<uint64_t>(unsigned index) const
    {
        return uint_params[index];
    }

    template<>
    inline double routing_params::get<double>(unsigned index) const
    {
        return double_params[index];
    }

    template<>
    inline std::string routing_params::get<std::string>(unsigned index) const
    {
        return string_params[index];
    }
}

constexpr crow::HTTPMethod operator "" _method(const char* str, size_t len)
{
    std::string_view strMethod(str, len);
    return
        strMethod == crow::strGet ? crow::HTTPMethod::Get :
        strMethod == crow::strDel ? crow::HTTPMethod::Delete :
        strMethod == crow::strHead ? crow::HTTPMethod::Head :
        strMethod == crow::strPost ? crow::HTTPMethod::Post :
        strMethod == crow::strPut ? crow::HTTPMethod::Put :
        strMethod == crow::strOptions ? crow::HTTPMethod::Options :
        strMethod == crow::strConnect ? crow::HTTPMethod::Connect :
        strMethod == crow::strTrace ? crow::HTTPMethod::Trace :
        strMethod == crow::strPatch ? crow::HTTPMethod::Patch :
        strMethod == crow::strPurge ? crow::HTTPMethod::Purge :
        throw std::runtime_error("invalid http method");
}
