#ifndef Q4_H
#define Q4_H

#include <iostream>
#include <numeric>

namespace q4 {

struct Vector2D {

    Vector2D() = default;
    Vector2D(double _x, double _y)
        : x { _x }
        , y { _y }
    {
    }

    double x {};
    double y {};
};

struct Sensor {

    Sensor() = default;
    Sensor(Vector2D _pos, double _accuracy)
        : pos { _pos }
        , accuracy { _accuracy }
    {
    }

    Vector2D pos;
    double accuracy;
};

struct x_mean_num {
    double operator()(double result, Sensor& sensor)
    {
        return result + sensor.pos.x * sensor.accuracy;
    }
};

struct y_mean_num {
    double operator()(double result, Sensor& sensor)
    {
        return result + sensor.pos.y * sensor.accuracy;
    }
};

inline q4::Vector2D kalman_filter(std::vector<Sensor> sensors)
{
    auto size = [&](double result, const Sensor& sensor) { return result + sensor.accuracy; };
    double init {};

    double size_den { std::accumulate(sensors.begin(), sensors.end(), init, size) };

    double weighted_sum_x = std::accumulate(sensors.begin(), sensors.end(), init, x_mean_num()) / size_den;
    double weighted_sum_y = std::accumulate(sensors.begin(), sensors.end(), init, y_mean_num()) / size_den;

    Vector2D v(weighted_sum_x, weighted_sum_y);
    return v;
}

}
#endif // Q4_H