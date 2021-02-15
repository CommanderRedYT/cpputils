#pragma once

namespace cpputils {

class Crc32Builder
{
public:
    std::size_t write(uint8_t c)
    {
        return write(&c, 1);
    }

    std::size_t write(const uint8_t *buf, std::size_t len)
    {
        auto lenTemp = len;
        while (lenTemp--)
        {
            uint32_t val = (crc ^ * buf++) & 0xFF;
            for (uint8_t i = 0; i < 8; i++)
            {
                val = val & 1 ? (val>>1)^0xEDB88320 : val>>1;
            }
            crc = val^crc>>8;
        }

        return len;
    };

    uint32_t hash() const
    {
        return crc ^ 0xFFFFFFFF;
    }

private:
    uint32_t crc{0xFFFFFFFF};
};

} // namespace cpputils
