# Koraidon

It's my Linux custom firmware project. It uses modified TWRP recovery for booting.

# How To Build

You need to get TWRP recovery for your phone.

You need to perform some modifications on your TWRP image:
1. Unpack image
2. Remove service `/sbin/recovery` from your `init.recovery.rc` file
3. Pack image back
4. Flash your modified recovery into your device.

If you're doing everything correct, instead of recovery you should see "frozen" boot logo: It's normal.
And if you connect your device to computer, you will be able to enter device's shell using `adb shell` command.

Also, you need an Android NDK (not SDK).
Download latest version from official website and unpack it.

Then download this repo.

Enter this repo: `cd Koraidon`

Then you need to modify Makefile: you can change the NDK and NDK_PATH to make build work.

Now, compile project using `make` command.

Then turn your device into recovery mode.

To deploy Koraidon, run `make push` command.

Then run Koraidon, using `make run` command.

# Supported devices

+ Dexp B140 (Spreadtrum)

# Images

![Dexp B140](https://github.com/NDRAEY/Koraidon/assets/47180136/2e1c2d14-e41e-4bba-8636-63d74b03bca1)

<p align="center">
    <i>Dexp B140</i>
</p>
