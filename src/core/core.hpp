#pragma once
#include <iostream>
#include <vector>
#include <string>

enum class CoreError
{
  OK = 0,
  CoreError,
  UNKNOWN
};

CoreError AutoFullUpgrade();

std::vector<std::string> GetPackageManagers();
