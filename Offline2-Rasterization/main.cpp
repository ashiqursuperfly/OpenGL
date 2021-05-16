#include "headers/1605103_util.h"
#include "headers/1605103_vector.h"
#include "headers/1605103_matrix.h"
#include "headers/1605103_input_handler.h"



int main() {

    InputHandler inputHandler = InputHandler("inputs/2/scene.txt");

    inputHandler.processInput();

    bool c1 = compareFiles("inputs/2/stage1.txt", "outputs/stage1.txt");
    bool c2 = compareFiles("inputs/2/stage2.txt", "outputs/stage2.txt");
    bool c3 = compareFiles("inputs/2/stage3.txt", "outputs/stage3.txt");

    if (!c1) {
        return 1;
    }
    if (!c2) {
        return 2;
    }
    if (!c3) {
        return 3;
    }
    return 1;

}
