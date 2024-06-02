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


_DEVICE_NAME = "Reginaaaa:)"
_CUSTOM_SERVICE_UUID = "00002333-0000-1000-8000-00805f9b34fb"
_INPUT_STATUS_CHAR_UUID = "00002334-0000-1000-8000-00805f9b34fb"


class Regina:
    def __init__(self, deviceName=_DEVICE_NAME):
        self._device_name = deviceName
        self._device = None
        self._client = None
        self._input_status = InputStatus()
        self._on_input_status_notify = None

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

            print(
                f"😎 找到了, 地址: {self._device.address}")
            break

    async def on_device_found(self):
        async with BleakClient(self._device.address) as client:
            self._client = client
            print(f"😎 连上了")
            await client.start_notify(_INPUT_STATUS_CHAR_UUID, self.on_input_status_update)

            try:
                while True:
                    await asyncio.sleep(1)
            except asyncio.CancelledError:
                print("😎 消息循环结束")

    def _handle_input_status_event_update(self, btnA=None, btnB=None, btnC=None, btnD=None, valueDialA=None, valueDialB=None, countDialA=None, countDialB=None):
        pass

    def on_input_status_update(self, sender, data):
        unpacked_data = struct.unpack('<????BBhh', data)
        self._handle_input_status_event_update(*unpacked_data)
        self._input_status.update(*unpacked_data)
        # print(self._input_status)
        if self._on_input_status_notify is not None:
            self._on_input_status_notify(self._input_status)

    def set_input_status_notify_callback(self, callback):
        self._on_input_status_notify = callback

    async def start(self):
        print("😎 你好")
        await self.scan_and_wait()
        await self.on_device_found()
