#pragma once

namespace Utility::Math
{
    template <typename T>
    auto map_value(T value, T fromLow, T fromHigh, T toLow, T toHigh) -> T
    {
        return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
    }
}