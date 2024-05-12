#include <string.h>
#include "esp_log.h"
#include "ble_channel_mapping.h"

uint8_t map_wifi_to_ble_adv_channels(uint8_t wifi_channel)
{
    // BLE advertising channels
    // Channel 37: 2402 MHz
    // Channel 38: 2426 MHz
    // Channel 39: 2480 MHz

    if (wifi_channel == 1)
    { // Channel 1: 2401-2423 MHz
        return ADV_CHNL_38 | ADV_CHNL_39;
    }

    if (wifi_channel > 1 && wifi_channel <= 6)
    { // Channel 2: 2406-2428 MHz
        // Channel 3: 2411-2433 MHz
        // Channel 4: 2416-2438 MHz
        // Channel 5: 2421-2443 MHz
        // Channel 6: 2426-2448 MHz
        return ADV_CHNL_37 | ADV_CHNL_39;
    }

    // Skip channel 7-12
    //  Channel 7: 2431-2453 MHz
    //  Channel 8: 2436-2458 MHz
    //  Channel 9: 2441-2463 MHz
    //  Channel 10: 2446-2468 MHz
    //  Channel 11: 2451-2473 MHz
    //  Channel 12: 2456-2478 MHz

    if (wifi_channel >= 13 && wifi_channel <= 14)
    { // Channel 13: 2461-2483 MHz
        // Channel 14: 2473-2495 MHz
        return ADV_CHNL_37 | ADV_CHNL_38;
    }

    return ADV_CHNL_ALL;
}

void map_wifi_to_ble_data_channels(uint8_t wifi_channel, esp_gap_ble_channels channels)
{
    // BLE data channels
    // Channel 0: 2404 MHz
    // Channel 1: 2406 MHz
    // ...
    // Channel 35: 2476 MHz
    // Channel 36: 2478 MHz

    // Enable all BLE data channels by default
    memset(channels, 0xFF, ESP_GAP_BLE_CHANNELS_LEN);

    // Disable unused BLE channels (37-39)
    channels[ESP_GAP_BLE_CHANNELS_LEN - 1] &= 0x1F;

    // Mapping Wi-Fi channel to BLE data channel exclusions
    switch (wifi_channel)
    {
    case 1: // 2401-2423 MHz - Disable data channels 0-9
        channels[0] &= 0x00;
        channels[1] &= 0xFC;
        break;
    case 2: // 2406-2428 MHz - Disable data channels 1-11
        channels[0] &= 0x01;
        channels[1] &= 0xF0;
        break;
    case 3: // 2411-2433 MHz - Disable data channels 4-13
        channels[0] &= 0x0F;
        channels[1] &= 0xC0;
        break;
    case 4: // 2416-2438 MHz - Disable data channels 6-16
        channels[0] &= 0x3F;
        channels[1] &= 0x00;
        channels[2] &= 0xFE;
        break;
    case 5: // 2421-2443 MHz - Disable data channels 9-18
        channels[1] &= 0x01;
        channels[2] &= 0xF8;
        break;
    case 6: // 2426-2448 MHz - Disable data channels 11-21
        channels[1] &= 0x07;
        channels[2] &= 0xC0;
        break;
    case 7: // 2431-2453 MHz - Disable data channels 13-23
        channels[1] &= 0x1F;
        channels[2] &= 0x00;
        break;
    case 8: // 2436-2458 MHz - Disable data channels 15-26
        channels[1] &= 0x7F;
        channels[2] &= 0x00;
        channels[3] &= 0xF8;
        break;
    case 9: // 2441-2463 MHz - Disable data channels 18-28
        channels[2] &= 0x03;
        channels[3] &= 0xE0;
        break;
    case 10: // 2446-2468 MHz - Disable data channels 20-31
        channels[2] &= 0x0F;
        channels[3] &= 0x00;
        break;
    case 11: // 2451-2473 MHz - Disable data channels 23-33
        channels[2] &= 0x7F;
        channels[3] &= 0x00;
        channels[4] &= 0xFC;
        break;
    case 12: // 2456-2478 MHz - Disable data channels 25-36
        channels[3] &= 0x01;
        channels[4] &= 0x00;
        break;
    case 13: // 2461-2483 MHz - Disable data channels 28-36
        channels[3] &= 0x0F;
        channels[4] &= 0x00;
        break;
    case 14: // 2473-2495 MHz - Disable data channels 34-36
        channels[4] &= 0x03;
        break;
    default:
        break;
    }
}

void log_ble_adv_channels(char *tag, uint8_t channel_map, char *prefix)
{
    char adv_channel_str[3 * 3 + 1];
    snprintf(adv_channel_str, sizeof(adv_channel_str), "%s%s%s",
             (channel_map & ADV_CHNL_37) ? "37 " : "",
             (channel_map & ADV_CHNL_38) ? "38 " : "",
             (channel_map & ADV_CHNL_39) ? "39 " : "");

    if (prefix != NULL) {
        ESP_LOGI(tag, "%s %s", prefix, adv_channel_str);
    } else {
        ESP_LOGI(tag, "BLE advertising channels: %s", adv_channel_str);
    }
}

void log_ble_data_channels(char *tag, esp_gap_ble_channels channels, char *prefix)
{
    char data_channels_str[ESP_GAP_BLE_CHANNELS_LEN * 8 * 3 + 1] = {0};
    int pos = 0;

    for (int i = 0; i < ESP_GAP_BLE_CHANNELS_LEN; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (channels[i] & (1 << j))
            {
                int channel_num = i * 8 + j;
                pos += sprintf(&data_channels_str[pos], "%02d ", channel_num);
            }
        }
    }

    if (pos > 0)
    {
        data_channels_str[pos - 1] = '\0';
    }

    if (prefix != NULL) {
        ESP_LOGI(tag, "%s %s", prefix, data_channels_str);
    } else {
        ESP_LOGI(tag, "BLE data channels: %s", data_channels_str);
    }
}