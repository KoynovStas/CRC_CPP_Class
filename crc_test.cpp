#include <iostream>
#include "unit_tests.h"
#include "ucrc_t.h"






struct CRC_Spec_Info
{
    const char *name;
    uint8_t     bits;
    uint64_t    poly;
    uint64_t    init;
    bool        ref_in;
    bool        ref_out;
    uint64_t    xor_out;
    uint64_t    check;
};




// Catalogue of parametrised CRC algorithms
// more see http://reveng.sourceforge.net/crc-catalogue/
const CRC_Spec_Info  CRC_List[] =
{
    // CRC-3
    { "CRC-3/GSM",  3, 0x3, 0,   false, false, 0x7, 0x4 },
    { "CRC-3/ROHC", 3, 0x3, 0x7, true,  true,  0x0, 0x6 },

    // CRC-4
    { "CRC-4/ITU",        4, 0x3, 0x0, true,  true,  0x0, 0x7 },
    { "CRC-4/INTERLAKEN", 4, 0x3, 0xF, false, false, 0xF, 0xB },

    // CRC-5
    { "CRC-5/EPC", 5, 0x09, 0x09, false, false, 0x00, 0x00 },
    { "CRC-5/ITU", 5, 0x15, 0x00, true,  true,  0x00, 0x07 },
    { "CRC-5/USB", 5, 0x05, 0x1F, true,  true,  0x1F, 0x19 },

    // CRC-6
    { "CRC-6/CDMA2000-A", 6, 0x27, 0x3F, false, false, 0x0,  0x0D },
    { "CRC-6/CDMA2000-B", 6, 0x07, 0x3F, false, false, 0x0,  0x3B },
    { "CRC-6/DARC",       6, 0x19, 0x00, true,  true,  0x0,  0x26 },
    { "CRC-6/ITU",        6, 0x03, 0x00, true,  true,  0x0,  0x06 },
    { "CRC-6/GSM",        6, 0x2F, 0x00, false, false, 0x3F, 0x13 },

    // CRC-7
    { "CRC-7",      7, 0x9,  0x0,  false, false, 0x0, 0x75 },
    { "CRC-7/ROHC", 7, 0x4F, 0x7F, true,  true,  0x0, 0x53 },
    { "CRC-7/UMTS", 7, 0x45, 0x0,  false, false, 0x0, 0x61 },

    // CRC-8
    { "CRC-8",            8, 0x7,  0x0,  false, false, 0x0,  0xF4 },
    { "CRC-8/AUTOSAR",    8, 0x2F, 0xFF, false, false, 0xFF, 0xDF },
    { "CRC-8/CDMA2000",   8, 0x9B, 0xFF, false, false, 0x0,  0xDA },
    { "CRC-8/DARC",       8, 0x39, 0x0,  true,  true,  0x0,  0x15 },
    { "CRC-8/DVB-S2",     8, 0xD5, 0x0,  false, false, 0x0,  0xBC },
    { "CRC-8/EBU",        8, 0x1D, 0xFF, true,  true,  0x0,  0x97 },
    { "CRC-8/GSM-A",      8, 0x1D, 0x0,  false, false, 0x0,  0x37 },
    { "CRC-8/GSM-B",      8, 0x49, 0x0,  false, false, 0xFF, 0x94 },
    { "CRC-8/I-CODE",     8, 0x1D, 0xFD, false, false, 0x0,  0x7E },
    { "CRC-8/ITU",        8, 0x7,  0x0,  false, false, 0x55, 0xA1 },
    { "CRC-8/MAXIM",      8, 0x31, 0x0,  true,  true,  0x0,  0xA1 },
    { "CRC-8/OPENSAFETY", 8, 0x2F, 0x0,  false, false, 0x0,  0x3E },
    { "CRC-8/ROHC",       8, 0x7,  0xFF, true,  true,  0x0,  0xD0 },
    { "CRC-8/SAE-J1850",  8, 0x1D, 0xFF, false, false, 0xFF, 0x4B },
    { "CRC-8/WCDMA",      8, 0x9B, 0x0,  true,  true,  0x0,  0x25 },

    // CRC-10
    { "CRC-10",          10, 0x233, 0x0,   false, false, 0x0,   0x199 },
    { "CRC-10/CDMA2000", 10, 0x3D9, 0x3FF, false, false, 0x0,   0x233 },
    { "CRC-10/GSM",      10, 0x175, 0x0,   false, false, 0x3FF, 0x12A },

    // CRC-11
    { "CRC-11",      11, 0x385, 0x1A, false, false, 0x0, 0x5A3 },
    { "CRC-11/UMTS", 11, 0x307, 0x0,  false, false, 0x0, 0x061 },

    // CRC-12
    { "CRC-12/3GPP",     12, 0x80F, 0x0,   false, true,  0x0,   0xDAF },
    { "CRC-12/CDMA2000", 12, 0xF13, 0xFFF, false, false, 0x0,   0xD4D },
    { "CRC-12/DECT",     12, 0x80F, 0x0,   false, false, 0x0,   0xF5B },
    { "CRC-12/GSM",      12, 0xD31, 0x0,   false, false, 0xFFF, 0xB34 },

    // CRC-13
    { "CRC-13/BBC", 13, 0x1CF5, 0x0, false, false, 0x0, 0x4FA },

    // CRC-14
    { "CRC-14/DARC", 14, 0x805, 0x0, true, true, 0x0, 0x82D },

    // CRC-15
    { "CRC-15",         15, 0x4599, 0x0, false, false, 0x0, 0x59E },
    { "CRC-15/MPT1327", 15, 0x6815, 0x0, false, false, 0x1, 0x2566 },

    // CRC-16
    { "CRC-16/ARC",         16, 0x8005, 0x0,    true,  true,  0x0,    0xBB3D },
    { "CRC-16/AUG-CCITT",   16, 0x1021, 0x1D0F, false, false, 0x0,    0xE5CC },
    { "CRC-16/BUYPASS",     16, 0x8005, 0x0,    false, false, 0x0,    0xFEE8 },
    { "CRC-16/CCITT-FALSE", 16, 0x1021, 0xFFFF, false, false, 0x0,    0x29B1 },
    { "CRC-16/CDMA2000",    16, 0xC867, 0xFFFF, false, false, 0x0,    0x4C06 },
    { "CRC-16/DDS-110",     16, 0x8005, 0x800D, false, false, 0x0,    0x9ECF },
    { "CRC-16/DECT-R",      16, 0x589,  0x0,    false, false, 0x1,    0x7E },
    { "CRC-16/DECT-X",      16, 0x589,  0x0,    false, false, 0x0,    0x7F },
    { "CRC-16/DNP",         16, 0x3D65, 0x0,    true,  true,  0xFFFF, 0xEA82 },
    { "CRC-16/EN-13757",    16, 0x3D65, 0x0,    false, false, 0xFFFF, 0xC2B7 },
    { "CRC-16/GENIBUS",     16, 0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E },
    { "CRC-16/MAXIM",       16, 0x8005, 0x0,    true,  true,  0xFFFF, 0x44C2 },
    { "CRC-16/MCRF4XX",     16, 0x1021, 0xFFFF, true,  true,  0x0,    0x6F91 },
    { "CRC-16/RIELLO",      16, 0x1021, 0xB2AA, true,  true,  0x0,    0x63D0 },
    { "CRC-16/T10-DIF",     16, 0x8BB7, 0x0,    false, false, 0x0,    0xD0DB },
    { "CRC-16/TELEDISK",    16, 0xA097, 0x0,    false, false, 0x0,    0xFB3 },
    { "CRC-16/TMS37157",    16, 0x1021, 0x89EC, true,  true,  0x0,    0x26B1 },
    { "CRC-16/USB",         16, 0x8005, 0xFFFF, true,  true,  0xFFFF, 0xB4C8 },
    { "CRC-A",              16, 0x1021, 0xC6C6, true,  true,  0x0,    0xBF05 },
    { "CRC-16/KERMIT",      16, 0x1021, 0x0,    true,  true,  0x0,    0x2189 },
    { "CRC-16/MODBUS",      16, 0x8005, 0xFFFF, true,  true,  0x0,    0x4B37 },
    { "CRC-16/X-25",        16, 0x1021, 0xFFFF, true,  true,  0xFFFF, 0x906E },
    { "CRC-16/XMODEM",      16, 0x1021, 0x0,    false, false, 0x0,    0x31C3 },

    // CRC-24
    { "CRC-24",           24, 0x864CFB, 0xB704CE, false, false, 0x0, 0x21CF02 },
    { "CRC-24/FLEXRAY-A", 24, 0x5D6DCB, 0xFEDCBA, false, false, 0x0, 0x7979BD },
    { "CRC-24/FLEXRAY-B", 24, 0x5D6DCB, 0xABCDEF, false, false, 0x0, 0x1F23B8 },

    // CRC-31
    { "CRC-31/PHILIPS", 31, 0x4C11DB7, 0x7FFFFFFF, false, false, 0x7FFFFFFF, 0xCE9E46C },

    // CRC-32
    { "CRC-32",        32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xCBF43926 },
    { "CRC-32/BZIP2",  32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0xFFFFFFFF, 0xFC891918 },
    { "CRC-32C",       32, 0x1EDC6F41, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xE3069283 },
    { "CRC-32D",       32, 0xA833982B, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x87315576 },
    { "CRC-32/MPEG-2", 32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0x0,        0x376E6E7  },
    { "CRC-32/POSIX",  32, 0x4C11DB7,  0x0,        false, false, 0xFFFFFFFF, 0x765E7680 },
    { "CRC-32Q",       32, 0x814141AB, 0x0,        false, false, 0x0,        0x3010BF7F },
    { "CRC-32/JAMCRC", 32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0x0,        0x340BC6D9 },
    { "CRC-32/XFER",   32, 0xAF,       0x0,        false, false, 0x0,        0xBD0BE338 },

    // CRC-40
    { "CRC-40/GSM", 40, 0x4820009, 0x0, false, false, 0xFFFFFFFFFF, 0xD4164FC646 },

    // CRC-64
    { "CRC-64",    64, 0x42F0E1EBA9EA3693, 0x0,                false, false, 0x0,                0x6C40DF5F0B497347 },
    { "CRC-64/WE", 64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, false, false, 0xFFFFFFFFFFFFFFFF, 0x62EC59E3F1A4F00A },
    { "CRC-64/XZ", 64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0x995DC9BBDF1939FA },

    { 0, 0, 0, 0, 0, 0, 0, 0 } // End Marker
};



//------------- tests for CRC_t methods -------------


int test_crc_t_name(struct test_info_t  *test_info)
{

    TEST_INIT;


    uCRC_t  crc;


    if( crc.name != "CRC-32" )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_name_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    const char* name = "some_name";

    uCRC_t crc(name);


    if( crc.name != name )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_t_get_bits(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_bits() != spec->bits )
        {
            std::cout << "For CRC: " << spec->name <<  " bits must be: " << spec->bits << " but get: " << ucrc.get_bits() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_get_poly(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_poly() != spec->poly )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " poly must be: 0x" << spec->poly << " but get: 0x" << ucrc.get_poly() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_get_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_init() != spec->init )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " init must be: 0x" << spec->init << " but get: 0x" << ucrc.get_init() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_get_xor_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_xor_out() != spec->xor_out )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " xor_out must be: 0x" << spec->xor_out << " but get: 0x" << ucrc.get_xor_out() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_get_ref_in(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_ref_in() != spec->ref_in )
        {
            std::cout << std::boolalpha;
            std::cout << "For CRC: " << spec->name <<  " ref_in must be: " << spec->ref_in << " but get: " << ucrc.get_ref_in() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_get_ref_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    const struct CRC_Spec_Info *spec = CRC_List;


    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        if( ucrc.get_ref_out() != spec->ref_out )
        {
            std::cout << std::boolalpha;
            std::cout << "For CRC: " << spec->name <<  " ref_out must be: " << spec->ref_out << " but get: " << ucrc.get_ref_out() << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_t_set_bits(struct test_info_t  *test_info)
{

    TEST_INIT;

    int i, res;

    uCRC_t crc(1, 0, 0, true, true, 0);


    if( crc.get_bits() != 1 )
        return TEST_BROKEN;


    if( crc.set_bits(0) != -1 )
         return TEST_BROKEN;

    // 1..64
    for( i = 1; i <= 64; ++i)
    {
        res = crc.set_bits(i);
        if( res != 0 )
             return TEST_BROKEN;

        if( crc.get_bits() != i )
            return TEST_BROKEN;
    }


    //more 64
    for( i = 65; i <= 256; ++i)
    {
        if( crc.set_bits(i) != -1 )
             return TEST_BROKEN;
    }



    return TEST_PASSED;
}



//------------- tests for Calculate CRC  -------------



// uses parameters constructor by class uCRC_t
int test_crc_std_check_constructor(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    const struct CRC_Spec_Info *spec = CRC_List;



    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);

        crc = ucrc.get_crc("123456789", 9);
        if( crc != spec->check )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " std check: 0x" << spec->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



// uses set_xxx methods
int test_crc_std_check_set_xxx(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    const struct CRC_Spec_Info *spec = CRC_List;
    uCRC_t ucrc;


    while( spec->name )
    {

        ucrc.set_bits(spec->bits);
        ucrc.set_poly(spec->poly);
        ucrc.set_init(spec->init);
        ucrc.set_ref_in(spec->ref_in);
        ucrc.set_ref_out(spec->ref_out);
        ucrc.set_xor_out(spec->xor_out);

        crc = ucrc.get_crc("123456789", 9);
        if( crc != spec->check )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " std check: 0x" << spec->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for file -------------



// uses parameters constructor by class uCRC_t
int test_crc_std_check_file(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    const struct CRC_Spec_Info *spec = CRC_List;



    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        int res = ucrc.get_crc(crc, "std_file_to_test_crc");
        if( (res != 0) ||  (crc != spec->check) )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " std check: 0x" << spec->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



int test_crc_no_file(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    const struct CRC_Spec_Info *spec = CRC_List;



    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        int res = ucrc.get_crc(crc, "");
        if( res != -1 )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " no file but get_crc() ret:" << res << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for cunks -------------



int test_crc_for_cunks(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    char buf[]  = "1234";
    char buf2[] = "56789";

    const struct CRC_Spec_Info *spec = CRC_List;



    while( spec->name )
    {

        uCRC_t ucrc(spec->bits, spec->poly, spec->init, spec->ref_in, spec->ref_out, spec->xor_out);


        crc = ucrc.get_crc_init();
        crc = ucrc.get_raw_crc(buf,  4, crc);
        crc = ucrc.get_raw_crc(buf2, 5, crc);
        crc = ucrc.get_final_crc(crc);

        if( crc != spec->check )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << spec->name <<  " std check: 0x" << spec->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }


        spec++;
    }


    return TEST_PASSED;
}



ptest_func tests[] =
{

    //CRC_t methods
    test_crc_t_name,
    test_crc_t_name_2,

    test_crc_t_get_bits,
    test_crc_t_get_poly,
    test_crc_t_get_init,
    test_crc_t_get_xor_out,
    test_crc_t_get_ref_in,
    test_crc_t_get_ref_out,

    test_crc_t_set_bits,


    //CRC
    test_crc_std_check_constructor,
    test_crc_std_check_set_xxx,


    test_crc_std_check_file,
    test_crc_no_file,

    test_crc_for_cunks,
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
