#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <functional>
#include <iostream>

namespace q1 {

template <typename T, typename Func>
inline double gradient_descent(T initial_value, T step_size, Func func)
{
    T value { func(initial_value) };
    T i { initial_value + step_size };

    while (true) {

        if (func(i) < value) {

            value = func(i);

            if (value < func(i - step_size) && value < func(i + step_size))
                break;

            i += step_size;
        }
        if (func(i) > value)
            i -= 2 * step_size;
    }

    return i;
}

template <typename T, typename Func>
inline double gradient_descent(T initial_value, T step_size)
{
    Func func;
    T value { func(initial_value) };
    T i { initial_value + step_size };

    while (true) {

        if (func(i) < value) {

            value = func(i);

            if (value < func(i - step_size) && value < func(i + step_size))
                break;

            i += step_size;
        }
        if (func(i) > value)
            i -= 2 * step_size;
    }

    return i;
}

}
#endif // Q1_H