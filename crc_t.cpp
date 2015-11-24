#include "crc_t.h"
#include <cstdio>




CRC_t::CRC_t(const std::string Name, uint8_t Bits, uint64_t Poly, uint64_t Init, bool RefIn, bool RefOut, uint64_t XorOut)
{
    name    = Name;
    bits    = Bits;
    poly    = Poly;
    init    = Init;
    ref_in  = RefIn;
    ref_out = RefOut;
    xor_out = XorOut;
}



CRC_t::CRC_t(uint8_t Bits, uint64_t Poly, uint64_t Init, bool RefIn, bool RefOut, uint64_t XorOut)
{
    bits    = Bits;
    poly    = Poly;
    init    = Init;
    ref_in  = RefIn;
    ref_out = RefOut;
    xor_out = XorOut;
}



uint64_t CRC_t::reflect(uint64_t data, uint8_t num_bits)
{
    uint64_t reflection = 0;
    uint64_t one = 1;

    for ( size_t i = 0; i < num_bits; ++i, data >>= 1 )
    {
        if ( data & one )
        {
            reflection |= ( one << (num_bits - one - i) );
        }
    }

    return reflection;
}
