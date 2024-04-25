
IDF_PATH=$HOME/esp/esp-idf-v5.1.3

if [ $# -eq 0 ]; then
    echo "need ouput name"
    exit 1
fi

# Get idf
. ${IDF_PATH}/export.sh

gen_esp32part.py build/partition_table/partition-table.bin

mkdir output
esptool.py --chip esp32s3 merge_bin --flash_mode dio --flash_freq 80m --flash_size 8MB \
    0x0 build/bootloader/bootloader.bin \
    0x10000 build/esp32s3.bin \
    0x8000 build/partition_table/partition-table.bin \
    0xd000 build/ota_data_initial.bin \
    0x510000 ../../build/desktop/AssetPool.bin \
    -o output/$1
