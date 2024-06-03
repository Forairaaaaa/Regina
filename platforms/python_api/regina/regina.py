import asyncio
import struct
from bleak import BleakClient, BleakScanner


class InputStatus:
    def __init__(self):
        self.btnA = False
        self.btnB = False
        self.btnC = False
        self.btnD = False
        self.valueDialA = 0
        self.valueDialB = 0
        self.countDialA = 0
        self.countDialB = 0

    def update(self, btnA=None, btnB=None, btnC=None, btnD=None, valueDialA=None, valueDialB=None, countDialA=None, countDialB=None):
        if btnA is not None:
            self.btnA = btnA
        if btnB is not None:
            self.btnB = btnB
        if btnC is not None:
            self.btnC = btnC
        if btnD is not None:
            self.btnD = btnD
        if valueDialA is not None:
            self.valueDialA = valueDialA
        if valueDialB is not None:
            self.valueDialB = valueDialB
        if countDialA is not None:
            self.countDialA = countDialA
        if countDialB is not None:
            self.countDialB = countDialB

    def copy_from(self, other):
        self.btnA = other.btnA
        self.btnB = other.btnB
        self.btnC = other.btnC
        self.btnD = other.btnD
        self.valueDialA = other.valueDialA
        self.valueDialB = other.valueDialB
        self.countDialA = other.countDialA
        self.countDialB = other.countDialB

    def __repr__(self):
        return (f"InputStatus(btnA={self.btnA}, btnB={self.btnB}, btnC={self.btnC}, btnD={self.btnD}, "
                f"valueDialA={self.valueDialA}, valueDialB={self.valueDialB}, "
                f"countDialA={self.countDialA}, countDialB={self.countDialB})")


class IMUAccelStatus:
    def __init__(self):
        self.accelX = 0.0
        self.accelY = 0.0
        self.accelZ = 0.0

    def update(self, accelX=None, accelY=None, accelZ=None):
        if accelX is not None:
            self.accelX = accelX
        if accelY is not None:
            self.accelY = accelY
        if accelZ is not None:
            self.accelZ = accelZ

    def copy_from(self, other):
        self.accelX = other.accelX
        self.accelY = other.accelY
        self.accelZ = other.accelZ

    def __repr__(self):
        return (f"IMUAccelStatus(accelX={self.accelX}, accelY={self.accelY}, accelZ={self.accelZ})")


class IMUGyroStatus:
    def __init__(self):
        self.gyroX = 0.0
        self.gyroY = 0.0
        self.gyroZ = 0.0

    def update(self, gyroX=None, gyroY=None, gyroZ=None):
        if gyroX is not None:
            self.gyroX = gyroX
        if gyroY is not None:
            self.gyroY = gyroY
        if gyroZ is not None:
            self.gyroZ = gyroZ

    def copy_from(self, other):
        self.gyroX = other.gyroX
        self.gyroY = other.gyroY
        self.gyroZ = other.gyroZ

    def __repr__(self):
        return (f"IMUGyroStatus(gyroX={self.gyroX}, gyroY={self.gyroY}, gyroZ={self.gyroZ})")


_DEVICE_NAME = "Reginaaaa:)"
_CUSTOM_SERVICE_UUID = "00002333-0000-1000-8000-00805f9b34fb"
_INPUT_CHAR_UUID = "00002334-0000-1000-8000-00805f9b34fb"
_IMU_ACCEL_CHAR_UUID = "00002335-0000-1000-8000-00805f9b34fb"
_IMU_GYRO_CHAR_UUID = "00002336-0000-1000-8000-00805f9b34fb"


class Regina:
    def __init__(self, deviceName=_DEVICE_NAME):
        self._device_name = deviceName
        self._device = None
        self._client = None
        self._input_status = InputStatus()
        self._imu_accel_status = IMUAccelStatus()
        self._imu_gyro_status = IMUGyroStatus()
        self._on_input_notify = None
        self._on_imu_accel_notify = None
        self._on_imu_gyro_notify = None

    async def scan_and_wait(self):
        while True:
            print("😎 扫描中..")
            devices = await BleakScanner.discover()

            self._device = None
            for device in devices:
                if device.name == self._device_name:
                    self._device = device
                    break

            if self._device is None:
                continue

            print(f"😎 找到了, 地址: {self._device.address}")
            break

    async def on_device_found(self):
        async with BleakClient(self._device.address) as client:
            self._client = client
            print(f"😎 连上了")
            await client.start_notify(_INPUT_CHAR_UUID, self.on_input_status_update)
            await client.start_notify(_IMU_ACCEL_CHAR_UUID, self.on_imu_accel_update)
            await client.start_notify(_IMU_GYRO_CHAR_UUID, self.on_imu_gyro_update)

            try:
                while True:
                    await asyncio.sleep(1)
            except asyncio.CancelledError:
                print("😎 消息循环结束")

    def on_input_status_update(self, sender, data):
        unpacked_data = struct.unpack('<????BBhh', data)
        self._handle_input_status_event_update(*unpacked_data)
        self._input_status.update(*unpacked_data)
        if self._on_input_notify is not None:
            self._on_input_notify(self._input_status)

    def on_imu_accel_update(self, sender, data):
        unpacked_data = struct.unpack('fff', data)
        self._imu_accel_status.update(*unpacked_data)
        if self._on_imu_accel_notify is not None:
            self._on_imu_accel_notify(self._imu_accel_status)

    def on_imu_gyro_update(self, sender, data):
        unpacked_data = struct.unpack('fff', data)
        self._imu_gyro_status.update(*unpacked_data)
        if self._on_imu_gyro_notify is not None:
            self._on_imu_gyro_notify(self._imu_gyro_status)

    def set_input_notify_callback(self, callback):
        self._on_input_notify = callback

    def set_imu_accel_notify_callback(self, callback):
        self._on_imu_accel_notify = callback

    def set_imu_gyro_notify_callback(self, callback):
        self._on_imu_gyro_notify = callback

    async def start(self):
        print("😎 你好")
        await self.scan_and_wait()
        await self.on_device_found()
