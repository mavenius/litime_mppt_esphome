# litime_mppt_esphome
ESPHome configuration for LiTime MPPT controllers with bluetooth (BLE)
I determined that my controller uses MODBUS over BLE, so this project takes advantage of that to interact with the device.
I have read that LiTime controller might be rebranded ones made by HQST, so this might work for those as well. YMMV.

### Usage
 - litime_solar_mppt.h should not need to be modified in order to get the default functionality out of this project.
 - In litime_solar_mppt.yaml, update the values in `substitutions` to match your needs (at least the liTimeMacAddress will need to be updated to match your device. You can determine your device's MAC by using a BLE scanner on Android or iOS.)

### Supported device(s)
This has been tested with the following charge controllers:

 - LiTime BT-LTMPPT4860
 - LiTime BT-LTMPPT2430
 - HQST M4860N

More information: It looks like HQST and LiTime both put their name on this controller. The base model is called the M4860 or M4860N (Negative ground). I think the OEM is Helios which lists the model as Venus-M4860 or Venus-M4860N

### Getting started with ESPHome
If you don't yet have any experience with ESPHome, I recommend looking here for guidance: https://esphome.io/guides/getting_started_command_line
I use the command line to compile and upload my configurations to my ESP32 board(s) and therefore don't have any experience with the ESPHome web interface (glancing through the docs, I don't know how to use a header file like `litime_solar_mppt.h` that is used in this project, so the CLI is probably your best bet.)
Here are instructions to install ESPHome manually (which is what I did.) https://esphome.io/guides/installing_esphome

Once that is done, you can run commands such as these from the root of this project:
`esphome compile litime_solar_mppt.yaml` # (compiles without uploading, so you can test your changes without needing a board connected)
`esphome run litime_solar_mppt.yaml` # (compiles and uploads to a connected board)

### Disclaimer

This is not an official library endorsed by the device manufacturer. LiTime and all other trademarks in this repo are the property of their respective owners and their use herein does not imply any sponsorship or endorsement. Further, all code contained herein is provided "as is" without guarantees of performance or suitability; use it at your own risk.