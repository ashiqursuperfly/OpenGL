#include "headers/1605103_input_handler.h"
#include "headers/1605103_zbuffer.h"

int main() {
    InputHandler inputHandler = InputHandler("inputs/2/scene.txt");
    inputHandler.processInput();

    ZBufferExecutor zBufferExecutor = ZBufferExecutor("inputs/2/config.txt");

    return 0;
}
