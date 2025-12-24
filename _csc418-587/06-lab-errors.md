---
layout: lecture
pretty_table: true
order: 3
title: "Lab: Error Handling"
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
  - name: "Step 1: Custom launch"
  - name: "Step 2: Error handling in Express"
  - name: "Step 3: Capstone Lab"
  
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


> - In this lab, we customize the launch NodeJS app via `package.json` and develop error handling code in Express controller.
> - You can begin the lab via the `start` directory of [Lesson 11 source code](https://github.com/ngo-classes/get-programming-with-nodejs/tree/master/unit_2/lesson_11)
> - You can cross check the final result in the `finish` directory. 
{: .block-tip}

## Step 1: Custom launch

- Edit the `package.json` file and modify the `script` section as follows:

```json
"scripts": {
  "test": "echo \"Error: no test specified\" && exit 1",
  "start": "node main.js"                                     1
},
```

- With this customization, you can run the commands such as `node test` and `node start` to launch your server app. 
- Run `node test` to confirm that no test is specified at the moment. 

## Step 2: Error handling in Express

- By default, Express.js handles any errors at the end of processing a request.

{% details Error handling approaches with Express %}

1. Logging to console (`console.log`) whenever an error occurs. 
2. (Recommended) Creating a new controller and install the `http-status-codes` package 

{% enddetails %}

{% details Setup error controller %}

- Install `http-status-codes`

```bash
npm install http-status-codes --save
```

- Create `errorController.js` in the `controllers` folder with the following contents (Listing 11.2 from the book)

```js
"use strict";

const httpStatus = require("http-status-codes");

exports.logErrors = (error, req, res, next) => {
  console.error(error.stack);
  next(error);
};

exports.respondNoResourceFound = (req, res) => {
  let errorCode = httpStatus.NOT_FOUND;
  res.status(errorCode);
  res.send(`${errorCode} | The page does not exist!`);
};

exports.respondInternalError = (error, req, res, next) => {
  let errorCode = httpStatus.INTERNAL_SERVER_ERROR;
  console.log(`ERROR occurred: ${error.stack}`);
  res.status(errorCode);
  res.send(`${errorCode} | Sorry, our application is experiencing a problem!`);
};
```

{% enddetails %}

- `respondNoResourceFound`: missing resources
- `respondInternalError`: resource processing caused a server-side error

{% details Exercise %}

- Look at the `main.js` in Lesson 11 and compare that with `main.js` in Lesson 10. 
- Examine the additional middleware layer added to handle error

{% enddetails %}

{% details Exercise %}

- Play with the static HTML file in the public directory inside `finish` and see the responses. 

{% enddetails %}

## Step 3: Capstone Lab

- Follow the instructions in Lesson 12: Capstone to wrap up Unit 2. 


