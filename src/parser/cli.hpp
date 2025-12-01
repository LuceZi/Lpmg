#pragma once
#include <string>
#include <vector>

struct CLIArgs
{
  std::string command;            // install / remove / search / update / full-upgrade
  std::string package;            // package name
  bool verbose = false;           // example flag
  std::vector<std::string> extra; // for future options
};

class CLIParser
{
public:
  CLIArgs parse(int argc, char *argv[]);
};
