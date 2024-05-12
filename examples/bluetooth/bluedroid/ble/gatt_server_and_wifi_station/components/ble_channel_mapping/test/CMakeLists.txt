idf_component_register(SRCS "test_ble_adv_channels_mapping.c"
                            "test_ble_data_channels_mapping.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES unity ble_channel_mapping)
