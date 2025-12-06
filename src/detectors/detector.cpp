#include "../detectors/detector.hpp"
#include "../backends/backend.hpp"
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

bool __commandExists(const std::string &cmd)
{
  return system(("command -V " + cmd + " >/dev/null 2>&1").c_str()) == 0;
}

std::vector<std::string> _detectPackageManagers()
{
  std::vector<std::string> managers;
  if (__commandExists("apt"))
    managers.push_back("apt");
  if (__commandExists("pacman"))
    managers.push_back("pacman");
  if (__commandExists("yay"))
    managers.push_back("yay");
  return managers;
}

std::pair<DetectorError, std::vector<std::string>> DetectPackageManagers()
{
  auto managers = _detectPackageManagers();
  if (managers.empty())
    return {DetectorError::SCAN_FAIL, {}};
  return {DetectorError::OK, managers};
}

// fill the struct~~ do it later
// std::pair<DetectorError, std::vector<package_info>> DetectInstalledPackages(const std::string &manager)