#pragma once

#include <concepts>
#include "../types.h"

/* BITSET.H: 
   A custom implementation of std::bitset. */

BEGIN_LYO_NAMESPACE
template <lyo::size Size, std::unsigned_integral Storage_type = unsigned char>
class bitset {
public:

    /* Constexpr functions. */
    static constexpr Storage_type   SHIFTED_ONE  (lyo::size pos) { return SC<Storage_type>(1) << (pos % (sizeof(Storage_type) * 8)); }
    static constexpr lyo::size      STORAGE_INDEX(lyo::size pos) { return SC<lyo::size>(pos / (sizeof(Storage_type) * 8)); }
    
    bitset() noexcept : m_storage{}
    {

    }

    bitset(bool initializer) noexcept : m_storage{}
    {
        /* Set all bits to 1 if initializer == true by negating zero. */
        if (initializer)
            for (Storage_type& unit : m_storage)
                unit = ~SC<Storage_type>(0);
    }

    void set(lyo::size pos) noexcept
    {
         m_storage[STORAGE_INDEX(pos)] |= SHIFTED_ONE(pos);
    }

    void reset(lyo::size pos) noexcept
    {
        m_storage[STORAGE_INDEX(pos)] &= ~SHIFTED_ONE(pos);
    }

    void flip(lyo::size pos) noexcept
    {
        m_storage[STORAGE_INDEX(pos)] ^= SHIFTED_ONE(pos);
    }

    void clear() noexcept
    {
        for (Storage_type& unit : m_storage) unit = SC<Storage_type>(0);
    }

    bool operator[](lyo::size pos) SAFE
    {
        return SC<bool>((m_storage[STORAGE_INDEX(pos)] >> (pos % (sizeof(Storage_type) * 8))) & SC<Storage_type>(1));
    }

private:

    /* You'll need eye bleach for this one. All you need to know is that it works. */
    Storage_type m_storage[(Size + (sizeof(Storage_type) * 8) - 1) / (sizeof(Storage_type) * 8)];
};
END_LYO_NAMESPACE