#pragma once
#include <string>
#include <vector>
#include <unordered_map>

//enumeration for detector errors
enum class DetectorError
{
  OK = 0,
  SCAN_FAIL,
  PARSE_FAIL,
  EMPTY_RESULT,
  UNKNOWN
};

// structure to hold package information
struct package_info
{
  std::string name;
  std::string version;
  std::string source;
};

// Detect available package managers on the system
std::pair<DetectorError, std::vector<std::string>> DetectPackageManagers();



