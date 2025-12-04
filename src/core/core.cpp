#pragma once
#include "core.hpp"
#include "detector.hpp"
#include "backend.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// generate spec backend for package managers
Backend *__CreateBackendForManager(const std::string &mgr)
{
  if (mgr == "pacman")
    return new PacmanBackend();
  else if (mgr == "aur") return new AurBackend();
    return new AurBackend();
  //else if (mgr == "apt") return new AptBackend();

  std::cerr << "Unsupported package manager: " << mgr << std::endl;
  return nullptr;
}

std::vector<std::string> GetPackageManagers()
{
  auto result = DetectPackageManagers();
  if (result.first != DetectorError::OK)
  {
    std::cerr << "Failed to detect package managers." << std::endl;
    return {};
  }
  return result.second;
}

void AutoFullUpgrade()
{
  auto managers = GetPackageManagers();
  //if only aur detected and running as root
  if (managers.size() == 1 && managers[0] == "aur")
  {
    std::cerr << "Warning: Only AUR detected. It's recommended to run full update as a normal user." << std::endl;
    return;
  }

  //if aur and pacman both detected, remove pacman from list
  if (managers.size() >= 2 && std::find(managers.begin(), managers.end(), "aur") != managers.end() && std::find(managers.begin(), managers.end(), "pacman") != managers.end())
  {
    managers.erase(std::remove(managers.begin(), managers.end(), "pacman"), managers.end());
  }

  for (const auto &mgr : managers)
  {
    Backend *backend = __CreateBackendForManager(mgr);
    if (!backend)
      continue;

    std::cout << "Updating package manager: " << mgr << std::endl;
    PackageResult updateResult = backend->Upgrade();
    if (updateResult.code != BackendError::OK)
    {
      std::cerr << "Failed to update " << mgr << ": " << updateResult.message << std::endl;
      delete backend;
      continue;
    }
    std::cout << "Upgrade result for " << mgr << ": " << updateResult.message << std::endl;

    delete backend;
  }
}
