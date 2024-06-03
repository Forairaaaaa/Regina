from regina import Regina, InputStatus
import asyncio


def handleInputNotify(intputStatus: InputStatus):
    print(intputStatus)


async def main():
    regina = Regina()
    regina.set_input_notify_callback(handleInputNotify)
    await regina.start()

try:
    asyncio.run(main())
except KeyboardInterrupt:
    print("😎 拜拜")
