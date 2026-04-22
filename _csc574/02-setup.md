---
layout: lecture
pretty_table: true
title: Development Environment
toc:
  - name: Overview
  - name: Setup Environment
  - name: VSCode and PlatformIO
  - name: Challenges of tinyML
  - name: Course Hardware
---


## Overview
>Disclaimer:
In this class, we aim to setup a development environment that is as isolated as possible 
without being fully containerized. This is possible via a Git repository that supports:
- a **conda environment** for Python, Jupyter, plotting, serial tooling, and TensorFlow
- a **downloaded Arduino CLI binary** placed in `tools/arduino-cli/`
- **repo-local Arduino CLI state** so package indexes, downloads, caches, and sketchbook files do not spill into each student's global machine setup
{: .block-tip}

## Setup Environment

{% details Clone repository %}

First, you are to clone the repository.

```bash
git clone https://github.com/ngo-classes/tinyml.git
cd tinyml
```

The layout of this repository can be presented as follows. 

```text
.
├── .arduino-build-cache/
├── .arduino-data/
├── .arduino-downloads/
├── .arduino-user/
├── arduino-cli.yaml
├── data/
├── environment.yml
├── firmware/
├── models/
├── notebooks/
├── scripts/
└── tools/
    └── arduino-cli/
```

- `environment.yml`: conda environment definition
- `arduino-cli.yaml`: Arduino CLI configuration
- `tools/arduino-cli/`: where each student places the correct Arduino CLI binary for their OS
- `data/`: reserved for datasets; contents ignored by git by default
- `models/`: reserved for trained/exported models; contents ignored by git by default
- `.arduino-*`: local Arduino CLI package/cache/user state, kept in the repo but ignored by git

{% enddetails %}

{% details Create and activate the conda environment %}

```bash
conda env create -f environment.yml
conda activate tinyml
```
{% enddetails %}


{% details Download and save the Arduino CLI binary %}

You are to download the [latest binary release of Arduino CLI](https://docs.arduino.cc/arduino-cli/installation/#latest-release) and unzip the downloaded files. Next, place **one** of the following in `tools/arduino-cli/` depending on your system:

- `arduino-cli.exe` for Windows
- `arduino-cli` for macOS or Linux

That directory is intentionally git-ignored so the binary file is not accidentally committed.

{% enddetails %}


{% details Activate the repo-local Arduino CLI configuration %}

For macOS/Linux/Git Bash, run the followings:

```bash
source scripts/activate.sh
```

For Windows PowerShell, run the followings:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\scripts\activate.ps1
```

{% enddetails %}

{% details Verify setup %}

For macOS/Linux/Git Bash, run the followings:

```bash
chmod u+x scripts/check-setup.sh
scripts/check-setup.sh
```

{% include figure.liquid path="assets/img/courses/csc574/02-setup/mac-check-setup.png" max-width="50%" zoomable=true alt="Check results of Arduino CLI activation" %}


For Windows PowerShell, run the followings:

```powershell
.\scripts\check-setup.ps1
```

{% include figure.liquid path="assets/img/courses/csc574/02-setup/win-check-setup.png" max-width="50%" zoomable=true alt="Check results of Arduino CLI activation" %}

{% enddetails %}


{% details Setup core libraries %}

- This script installs the `Arduino Mbed OS Nano Boards` core used by the Nano 33 BLE/BLE Sense, plus the course libraries `ArduinoBLE`, `Arduino_LSM9DS1`, and `Harvard_TinyMLx`. 
- The script also forces Arduino CLI to use repo-local state via ARDUINO_* variables. 

For macOS/Linux/Git Bash, run the followings:

```bash
chmod u+x scripts/bootstrap-arduino.sh
scripts/bootstrap-arduino.sh
```

For Windows PowerShell, run the followings:

```powershell
.\scripts\bootstrap-arduino.ps1
```

{% enddetails %}

## VSCode and PlatformIO

In this set up, we are using PlatformIO from **inside** VSCode. Therefore, it is important that **you do not need to install PlatformIO Core separately** for this workflow; PlatformIO Core is bundled with the VS Code extension and is meant to be used through the **PlatformIO IDE Terminal**. 


{% details Install VSCode %}

Download and install the official Microsoft build of Visual Studio Code. PlatformIO IDE is built on top of VS Code. 

{% enddetails %}

{% details Install PlatformIO %}

Do the followings in VSCode:

- On the left sidebar, click the **Extensions** icon.

{% include figure.liquid path="assets/img/courses/csc574/02-setup/vscode-extensions.png" max-width="25%" zoomable=true alt="Red arrow pointing to the extension side icon" %}

- In the search box, type **PlatformIO**.
    - Look for the **official `PlatformIO IDE` extension**.
- Click **Install**. 

{% include figure.liquid path="assets/img/courses/csc574/02-setup/vscode-platformio.png" max-width="50%" zoomable=true alt="Top result of searching for PlatformIO showing the official extension" %}

- Completely close and reopen VSCode (it might ask for a restart).
- After restart, the `PlatformIO` icon will show up on the left activity bar.

{% include figure.liquid path="assets/img/courses/csc574/02-setup/platformio-icon.png" max-width="25%" zoomable=true alt="Red arrow pointing to PlatformIO icon on the left side activity bar" %}

{% enddetails %} 

{% details Verify PlatformIO is using the built-in core %}

- Open **Settings** in VS Code.
- Search for: `platformio use builtin`
- Make sure the box `Use a built-in PlatformIO Core` is checked. 

{% include figure.liquid path="assets/img/courses/csc574/02-setup/vscode-platformio.png" max-width="50%" zoomable=true alt="Settings for platformio use builtin show two checked boxes for Core and Python" %}

{% enddetails %}

{% details Open the PlatformIO CLI inside VSCode %}


 PlatformIO sidebar

1. Click the **PlatformIO ant icon** in the left activity bar.
2. Go to **Quick Access**.
3. Open **Miscellaneous**.
4. Click **PlatformIO Core CLI**. ([PlatformIO Documentation][1])

Once that terminal opens, test:

```bash
pio --version
```

If it works there, PlatformIO is installed correctly inside VS Code.

{% enddetails %}


## First PlatformIO Project

{% details Create your first Arduino project %}

PlatformIO’s own quick start uses a Blink project to introduce the workflow. ([PlatformIO Documentation][1])

In VS Code:

1. Click the **PlatformIO Home** button on the PlatformIO toolbar.
2. Click **New Project**.
3. Enter a project name.
4. Choose your board.
5. Choose the framework, if prompted.
6. Create the project. PlatformIO describes this as the normal new-project flow. ([PlatformIO Documentation][1])

After creation, PlatformIO will generate a standard project structure with:

* a `platformio.ini`
* a `src/` folder
* a default `main.cpp` inside `src/` ([PlatformIO Documentation][1])

{% enddetails %}

{% details Replace `main.cpp` with Blink %}

Open `src/main.cpp` and replace the contents with the Blink example. PlatformIO’s quick start provides the Arduino-based Blink code and notes that it is for Arduino-based boards. ([PlatformIO Documentation][1])

Use:

```cpp
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

This is essentially the same Blink pattern PlatformIO shows in its quick start. ([PlatformIO Documentation][1])

{% enddetails %}

{% details Build the project %}

PlatformIO documents two easy routes: toolbar or keyboard shortcut. The toolbar is less mysterious for students. ([PlatformIO Documentation][1])


Keyboard shortcut

* On macOS, PlatformIO lists **`cmd-shift-b`** as the build shortcut.
* Other shortcuts vary by platform, but on Mac that is the one to remember. ([PlatformIO Documentation][1])

You can also use the task menu:

1. Go to **Terminal → Run Task...**
2. Select **PlatformIO: Build**. PlatformIO documents these built-in tasks as part of the IDE integration. ([PlatformIO Documentation][1])

{% enddetails %}

{% details Connect the board and upload firmware %}

After a successful build:

1. Plug in the board over USB.
2. Click the **Upload** button on the PlatformIO toolbar.

Or:

1. Go to **Terminal → Run Task...**
2. Select **PlatformIO: Upload**. PlatformIO includes Upload as one of its built-in tasks. ([PlatformIO Documentation][1])

The keyboard shortcut PlatformIO lists for upload is **`ctrl+alt+u`**. ([PlatformIO Documentation][1])

{% enddetails %}

{% details Open the Serial Monitor %}

PlatformIO includes a Serial Port Monitor in the toolbar and in its task system. It also allows customization in `platformio.ini` through monitor-related options such as `monitor_port` and `monitor_speed`. ([PlatformIO Documentation][1])

To open it:

1. Click the **Serial Port Monitor** button on the PlatformIO toolbar.

Or:

1. Go to **Terminal → Run Task...**
2. Select **PlatformIO: Monitor**. ([PlatformIO Documentation][1])

The listed shortcut is **`ctrl+alt+s`**. ([PlatformIO Documentation][1])

If you want to define the monitor baud rate in `platformio.ini`, PlatformIO documents `monitor_speed` for that purpose. ([PlatformIO Documentation][1])

Example:

```ini
[env:yourboard]
monitor_speed = 115200
```
{% enddetails %}

{% details Understand the PlatformIO toolbar %}

PlatformIO documents the status-bar toolbar and its common buttons. This is worth showing students explicitly because it becomes their dashboard. The toolbar includes quick access to:

* PlatformIO Home
* Build
* Upload
* Clean
* Serial Port Monitor
* PlatformIO Core CLI
* environment switcher if multiple environments exist ([PlatformIO Documentation][1])

{% enddetails %}

{% details Use Project Tasks when you want more visibility %}

PlatformIO exposes a **Project Task Explorer** under the PlatformIO activity bar and also integrates tasks into **Terminal → Run Task...**. That is useful when students need a visible list of actions such as Build, Upload, Clean, and Monitor instead of memorizing icons or shortcuts. ([PlatformIO Documentation][1])

{% enddetails %}

{% details 14. Working with multiple PlatformIO projects %}

If your repo contains several firmware projects, PlatformIO supports **multi-project workspaces** through VS Code’s **multi-root workspaces**. That is the official route when you are working on multiple related firmware folders at once. ([PlatformIO Documentation][1])

{% enddetails %}

{% details “`pio` command not found” %}

Usually one of these:

* you opened a normal terminal, not **PlatformIO Core CLI**
* `platformio-ide.useBuiltinPIOCore` is off
* your shell `PATH` was overwritten instead of extended
* you expected `pio` to work system-wide without using **Install Shell Commands** ([PlatformIO Documentation][1])

{% enddetails %}


## Notes:

- `firmware/` starter sketch templates
- `notebooks/serial_plot.ipynb`
- `models/README.md` describing naming conventions for exported models
