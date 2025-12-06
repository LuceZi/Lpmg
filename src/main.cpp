#include "parser/cli.hpp"
#include "detectors/detector.hpp"
#include "backends/backend.hpp"
#include "core/core.hpp"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[])
{
  CLIParser parser;
  try
  {
    CLIArgs args = parser.parse(argc, argv);

    if (args.command == "full-upgrade")
    {
      std::cout << "Performing full upgrade...\n";
      if (AutoFullUpgrade() != CoreError::OK)
      {
        std::cerr << "Full upgrade failed.\n";
        return 1;
      }
      std::cout << "Full upgrade completed.\n";
      // dector loop heire
      return 0;
    }

    // 這裡呼叫 core (後續實作)
    std::cout << "Command: " << args.command << "\n";
    std::cout << "Package: " << args.package << "\n";
    if (args.verbose)
      std::cout << "Verbose mode ON\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}