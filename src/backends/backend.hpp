#pragma once
#include <string>
#include <vector>

enum class BackendError
{
  OK = 0,
  INVALID_ARGUMENT,
  EXEC_FAIL,
  PACKAGE_NOT_FOUND,
  UPDATE_FAILED,
  UNKNOWN
};

struct PackageResult
{
  BackendError code;
  std::string message;
  int exit_code;
};

//=============================================================
class Backend
{
public:
  virtual ~Backend() {}

  virtual PackageResult Install(const std::string &pkg) = 0;
  virtual PackageResult Remove(const std::string &pkg) = 0;
  virtual PackageResult Update() = 0;
  virtual PackageResult Upgrade() = 0;
  virtual PackageResult Detect() = 0;
};

class PacmanBackend : public Backend
{
public:
  PackageResult Install(const std::string &pkg) override;
  PackageResult Remove(const std::string &pkg) override;
  PackageResult Update() override;
  PackageResult Upgrade() override;
  PackageResult Detect() override;

private:
  PackageResult RunCommand(const std::string &cmd);
};

class AurBackend : public Backend
{
public:
  PackageResult Install(const std::string &pkg) override;
  PackageResult Remove(const std::string &pkg) override;
  PackageResult Update() override;
  PackageResult Upgrade() override;
  PackageResult Detect() override;

private:
  PackageResult RunCommand(const std::string &cmd);
};
