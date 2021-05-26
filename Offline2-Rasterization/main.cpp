#include "headers/1605103_input_handler.h"
#include "headers/1605103_zbuffer.h"

int main() {
    InputHandler inputHandler = InputHandler("inputs/1/scene.txt");
    inputHandler.processInput();
    ZBufferExecutor zBufferExecutor = ZBufferExecutor("inputs/1/config.txt", "outputs/stage3.txt");
    zBufferExecutor.applyProcedure();
    zBufferExecutor.generateZBufferOutput();
    zBufferExecutor.generateImage();

    return 0;
}
