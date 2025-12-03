#include "backend.hpp"
#include <cstdio>
#include <memory>
#include <array>
#include <sys/wait.h>

PackageResult PacmanBackend::Detect()
{
  return RunCommand("pacman -Qn ");
}

PackageResult PacmanBackend::Install(const std::string &pkg)
{
  return RunCommand("sudo pacman -S --noconfirm " + pkg);
}

PackageResult PacmanBackend::Remove(const std::string &pkg)
{
  return RunCommand("sudo pacman -R --noconfirm " + pkg);
}

PackageResult PacmanBackend::Update()
{
  return RunCommand("sudo pacman -Sy");
}

PackageResult PacmanBackend::Upgrade()
{
  return RunCommand("sudo pacman -Syu --noconfirm");
}

PackageResult PacmanBackend::RunCommand(const std::string &cmd)
{
  std::array<char, 256> buffer{};
  std::string output;

  FILE *pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    return {BackendError::EXEC_FAIL, "Failed to spawn process", -1};

  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    output += buffer.data();

  int status = pclose(pipe);

  // 正確解析 exit code
  int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

  PackageResult ret;
  ret.exit_code = exit_code;
  ret.message = output;

  if (exit_code == 0)
    ret.code = BackendError::OK;
  else
    ret.code = BackendError::EXEC_FAIL;

  return ret;
}