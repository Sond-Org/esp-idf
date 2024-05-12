#pragma once

#ifndef BLE_CHANNEL_MAPPING_H_
#define BLE_CHANNEL_MAPPING_H_

#ifdef __cplusplus
extern "C"
{
#endif

    #include <stdint.h>
    #include "esp_gap_ble_api.h"

    /**
     * Maps Wi-Fi channels to BLE advertising channels
     *
     * @param wifi_channel [in] Wi-Fi channel number
     *
     * @return BLE advertising channel map
     */
    uint8_t map_wifi_to_ble_adv_channels(uint8_t wifi_channel);

    /**
     * Maps Wi-Fi channels to BLE data channel maps
     *
     * @param wifi_channel [in] Wi-Fi channel number
     * @param channels [out] BLE data channel map
     *
     * @note The BLE data channel map is a 5-byte array where each bit represents a BLE data channel.
     */
    void map_wifi_to_ble_data_channels(uint8_t wifi_channel, esp_gap_ble_channels channels);

    /**
     * @brief Convert a byte to a string of BLE advertising channels and log it
     *
     * @param tag [in] Tag for the log message
     * @param channel_map [in] BLE advertising channel map
     * @param prefix [in?] Prefix for the log message
     */
    void log_ble_adv_channels(char *tag, uint8_t channel_map, char *prefix);

    /**
     * @brief Convert a byte array to a string of BLE data channels and log it
     *
     * @param tag [in] Tag for the log message
     * @param channels [in] BLE data channels map
     * @param prefix [in?] Prefix for the log message
     */
    void log_ble_data_channels(char *tag, esp_gap_ble_channels channels, char *prefix);

#ifdef __cplusplus
}
#endif

#endif /* BLE_CHANNEL_MAPPING_H_ */