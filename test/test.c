#include "minunit.h"

#include "sfp_utils.h"

MU_TEST(test_sfp_crc_init_returnsAllOnes) {
    mu_assert_int_eq(0xFFFF,sfp_crc_init());
}

MU_TEST_SUITE(test_sfp_crc_init) {
    MU_RUN_TEST(test_sfp_crc_init_returnsAllOnes);
}

MU_TEST(test_sfp_crc_defensiveCoding) {
    sfp_crc_t crc = 10;
    mu_assert(crc == sfp_crc(crc, NULL, 1), "Did not return given CRC when data was null!");
}

MU_TEST(test_sfp_crc_againstKnownValues) {
    sfp_crc_t crc;
    uint8_t crc_upper, crc_lower;
    uint8_t test_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    crc = sfp_crc(sfp_crc_init(), test_data, sizeof(test_data) / sizeof(test_data[0]));
    mu_assert(0xC241 == crc, "Did not compute expected CRC for known data");
    
    crc_upper = (crc & 0xFF00) >> 8;
    crc_lower = crc & 0xFF;
    crc = sfp_crc(crc, &crc_upper, 1);
    crc = sfp_crc(crc, &crc_lower, 1);

    mu_assert(crc == 0, "CRC did not return to 0 as expected");
}

MU_TEST_SUITE(test_sfp_crc) {
    MU_RUN_TEST(test_sfp_crc_defensiveCoding);
    MU_RUN_TEST(test_sfp_crc_againstKnownValues);
}

int main(void)
{
    MU_RUN_SUITE(test_sfp_crc_init);
    MU_RUN_SUITE(test_sfp_crc);

	MU_REPORT();
	return MU_EXIT_CODE;
}