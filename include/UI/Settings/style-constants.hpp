#pragma once
#include <SFML/System.hpp>

/**
 * @brief Constants which define the styles.
 * 
 */
namespace Constants
{
    constexpr sf::Uint32 background_color = 0xeeeeeeff;
    namespace PopupMenu
    {
        namespace Button
        {
            constexpr int Width = 150;
            constexpr int Height = 20;
            constexpr int FontSize = 14;
            namespace TextPadding
            {
                constexpr int Left = 10;
                constexpr int Top = 0;
            }
        }
    }
}
