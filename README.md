# Modded fork of the experimental simulator for Mbed OS 5.10 applications

### Motivation
 - While *some* of the instructions from the original readme work, most of them don't anymore because of version mismatches and whatnot. 
 - What's extra frustrating is that even the docker image doesn't work 
   - I mean is anyone really surprised? That a docker image doesnt "just works out of the box"?
 - Not all the demos that are online exist in the [original repository](https://github.com/ARMmbed/mbed-simulator) nor the [originally original repository](https://github.com/janjongboom/mbed-simulator).
 - I need my Embedded Systems students to have an independent (of internet, arm server outages etc.) development environment.
 
### What's new?
 - Has a stdin serial demo also thanks to [@janjongboom](https://github.com/janjongboom)
 - We almost made the MQTT demo work (but socket.recv function does not timeout so the program hangs).
 - Dockerfile fixed.
 - Readme below is modified to reflect updated/advised setup method.
 - This also sets up a modified version of [FreeRTOS-Emulator repo](https://github.com/alxhoff/freeRTOS-Emulator) by [@alxhoff](https://github.com/alxhoff).
 - It sets up some of my favourite editors and programs too (sublime, terminator)

### Documentation
 - A quick introduction video (youtube) can be found [here](https://www.youtube.com/watch?v=FjyCILASznE) and advice on running it on a VM can be found [here](https://www.youtube.com/watch?v=guM6YvnveaM).
 - Neither mbed OS 6 nor mbed 2 _(which used to keep showing up on google search)_ is not even remotely compatible with 5.x. So please don't refer to those docs.
 - Original mbed documentation is neatly hosted at https://os.mbed.com/docs/mbed-os/v5.15/introduction/index.html
   - As much as 5.15 API is mostly compatible with 5.10, some things may not be. And it will surely be deprecated soon.
 - Original documentation can be accessed from here: https://github.com/ARMmbed/mbed-os-5-docs/blob/5.10/docs/introduction/introduction.md
   - If that's gone too by the time you're here, head here for last resort: https://github.com/alpsayin/mbed-os-5-docs/tree/5.10/docs/introduction/introduction.md
   - Of course this isn't as navigable as the original hosted version. Let me know if you know what's the builder for this and I'll apply and host.
 
### TL;DR ?

 - Run `setup_script.bash`
 - OR    `docker build . -t mbed-simulator && docker run -dp7829:7829 -it mbed-simulator`

 ### Video links 
 #### mbed and mbed Simulator Introduction
 [![mbed and mbed Simulator Introduction](https://img.youtube.com/vi/FjyCILASznE/hqdefault.jpg)](https://www.youtube.com/watch?v=FjyCILASznE)
 #### Hosting and Running mBed Simulator (api v5.10) on a VM
 [![Hosting and Running mBed Simulator (api v5.10) on a VM](https://img.youtube.com/vi/guM6YvnveaM/hqdefault.jpg)](https://www.youtube.com/watch?v=guM6YvnveaM)
 

### Original readme ensues ...

# Experimental simulator for Mbed OS 5 applications

**Demo: https://simulator.mbed.com**
_(this is not the same version as the one provided here)_

![Screenshot](https://os.mbed.com/media/uploads/janjongboom/simulator2.png)

While we have worked hard to improve embedded development tooling in Mbed (e.g. via the Online Compiler), the development for microcontrollers is still very similar to how it was in the 90s. Compilation is slow, and flashing is even slower. When fixing a bug, you need to get the device into the exact state as before encountering the bug. This makes for a very slow feedback loop, which hinders productivity and often pulls you out of the zone.

To make this feedback loop much shorter, we're releasing an alpha version of the Mbed Simulator. The simulator allows you to run your Mbed OS 5 applications directly on your computer, so that you can quickly test and verify applications without flashing them on a real board. This is a valuable learning tool, as you quickly learn how Mbed works. It is also very useful for developing complex applications. Within Arm, we have been using the simulator for work on [mbed-http](https://os.mbed.com/teams/sandbox/code/mbed-http/), the Mbed LoRaWAN stack and [uTensor](http://utensor.ai/).

**Note:** The Mbed Simulator is part of [Mbed Labs](https://labs.mbed.com/). The Mbed Labs projects showcase interesting side projects developed by Mbed engineers. However, these projects are not actively supported by Arm, and may be added, removed or break at any time.

[More information in the introductionary blog post](https://os.mbed.com/blog/entry/introducing-mbed-simulator/)

## Docs

* Installation, see below.
* [Configuration and compiler options](docs/simconfig.md)
* [Peripherals](docs/peripherals.md)
* [File systems and block devices](docs/fs.md)
* [Pelion Device Management](docs/pelion.md)
* [Debugging](docs/debugging.md)
* [Architecture](docs/architecture.md)

## Installation

### Docker installation

1. Install Docker
1. Build the Docker image _(run below command from inside repository folder)_:  
    `docker build . -t mbed-simulator`
1. Run the Docker image:  
   `docker run -dp7829:7829 -it mbed-simulator`
1. The simulator can now be accessed at:  
    http://localhost:7829

### Local installation

**Arch Linux (Manjaro advised for students)**

1. Run the setup script and follow the prompts. Note that this will download all dependencies (including Mbed OS) and will build the common `libmbed` library so this'll take some time. 
I highly advise to give it a good read before running the script;
 - It'll call sudo, 
 - it will install development libraries such as SDL2, clang, binutils, fakeroot, base-devel, cmake, 
 - it'll install nvm, npm and emsdk environments. 
While this is great for a student with a fresh VM, may be disastrous if you've a finely aged development environment (but then you should also know better than running arbitrary scripts from internet :)).

    ```
    $ ./setup_script.bash
    ```

2. Run the simulator (this will activate some environment variables):

    ```
    $ ./start_mbed_simulator.bash
    ```

**Ubuntu**

Follow the commands inside the Dockerfile.

**Windows**

1. Use the docker image 
1. Or use the commands inside the Dockerfile inside
   1. Multipass by Canonical
   1. Windows Subsystem for Linux (WSL) and follow the commands inside 

**MacOS**

Get a real computer or use the docker image?

_p.s. this is still unlikely to work properly in M1 macs. You really need to get a proper development computer, not an overglorified smartphone._

### Troubleshooting

**Pointer_stringify Issues**
This error is thrown when you use too high an emscripten version. According to release notes 1.38.27 version of Emscripten aborts by default when Pointer_stringify is called. I tried 1.38.26 which didn't quite compile. So I decided to use 1.38.21 as per the original docs. Further reading below:
 - https://github.com/janjongboom/mbed-simulator/issues/44
 - https://github.com/janjongboom/mbed-simulator/issues/43

**Windows: [Error 87] The parameter is incorrect**

This error is thrown on Windows systems when the path length limit is hit. Move the `mbed-simulator` folder to a folder closer to root (e.g. `C:\mbed-simulator`).

## How to run the hosted version

1. Install all dependencies _(cheating from Dockerfile or the setup script)_, and clone the repository from source (see above).
1. Run:

    ```bash
    npm install
    npm run build-demos
    ```

1. Then, start a web server:

    ```bash
    node server
    ```

1. Open http://localhost:7829 in your browser.
1. Blinky runs!

## CLI

The simulator comes with a CLI to run any Mbed OS 5 project under the simulator.

**Running**

To run an Mbed OS 5 project:

```bash
mbed-simulator .
```

The project will build and a web browser window will open for you.

To see if your program runs in the simulator, check the `TARGET_SIMULATOR` macro.

**Running in headless mode**

You can also run the simulator in headless mode, which is great for automated testing. All output (through `printf` and traces) will be routed to your terminal. To run in headless mode, add the `--launch-headless` option. You might also want to limit the amount of logging the server does through `--disable-runtime-logs` to keep the output clean.

## Changing mbed-simulator-hal

After changing anything in the simulator HAL, you need to recompile the libmbed library:

1. Run:

    ```bash
    rm mbed-simulator-hal/libmbed.bc
    ```

1. Rebuild your application. libmbed will automatically be generated.

## Updating demos

In the `out` folder a number of pre-built demos are listed. To upgrade them:
```bash
npm run build-demos
```

## Attribution

* `viewer/img/controller_mbed.svg` - created by [Fritzing](https://github.com/fritzing/fritzing-parts), licensed under Creative Commons Attribution-ShareALike 3.0 Unported.
* Thermometer by https://codepen.io/mirceageorgescu/pen/Ceylz. Licensed under MIT.
* LED icons from https://pixabay.com/en/led-icon-logo-business-light-1715226/, Licensed under CC0 Creative Commons.
* Some of the demo/component JS sources were taken from https://simulator.mbed.com.
