#include <DxLib.h>
#include <Windows.h>

#include "SceneManager.h"
#include "Application.h"
void SetupGame() {
  auto& SM = SceneManager::GetInstance();
  SM.SetStartupLevelPath(".BLevel");
  SetMouseDispFlag(1);
}

int WINAPI
WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, LPSTR CommandLine, int ShowCommand) {
  (void)Instance;
  (void)PreviousInstance;
  (void)CommandLine;
  (void)ShowCommand;
  Application::SetGameSetupCallback(&SetupGame);
  Application App;
  return App.Run() ? 0 : 1;
}
