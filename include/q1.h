#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <functional>
#include <iostream>
namespace q1 {
inline double gradient_descent(double initial_value, double step_size, double (*func)(double a))
{
    double value {};
    value = func(initial_value);
    double i { initial_value + step_size };

    while (true) {

        if (func(i) < value)
            value = func(i);

        if (value == func(i)) {
            if (value < func(i - step_size) && value < func(i + step_size))
                break;

            // If func(initial_value) is minimum:
        } else if (value < func(i - 2 * step_size))
            return initial_value;

        i += step_size;
    }
    std::cout << value << ", " << i << std::endl;
    return i;
}

}
#endif // Q1_H