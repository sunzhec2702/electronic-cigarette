electronic cigarette project

This project is based on GD32F106 which has the similar features and performance with STM32F106 but much cheaper.
This project can be run succesfully with our PCB which has been MP (mass production) already.

The electornic cigarette in this project currently support 30W/45W/60W/90W output. And the output modes supported are fixed voltage, fixed watt and fixed temperature.
Of course, the extra features in other electronic cigarette are also supported, such as coil missing check, coil resistor evaluation, long press protection, button lock and so on.
Over voltage/current protections are also done in this projects.
With our designed algorithm, the temperature and voltage can be controlled greatly and exactly same with the preset target.
And the whole system stability is perfect. We have done monkey test and stability test for over one month. No issue (crash/hang) is seen.
Besides that, the power control is also great under SW/HW effort. In standby mode, the leakage current is less than 0.1mA and in output mode, the effiency is very high.

Easily UI custom modification and extension. some animations support.

电子烟项目

本项目编译和运行基于GD32F106，该芯片与STM32F106有着类似的特性以及性能，但是整体的保价会更为便宜。
本项目已经在自己的PCB上面成功量产。

本电子烟项目支持主流的30W/45W/60/90W输出，更大的功率存在安全风险，暂不支持。
支持固定电压输出、固定功率输出以及固定温度输出，用来保证不同场景下的不同需求。同类产品的一些其他特性也是支持的，比如烟头丢失保护、烟头电阻测量、抽烟长按保护、按键锁等等。
支持过流过压保护。

本项目中特定的算法设计可以快速并且准确的控制输出电压来保证我们预先设定的温度以及功率。
我们已经进行了超过一个月的Monkey test以及正常的稳定性测试，没有任何死机重启等等问题发生。
除此了上述特性之外，通过软件和硬件的配合，我们的电量控制非常的优秀。待机模式下，leakage小于0.1mA。输出模式也能保持整体高效。

UI可以轻易的进行定制和扩展。

