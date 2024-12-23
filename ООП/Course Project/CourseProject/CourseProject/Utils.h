#pragma once
#include <random>

class Utils
{
public:
    static int randInclusive(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(min, max);

        return dis(gen);
    }

    static float repeat(float t, float min, float max)
    {
        if (t > max)
        {
            t -= (max - min);
        }
        else if (t < min)
        {
            t += (max - min);
        }

        return t;
    }
};

