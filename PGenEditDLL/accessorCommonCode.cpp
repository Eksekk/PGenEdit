#include "pch.h"
#include "main.h"
#include "accessorCommonCode.h"

std::stringstream accessorDetail::ss;

void accessorDetail::printInventory(int itemSize, const void* p, int width, int height)
{
    ss.clear();
    char ch = ss.fill();
    ss.fill(' ');
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int add = y * width + x;
            // ternary conditional operands must have same type
            std::string str = itemSize == 2 ? std::to_string(*((sword_t*)p + add)) : std::to_string(*((sdword_t*)p + add));
            ss << std::setw(5) << str;
        }
        ss << "\n";
    }
    ss.fill(ch);
    if (IsDebuggerPresent())
    {
        OutputDebugStringA(ss.str().data());
    }
    else
    {
        std::cout << ss.str();
    }
}