#include "cli.hpp"
#include <iostream>
#include <stdexcept>

CLIArgs CLIParser::parse(int argc, char *argv[])
{
  CLIArgs args;

  if (argc < 2)
  {
    throw std::runtime_error("Usage: lpmg <command> [package] [options]");
  }

  args.command = argv[1];

  if (args.command != "install" &&
      args.command != "remove" &&
      args.command != "search" &&
      args.command != "update" &&
      args.command != "full-upgrade")
  {
    throw std::runtime_error("Error: unknown command '" + args.command + "'");
  }

  // write special case for full-upgrade since it does not need package name
  // TO DO: maybe refactor this later
  if (args.command == "full-upgrade")
  {
    // just full upgrade all. maybe need special loop later

    return args;
  }

  // 對 install/remove/search/update 之類的 command，第二個參數通常是 package
  if (argc >= 3)
  {
    args.package = argv[2];
  }
  else if (args.command == "install" || args.command == "remove")
  {
    throw std::runtime_error("Error: package name required for this command");
  }

  // 解析額外 flag / options
  for (int i = 3; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg == "-v" || arg == "--verbose")
    {
      args.verbose = true;
    }
    else
    {
      args.extra.push_back(arg); // 暫存未識別參數
    }
  }

  return args;
}
