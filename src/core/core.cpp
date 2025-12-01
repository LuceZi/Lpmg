#include "backend.hpp"
#include <iostream>
#include <vector>

// demo function showing usage of PacmanBackend
void CoreUpdateLoop(const std::vector<std::string> &packages)
{
  // 創建 pacman backend 物件
  PacmanBackend pac;

  // 更新資料庫
  auto update_db = pac.Update();
  if (update_db.code != BackendError::OK)
  {
    std::cerr << "Update DB failed:\n"
              << update_db.message << "\n";
    return;
  }

  // 迴圈升級每個套件
  for (const auto &pkg : packages)
  {
    auto res = pac.Install(pkg);
    if (res.code != BackendError::OK)
    {
      std::cerr << "Failed to install " << pkg << ":\n"
                << res.message << "\n";
    }
    else
    {
      std::cout << pkg << " installed/upgraded successfully.\n";
    }
  }
}
