#include <KlaoudeEngine.h>
#include <Window.h>

int main(int argc, char* argv[])
{
  KlaoudeEngine::init();

  KlaoudeEngine::Window window;
  window.create("Name", 800, 600, 0);

  while (1)
  {
    window.swapBuffer();
  }

  return 0;
}
