/*  
    This file is part of FISCO BCOS.

	FISCO BCOS is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FISCO BCOS is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FISCO BCOS.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * @file: ConfigParser.h
 * @author: fisco-dev
 * @date: 2019.9.1
 * @function: config parser
 */

#pragma once
#include <exception>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <fstream>
#include <json/json.h>
#include "easylog.h"

using namespace std;

namespace dev
{
namespace eth
{
//interface of Configuration class
template <typename T>
class ConfigParserInterface
{
public:
    ConfigParserInterface()
    {
    }

    template <typename... Args>
    void create(Args &&... args)
    {
        //LOG(DEBUG)<<"Begin create config_obj"<<std::endl;
        config_obj = make_shared<T>(std::forward<Args>(args)...);
    }

    /*
             * @function: read configuration value of key, default is default_value 
             * @param: 1. key: configuration key; 2. value: value of key;
             *         3. default_value: default value of key
             * @ret: 1. true: value of key is set by configuration;
             *       2. false：value of key is set by default_value;
             */
    template <typename... Args>
    bool get_value(Args &&... args)
    {
        return config_obj->get_value(std::forward<Args>(args)...);
    }

    template <typename S, typename... Args>
    S get_value(Args &&... args)
    {
        return config_obj->template get_value<S>(std::forward<Args>(args)...);
    }

    /*
             *@function: set value for key;
             *@params: key; 
             */
    template <typename... Args>
    void set_value(Args &&... args)
    {
        return config_obj->set_value(std::forward<Args>(args)...);
    }

    //dump configuration
    template <typename... Args>
    void dump_config(Args &&... args)
    {
        return config_obj->dump_config(std::forward<Args>(args)...);
    }

    //load configuration
    template <typename... Args>
    void load_config(Args &&... args)
    {
        return config_obj->load_config(std::forward<Args>(args)...);
    }

private:
    shared_ptr<T> config_obj;
};

//####base class of json parser######
enum JsonConfigType
{
    JsonString,
    JsonFile
};
class JsonConfigParser
{
private:
    //forbid assignment and default transition
    JsonConfigParser(const JsonConfigParser &);
    JsonConfigParser();
    JsonConfigParser &operator=(const JsonConfigParser &);

public:
    //init Json::value according to json string or json file
    int error;
    JsonConfigParser(string const &json_str,
                     JsonConfigType type = JsonFile) : input_type(type)
    {
        error = 0;
        Json::Reader reader;
        if (JsonString == type)
        {
            if (!reader.parse(json_str.c_str(), json_pt))
            {
                error = 1;
            }
        }
        //default is JsonFile
        else
        {
            config_file = json_str;
            std::ifstream ifs(json_str);
            if (!reader.parse(ifs, json_pt))
            {
                error = 1;
            }
        }
    }

    inline bool get_value_inline(const string &key, bool &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asBool();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, int &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asInt();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, uint &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asUInt();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, int64_t &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asInt64();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, uint64_t &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asUInt64();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, double &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asDouble();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    inline bool get_value_inline(const string &key, string &value, Json::Value &pt)
    {
        bool ret = false;
        try
        {
            ret = pt.isMember(key);
        }
        catch (exception &error_msg)
        {
            LOG(ERROR) << "find key error" << error_msg.what();
            error = 1;
            return false;
        }
        if (ret)
        {
            try
            {
                value = pt[key].asString();
            }
            catch (exception &error_msg)
            {
                LOG(ERROR) << "get value error" << error_msg.what();
                error = 1;
            }
            return true;
        }
        else
        {
            error = 1;
            return false;
        }
    }

    /*@function: get value of key from json string, result is stored in value
             *@param: 1. key; 
             *        2. value: value of key;
             *        3. default_value: default value of key
             *@ret: case 1. value of key is obtained from configuration: true;
             *      case 2. value of key is obtained from default_value: false;
             */
    template <typename T>
    bool get_value(const string &key, T &value, Json::Value &pt)
    {
        return get_value_inline(key, value, pt);
    }

    template <typename T>
    bool get_value(const string &key, T &value, const T &default_value, Json::Value &pt)
    {
        value = default_value;
        return get_value(key, value, pt);
    }

    template <typename T>
    bool get_value(const string &key, T &value, const T &default_value)
    {
        return get_value(key, value, default_value, json_pt);
    }

    template <typename T>
    bool get_value(const string &key, T &value)
    {
        return get_value(key, value, json_pt);
    }

    template <typename T>
    T get_value(const string &key)
    {
        T value;
        get_value(key, value, json_pt);
        return value;
    }

    /*
             *@function: set value of key;
             *@params: key;
             */
    template <typename T>
    void set_value(const string &key, const T &value)
    {
        json_pt[key] = value;
    }

    template <typename T>
    static void convert_to_json_str(std::string &json_str,
                                    std::map<string, T> value_map)
    {
        Json::Value root_json;
        for (auto item : value_map)
            root_json[item.first] = item.second;
        Json::StyledWriter writer;
        json_str = writer.write(root_json);
    }

protected:
    Json::Value json_pt;
    JsonConfigType input_type;
    string config_file = "";
}; // namespace eth
} // namespace eth
} // namespace dev
