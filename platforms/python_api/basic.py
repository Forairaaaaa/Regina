from regina import Regina, InputStatus
import asyncio


def handleInputStatusNotify(intputStatus: InputStatus):
    print(intputStatus)


async def main():
    regina = Regina()
    regina.set_input_notify_callback(handleInputStatusNotify)
    await regina.start()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("😎 拜拜")
