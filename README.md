## STM32-detectio

![FmeMts-YCAiyiuzcXEVy9c4lXGZI.jpg](https://image.tobeshow.top/2019/04/13/FmeMts-YCAiyiuzcXEVy9c4lXGZI.jpg)

一、SD卡记录功能。
自动识别有无SD卡，支持4G以下SD卡。

下图为SD卡记录的数据。以日期为文件名自动创建文件。

记录格式为：时间，PM1.0，PM2.5，PM10，温度，湿度，大气压，光照强度。



记录的文件可导如Excel，绘制曲线图。



二、利用NTP服务器授时。

上电待ESP8266连接WIFI后，连接NTP服务器获取时间，然后设置R8025AC时间。

也可以短按按键手动授时。

三、利用ESP_TOUCH来配置ESP8266网络。 



四、包含STM32的USB模拟串口源码。（暂未使用）



五、软件流程图。



说明：

由于利用ESP8266的SDK来获取NTP时间，所以需要向ESP8266下载程序（下载教程网上有）。

ESP8266的Flash必须1M以上。

/********************************************************分割线****************************************************************/

概述：

该空气监测仪采集环境参数后通过wifi上传到OneNET物联网平台。

OneNET开放应用：https://open.iot.10086.cn/appview/p/6f923e51e13228df6f24d2fdadc07ab0

硬件资源：

1、单片机：STM32F103CB
2、AM2320：温湿度传感器
3、BMP280：大气压传感器
4、BH1750：光照强度传感器
5、攀藤G5传感器：PM2.5传感器
6、ESP-01S：WIFI模块
7、SD卡模块
8、R8025：RTC实时时钟芯片


