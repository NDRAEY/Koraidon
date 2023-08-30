# Koraidon

It's my Linux custom firmware project. It uses modifed TWRP recovery for booting.

# How To Build

You need to get TWRP recovery for your phone.

You need to perform some modifications on your TWRP image:
1. Unpack image
2. Remove service `/sbin/recovery` from your `init.recovery.rc` file
3. Pack image back
4. Flash your modified recovery into your device.

If you doing everything correct, instead of recovery you should see "frozen" boot logo: It's normal.
And if you connect your device to computer, you will able to enter device's shell using `adb shell` command.

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
