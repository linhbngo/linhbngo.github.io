---
layout: lecture
pretty_table: true
order: 3
title: "Lab: Routing"
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
  - name: "Step 1: The smallest possible server"
  - name: "Step 2: Inspect method and URL"
  - name: "Step 3: First real route: GET"
  - name: "Step 4: POST"
  - name: "Step 5: GET vs POST"
  - name: "Step 6: Read POST Data"
  - name: "Step 7: Routing Logic"
  
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


> In this lab, we are demonstrating the basic of GET and POST routes in Node.js. We are not *building a web app*. We are observing how HTTP requests get dispatched to code.
{: .block-tip}

## Step 1: The smallest possible server

- Create a directory called `3-lab-routes` inside `/apps`. 
- Inside `3-lab-routes`, create a file called `server.js` with the following contents

```js
const http = require('http');

const server = http.createServer((req, res) => {
  res.end('Hello\n');
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});
```

- `req` and `res` are the key components for routing
- You will observe `Hello` in the browser at `http://127.0.0.1:3000` and the line `Server running on port 3000` in the terminal. 
- Press `Ctrl-C` to terminate the server. 

## Step 2: Inspect method and URL

- Let update `server.js` as follows:

```js
const http = require('http');

const server = http.createServer((req, res) => {
  console.log(req.method, req.url);
  res.end('Check the console');
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});
```

- This time, any time you access/refresh the browser at `127.0.0.1:3000`, you will see the following on the terminal:

```bash
root@4285d71fdcf6:/apps/3-lab-routes# node server.js 
Server running on port 3000
GET /
GET /favicon.ico
GET /
GET /favicon.ico

```

- Mapping this with the code, we have:
    - `req.method`: `GET` - an HTTP request
    - `req.url`: `/` or `/favicon.ico` - tell the server what resource path the user is requesting. 
    - URL: Uniform Resource Locator

{% details Exercise %}

Open a new terminal and run the following command: `curl http://127.0.0.1:3000`, and observe that the line `GET /favicon.ico` no longer appears. Search for an explanation. 

{% enddetails %}


## Step 3: First real route: GET

- Let further update `server.js` as follows:

```js
const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    console.log(req.method, req.url);
    res.end('Home page\n');
  } 
  else if (req.method === 'GET' && req.url === '/users') {
    console.log(req.method, req.url);
    res.end('List users\n');
  } 
  else {
    res.statusCode = 404;
    console.log(req.method, req.url);
    res.end('Not Found\n');
  }
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});
```

- Use different `curl` statements to observe the outcomes:
    - Different paths
    - Different handlers
- It is important to note that these are multiple routes, not multiple pages.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/lab-routes/task-3.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


## Step 4: POST

- Let further update `server.js` as follows:

```js
const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    console.log(req.method, req.url);
    res.end('Home page\n');
  } 
  else if (req.method === 'GET' && req.url === '/users') {
    console.log(req.method, req.url);
    res.end('List users\n');
  } 
  else if (req.method === 'POST' && req.url === '/users') {
    console.log(req.method, req.url);
    res.end('Create a user\n');
  }
  else {
    res.statusCode = 404;
    console.log(req.method, req.url);
    res.end('Not Found\n');
  }
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});

```

- Observe the terminal with the following commands:

```bash
curl http://localhost:3000/users
curl -X POST http://localhost:3000/users
```

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/lab-routes/task-4.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


- With the same URL but different requests, we have different outcome. 

> Method is part of the route identity
> - A route is not a URL.
> - A route is method + URL.
{: .block-tip}

## Step 5: GET vs POST

- Another example that demonstrate GET versus POST is the login form. 
- Modify your `server.js` code as follows:


```js
const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    console.log(req.method, req.url);
    res.end('Home page\n');
  } 
  else if (req.method === 'GET' && req.url === '/login') {
    console.log(req.method, req.url);
    res.end('show login form\n');
  } 
  else if (req.method === 'POST' && req.url === '/login') {
    console.log(req.method, req.url);
    res.end('process login\n');
  }
  else {
    res.statusCode = 404;
    console.log(req.method, req.url);
    res.end('Not Found\n');
  }
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});

```

- `GET`: request information or form
- `POST`: submit information


## Step 6: Read POST Data

- Let generate some data for POST
- Modify your `server.js` code as follows:

```js
const http = require('http');

const server = http.createServer((req, res) => {
  if (req.method === 'GET' && req.url === '/') {
    console.log(req.method, req.url);
    res.end('Home page\n');
  } 
  else if (req.method === 'GET' && req.url === '/login') {
    console.log(req.method, req.url);
    res.end('show login form\n');
  } 
  else if (req.method === 'POST' && req.url === '/login') {
    let body = '';
    req.on('data', chunk => {
      body += chunk;
    });

    req.on('end', () => {
      console.log(req.method, req.url);
      console.log('POST body:', body);
      res.end(`Received: ${body}`);
    });
  }
  else {
    res.statusCode = 404;
    console.log(req.method, req.url);
    res.end('Not Found\n');
  }
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});

```

- Run the following and observe the outcomes

```bash
curl -X POST \
  -H "Content-Type: application/x-www-form-urlencoded" \
  -d "username=linh&password=secret" \
  http://localhost:3000/login
```

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/lab-routes/task-6.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- POST carries data in the body
- GET does not (at least not traditionally)

## Step 7: Routing Logic

- Let's refactor our server code

```js
const http = require('http');

function handleGet(req, res) {
  if (req.url === '/') {
    console.log(req.method, req.url);
    res.end('Home page\n');
  } else if (req.url === '/login') {
    console.log(req.method, req.url);
    res.end('show login form\n');
  }
}

function handlePost(req, res) {
  if (req.url === '/login') {
    let body = '';
    req.on('data', chunk => {
      body += chunk;
    });

    req.on('end', () => {
      console.log(req.method, req.url);
      console.log('POST body:', body);
      res.end(`Received: ${body}`);
    });
  }
}

const server = http.createServer((req, res) => {
  if (req.method === 'GET') handleGet(req, res);
  else if (req.method === 'POST') handlePost(req, res);
});

server.listen(3000, () => {
  console.log('Server running on port 3000');
});
```

- This is routing architecture.

