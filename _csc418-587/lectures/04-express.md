# Web Development with EJS (Embedded JS)

After we discussed about using Node.js with the http module to develop a 
server, we introduce another Node module, `Express.js` that we will use 
to simplify the development activities. We will follow the textbook 
for the lab activities. We will cover the following lessons in our textbook.

Before we start, I recommend that you read through this article from Mozilla 
that provides another [introduction to Node and Express](https://developer.mozilla.org/en-US/docs/Learn/Server-side/Express_Nodejs/Introduction).



## 1. Lesson 8: Setting an app with Express.js

???tip "Recording: Web Development with EJS"

- Enter `npm install express –-save`
- Enter the content for `main.js` from listing 8.1:

```js
  'use strict';
  const port = 3000,
    express = require('express'),
    app = express();
  app.get('/', (req, res) => {
    console.log(req.params);
    console.log(req.body);
    console.log(req.url);
    console.log(req.query);
    res.send('Hello, Universe!');
  }).listen(port, function () {
    console.log(`The Express.js server has started and is listening on port number:
    ${port}`);
  });
```

- Check Table 8.2 for the information about `req.params`, `req.body`, `req.url`, and `req.query`.

## 2. Lesson 9: Routing in Express.js

???tip "Recording: Web Development with EJS"

- Read through Lesson 9 and examine the codes in the `finish` folder of 
`lesson_9` to observe how the routes are managed via Express.js
- Run `node main.js` to view

## 3. Lesson 10: EJS (Embedded JS) and Layouts

???tip "Recording: Web Development with EJS"


???note "Review"
    First, you are to review the web page at [the official website for EJS](https://ejs.co/#docs). 
    It is strongly recommended that you pause and go through the official website to learn more 
    about EJS. 

    If you are interested in learning more about EJS, here is a good tutorial entitled [How To
    Use EJS to Template Your Node Application](First, you are to read the tutorial on [How to use EJS to Template your Node Application](https://www.digitalocean.com/community/tutorials/how-to-use-ejs-to-template-your-node-application). 
    You can follow this tutorial to develop a
    complete front-end of a web application with EJS. But it is not required. We will move
    on and begin to develop our view pages following our textbook in Lesson 10.

???note "Webpage structure: layout.js"
    Use a `layout.js` to specify the structure of a web page in your project. Store the layout.js
    and view files in the same folder, i.e., the views folder.

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

???note "Prepare view files and controllers"
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

    Here the EJS tag “<%= name %>” replaces the name by the value of the name into the
    template while completing the rendering operation.

???note "Testing"
    - Test your code with the URL: http://127.0.0.1:3000/name/John
    - Test your code with the URL: http://127.0.0.1:3000/veg/banana
    - Notice that the format of the ‘include’ statement in a view file is:
    `<% include partials/navigation %>`


