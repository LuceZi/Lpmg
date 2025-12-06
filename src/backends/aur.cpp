#include "backend.hpp"
#include <cstdio>
#include <memory>
#include <array>
#include <sys/wait.h>

PackageResult AurBackend::Detect()
{
  return RunCommand("yay -Qm ");
}

PackageResult AurBackend::Install(const std::string &pkg)
{
  return RunCommand("yay -S --noconfirm " + pkg);
}

PackageResult AurBackend::Remove(const std::string &pkg)
{
  return RunCommand("yay -R --noconfirm " + pkg);
}

PackageResult AurBackend::Update()
{
  return RunCommand("yay -Sy");
}

// aur and pacman use same command for update
PackageResult AurBackend::Upgrade()
{
  return RunCommand("yay -Syu --noconfirm");
}

PackageResult AurBackend::RunCommand(const std::string &cmd)
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