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

- Click the **PlatformIO ant icon** in the left activity bar.
- Go to **Quick Access**.
- Open **Miscellaneous**.
- Click **PlatformIO Core CLI**.
- Once that terminal opens, test:

```bash
pio --version
```

{% include figure.liquid path="assets/img/courses/csc574/02-setup/PlatformIO-CLI.png" max-width="50%" zoomable=true alt="Red arrow pointing to PlatformIO CLI from the icon" %}

For Mac, it is possible that you will need to do some extra PATH setup

```bash
ln -sf ~/.platformio/penv/bin/platformio ~/.local/bin/platformio
ln -sf ~/.platformio/penv/bin/platformio ~/.local/bin/pio
grep -qxF 'export PATH="$HOME/.local/bin:$PATH"' ~/.zshrc || echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

{% enddetails %}


## First PlatformIO Project

{% details Connect the Nano BLE33 %}

- Plug the Nano BLE33 into your computer. 
- Open the PlatformIO CLI inside VSCode
- Run the followings to confirm

```bash
pio device list
```

{% details info Device list on Mac %}

{% include figure.liquid path="assets/img/courses/csc574/02-setup/mac-pio-device-list.png" max-width="25%" zoomable=true alt="List of pio devices with Nano BLE33 is the USB Serial Device" %}

{% enddetails %}

{% details info Device list on Windows %}

{% include figure.liquid path="assets/img/courses/csc574/02-setup/win-pio-device-list.png" max-width="25%" zoomable=true alt="List of pio devices with Nano BLE33 is the USB Serial Device" %}

{% enddetails %}

{% enddetails %}

{% details Create your first Arduino project %}

In VS Code:

- Click the **PlatformIO** icon.
- Click `Open` under `PIO Home` to open up the `PIO Home` tab. 
- Click **New Project**.


{% include figure.liquid path="assets/img/courses/csc574/02-setup/platformio-home.png" max-width="25%" zoomable=true alt="Red boxes showing icons to click" %}


- Enter a project name: `Blink`.
- Choose your board.
- **Uncheck the location box**
- Specific the location of the project directory, which should be the `firmware` directory of the cloned `tinyml` repository.  

{% include figure.liquid path="assets/img/courses/csc574/02-setup/platformio-blink.png" max-width="25%" zoomable=true alt="Red boxes showing icons to click" %}

- Click `Finish` to create the project. 
- After creation, PlatformIO will generate a standard project structure with:
    - a `platformio.ini` file
    - two runtime folders, `.pio` and `.vscode`. 
    - a `src/` folder containing aa default `main.cpp` inside `src/`
    - empty folders for `include`, `lib`, and `test`. 
    - a default `.gitignore` file. 

{% enddetails %}

{% details Build and Deploy %}

- Replace the content of `main.cpp` with the following 
    - We will go into the details of this code in the next lecture. 

```c
#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

- You should also make sure that the `platform.ini` file has the following contents

```c
[env:nano33ble]
platform = nordicnrf52
board = nano33ble
framework = arduino
lib_deps = 
    arduino-libraries/Arduino_LSM9DS1
monitor_speed = 9600
```

- To build this project, you are to 
    - open the PlatformIO terminal
    - change to the project directory
    - run `pio run`
- You might have a `warning` on LF clock source. That warning can be ignored. 

{% include figure.liquid path="assets/img/courses/csc574/02-setup/mac-blink-run.png" max-width="25%" zoomable=true alt="Run results of the Blink project build on a Mac" %}

- After a successful build, we will need to deploy the built binary to the `Nano 33 BLE` board. 
    - Plug in the board over USB.
    - Run the following command. Use the port identified previously from `pio device list`. 

```bash
# This is for Mac
pio run -t upload --upload-port /dev/cu.usbmodem1201
```

{% include figure.liquid path="assets/img/courses/csc574/02-setup/mac-blink-upload.png" max-width="25%" zoomable=true alt="Upload the built source code to the board" %}

{% enddetails %}


## Notes:

- `firmware/` starter sketch templates
- `notebooks/serial_plot.ipynb`
- `models/README.md` describing naming conventions for exported models
