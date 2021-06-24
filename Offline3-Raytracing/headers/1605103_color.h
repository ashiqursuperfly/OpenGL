//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_COLOR_H
#define OFFLINE2_1605103_COLOR_H

#endif //OFFLINE2_1605103_COLOR_H

class Color {
public:
    int r,g,b;

    Color() {
        r = g = b = 0;
    }

    Color(int red, int green, int blue){
        r = red;
        g = green;
        b = blue;
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &t) {
        os <<"("<< t.r << ", " << t.g << ", " << t.b << ")" << std::endl;
        return os;
    }
};