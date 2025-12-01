#pragma once
#include <string>
#include <vector>

//=============================================================
// 錯誤代碼列舉
enum class BackendError
{
  OK = 0,
  INVALID_ARGUMENT,
  EXEC_FAIL,
  PACKAGE_NOT_FOUND,
  UPDATE_FAILED,
  UNKNOWN
};

//=============================================================
// 套件操作結果結構
struct PackageResult
{
  BackendError code;
  std::string message;
  int exit_code; // system() 或 popen() 的原始碼
};

//=============================================================
// 抽象基底類別
class Backend
{
public:
  virtual ~Backend() {}

  virtual PackageResult Install(const std::string &pkg) = 0;
  virtual PackageResult Remove(const std::string &pkg) = 0;
  virtual PackageResult Update() = 0;
  virtual PackageResult Upgrade() = 0;
};

//=============================================================
// Pacman 後端實作
class PacmanBackend : public Backend
{
public:
  PackageResult Install(const std::string &pkg) override;
  PackageResult Remove(const std::string &pkg) override;
  PackageResult Update() override;
  PackageResult Upgrade() override;

private:
  PackageResult RunCommand(const std::string &cmd);
};