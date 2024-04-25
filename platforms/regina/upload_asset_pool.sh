echo "upload asset pool"
parttool.py --port "/dev/ttyACM0" write_partition --partition-name=assetpool --input "../../build/desktop/AssetPool.bin"
