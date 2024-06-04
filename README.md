# Regina

(=・ω・=) 噻博柆圾.. 僅栱娯泺~

## 文件树

```bash
.
├── app
│   ├── apps                      应用层
│   │   ├── app_desktop             桌面
│   │   ├── app_input_daemon        输入管理
│   │   ├── app_sleep_daemon        睡眠管理
│   │   ├── app_startup_anim        开机动画
│   │   ├── app_template            App模板
│   ├── assets                    静态资源
│   ├── hal                       HAL定义
│   └── shared                    共享数据定义
└── platforms
    ├── desktop                   桌面项目
    ├── python_api                Python api
    └── regina                    ESP32C6项目
```

## 编译

### 下载依赖

```bash
python ./fetch_repos.py
```

### 桌面端

#### 工具链

```bash
sudo apt install build-essential cmake
```

#### 编译

```bash
mkdir build && cd build
```
```bash
cmake .. && make
```
#### 运行

```bash
cd desktop
```

要先 cd 过去，因为序列化时用的相对路径 :(

```bash
./app_desktop_build
```

### ESP32 端

#### 工具链

[ESP-IDF v5.1.3](https://docs.espressif.com/projects/esp-idf/en/v5.1.3/esp32s3/index.html)

#### 编译

```bash
cd platforms/regina
```

```bash
idf.py build
```

#### 上传

```bash
idf.py -p <YourPort> flash -b 1500000
```

##### 上传静态资源

```bash
parttool.py --port <YourPort> write_partition --partition-name=assetpool --input "path/to/AssetPool.bin"
```

静态资源是桌面端序列化出来的，如果运行过桌面端， `AssetPool.bin` 可以在 `app_desktop_build` 的旁边找到

或者 [release](https://github.com/Forairaaaaa/Regina/releases/latest) 里下一个

## BLE 接口

**在线接口测试 ->** [点我 :)](https://phalange.vercel.app/)

设备名：`Reginaaaa:)`

自定义服务：`2333`

JS web api [参考](https://github.com/Forairaaaaa/Phalange/blob/main/app/page.tsx#L40)，Python api [参考](https://github.com/Forairaaaaa/Regina/tree/main/platforms/python_api)，具体如下：

### 输入

特征值：`2334`

[数据格式](https://github.com/Forairaaaaa/Regina/blob/main/platforms/regina/main/hal_regina/components/hal_ble.cpp#L50)：`bool, bool, bool, bool, uint8, uint8, int16, int16`

对应：按键A、B、C、D、小轮值、大轮值、小轮增量、大轮增量

**JS**

```js
btnA = value[0] !== 0;
btnB = value[1] !== 0;
btnC = value[2] !== 0;
btnD = value[3] !== 0;
dialAValue = value[4];
dialBValue = value[5];
dialACount = value.getInt16(6, true);
dialBCount = value.getInt16(8, true);
```

**Python**

```python
unpacked_data = struct.unpack('<????BBhh', value)
```

### 陀螺仪

#### 加速度

特征值：`2335`

[数据格式](https://github.com/Forairaaaaa/Regina/blob/main/platforms/regina/main/hal_regina/components/hal_ble.cpp#L103)：`float, float, float`

对应：X、Y、Z轴

**JS**

```js
let imuAccel = [0, 0, 0];
for (let i = 0; i < 3; i++) {
  imuAccel[i] = value.getFloat32(i * 4, value);
}
```

**Python**

```python
unpacked_data = struct.unpack('fff', data)
```

#### 角速度

特征值：`2336`

其他和加速度一样

### 系统配置

特征值：`2337`

数据格式：`JSON UTF-8`

相关 key 参考[系统配置结构体](https://github.com/Forairaaaaa/Regina/blob/main/app/hal/types.h#L100)

其中 `ringtone` 为 [RTTTI](https://en.wikipedia.org/wiki/Run-time_type_information) 格式音频

此外可用特殊 key `unixTimestamp` 来设置 RTC 时间，value 用数字类型 unix 时间戳（ms）

### 消息

特征值：`2338`

数据格式：`JSON UTF-8`

### FFT 投屏 

特征值：`2339`

数据格式：21 个 `uint8`

对应屏幕从左到右 21 个矩形，其中数值为 `0~35` ，对应该矩形的高度

## 懒得TODO

- 现在不是真正的睡眠，只是关屏幕
- 字库非完整，用完整字库的话字体识别的高度不对，直接用lgfx的换行就寄了，懒得写了
- 启动器、设置、打砖块

## 硬件

**立创链接 ->** [点我 :)](https://oshwhub.com/eedadada/phalange)

板厚1MM

- 主控：[ESP32C6](https://item.taobao.com/item.htm?_u=42bdtj0fc30b&id=745245326098&spm=a1z09.2.0.0.52ce2e8dzg9AZA)

- 屏幕：[中景园1.3寸OLED](https://item.taobao.com/item.htm?_u=42bdtj0f8fa9&id=634786783290&spm=a1z09.2.0.0.52ce2e8dzg9AZA)

- 编码开关：[7.4寸贴片，带旋柄，16档](https://detail.tmall.com/item.htm?_u=42bdtj0f1a01&id=608662157272&spm=a1z09.2.0.0.52ce2e8dzg9AZA&skuId=5177216842298)

- 电池：[402728 400毫安](https://detail.tmall.com/item.htm?_u=42bdtj0f77a8&id=632947661144&spm=a1z09.2.0.0.52ce2e8dzg9AZA)
- 电源管理：[mondraker/axp202](https://oshwhub.com/mondraker/axp202-zeng-ge-yan-zheng)

应该比较好焊，想偷懒可以不焊 RTC、IMU 和 MIC

我是铁板烧的屏幕这一面

如果编码开关方向焊反了，可以在程序里设置反转，具体在BLE接口的系统配置部分

麦克风用的模拟麦，不知道是我焊烂了还是电路不对，波形异常的平静~

## 结构

**STL 文件 ->** [点我 :)](https://github.com/Forairaaaaa/Regina/releases/latest)

这次没有螺丝，后盖用滑槽和卡扣固定

间隙什么的根据拓竹 a1 mini 0.4 喷嘴调整的，树脂打印的话可能会偏松，没试过

组装时滑槽会有点顶 PCB，需要一些技巧~
