# STM32WBA HeartRate FreeRTOS 

This application demonstrates how to build a BLE application on STM32WBA5 with X-cubeFreeRTOS.

## Setup
This application is running on s **NUCLEO-WBA55CGA board**.

It implements standard BLE HeartRate profile build thanks to: 
- STM32CubeMX v6.11.1
- STM32CubeWBA v1.3.1
- X-Cube-FreeRTOS v1.2.0

Open firmware project with desired IDE, compile and flash the board.

## Application description
At startup board starts advertising

To connect to the board use one of following application:
- <a href=https://play.google.com/store/apps/details?id=com.st.dit.stbletoolbox> ST BLE Toolbox Android</a>
- <a href=https://apps.apple.com/us/app/st-ble-toolbox/id1531295550> ST BLE Toolbox iOS</a>
- <a href=https://play.google.com/store/apps/details?id=com.st.bluems> ST BLE Sensor Android</a>
- <a href=https://itunes.apple.com/us/App/st-bluems/id993670214?mt=8> ST BLE Sensor iOS</a>
- <a href=https://applible.github.io/Web_Bluetooth_App_WBA/> ST Web Bluetooth page</a>

Connect to targeted device and you can see heartbeat values notified.

This application uses standby as low power mode. All timings are based on RTC, systick is not used.

## Troubleshooting

**Caution** : Issues and the pull-requests are **not supported** to submit problems or suggestions related to the software delivered in this repository. The STM32WBA-BLE-HeartRate-FreeRTOS example is being delivered as-is, and not necessarily supported by ST.

**For any other question** related to the product, the hardware performance or characteristics, the tools, the environment, you can submit it to the **ST Community** on the STM32 MCUs related [page](https://community.st.com/s/topic/0TO0X000000BSqSWAW/stm32-mcus).
