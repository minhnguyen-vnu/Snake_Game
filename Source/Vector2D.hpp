#pragma once
#include <iostream>

struct Vector2D {
	int x, y;

    Vector2D(int x_ = 0, int y_ = 0): x(x_), y(y_) {}
    inline Vector2D operator+(const Vector2D& v2) const {
        return Vector2D(x + v2.x, y + v2.y);
    }
    inline Vector2D operator-(const Vector2D& v2) const {
        return Vector2D(x - v2.x, y - v2.y);
    }
    inline Vector2D operator*(const float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    inline Vector2D& operator+=(const Vector2D& v2) {
        this->x += v2.x;
        this->y += v2.y;
        return *this;
    }
    inline Vector2D& operator-=(const Vector2D& v2) {
        this->x -= v2.x;
        this->y -= v2.y;
        return *this;
    }
    inline bool operator==(const Vector2D& v2) const {
        return (x == v2.x && y == v2.y);
    }
    inline bool operator>=(const Vector2D& v2) const {
        return (x >= v2.x && y >= v2.y);
    }
    inline bool operator<=(const Vector2D& v2) const {
        return (x <= v2.x && y <= v2.y);
    }
    inline bool operator>(const Vector2D& v2) const {
        return (x > v2.x && y > v2.y);
    }
    inline bool operator<(const Vector2D& v2) const {
        return (x < v2.x && y < v2.y);
    }
    void SetPos(const int &x_, const int &y_) {
        x = x_;
        y = y_;
    }
    void SetPos(const Vector2D& v2) {
        x = v2.x;
        x = v2.y;
    }
    void Log(std::string msg = "") {
        std::cout << msg << "(x y) = (" << x << " " << y << ")" << '\n';
    }
};

