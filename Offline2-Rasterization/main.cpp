#include "headers/1605103_input_handler.h"
#include "headers/1605103_zbuffer.h"

int main() {
    InputHandler inputHandler = InputHandler("inputs/4/scene.txt");
    inputHandler.processInput();
    std::cin.clear();
    ZBufferExecutor zBufferExecutor = ZBufferExecutor("inputs/4/config.txt", "outputs/stage3.txt");
    zBufferExecutor.applyProcedure();
    zBufferExecutor.generateZBufferOutput();
    zBufferExecutor.generateImage();
    std::cin.clear();

    return 0;
}
