#pragma once

namespace Utility::File
{
    template <typename T>
    T map_value(T value, T fromLow, T fromHigh, T toLow, T toHigh)
    {
        return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
    }
}