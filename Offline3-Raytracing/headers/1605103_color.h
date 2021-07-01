//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_COLOR_H
#define OFFLINE2_1605103_COLOR_H

#endif //OFFLINE2_1605103_COLOR_H

class Color {
public:
    double r,g,b;

    Color() {
        r = g = b = 0;
    }

    Color(double red, double green, double blue){
        r = red;
        g = green;
        b = blue;
    }

    Color operator*(const double &coefficient) const{
        Color result;
        result.r = r * coefficient;
        result.g = g * coefficient;
        result.b = b * coefficient;
        return result;
    }

    Color operator+(const Color &color) const{
        Color result;
        result.r = r + color.r;
        result.g = g + color.g;
        result.b = b + color.b;
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &t) {
        os <<"("<< t.r << ", " << t.g << ", " << t.b << ")" << std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Color &v) {
        is >> v.r >> v.g >> v.b;
        return is;
    }

};