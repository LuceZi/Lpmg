#pragma once
#include "../backends/backend.hpp"
#include <iostream>
#include <vector>
#include <string>

static void AutoFullUpdate();

// generate spec backend for package managers
Backend *CreateBackendForManager(const std::string &mgr);

std::vector<std::string> GetPackageManagers();
