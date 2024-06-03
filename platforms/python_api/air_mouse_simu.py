from regina import Regina, InputStatus, IMUAccelStatus, IMUGyroStatus
import asyncio
import pyautogui
import math


def handleImuAccelNotify(imuAccelStatus: IMUAccelStatus):
    # print(imuAccelStatus)
    # print(pyautogui.position())

    speed = 250
    threshold = 0.5
    new_x = pyautogui.position().x
    new_y = pyautogui.position().y

    # 😎 x
    if (math.fabs(imuAccelStatus.accelX) > threshold):
        increment = (math.fabs(imuAccelStatus.accelX) - threshold) * speed
        if imuAccelStatus.accelX > 0:
            new_x -= increment
        else:
            new_x += increment

    # 😎 y
    if (math.fabs(imuAccelStatus.accelY) > threshold):
        increment = (math.fabs(imuAccelStatus.accelY) - threshold) * speed
        if imuAccelStatus.accelY > 0:
            new_y += increment
        else:
            new_y -= increment

    # 😎 go
    if new_x != pyautogui.position().x or new_y != pyautogui.position().y:
        pyautogui.moveTo(new_x, new_y)


async def main():
    regina = Regina()
    regina.set_imu_accel_notify_callback(handleImuAccelNotify)
    await regina.start()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("😎 拜拜")
