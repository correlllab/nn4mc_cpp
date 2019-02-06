deps_config := \
	/home/sarahaguasvivas/esp/esp-idf/components/app_trace/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/aws_iot/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/bt/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/driver/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/esp32/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/ethernet/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/fatfs/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/freertos/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/heap/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/libsodium/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/log/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/lwip/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/mbedtls/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/mdns/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/openssl/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/pthread/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/spi_flash/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/spiffs/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/vfs/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/sarahaguasvivas/esp/esp-idf/Kconfig.compiler \
	/home/sarahaguasvivas/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/sarahaguasvivas/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/sarahaguasvivas/esp/esp-idf/source-local-board/tcp_perf/main/Kconfig.projbuild \
	/home/sarahaguasvivas/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/sarahaguasvivas/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
