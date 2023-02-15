#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <map>
#include <string>
#include <variant>


struct commands {
  enum commands_dql {
    SELECT,
    FROM,
    WHERE,
    JOIN,
    UNION
  };
  static const std::map<std::string, commands_dql> dql_map;

  enum commands_ddl {
    CREATE,
    ALTER,
    DROP
  };
  static const std::map<std::string, commands_ddl> ddl_map;

  enum commands_dml {
    INSERT,
    UPDATE,
    DELETE
  };
  static const std::map<std::string, commands_dml> dml_map;

  enum command_none{
    NONE
  };

  using command_types = std::variant<commands_dql, commands_ddl, commands_dml, command_none>;
  const static auto get_command(const std::string user_input);
};

#endif