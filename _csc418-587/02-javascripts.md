---
layout: lecture
pretty_table: true
order: 3
title: Javascript and HTTP
mermaid:
  enabled: true
  zoomable: true
code_diff: true
typograms: true


# Optionally, you can add a table of contents to your post.
# NOTES:
#   - make sure that TOC names match the actual section names
#     for hyperlinks within the post to work correctly.
#   - we may want to automate TOC generation in the future using
#     jekyll-toc plugin (https://github.com/toshimaru/jekyll-toc).
toc:
  - name: Overview
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: HTTP Protocol
  - name: Javascript
  - name: NodeJS
  
# Below is an example of injecting additional post-specific styles.
# If you use this post as a template, delete this _styles block.
_styles: >
  .fake-img {
    background: #bbb;
    border: 1px solid rgba(0, 0, 0, 0.1);
    box-shadow: 0 0px 4px rgba(0, 0, 0, 0.1);
    margin-bottom: 12px;
  }
  .fake-img p {
    font-family: monospace;
    color: white;
    text-align: left;
    margin: 12px 0;
    text-align: center;
    font-size: 16px;
  }
---

{% details Learning Objectives %}

- Students will be able to explain the meanings of the content of an HTML file.
- Students will be able to explain the meaning of a communication/networking 
protocol known as HTTP.
- Students will be able to develop a node.js module using Visual Studio Code 
and execute the web application using the command "node" or "npm".
- Students will be able to develop a web server. using the node.js module http 
that is based on the HTTP protocol.

{% enddetails %}

{% details What's Due %}

- Students will need to complete this module before moving onto the next module

{% enddetails %}


## Overview

In this module, we will discuss about the **background theory** behind the interaction between
a web server and a web client. We will begin with the terminologies regarding the concepts
about the interaction or communication between the web client and the web server. The
knowledge will pave the road toward the required programming tasks when we develop a web
server.

We will cover the fundamental JavaScript Programming Language features, and Node.JS with
the HTTP package. Our goal is to develop a Web Server to be running as the back-end of an
application.


## HTTP Protocol

### Overview

Web accessing is known as a service and HTTP is a protocol. A protocol is a set of rules 
both the client and the server comply to achieve successful communications. An HTTP protocol 
is used by a Web Client to communicate with a Web Server.


<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/javascripts/http.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

{% details Protocols vs. Applications %}

Application layer protocols and applications are two different concepts. For example,
file transfer is an application that provides the capability of copying files from one
machine to another. FTP is a protocol (RFC 959). When web accessing is an application,
the term HTTP represents the protocol used by the client and the server to achieve web
page accessing & displaying. In the first part of this semester, we will explore some
applications and the protocols associated with them.
{% enddetails %}

{% details Web accessing %}

The Internet started out as a research network mainly used by researchers, university
students, and national labs to log in remotely, to transfer files, and to receive news, e-
mail messages. Around 1992, WWW began to draw the attention of almost every
discipline. It is simply based on one simple protocol, called Hyper-Text Transfer Protocol
or HTTP as illustrated in Figure 1. 

HTTP is essentially a protocol used for representing message formats between a Web 
Browser and a Web Server to communicate with each other. The client may send a request 
of a web page to the server, and the server retrieves the web page and sends the web 
page back to the client. The Web Browser locating at the client machine displays the 
web page. 

It is very simple. But it provides the platform for the future web applications. The 
client and the server usually are executed on different hosts. When a Uniform Resource 
Locator (URL) is passed onto the Web Browser, the Web Browser will construct an HTTP 
request, sends the request message to the server via the Internet. The server serves 
one request at a time without checking the current state of the client.

{% enddetails %}

## Javascript 

### Constants, Variables, Controls, and Functions

{% details LinkedIn Learning activity %}

You should complete the hands-on introduction to Javascript on Linked Learning (accessible via WCUPA)

- [Direct course link](https://www.linkedin.com/learning/hands-on-introduction-javascript/hands-on-javascript?u=56745321)
- You can also login to LinkedIn Learning via [WCUPA's LinkedIn Learning](https://www.wcupa.edu/LinkedInLearning/) and search for the course title: "Hands-On Introduction: JavaScript".

{% enddetails %}

### Asynchronous Programming in JavaScript

{% details Event Loop %}

- JavaScript engine is single-threaded. 
- Handling multiple concurrent requests using blocking mechanisms (`wait until this is done`) is inefficient. 
- This is possible by a mechanism called `event loop`, which enable non-blocking operations in JavaScript. 
- Examples of typically blocking tasks that are to be executed as non-blocking: 
    - HTTP requests, 
    - I/O operations, including reading files or waiting for user input
- Code execution procedure via event loop: 
    - Execution environment: client-side (e.g., web browser) or server side (e.g., Node.js)
    - Functions/instructions are executed sequentially on a `call stack` - LIFO (Last In/First Out)
    - If a blocking operation is encountered
        - Need to be executed asynchronously by being sent to the Web APIs (browser) or `libuv` library (Node.js)
        - Once these asynchronous operations complete, they push their callbacks onto either the `callback` queue (macrotasks) or `job` queue (microtasks), depending on their priority. 
    - Event loop continuously checks
        - Execute everything in the call stack first, then
        - Drain microtasks from the job queue and macrotasks from the callback queue. 

{% enddetails %}


{% details Queues versus Call Stack %}
- Call Stack
    - Is conceptually similar to the concept of the stack in standard programming (recall Computer Systems)
    - Is a data structure that keeps track of function calls in the JavaScript code. 
    - When a function is invoked, it is pushed on to the top of the stack. 
        - The stack follows a LIFO (last-in, first out) mechanism. 
    - When the function completes, it is popped from the top of the stack. 
    - If the function calls another function, the new function is pushed on to the top of the stack. 
    - Asynchronous functions (those that would cause blocking) are pushed on to the stack but then popped off immediately, and registered as a callback in the Callback queue. 
- Callback Queue and Job Queue
    - Callback Queue (Macrotask): handles traditional asynchronous tasks like 
        - Callbacks for timers (`setTimeout`, `setInterval`)
        - User interaction events (clicks, key presses)
        - I/O and network events
        - Operates on a FIFO basis, handling one item per tick of the event loop.
    - Job Queue (Microtask): hands callbacks for `Promises` (`.then()`, `.catch()`, `.finally()`, and `queueMicrotask()`) calls. 
        - The event loops will handle the entire Microtask queue until it is empty before the Macrotask queue is processed. 

{% enddetails %}


{% details More Javascript: Callbacks %}

Read the following article: [Async JavaScript: From Callbacks, to Promises, to Async/Await](https://ui.dev/async-javascript-from-callbacks-to-promises-to-async-await)

{% enddetails %}


{% details Recording: Instructions on Hands-on and Exercises %}

[Recording Link](https://wcupa.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=1663a997-0444-4432-894a-b3b401830080)

{% enddetails %}


{% details Hands-on: test.js %}

- Create a directory called `1-javascript` inside the `/apps` directory.
- Create a Javascript file named `test.js` inside the `1-javascript` directory with the following content:

```js
a = 10;
b = 20;
console.log(a + b);
```

- Open a terminal, change into `1-javascript` and run:

```bash
cd 1-javascript
node test.js
```

- You should expect number `30` to be printed to the screen. 
- Modify the file and try out the following Javascript operators to understand their usage"
    - Arithmetic operations: `+`, `-`, `++`, `--`, `*`, `/`, `%`
    - Assignment operators: `+=`, `-=`, `*=`, `/=`, `%=` 
    - Comparison operators and Logic Operators: `==`, `===`, `!=`, `&&`, `||`


{% enddetails %}


{% details Hands-on: Event Loop %}

- Create a Javascript file named `event_loop.js` inside the `1-javascript` directory with the following content:

```js
console.log('Start');

setTimeout(() => {
  console.log('Timeout callback'); // callback queue - macrotasks
}, 0);

Promise.resolve().then(() => {
  console.log('Promise callback'); // job queue - microtasks
});

console.log('End');
```


- Open a terminal, change into `1-javascript` and run:

```bash
cd 1-javascript
node event_loop.js
```

- Observe the order of the output. 

{% enddetails %}

## NodeJS: Unit 1

{% details Overview %}

    We just learned about JavaScript and use JavaScript as a server-side technology. Now, 
    we can begin to look into the node.js platform. We will begin our journey about 
    node.js using the HTTP library module in the following lessons from Unit 1 of the 
    textbook.

    - Lesson 3 – Creating a Node.js module
    - Lesson 4 – Building a simple web server in Node.js
    - Lesson 5 – Handling incoming data
    - Lesson 6 – Writing better routes and serving external files
    - Lesson 7 – Capstone: Creating your first web application

    The listings mentioned in the lessons will be from the textbook. 

{% enddetails %}

{% details Lesson 3 – Create a Node.js Module %}

- Lab Exercise 1: Create a Node.js Module and access the variable from another 
JavaScript file
    - Create a JavaScript file using listing 3.1 to display the following messages in 
    the array messages.
    - The function `require` is a Node.js global object used to locally introduce 
    methods and objects from other modules. If the module is a user-defined module, 
    e.g., ./messages, you don’t have to prepare for it; you may use `npm install` 
    followed by `npm run start`.
    - If it is a system module, e.g., `express`, to be included in this application 
    with main.js statement `require("express")` in main.js, you will need to enter 
    the command `npm install express` before you can enter `node main.js`, 
    `npm run start`, or `npm start` to bring up the web server main.js. This is true for 
    all server programs hereinafter. 
    - For example, very soon, you will see a require statement to require `http` or 
    require `http-status-codes”. You will need to enter “npm install http http-status-codes` before you can enter `node main.js`. 
    - The folder `node_modules` will have a lot of contents. It can be regenerated. The 
    `package-lock.js` is also a re-generable file.
    - You can execute the program printMessages.js using the following: `node printMessages.js`
- Lab Exercise 2: Create a Node.js Module and access the variable from another 
JavaScript file
    - Now, we will try another experiment using Listing 3.4 as `main.js`.
    - Open a command prompt window and enter the followings:
    
    ```js
    npm init --yes
    npm install --save
    npm install cities –-save
    ```

    - Create another file `main.js` as in Listing 3.4
    - Enter the command `node main.js`.

- Lab Exercise #3: Use Listing 3.6 to develop a module and call the function from 
another JavaScript file.

{% enddetails %}

### Important notes

> Later, we will begin to rely on reading the textbook more and we only include the explanations of the code that requires attentions in the lecture notes. It is highly recommend that you read all lessons in `Unit_0`, `Unit_1`, `Unit_2`, `Unit_3`,  `Unit_4`, and the first two chapters in `Unit_6` by the end of this course. You may skip `Unit_5`.

{% details Lesson 4 - HTTP and Web Servers %}

- In this lesson, the use of the module HTTP is demonstrated. As we had explained 
previously, the term HTTP represents the protocol used by the client and 
the server to achieve web page accessing & displaying. 
- We need to install the two modules `http` and `http-status-code` before 
executing the web server.
- Create a new file main.js using Listing 4.1
- Enter the following commands:

```bash
npm init --yes
npm install http http-status-codes
node main.js
```

- Bring up a web browser and enter “http://127.0.0.1:3000/”

{% enddetails %}

{% details Lesson 5 - Handling Incoming Requests %}

In previous lab experiment, the web browser displays `Hello Universe!` after 
a URL `http://127.0.0.1:3000` is entered. If you try `http://127.0.0.1:3000/testing`, 
it still displays the same. The reason is because the server does nothing but 
displaying the string `Hello Universe`.

In this lesson, we will begin to learn how to complete some processing 
before `rendering` a web page. We use the term `render` to refer to the 
activities of formatting a web page into an HTTP reply message and sending 
it back to the browser.

- Lab Exercise 1: Display a string
    - Use the listing 5.1 to create a main.js.
    - Enter `npm install http http-status-codes`.
    - Enter the command `node main.js` and
    - Bring up a browser and enter `http://127.0.0.1:3000`.
- Lab Exercise 2: Displays different messages with respect to different routes, 
i.e., the `taps` behind the string `localhost:3000`.
    - Modify the previous main.js and call it main1.js using Listing 5-4.
    - Run it with `node main1.js`
    - Run the following command in the terminal to test the module as follows:
    
    ```js
    curl --data "username=Jon&password=secret" http://127.0.0.1:3000
    ```

    - Observe the outcome. 

{% enddetails %}

{% details Lesson 6 – Better Routes %}
    
In this lesson, we need to add some routes after `localhost:3000`. For example, we 
need to enter `localhost:3000/contact` or `localhost:3000/about`, etc. We need to 
modify the `main.js` and add some “route handling” code.

Use the following `views/index.html` file (Listing 6.1) in the views folder for 
all three labs.

- Lab Exercise 1: 
    - Create `main.js` from Listing 6.2.
    - Run `node main.js` in the terminal
    - Bring up a browser and enter `localhost:3000/about` or `localhost:3000/contact`
- Lab Exercise 2: 
    - Create `main.js` from a combination of Listing 6.2 andListing 6.3 (see 
    textbook instructions).
    - Run node main.js on the terminal
    - Bring up a browser and enter `localhost:3000/about` or `localhost:3000/contact`
- Lab Exercise 3: 
    - Create `main.js` from Listing 6.6 
    - Create `router.js` from Listing 6.5 
    - Make sure that your folder structure is similar to Figure 6.3
    - Run `node main.js` in the terminal
    - Bring up a browser and enter `localhost:3000/about` or `localhost:3000/contact`

{% enddetails %}

{% details Lesson 7 – Capstone: Create the first web server with HTTP and Node.js %}

Carrying out the following steps to create your first web application project:

- Step 1: Create a folder my_project. Change into this folder and 
run the following commands:

```bash
npm init --yes
npm install --save
```

- Step 2: Create files (currently empty) and folders to form the structure as in Listing 7.2
    - Creating `main.js` as Listing 7.3
    - Create `contentTypes.js` as Listing 7.4
    - Create `utils.js` as Listing 7.5
    - Create `router.js` as Listing 7.6
    - Add routes with the router module in main.js as listing 7.8

- Step 3: Run `node main.js` and navigate to http://127.0.0.1:3000 to see the 
application’s home page.

This lesson concludes our discussion about using the node.js http module to develop 
a web server. It is instructive to know that the activities for registering a route in 
a web server include the following:

- Whether the request is a GET or a POST request
- The URL’s path
- The name of the file to return
- An HTTP status code
- The type of the file being returned (as the content type)

{% enddetails %}