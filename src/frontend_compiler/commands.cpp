#include "commands.h"
#include <boost/algorithm/string.hpp>

const std::map<std::string, commands::commands_dql> commands::dql_map{
    {"SELECT", SELECT},
    {"FROM", FROM},
    {"WHERE", WHERE},
    {"JOIN", JOIN},
    {"UNION", UNION}};

const std::map<std::string, commands::commands_ddl> commands::ddl_map{
    {"CREATE", CREATE},
    {"ALTER", ALTER},
    {"DROP", DROP}
};

const std::map<std::string, commands::commands_dml> commands::dml_map{
    {"INSERT", INSERT},
    {"UPDATE", UPDATE},
    {"DELETE", DELETE}
};


const auto commands::get_command(const std::string user_input){
    std::string user_input_copy = user_input;
    boost::to_upper(user_input_copy);
    if(auto command = ddl_map.find(user_input_copy); command != ddl_map.end()){
        return command_types((*command).second);
    }
    if(auto command = dql_map.find(user_input_copy); command != dql_map.end()){
        return command_types((*command).second);
    }
    if(auto command = dml_map.find(user_input_copy); command != dml_map.end()){
        return command_types((*command).second);
    }
    return command_types(NONE);
}