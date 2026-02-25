---
layout: lecture
pretty_table: true
collection: csc496
course: CSC 496: iOS App Development
title: "Swift Language"
toc:
  - name: Overview about the Swift Language
  - name: Control Flow
  - name: Exercises
---
# Swift Language


## Overview about the Swift Language

{% details info Details %}

- On Xcode, go to `File`>`New`>`Playground`.
- Choose `iOS` platform and the Blank template. 
- In this section, we can use the Playground to test out snippet of codes. 

{% enddetails %}
{% details Constants, Variables, and Data Types %}


- Constants and variables must be declared before they’re used. You
declare constants with the let keyword and variables with
the var keyword.

```swift
let maximumNumberOfLoginAttemps = 10
var currentLoginAttempt = 0
```

- You can declare multiple constants or multiple variables on a single line,
separated by commas:

```swift
var x = 0.0, y = 0.0, z = 0.0
```

{% enddetails %}
{% details Type annotations %}

- You can provide a type annotation when you declare a constant or 
variable, to be clear about the kind of values the constant or variable can 
store.
- Write a type annotation by placing a colon after the constant or variable 
name, followed by a space, followed by the name of the type to use.

```swift
var welcomeMessage: String
```

{% enddetails %}
{% details Printing constants and variables %}

- Swift uses string interpolation to include the name of a constant or 
variable as a placeholder in a longer string, and to prompt Swift to replace 
it with the current value of that constant or variable.
- Wrap the name in parentheses and escape it with a backslash before 
the opening parenthesis:

```swift
var friendlyWelcome = "Bonjour"
print("The current value of friendlyWelcome is \(friendlyWelcome)")
```

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/printVar.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Semicolons %}

- Unlike many other languages, Swift doesn’t require you to write a
semicolon (;) after each statement in your code, although you can do so if
you wish.
- However, semicolons are required if you want to write multiple separate
statements on a single line.

{% enddetails %}
{% details Most common types in Swift %}

- Types:
    - Integer
    - Double
    - Boolean (`true`, `false`)
    - String
    - Swift 
- You may have noticed that you don’t have to specify the type of value
when you declare a constant or variable. This is called type inference.
- Swift uses type inference to make assumptions about the type based on
the value assigned to the constant or variable.

```swift
let pi = 3.1415
```

or

```swift
let pi: Double = 3.1414
```

{% enddetails %}
{% details Create your own type %}


```swift
import UIKit

struct Car {
    var make: String
    var model: String
    var Year: Int
}

var c = Car(make: "BMW", model: "X3", year: 2022)
print (c.make)
```

{% include figure.liquid path="assets/img/courses/csc496/01-introduction/custom_types.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Operators %}

- Assignment: 

```swift
let jedi = "Luke"
```

- Basic arithmetic

```swift
var opponentScore = 3 * 8
print(opponentscore)
var myScore = 100 / 4
print(myScore)
```

- Compound assignment

```swift
myScore += 3
myScore -= 5
myScore *= 2
myScore /=2
```

- Numeric type conversion

```swift
let x = 3
let y = 0.1415
let pi = x + y /* not work */
let pi = Double(x) + y
```

{% enddetails %}
## Control Flow

{% details Logical and comparison operators %}

- `==`
- `!=`
- `>`
- `>=`
- `<`
- `<=`
- `&&`
- `||`
- `!`

{% enddetails %}
{% details if and if/else %}


```swift
let temperature = 100
if temperature >= 100 {
    print("The water is boiling")
}
```

```swift
var finished = 2
if finished == 1 {
    print("First place!") 
} else if finished == 2 {
    print("Second place!")
} else {
    print("Third place!")
}
```

{% enddetails %}
{% details Boolean values %}


```swift
var isSnowing = false
if !ifSnowing {
    print("It is not snowing")
}
```

{% enddetails %}
{% details Switch statement %}


```swift
let numberOfWheels = 2
switch numberOfWheels {
    case 0:
        print("Missing wheels!")
    case 1:
        print("Unicycle")
    case 2:
        print("Bicycle")
    case 3:
        print("Tricycle")
    case 4:
        print()"Cars!")
    default:
        print("Too many wheels!")
}
```

```swift
let character = "z"
switch character {
    case "a", "e", "i", "o", "u":
        print("Vowels")
    default:
        print("consonant")
}
```

```swift
switch distance {
    case 0...9:
        print("It is close")
    case 10...99:
        print("A bit further")
    case 100..999: 
        print("Quite far out")
    default:
        print("Let's call a cab")
}
```

{% enddetails %}
## Exercises

{% details Grade calculation using if-else %}

Write a Swift program that takes a student's numerical grade (0 to 100) as input and outputs the corresponding 
letter grade based on the following criteria:

- A: 90-100
- B: 80-89
- C: 70-79
- D: 60-69
- F: Below 60

Template playground code:

```swift
let grade = 95

//implement if-else logic here

```

{% enddetails %}
{% details Grade calculation using switch %}

Write a Swift program that takes a student's numerical grade (0 to 100) as input and outputs the corresponding 
letter grade based on the following criteria:

- A: 90-100
- B: 80-89
- C: 70-79
- D: 60-69
- F: Below 60

Template playground code:

```swift
let grade = 95

//implement switch logic here

```

{% enddetails %}
{% details Grade calculation on app %}


- Create a new app using the pokemon app from the introduction lecture as template
- Modify it such as as a user enter the numeric grade, the corresponding letter grade is displayed
- Bonus: display the letter grade using images!

{% enddetails %}
