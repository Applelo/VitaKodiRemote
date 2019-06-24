# VitaMaterialProject [![Build Status](https://travis-ci.org/Applelo/VitaMaterialKit.svg?branch=master)](https://travis-ci.org/Applelo/VitaMaterialKit)

### Kit in C++ inspired by Material UI to create quickly a beautiful application for PSVita systems

Wiki will be available soon to explain how to create an app, the view system and details each functions in each class.

## Showcase

* [Vita-CTP-Shortcut](https://github.com/CTPBenchmark/Vita-CTP-Shortcut), soon

(More to come :smiley: )

## Changelog

See [Changelog](https://github.com/Applelo/VitaMaterialKit/blob/master/src/kit/Changelog.md) file


## Build
Install **VitaSDK** with [**VDPM**](https://github.com/vitasdk/vdpm) and run the followed commands :

```shell
cmake .
make
```

CMake will download and update all dependencies.

You can also use this followed commands to send directly built files and launch Vita3K :

```shell
#send eboot.bin file with FTP
make send
#send vpk with FTP
make send_vpk
#copy eboot.bin file with USB
make copy
#send vpk with USB
make copy_vpk
#emulate Update eboot.bin and launch app in Vita3K
make emulate
#emulate_vpk Install the app in Vita3K
make emulate
```

## Credits

* Developed & maintained by *Applelo*
* *Tuxbot123* for his suggestions and his support
* My master, *MisterAlex*


* *coderx3* (aka devingDev) for his work on VitaCord inspired me for my own IME, Scroll, Pad and Touch functions
* *gnuton* for Travis CI for PSVita homebrews
* *Google* for Material Guidelines, Fonts, Components, Themes
* [Material Design Icons](https://github.com/Templarian/MaterialDesign-Webfont/) teams for all icons
* *juliettef* for [Material Design Icons Headers](https://github.com/juliettef/IconFontCppHeaders)
* [unilib](https://github.com/ufal/unilib) for lowercase & UPPERCASE work with unicode char

