---
layout: lecture
pretty_table: true
order: 4
title: Modern Server-Side Development with Express.js
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
  - name: Setup Express
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: Node HTTP and Node Express
  - name: "Lesson 8: Setting an app with Express.js"
  - name: "Lesson 9: Routing in Express.js"
  - name: "Lesson 10: EJS (Embedded JS) and Layouts"
  
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

## Overview

After we discussed about using Node.js with the http module to develop a 
server, we introduce another Node module, `Express.js` that we will use 
to simplify the development activities. We will follow the textbook 
for the lab activities. We will cover the following lessons in our textbook.

Before we start, I recommend that you read through this article from Mozilla 
that provides another [introduction to Node and Express](https://developer.mozilla.org/en-US/docs/Learn/Server-side/Express_Nodejs/Introduction).

> Express.js is not a web server. It is a framework that runs on top of Node's HTTP server. 
> Under the hood, Express still calls *http.createServer()(...)*
{: .block-tip}

## Setup Express

Express is a downloadable module that can be installed from the command line once with:

```bash
npm install express --save
```

At this point, you should familiarize yourself with the source code from the book, which is [available freely at](https://github.com/JonathanWexler/get-programming-with-nodejs/tree/master). This can be done by:

```bash
cd /apps
apt install -y git
git clone https://github.com/JonathanWexler/get-programming-with-nodejs.git
```


## Node HTTP and Node Express

- Create a directory called `4-express` in `apps`.
- Create a file called `server-http.js` with the following contents:

```js
const http = require('http');

const server = http.createServer((req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
  res.end('Hello from Node HTTP\n');
});

server.listen(3000, () => {
  console.log('Node HTTP server listening on port 3000');
});
```

{% details HTTP %}
- The server is manually created (1, 3)
- The headers are manually written (4)
- The response is manually handled (5)
{% enddetails %}

- Create a file called `server-express.js` with the following contents:

```js
const express = require('express');
const app = express();

app.get('/', (req, res) => {
  res.send('Hello from Express\n');
});

app.listen(3000, () => {
  console.log('Express server listening on port 3000');
});
```

- Launch the two JavaScript files and use the curl commands on `127.0.0.1:3000` to observe the outputs. 

{% details Express %}

- Express uses Node’s HTTP server internally
- Headers and status codes are managed by Express. 
- Routing (GET /) is handled declaratively. 
    - The response helper (res.send) handles the boilerplate

{% enddetails %}

## Lesson 8: Setting an app with Express.js

- For this lesson, create the `main.js` using the content from Listing 8.1 in the book (`first_express_project_8_3` in `lesson_8` from the git repo)
- Check Table 8.2 for the information about `req.params`, `req.body`, `req.url`, and `req.query`.

{% details Expected outcome %}

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/express/lst8-2.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

{% enddetails %}

## Lesson 9: Routing in Express.js

This lesson provides a preliminary view on routing/MVC

{% details Reading %}

>- Read through Lesson 9 and examine the codes in the `finish` folder of `lesson_9` to observe how the routes are managed via Express.js
>- Run `node main.js` to view

{% enddetails %}

Another way to approach this is to start this lesson from the end, which is the [9-3 example](https://github.com/JonathanWexler/get-programming-with-nodejs/tree/master/unit_2/lesson_9/finish/express_routes_9_3) in GitHub. 

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/express/9-3.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

{% details main.js %}

```js
"use strict";

const port = 3000,
  express = require("express"),
  app = express(),
  homeController = require("./controllers/homeController");

app.use(
  express.urlencoded({
    extended: false
  })
);
app.use(express.json());

app.use((req, res, next) => {
  console.log(`request made to: ${req.url}`);
  next();
});

app.post("/", (req, res) => {
  console.log(req.body);
  console.log(req.query);
  res.send("POST Successful!");
});

app.get("/items/:vegetable", homeController.sendReqParam);

app.listen(port, () => {
  console.log(`Server running on port: ${port}`);
});
```

{% enddetails %}


- App bootstrapping (line 3-5)
    - `express()` creates the app object, which is basically a big request router + middleware pipeline.
    - `homeController` is a custome Node module we build and import. It contains a function to be passed to Express.

- Body-parsing middleware pipeline, as shown in the figure above, containing multiple stages
    - Line 8-12: Parses application/x-www-form-urlencoded bodies (classic HTML form posts).
        - With extended: false, it uses a simpler parser (fine for typical forms).
    - Line 13: Parses application/json bodies (common for APIs / fetch / axios).
    - **Important**: middleware order matters. By the time `app.post("/")` runs, req.body is already populated (if the request body matches the expected content-type).
    - Line 15-18: logging middleware 
        - This runs for every incoming request because it’s [app.use(...)](https://expressjs.com/en/guide/using-middleware.html) with no path restriction.
            - `req` = request (incoming data)
            - `res` = response (how the server replies)
            - `next()` = *I’m done, let the next middleware/route handler run*
        - Missing `next()` will cause the request to hangs.

- Line 20-24: `Route: POST /`
    - This route matches HTTP method = POST and path = / exactly.
        - `req.body`: Results of the body-parsing middleware. For example, sending JSON { "a": 1 } will activate the parser at line 13 and resulting in  `req.body.a === 1`
        - `req.query`: Comes from the URL query string. For example, `POST /?debug=true` resulting in `req.query.debug === "true"`
    - Query parsing does not require body-parser middleware; Express parses it from the URL.
        - `res.send(...)`: Ends the response immediately (sets headers, writes body, closes).

- Line 26: `Route: GET /items/:vegetable`
    - Match method GET with a path pattern: `/items/<something>`
    - Examples:
        - `/items/carrot`: `req.params.vegetable === "carrot"`
        - `/items/bokchoy`: `req.params.vegetable === "bokchoy"`
    - When `GET` is called, the function `sendRequestParam` in `homeController` is activated. 
  
- Line 28-30: Listening
    - This starts the HTTP server and hands all incoming requests into Express’s middleware and routing system.

{% details homeController.js %}

```js
"use strict";

exports.sendReqParam = (req, res) => {
  let veg = req.params.vegetable;
  res.send(`This is the page for ${veg}`);
};
```

{% enddetails %}

- Express treats `sendReqParam` as a route handler:
    - It receives the same (req, res) objects.
    - It reads req.params (filled by Express route matching).
    - It sends a response.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/express/mvc.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- MVC: Abbreviation of Model, View, Controller.  
- MVC: separation-of-concerns
    - Model: data + business rules (DB, validation, domain logic)
    - View: presentation (EJS, Pug, React SSR, templates, etc.)
    - Controller: translates HTTP requests into actions, returns responses (or chooses a view)
- From `9-3`:
  - `controllers/homeController.js` is the Controller layer:
      - It handles request input (req.params)
      = It decides what to send back (res.send(...))
  - There is currently no View, things are being returned to users via `res.send(...)`.
  - There is current no Model

## Lesson 10: EJS (Embedded JS) and Layouts

{% details Review %}

First, you are to review the web page at [the official website for EJS](https://ejs.co/#docs). It is strongly recommended that you pause and go through the official website to learn more about EJS. 

If you are interested in learning more about EJS, here is a good tutorial entitled [How To Use EJS to Template Your Node Application](https://www.digitalocean.com/community/tutorials/how-to-use-ejs-to-template-your-node-application). 

You can follow this tutorial to develop a complete front-end of a web application with EJS. But it is not required. We will move on and begin to develop our view pages following our textbook in Lesson 10.

{% enddetails %}

> Prior to running, need to run the following in terminal:
> ```bash
> npm install express-ejs-layout
> ```
{:.block-tip}

{% details Webpage structure: layout.js %}

Use a `layout.js` to specify the structure of a web page in your project. Store the layout.js and view files in the same folder, i.e., the views folder.

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Recipe App</title>
    <link rel="stylesheet" href="./css/custom.css">
    <style media="screen">
      body {
        margin: 0;
        padding: 0;
        height: 100%;
        color: black;
        text-align: center;
        font-family: 'open sans';
      }
      #nav {
        width: 100%;
        text-align: center;
        height: 60px;
        background-color: #7D498D;
      }
      #footer {
        width: 100%;
        text-align: center;
        height: 60px;
        background-color: #9C73A9;
        position: relative;
        bottom: 0;
      }
      #container {
        height: 100px;
      }
    </style>
  </head>
  <body>
    <% include partials/navigation %>
    <div id="container">
      <%- body %>
    </div>
    <div id="footer">FOOTER</div>
  </body>
</html>
```

{% enddetails %}

{% details Prepare view files and controllers %}

Third, you are to Prepare view files and controllers.

```js
// homeController.js
'use strict';
const express = require( 'express' ),
layouts = require( 'express-ejs-layouts' ),
app = express(),
homeController = require( './controllers/homeController' );
app.set( 'port', process.env.PORT || 3000 );
app.set( 'view engine', 'ejs' );
app.use( layouts );
app.use( homeController.logRequestPaths );
app.get( '/items/:vegetable', homeController.sendReqParam );
app.get( '/name/:myName', homeController.respondWithName );
app.listen( app.get( 'port' ), () => {
  console.log( `Server running on port: ${app.get('port')}` );
} );
```

```js
// view file: index.js
<h1> Hello, <%= name %> </h1>
//view file in the partials folder: navigation.js
<div id="nav">TOP NAVIGATION</div>
```

Here the EJS tag `<%= name %>` replaces the name by the value of the name into the template while completing the rendering operation.

{% enddetails %}

{% details Testing %}

- Test your code with the URL: http://127.0.0.1:3000/name/John
- Test your code with the URL: http://127.0.0.1:3000/veg/banana
- Notice that the format of the ‘include’ statement in a view file is: `<% include partials/navigation %>`

{% enddetails %}

