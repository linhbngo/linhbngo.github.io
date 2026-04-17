---
layout: lecture
pretty_table: true
collection: csc496
title: "Concurrency and Threading, Asynchronous Programming"
toc:
  - name: Overview
  - name: Threads
  - name: Concurrency and Threads in Apple Ecosystem
---
# Concurrency and Threading, Asynchronous Programming

## Overview

{% details What is concurrency? %}

- Doing multiple tasks at the same time. 
    - The tasks can be completely different from one another in term of instructions, datasets, durations, etc.
- Apple's processors have multiple cores

{% include figure.liquid path="assets/img/courses/csc496/07-concurrency/a17bionic.png" width="50%" zoomable=true %}

{% include figure.liquid path="assets/img/courses/csc496/07-concurrency/a17stats.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Apple A-series chips %}

- Apple's A-series chips are custom-designed chips for the iPhone, iPad, and other 
Apple devices. Starting from certain versions, these chips contain two different types
of cores: efficiency cores (E-cores) and performance cores (P-cores).
- Efficiency (E) cores:
    - Design Objective: These are designed for energy conservation, capable of running 
    consistently even under high loads.
    - Usage: For handling background tasks, tasks with low computational demands, or task 
    that run continuously.
    - Characteristics: They have relatively lower processing power, but they're more 
    energy-efficient.   
- Performance (P) cores:
    - Design Objective: Designed for handling high-load tasks, such as complex graphics 
    rendering or computation-intensive tasks.
    - Usage: For tasks that demand a high computational capability within a short time.
    - Characteristics: They process tasks faster but also consume more power.

{% enddetails %}
## Threads

{% details Overview %}

- Every iOS application has a main thread, which is there to display your user interface and 
listen for events
- Complex computations may slow down the main thread and freeze the app. 
    - There is where multithreading comes into play
    - Move all the heavy computations to background threads and then move the result back to 
    the main thread once done. 

{% include figure.liquid path="assets/img/courses/csc496/07-concurrency/multithreads.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Analogy %}

- Main Thread (Waiter): Imagine a waiter serving customers at a restaurant. They interact directly with customers, take orders, deliver food, and handle payments. They must remain responsive and attentive at all times—just like the main thread, which updates the user interface and handles user interactions. If the waiter stops or slows down, customers become frustrated.

- Background Thread (Kitchen Staff): The kitchen staff prepares the food. They work behind the scenes, independently preparing orders, washing dishes, and organizing supplies. Their tasks might be time-consuming, but they do not directly interact with customers. These are like background threads, handling tasks that could take time or block the main thread without directly affecting the immediate responsiveness.

{% enddetails %}
## Concurrency and Threads in Apple Ecosystem

{% details Overview %}

- In iOS, threads can be used to achieve concurrency and multitasking. 
- However, Apple recommends using more advanced concurrency models, such as 
`Grand Central Dispatch (GCD)` and `Operation Queues`, because they are easier to
manage and have a smaller overhead.

{% enddetails %}
{% details Queues %}

- A queue is just a bunch of code blocks, lined or queued up, waiting for a 
thread to execute them.
- You don’t need to worry about threads in Swift, only queues.
– The iOS system takes care of providing/allocating threads to execute code off 
the queues

```swift
DispatchQueue.main.async {
    completionHandler(pokemonData)
}
```

{% enddetails %}
{% details Grand Central Dispatch %}

- Programmer's responsibility
    - Create a queue
    - Put blocks of code on a queue
- Grand Central Dispatch (GCD) is a powerful framework provided by Apple that manages concurrent 
execution of code, simplifying multithreading and asynchronous programming in Swift and Objective-C.
    - GCD abstracts the complexity of threads, managing thread pools efficiently and automatically, without needing manual thread management.
    - GCD uses Dispatch Queues to organize tasks:
        - Main Queue (DispatchQueue.main): Handles UI-related tasks and user interactions.
            - This is the queue where all blocks of code that affect the UI must be run on. 
        - Background Queues (DispatchQueue.global()): Perform time-consuming or intensive tasks asynchronously.
            - Used to queue up any long-lived, non UI tasks
            - Often runs simultaneously and in parallel with the main UI queue. 
        - Enables tasks to run concurrently without blocking the main thread, keeping the UI responsive.
            - Through the A-series multiple cores
        - Provides easy-to-use synchronization mechanisms (like Dispatch Groups, Semaphores, and Barriers) to coordinate execution between multiple tasks and prevent data races.
        - Prioritizes tasks based on importance and urgency, optimizing performance and resource usage:
            - .userInteractive: highest priority
            - .userInitiated: second only to userInteractive
            - .utility: lower priority, for tasks that do not prevent user from continuing to use your app. 
            - .background: lowest priority, for work that needs to be performed while the app is running (e.g.
            maintenance tasks or cleanup tasks)

{% enddetails %}
{% details Example of GCD in Playground %}


```swift
import PlaygroundSupport
import UIKit

// Necessary to keep the playground running
PlaygroundPage.current.needsIndefiniteExecution = true

// Simulate a heavy task on a background queue
DispatchQueue.global(qos: .background).async {
    print("🚀 Heavy task started on background thread.")

    // Simulate heavy computation or network task
    for i in 1...5 {
        print("Processing item \(i)")
        sleep(1)  // Simulate a time-consuming task
    }

    print("✅ Heavy task completed!")

    // Update UI or execute main-thread task after background work
    DispatchQueue.main.async {
        print("🎉 Updating UI on main thread.")
        // e.g., update labels, images, etc.
    }
}

print("⏳ Main thread continues executing without waiting...")
```

{% include figure.liquid path="assets/img/courses/csc496/07-concurrency/gcd1.png" width="50%" zoomable=true %}

{% enddetails %}
{% details Drawback of GCD: callback hell %}

- Callback Hell, also called the `Pyramid of Doom`, occurs when asynchronous operations are nested deeply within callbacks, making code increasingly unreadable, difficult to debug, and maintain.
- Even though GCD is powerful, heavily nested calls can become problematic.

{% enddetails %}
{% details Example %}


```Swift
import PlaygroundSupport
PlaygroundPage.current.needsIndefiniteExecution = true

func fetchUser(completion: @escaping (String) -> Void) {
    DispatchQueue.global().asyncAfter(deadline: .now() + 1) {
        completion("User123")
    }
}

func fetchOrders(for user: String, completion: @escaping ([String]) -> Void) {
    DispatchQueue.global().asyncAfter(deadline: .now() + 1) {
        completion(["Order1", "Order2", "Order3"])
    }
}

func fetchOrderDetails(order: String, completion: @escaping (String) -> Void) {
    DispatchQueue.global().asyncAfter(deadline: .now() + 1) {
        completion("Details for \(order)")
    }
}

// Callback Hell Example
fetchUser { user in
    print("User fetched: \(user)")

    fetchOrders(for: user) { orders in
        print("Orders fetched: \(orders)")

        fetchOrderDetails(order: orders[0]) { details in
            print("First order details fetched: \(details)")

            fetchOrderDetails(order: orders[1]) { details in
                print("Second order details fetched: \(details)")

                fetchOrderDetails(order: orders[2]) { details in
                    print("Third order details fetched: \(details)")

                    DispatchQueue.main.async {
                        print("✅ Finally done updating UI.")
                    }
                }
            }
        }
    }
}

```

- Why was this necessary?
    - When tasks must be performed one after another asynchronously, each subsequent 
    task depends on the previous task's result.
        - Fetch User
        - Then Fetch Orders (requires User)
        - Then Fetch Order Details (requires Orders)
        - Then Update UI after all previous tasks
    - To maintain this sequence clearly, you must place each next call inside the completion 
    handler of the previous one:

{% enddetails %}
{% details Solution for callback hell: async/await %}

- async/await introduced in Swift 5.5
- In Swift, the async/await feature enables you to write cleaner asynchronous 
code. It's like saying, "Hey, you go do this task, but let me know when you're
finished so I can use the result."

```Swift
import PlaygroundSupport
PlaygroundPage.current.needsIndefiniteExecution = true

// Async functions using Swift concurrency
func fetchUser() async -> String {
    try? await Task.sleep(nanoseconds: 1_000_000_000)
    return "User123"
}

func fetchOrders(for user: String) async -> [String] {
    try? await Task.sleep(nanoseconds: 1_000_000_000)
    return ["Order1", "Order2", "Order3"]
}

func fetchOrderDetails(order: String) async -> String {
    try? await Task.sleep(nanoseconds: 1_000_000_000)
    return "Details for \(order)"
}

Task {
    let user = await fetchUser()
    print("User fetched: \(user)")

    let orders = await fetchOrders(for: user)
    print("Orders fetched: \(orders)")

    for order in orders {
        let details = await fetchOrderDetails(order: order)
        print("Order details fetched: \(details)")
    }

    DispatchQueue.main.async {
        print("✅ Finally done updating UI.")
    }
}

```

{% enddetails %}
