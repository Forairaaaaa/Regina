from regina import Regina, InputStatus
import asyncio
import pyautogui


_last_input_status = None


def handleKeysUpdate(intputStatus: InputStatus):
    key_map = {
        "prevtrack": {"new":  intputStatus.btnA, "last": _last_input_status.btnA},
        "playpause": {"new":  intputStatus.btnB, "last": _last_input_status.btnB},
        "nexttrack": {"new":  intputStatus.btnC, "last": _last_input_status.btnC},
        "volumemute": {"new": intputStatus.btnD, "last": _last_input_status.btnD}
    }

    for key, state in key_map.items():
        if state["new"] == state["last"]:
            continue
        if state["new"]:
            pyautogui.keyDown(key)
        else:
            pyautogui.keyUp(key)


def updateDial(newCount, lastCount, keyCountUp, keyCountDown):
    if newCount > lastCount:
        pyautogui.press(keyCountUp)
    elif newCount < lastCount:
        pyautogui.press(keyCountDown)


def handleDialsUpdate(intputStatus: InputStatus):
    global _last_input_status
    updateDial(
        intputStatus.countDialA, _last_input_status.countDialA, "up", "down")
    updateDial(
        intputStatus.countDialB, _last_input_status.countDialB, "volumeup", "volumedown")


def handleInputStatusNotify(intputStatus: InputStatus):
    global _last_input_status
    if _last_input_status is None:
        _last_input_status = InputStatus()
        _last_input_status.copy_from(intputStatus)
        return

    handleKeysUpdate(intputStatus)
    handleDialsUpdate(intputStatus)

    _last_input_status.copy_from(intputStatus)


async def main():
    regina = Regina()
    regina.set_input_status_notify_callback(handleInputStatusNotify)
    await regina.start()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("😎 拜拜")
