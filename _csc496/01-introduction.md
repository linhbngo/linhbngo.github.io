---
layout: lecture
pretty_table: true
collection: csc496
course: CSC 496: iOS App Development
title: "Introduction"
toc:
  - name: Getting Started with App Development
  - name: Coding in Swift
  - name: Coding Swift: Xcode IDE
  - name: "Modify/build your first app"
---
# Introduction

{% details info Details %}

This slide deck is based on Dr. Si Chen's slides


{% enddetails %}
{% details Planning %}

- Attendance is critical. 
- Weekly planning:
    - Swift Fundamental (usually on Thursday)
        - Basic syntax
        - Some new concepts
    - App Design and Development (usually on Tuesday)
        - SDK
        - Building specific features for iOS apps
        - Mini-project, in-class labs

{% enddetails %}
## Getting Started with App Development

{% details History of Swift %}

- At the Apple Worldwide Developers Conference 2014, Apple introduced Swift as 
a modern language for writing apps for iOS and macOS. Apple now has new 
platforms, including watchOS and tvOS, that also use Swift as the primary
programming language.
- Since the 1990s, most developers have written applications for Apple platforms in 
Objective-C, a language built on top of the C programming language. Objective-C 
is more than 30 years old, and C is more than 40 years old.
- As you learn Swift, you may see the influence of its C and Objective-C heritage.

- In 2020, the percentage of Swift was 1.88%.

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/language_2024.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Pros and Cons of Swift %}

{% details success Pros %}

- Advanced functionality (frequent updates and commitment from Apple)
- High speed of development
- Cross-platform development
- Open source

{% enddetails %}
{% details Cons %}

- Constant changes (frequent updates)
- No support for earlier versions
- Need bridging to import C++ libraries into Swift

{% enddetails %}
{% enddetails %}
{% details Apps built using Swift %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_app.jpeg" width="50%" zoomable=true %}

{% enddetails %}
{% details Swift language features %}

- Multi-paradigm language
    - Support object-oriented programming
    - Include functional programming features such as high-order function, functions as values, 
    nested functions, closures, anonymous functions, etc.

{% enddetails %}
## Coding in Swift

{% details Hello World %}

- Swift code is written in plain text files with a .swift file extension. Each line 
in the file represents a statement, and a program is made up of one or 
more statements. These are the instructions you wish your app to run.
- In Swift, the default file is called `main.swift`. Any Swift code included in 
the `main.swift` file will be executed from top to bottom.

{% enddetails %}
{% details Terminal and Swift REPL %}

- **macOS** comes with a console app called `Terminal`, and `Swift` comes with
a tool called a `REPL`, which stands for `Read, Eval, Print Loop`. 
- The REPL allows you to enter simple commands, evaluate them, and print the result.
- Use the Swift REPL in the console to write your first “Hello, world!”
program.
    – Open the Terminal application on your Mac. You can search `Terminal` in
    Spotlight or find the application in the system Applications/Utilities folder.
    – Enter the Swift REPL by typing `swift repl` and pressing Return.
    – Type the command `print(”Hello, world!”)` and press Return to execute it.

{% details warning License %}

- If you are using your personal computer, the first time that you run swift, you will be asked to 
accept the Xcode license. 
    - Enter your account password (should be administrative account)
    - Type `agree` and press `Enter`

```bash
sudo xcodebuild -license
```

{% enddetails %}
```bash
swift repl
```

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_hello.png" width="50%" zoomable=true %}

{% enddetails %}
{% details User Interface design in Swift %}

- Visit [Apple Developer Documentation Site](https://developer.apple.com/documentation/)
- Learn about:
    - SwiftUI
    - SpriteKit
    - AVFoundation
    - GameKit

{% enddetails %}
{% details Model-View-Controller %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/mvc.png" width="50%" zoomable=true %}

{% enddetails %}
## Coding Swift: Xcode IDE

{% details Getting started %}


- On personal computer: Install via Mac App Store
- Online playground: [http://online.swiftplayground.run/](http://online.swiftplayground.run/)
- First time launch:
    - Additinal downloads might be needed

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_xcode.png" width="50%" zoomable=true %}

{% enddetails %}
{% details First project %}


- Select `Create a new Xcode project`

{% details info Create a new Xcode project %}

- Select `iOS`
- Select `App`
- Click `Next`

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_ios.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Choose the following options for your project %}

- Product name: `hello`
- Organization identifier: `wcupa`
- Keep everything else as default
- Click `Next`

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_proj_options.png" width="50%" zoomable=true %}

{% enddetails %}
- Follow the instructions to identify the location of a directory where the 
new project directory will be placed.
- Once everything is done, the Swift IDE will be displayed, with a default 
template project called `hello` generated. 

{% details info Swift IDE %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/swift_ide.png" width="50%" zoomable=true %}

{% enddetails %}
- To run this project, clock on the `Play` icon on the tool bar. 
    - A iPhone simulator will be display, with the `hello` app shown 
    on the home screen. 
    - Double-click on the app to launch. 

{% details Run the project %}


{% details Default home screen %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/hello_closed.png" width="50%" zoomable=true %}

{% enddetails %}
{% details App launched %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/hello_launched.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% enddetails %}
## "Modify/build your first app"

{% details App Icon %}

- Download the [AppIcons.zip](codes/AppIcons.zip) file and double click 
to unzip
- Inside the unzipped directory, navigate to `Assets.xcassets`/`AppIcon.appiconset`,
- In the Xcode IDE navigator, go to `Assets`, select `AppIcon`. 
- In the `Inspector` area, select `Single Size` for iOS.
    - Start drag and drop the `.png` files into the boxes according to the dimension/file name. 
    - The unzipped directory contains file sizes for others. 

{% details info AppIcon %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/appicon.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info Local storage %}

The icon pictures will show up inside your app's local directory.

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/appicon_storage.png" width="50%" zoomable=true %}

{% enddetails %}
{% details info New Icon! %}


Rerun the simulator and observe the new icon

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/newicon.png" width="50%" zoomable=true %}

{% enddetails %}
{% enddetails %}
{% details Buttons and Images %}


{% details note Clickable button %}


- Modify the `ContentView: View` struct code as follows.

{% details ContentView: View %}


```swift linenums="1"
--8<-- "docs/csc496/lectures/codes/01-intro/button.swift"
```

{% enddetails %}
- Simulate the code and test out the clickable button. 

{% enddetails %}
{% details note More details ... %}

- Download the [pokemon.zip](codes/pokemon.zip) and unzip
- Drag the first four image files (1 through 4) into `Assets`

{% details More images in Assets %}

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/images.png" width="50%" zoomable=true %}

{% enddetails %}
 - Modify the `ContentView: View` struct code as follows to
    - Add a typeable text file that takes a `user-input` pokemon ID
    - Use this value to display a pokemon. 

{% details ContentView: View %}


```swift
--8<-- "docs/csc496/lectures/codes/01-intro/images.swift"
```

{% enddetails %}
- Simulate the code and test out the clickable button. 




{% enddetails %}
{% enddetails %}
