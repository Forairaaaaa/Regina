# Regina

## BLE 接口

设备名：`Reginaaaa:)`

自定义服务：`2333`

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
