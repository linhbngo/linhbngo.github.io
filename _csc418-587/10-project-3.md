---
layout: lecture
pretty_table: true
order: 9
title: Endpoints and RESTful Web Service API
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
  - name: Javascript
  - name: HTTP Protocol
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


- CSC418 – Complete Part I and Part II
- CSC587 – Complete Part I, Part II, and Part III

Notice that, throughout the specification, I used the terms `server Endpoint and client
Endpoint` to refer to the two applications for the REST API applications: server and the client,
respectively.

This project is not quite a continuation of the previous project. You do not need to implement
the three tabs as in the Project 2. Instead, your application will server as the Endpoint to return
a list of user data in JSON format. The server only needs to be able to respond to the request
for a list of users using the URL http://localhost:3000/users?format=json/. Then, you need to
demonstrate the capability of READ operation from a client Endpoint. You do not need to worry
about Create, Update, and Delete operations.

For CSC418 students, you are given a stand-alone JavaScript code serving as the client Endpoint
for consuming the API function provided by the server Endpoint. You need to demonstrate that
your server Endpoint works by returning a list of user data in JSON format.

For CSC587 students, you will continue to implement a client Endpoint with a website similar to
that in Project#2 only using the port 4200 without the three tabs. Details about how to execute
the client Endpoint will be given later in Part III.

In Project#2, we used a database to store the user data and we accessed the database directly
via Mongoose Schema and a Model. In this project, you will still allow that in the server
Endpoint. In addition, you will add a RESTful API to access the database. You will change the
route options to allow the access of the user data via the namespace `/api/users`.

## 1. Change the code to use Mongoose Schem a and a Model to access the database

In the first part of the project, you will begin with accessing the MongoDB database with a
Mongoose Schema and a Model (mapping to a collection) if you haven’t used Mongoose in
Project 2.

Then, you need to change your project#2 to become an Endpoint of a RESTful API. You only
need to implement the route http://localhost:3000/users with the Read operration in CRUD.
You don’t need to implement other operations.

For CSC418 students, you need to implement reading user information from your testing
database. You do not need to implement more functions, e.g., POST, UPDATE, DELETE. You only
need to be able to ‘GET’ user information. But you do need to add some user data into your
database using your database tool or change the seed.js to do that. You may use part I of your
Project#2 to complete that. That is, you may use Robo3T or MongoDB Compass to add user
data into your database.

For CSC587 studens, you need to implement the REST API client Endpoint without accessing
thee MongoDB database directly.

In the sample screenshots below, not all the CRUD operations are shown with navigation tabs.
For example, the Edit and the Delete are shown for each row. But the three tabs may not need
to work. You should be able to enter http://localhost:3000/users to display the Users Table.
You may show that the above screen can be displayed with the URL
http://localhost:3000/users. Then you need to move on to use a client to consume the API. For
the client Endpoint, you only need to show that your client application can consume the API
users in JSON format. You do not need to implement the Create, Update, or Delete in the client
Endpoint application.


## 3. Access MongoDB Database via the API from an API Client – a standalone program

You are going to use a simplified JavaScript code to consume the API. Once the server Endpoint
is started successfully, you can access the database with the following JavaScript code using the
command `node consume_API.js`. You may run into a warning that the Request.get is
deprecated. It simply means that the implementation of this function will not be updated
anymore. It should still work. You need to run the command first using a Command Prompt or
Terminal window:

```bash
npm install request
node consume_REST_API.js
```

Code template:

```js
//======== consume_REST_API.js =====
var Request = require("request");
Request.get("http://localhost:3000/api/users?format=json", (error, response, body) => {
if(error) {
return console.dir(error);
}
console.dir(JSON.parse(body));
console.log(`result = ${body}`);
});
//======= End of Code =========
```

Alternatively, you may use the node-fetch module instead. You need to run the following:

```bash
npm install node-fetch
node consume-API-new.js
```

The sample code consumeAPI-new.js is shown below:


```js
import fetch = 'node-fetch'; // It is an ESM module
// convert to CommonJS module
const fetch = (...args) => import('node-fetch').then(({ default: fetch }) => fetch(...args));
const consumeAPI = async function () {
    const response = await fetch('http://localhost:3000/users');
    const data = await response.json();
    console.log(data);
};
try {
    consumeAPI();
} catch (error) {
    console.log(error);
}
```

The only issue for using node-fetch is that the module is an ESM Module where the `require`
function is not supported. Instead, it supports the use of `import`. We need to convert the
import statement to the CommonJS format. The sample code should work. If you run into an
error message `node-fetch module is not found`, you need to run the `npm install node-fetch`
command first.

You must issue the command after (1) starting the database server, (2) starting the server
Endpoint using port 3000.

CSC418 students stop here. Take the necessary screeshots and move on to prepare the code
and the Word document for the submission. Make sure your project name won’t change
BEFORE being compressed, and AFTER being uncompressed.
CSC587 students continue to Part III.

## 3. Access MongoDB Database via the API from an API Client – an Application

You will now develop your code to consume the API from another application code, known as a
`client Endpoint code` here, via port 4200. This part could be confusing. We are about to
develop a Web Application instead of a JavaScript program, like consume_REST_API.js, to send
a request to the Web Service server. Now you may recall the picture we used to explain about
the concept of a web service. The amazon.com server is a Web Service Client that is going to
send a request to the web service cerver that is listening on port 3000. The difference between
a Web Service client and the program consume_REST_API.js is that the Web Service client is
also a (web) server listening to port 4200. We will be able to request for the user data to be
displayed on a browser if we enter http://localhost:4200/api/users`.

Once developed, your client code CANNOT access the database directly. But it will display the
user list via the route namespace `/api/users`. It will display the user list in JSON format.
You need to show:

- (1) You cannot use http://localhost:4200/users to access the database and displays the user
list.
- (2) You need to enter http://localhost:4200/api/users to display the user list.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_3/project_3_1.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


You need to submit your source code and screen shots to demonstrate the result. The check
points include:

- (1) Starting the database – must be developed with the Mongoose Schema and Model.
- (2) Starting the server Endpoint – must show the list of users in JSON format.
- (3) Starting the simple Client – Enter the command `node consume_REST_API.js` or `nodeconsumeAPI-new.js`.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_3/project_3_2.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- (4) Starting the application client 
    – (1) show the result of entering localhost:4200/users, and
    - (2) show the result of entering localhost:4200/api/users.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_3/project_3_3.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


In summary, the procedure to run the client Endpoint includes the following:

- (1) Start the database server using `mongod –dbpath=./db`
- (2) Start the server Endpoint using `node main.js`
- (3) The server must use the port 3000.
- (4) Enter `node consume_API.js` or `node consumeAPI-new.js`
- (5) Start your client Endpoint using `node main.js` from the client App folder where the
code main.js is stored.
- (6) Bring up a browser window and enter `localhost:4200/users`. It should show an error
message.
- (7) Bring up a browser window and enter `localhost:4200/api/users?format=json`. It should
show a list of users in JSON format.

You will need to start three servers: 

- the database server(port 27017) - this is not necessary for the Docker-based setup, 
- server Endpoint (port 3000), and 
- the client Endpoint (port 4200).

Submission rules are similar to that for Project #2. You need to submit two files: 

- one Word document and 
- one compressed file. 

The compressed file will include the server and the client Endpoints Apps in two separate folders. Please check 

- (1) if you remove node_modules, and 
- (2) if your app changes the name after you uncompress your compress folder. 

You need to submit two apps in one compressed folder. You are free to call the server and the client Apps 
inside the compressed folder.

## 4. Grading Rubric:

1. 30% MVC architecture - must separate model, view, and controller. You cannot merge
model/view/controller in any way. If you use one folder to keep any two in MVC together, it is a
violation of this rule. If you use one file to combine any two or more of the MVC parts, it is
worse.
2. 30% Soundness - Your project must be executable and provide required functions. When
implementing the database, you must use the model/schema/mongoose operations to
complete the functions.
In the client of the API or the endpoint that consumes the API, you are not allowed to add
database accessing code.
If a browser is started and the URL is `http://localhost:4200/users`, the browser should return
`Cannot Get /`. If your code returns a list of users, it is a violation of the specification.
If you access http://localhost:4200/api/users?format=json after you started the (server)
Endpoint, you should see a list of users.
These scenarios will be verified for grading.
3. 30% Front-End Implementation - You must use JavaScript with EJS to implement the front-
end. You are not allowed to use HTML/CSS with jQuery, PHP, etc., to implement the project. If
we use a browser to access http://localhost:3000/, we should see the three tabs. All three tabs
do not need to be working. However, if you access http://localhost:4200/users, you should
receive an error message.
4. 10% Submission Rules and documentation - Two files are required: a Word document with
screenshots to demonstrate that your code works; and a .zip file that contains the code. Please
do not use special compressing format such that special software is needed. If so, you will need
to describe the procedure to unzip your file in the Word document. The Word document must
include the instructions to execute your code, if needed. The Word document must not be
compressed with the code in the second file. The second file must not include nide_modules.
The naming convention for the folder containing the code must follow the naming convention
BEFORE or AFTER the compressed file is unzipped.