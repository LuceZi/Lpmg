#pragma once
#include "detector.hpp"
#include "backend.hpp"
#include <iostream>
#include <vector>
#include <string>

// generate spec backend for package managers
Backend *CreateBackendForManager(const std::string &mgr)
{
  if (mgr == "pacman")
    return new PacmanBackend();
  // else if (mgr == "aur") return new AurBackend();
  // else if (mgr == "apt") return new AptBackend();

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

void AutoFullUpdate()
{
  // Get all package managers
  auto managers = GetPackageManagers();
  for (const auto &mgr : managers)
  {
    std::cout << "Updating packages for manager: " << mgr << std::endl;

    Backend *backend = CreateBackendForManager(mgr);
    if (!backend)
      continue;

    // Perform the update operation
    auto res = backend->Update();
    if (res.code != BackendError::OK)
    {
      std::cerr << "Failed to update packages for " << mgr << ": " << res.message << std::endl;
      continue; // Continue with the next manager even if one fails
    }
    delete backend; // REMEMBER TO DELETE THE BACKEND INSTANCE
    std::cout << "Successfully updated packages for " << mgr << ": " << res.message << std::endl;
  }
}
