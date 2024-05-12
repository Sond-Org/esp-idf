
#include <string.h>
#include "unity.h"
#include "ble_channel_mapping.h"

void test(uint8_t channel, uint8_t expected_channels[ESP_GAP_BLE_CHANNELS_LEN]);

TEST_CASE("Wifi channel 1: BLE data channel", "[ble_data]")
{
    test(1, (uint8_t[]){0b00000000, 0b11111100, 0b11111111, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 2: BLE data channel", "[ble_data]")
{
    test(2, (uint8_t[]){0b00000001, 0b11110000, 0b11111111, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 3: BLE data channel", "[ble_data]")
{
    test(3, (uint8_t[]){0b00001111, 0b11000000, 0b11111111, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 4: BLE data channel", "[ble_data]")
{
    test(4, (uint8_t[]){0b00111111, 0b00000000, 0b11111110, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 5: BLE data channel", "[ble_data]")
{
    test(5, (uint8_t[]){0b11111111, 0b00000001, 0b11111000, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 6: BLE data channel", "[ble_data]")
{
    test(6, (uint8_t[]){0b11111111, 0b00000111, 0b11000000, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 7: BLE data channel", "[ble_data]")
{
    test(7, (uint8_t[]){0b11111111, 0b00011111, 0b00000000, 0b11111111, 0b00011111});
}

TEST_CASE("Wifi channel 8: BLE data channel", "[ble_data]")
{
    test(8, (uint8_t[]){0b11111111, 0b01111111, 0b00000000, 0b11111000, 0b00011111});
}

TEST_CASE("Wifi channel 9: BLE data channel", "[ble_data]")
{
    test(9, (uint8_t[]){0b11111111, 0b11111111, 0b00000011, 0b11100000, 0b00011111});
}

TEST_CASE("Wifi channel 10: BLE data channel", "[ble_data]")
{
    test(10, (uint8_t[]){0b11111111, 0b11111111, 0b00001111, 0b00000000, 0b00011111});
}

TEST_CASE("Wifi channel 11: BLE data channel", "[ble_data]")
{
    test(11, (uint8_t[]){0b11111111, 0b11111111, 0b01111111, 0b00000000, 0b00011100});
}

TEST_CASE("Wifi channel 12: BLE data channel", "[ble_data]")
{
    test(12, (uint8_t[]){0b11111111, 0b11111111, 0b11111111, 0b00000001, 0b00000000});
}

TEST_CASE("Wifi channel 13: BLE data channel", "[ble_data]")
{
    test(13, (uint8_t[]){0b11111111, 0b11111111, 0b11111111, 0b00001111, 0b00000000});
}

TEST_CASE("Wifi channel 14: BLE data channel", "[ble_data]")
{
    test(14, (uint8_t[]){0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b00000011});
}

void test(uint8_t channel, uint8_t expected_channels[ESP_GAP_BLE_CHANNELS_LEN]) {
    esp_gap_ble_channels channels = {0};
    map_wifi_to_ble_data_channels(channel, channels);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_channels, channels, ESP_GAP_BLE_CHANNELS_LEN);
}