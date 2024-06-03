from regina import Regina, InputStatus, IMUAccelStatus, IMUGyroStatus
import asyncio
import pyautogui
import math


def handleImuAccelNotify(imuAccelStatus: IMUAccelStatus):
    print(imuAccelStatus)
    print(pyautogui.position())

    new_possition = pyautogui.position()
    speed = 5
    threshold = 0.5

    # 😎 x
    if (math.fabs(imuAccelStatus.accelX) > threshold):
        increment = (math.fabs(imuAccelStatus.accelX) - threshold) * speed
        if imuAccelStatus.accelX > 0:
            new_possition[0] += increment
        else:
            new_possition[0] -= increment

    # 😎 y
    if (math.fabs(imuAccelStatus.accelY) > threshold):
        increment = (math.fabs(imuAccelStatus.accelY) - threshold) * speed
        if imuAccelStatus.accelY > 0:
            new_possition[1] += increment
        else:
            new_possition[2] -= increment

    # 😎 go
    if new_possition != pyautogui.position():
        pyautogui.moveTo(new_possition)


async def main():
    regina = Regina()
    regina.set_imu_accel_notify_callback(handleImuAccelNotify)
    await regina.start()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("😎 拜拜")
