
#include "unity.h"
#include "ble_channel_mapping.h"

TEST_CASE("Wifi channel 1: BLE advertising channel", "[ble_adv]")
{
    TEST_ASSERT_EQUAL(ADV_CHNL_38 | ADV_CHNL_39, map_wifi_to_ble_adv_channels(1));
}

TEST_CASE("Wifi channel 2 - 6: BLE advertising channel", "[ble_adv]")
{
    for (int i = 2; i <= 6; i++) {
        TEST_ASSERT_EQUAL(ADV_CHNL_37 | ADV_CHNL_39, map_wifi_to_ble_adv_channels(i));
    }
}

TEST_CASE("Wifi channel 7 - 12: BLE advertising channel", "[ble_adv]")
{
    for (int i = 7; i <= 12; i++) {
        TEST_ASSERT_EQUAL(ADV_CHNL_ALL, map_wifi_to_ble_adv_channels(i));
    }
}

TEST_CASE("Wifi channel 13 - 14: BLE advertising channel", "[ble_adv]")
{
    for (int i = 13; i <= 14; i++) {
        TEST_ASSERT_EQUAL(ADV_CHNL_37 | ADV_CHNL_38, map_wifi_to_ble_adv_channels(i));
    }
}