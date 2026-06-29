---
layout: lecture
pretty_table: true
order: 2
title: Introduction
mermaid:
  enabled: true
  zoomable: true
code_diff: true
map: true
chart:
  chartjs: true
  echarts: true
  vega_lite: true
tikzjax: true
typograms: true


# Optionally, you can add a table of contents to your post.
# NOTES:
#   - make sure that TOC names match the actual section names
#     for hyperlinks within the post to work correctly.
#   - we may want to automate TOC generation in the future using
#     jekyll-toc plugin (https://github.com/toshimaru/jekyll-toc).
toc:
  - name: 1. Course Overview
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: 2. Setup Computing Environment
  - name: 3. Setup Testing Environment
  - name: 4. Introduction to HTML
  - name: 5. Introduction to CSS
  - name: 6. Quiz Information
  
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
- Students will be able to describe the definitions of Tags, Attributes, 
Elements, and Entities.
- Students will be able to describe the meanings of the content of a CSS style 
and the three ways to specify CSS styles.
- Students will download and install Docker Desktop.
- Students will be able to launch two containers with web development components 
such as Node.js, Visual Studio Code Server, and MongoDB. 

{% enddetails %}

{% details What's Due %}

- Students will need to complete the installation of Docker Desktop and be able to 
test Node.js and Visual Studio Code Server before moving on to the next module.
- Students will need to learn HTML and CSS before moving on to the next module.

{% enddetails %}


## 1. Course Overview

In this course, we will use a hands-on approach for learning Node.js. When we use the 
term Node.js, we mean to use JavaScript for the server-side development of web applications. 
Although we use the term Node.js, we refer to the architecture that includes MongoDB, 
Express.JS (or Express) and Node.js.

We will begin with the concepts of HTML/CSS, and then the introduction to JavaScript programming, 
followed by HTTP server development, Express server development. Also, we will use EJS (Embedded 
JavaScript) as the View Engine, also known as the Template View Engine for the front-end of a 
web application and the Bootstrap for CSS styles.

Then we will focus on MongoDB for the purpose of creating NoSQL (Not Only SQL) databases and 
the accessing of collections (i.e., tables in a relational database).

Finally, we will introduce the concept of RESTful Web Service API and the development of an 
End Point and a web client to consume the web services. In the remaining part of this document, 
we will also describe detailed learning activities for learning the web development skills.

---

> You need to purchase a copy of the e-book entitled **Get Programming with Node.js**, Manning, 2019 asap by the second day of the class. If you don’t, you will get lost and will not understand where we are and what we are talking about. You may download the Source Code for the textbook here. Please try to use 7-Zip to unzip the compressed file. 
{: .block-tip}

> As described at the beginning of Lesson 0 of the book, **Setting Up Node.js and the JavaScript Engine**, 
the goal of this book is to teach us how to build web applications on a platform called Node.js 
using the JavaScript language. Prior to learning node.js, it is strongly recommended that you 
learn some groundwork including HTML and CSS briefly followed by JavaScript. In this lesson, 
we will complete the groundwork. Also, we will learn how to set up the development environment 
so that we can begin with hands-on coding with node.js and JavaScript.
{: .block-tip}


---

## 2. Setup Computing Environment

{% details Overview %}

When we use the term Server-Side Web Development, we are referring to the use of the 
Embeded JavaScript (EJS) at the front-end client-side scripting with HTML/CSS, and the 
use of JavaScript at the backend with Node.js, Express.js, and MongoDB. 

Since there are too many subjects to be covered in one semester, we briefly cover the front-end 
development using the sequence HTML, CSS, JavaScript, and EJS to learn how to develop the User 
Interface as the front end; and we will not cover the front-end UI technology such as Angular, 
React.js, or Vue.js. With HTML, CSS, and EJS, we will be able to focus on back-end server-side 
technologies. 

During this course, we will begin with introduction to HTML and CSS briefly so 
that we will have enough knowledge to learn EJS for the front end, and JavaScript & Node.js 
for the backend later.

{% enddetails %}

{% details Manual Deployment %}

The first three lessons of the textbook provide instructions to set and install Node.js 
on your local device directly. 

- Lesson 0: Setting up Node.js and JavaScript engine
- Lesson 1: Configuring your environment:  installing node.js
- Lesson 2: Getting Started with Node.js: running a node.js application

You can read and follow these instructions on your own if you choose to do so. 

{% enddetails %}

### Container Deployment (recommended)

For this class, we will use a premade containerized environment for node.js development, which consists of two 
containers:

- Master: Node.js, VS Code Server, Python
- Worker: MongoDB
- AI Agent (optional): Ollama
    
This is designed such that you will be come familiar with working in a 
container-based environment and to the idea that the individual back-end 
components of modern web applications are likely to be hosted on individual servers. 


**Docker and Docker Desktop**

> You can setup Docker and familiarize youself with the tool via 
> the [following instructions](https://www.cs.wcupa.edu/LNGO/courses/workshops/intro-docker/).

{% details Deploy CSC418 environment on Mac %}

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=ad6f193a-561f-4226-adc4-b244016b5b9a&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="docker-mac" ></iframe>

{% enddetails %}

{% details Deploy CSC418 environment on Windows %}

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=104f5663-0146-462e-9304-b2440178d08f&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="install_docker_desktop" ></iframe>

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=ba06651c-cb9e-4ac9-ac99-b2440178dadb&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="docker_windows" ></iframe>

{% enddetails %}

{% details More about CSC418 environment %}

- [csc418env GitHub](https://github.com/class-master/csc418env/tree/main)
- [csc418data GitHub](https://github.com/class-master/csc418data)

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=e0f48d22-289a-49a9-81b9-b244016eadb6&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="docker-explanation" ></iframe>

{% enddetails %}


## 3. Setup Testing Environment

Before we dive into the world of server-side programming, we will need to set up a 
testing environment for testing HTML/CSS. (For learning JavaScript, we will use 
Node.js environment)

- On VSCode Server, go to `File`/`Open Folder` and type in `/apps/`, then press Enter.
- Use the `Create Folder` icon to create a new folder called `0-server`.
- Inside `0-server`, create another folder named `public`. 

### Prepare the HTML file

Inside the `public` folder, create a file named `test.html` with the following contents:

```html
<html>
    <head>
        <title>Test HTML</title>
    </head>
    <body>
        This is a test
    </body>
</html>
```

### Develop a Web Server

Let’s develop one simple web server. Although it is a simple one, 
we can use it for display some web pages with text or even images. 

Inside the `0-server` directory, create a file named `server.js` 
with the following content:

```js
const express = require('express');

const app = express();
console.log("*** before calling static: public");
app.use(express.static('public'));
console.log("*** before listen ***");
app.listen(3000, function(){
    console.log('App started on port 3000');
});
```

### Run and test

- Open a Terminal inside the VSCode Server
- Change into the `0-server` folder. 
- Run the following commands:

```bash
npm install express
node server.js
```

- Open up a new browser and visit `127.0.0.1:3000/test.html`. 
    - Confirm the the HTML content is as expected. 
- We have just developed a web server development environment. Of course, this is just a 
toy server and a toy HTML file as a web client.


{% details Demo: Testing Environment %}

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=8ec6ea27-0c04-46ee-8ac7-b24700fe3a84&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="html-test-environment" ></iframe>

{% enddetails %}


## 4. Introduction to HTML 
    
### What is HTML used for?

In general, we know that two programs running on two different machines can 
communicate with each other similarly to two people talking to each other. 
Hence, we sometimes refer to the case as two programs “talking” to each other. 
In the case of the communication between a web client and a web server, the server 
needs to “understand” what the client requests for, e.g., the names of the web 
pages and the locations to name just a few. There are two requirements to achieve 
this goal. First, a special set of rules are needed to regulate the formats of 
messages. The set of rules is known as Hypertext Transfer Protocol (HTTP). Second, 
a “web page development language” is required to develop a web page and a set of 
rules is needed for the client and the server to be able to understand each other. 
Hence, the language known as the Hypertext Text Markup Language (HTML) specifies 
the rules about how a web document is formatted. It is used for the development of 
web page documents as the sources of web pages. In the next section, we will explain the detailed rules about HTML. 

### What does an HTML document contain?

The acronym HTML stands for Hyper-Text Markup Language. A markup tag is a 
“pre-defined” web page construct that appears in angle brackets, e.g., 
`<p>` for “paragraph” or `<title>` for the title of the web page. 

A web page document may be developed to include many pairs of “Markup Tags”.  Each pair 
of markup tag normally starts with a Start Tag and ends with a matching End Tag. The start tag, 
the end tag, and the text in between, collectively are called an HTML Element. As an example, 
the component `<title>Essentials of Computing</title>` appearing in a web page can be used to 
tell a web browser to display the text “Essentials of Computing” as the title of the web 
page as the pair of markup tags, i.e., `<title>` and `</title>`, specifies. 

Many tags can be annotated with attributes to provide additional information about a tag. 
For example, the attribute `href` can be used to describe the web page address about the 
“anchor” represented as the tag `<a>`. Usually, an attribute is specified with the name of 
the attribute followed by the value of the attribute. For example, the attribute “href” 
in the following element `<a href=”http://www.wcupa.edu”>West Chester University</a>` makes the 
text “West Chester University” clickable when this web page is displayed via a browser. 
Clicking the link will bring up the main page of the West Chester University.

Since our goal is to learn basics about HTML, we will introduce just enough HTML tags for 
understand a sample HTML web page: 

- HTML: `<html>`
- Body: `<body>`
- Title: `<title>`
- Paragraph: `<p>`
- Break: `</br>`
- Horizontal Break: `<hr />` draws a horizontal line
- Heading Text: `<h1>`, `<h2>`, `<h3>`, `<h4>`, `<h5>`, and `<h6>`.
- Italicized Text: `<i>`
- Bold-faced Text: `<b>`
- Ordered List: `<ol>` for the list and `<li>` for each list item
- Unordered List: `<ul>` for the list and `<li>` for each list item
- Hyperlinks: `<a href=http://www/wcupa.edu”>West Chester University</a>` 
- Image: `<img src=”images/tulip.jpg” alt=”Tulip” title=”Tulip Flower” />`
    - `src`: the location of the image file
    - `alt`: text description of the image
    - `title`: additional information about the image
    - `width`: the width of the image 
    - `height`: the height of the image 
    - `align=”left”` or `”right”`: align the image to the left or to the right
    - `align=”top”`, `“middle”`, or `“bottom”`: align the image to top, middle, or bottom. 

A good online reference for HTML ans CSS can be found at the link http://www.htmldog.com. 
     

## 5. Introduction to CSS

### Introduction

We will review the definitions of several terms before we move on to discuss about 
advanced CSS properties. Once you learn the fundamentals of CSS, you can begin to 
study the remaining CSS properties progressively. You may begin from the HTML 
Tutorials for learning CSS starting from the [Beginner](https://htmldog.com/guides/css/) 
to the [Intermediate](https://htmldog.com/guides/css/intermediate/) level. 
     
### Why is it called the Cascading Style Sheet (CSS)?

There are three ways to specify the properties of an element in an HTML source file: in-line, 
internal, and external. The precedence rules allows a web browser to use the in-line specifications 
first, then the internal, followed by the external. Thus, CSS is called the “cascading style sheet.” 
    
### How can we specify properties?

We explain what these three ways are.

{% details inline %}

```html
<html>
    <head>
        <title>HTML abd CSS</title>
    </head>
    <body style="color:red">
        This is a test
    </body>
</html>
```

{% enddetails %}
    
{% details internal style %}
    
If you have many tags that share the same styles, you don’t want 
to use the `in-line` stylesheet method to specify styles; you need 
to add the attribute `style` in ten places with a web page. Instead, 
we can use internal stylesheet.
    

```html
<html>
    <head>
        <title>HTML abd CSS</title>
        <style>
        P {
            Color:Blue
        }
        </style>
    </head>
    <body style="color:red">
        This is a test
        <p> This is a paragraph </p>
    </body>
</html>
```

{% enddetails %}

{% details external style %}

If you have many web pages using the same stylesheets, you don’t want to use 
any of the above methods. Instead, you may use “external stylesheets.” That is 
to include all styles in one external file. An example is given below with the `<link>` tag.

```html
<html>
    <head>
        <title>External Stylesheets</title>
        <style>
            <link rel="stylesheet" href="style.css">
        </style>
    </head>
    <body>
        ...
    </body>
</html>
```

{% enddetails %}


### A brief overview on selectors

{% details Type selector %}

- Select elements by their tag name (e.g., `p` or `h1`, etc.)
- Apply to **all** elements with the same tag on the page. 
- Use sparingly

```html
p {
  color: blue;
}

h1 {
  font-size: 2em;
}
```

{% enddetails %}

{% details Descendant selector %}

- Select elements that appear *anywhere inside* another element

```html
p b { 
    color: red; 
}  

ul li b { 
    color: red;
}
```

- `p b`: any `<b>` inside a `<p>` (at any depth)
- `ul li b`: any `<b>` inside an `<li>` inside a `<ul>` (at any depth)
- This selector expresses containment, not proximity

{% enddetails %}

{% details Child selector %}

- Select only **direct children**, not deeper descendants

```html
p > b {
    color: red; 
}
```

{% enddetails %}

{% details ID and Class selectors %}

- ‘#’ for an ID
    - Matches exactly one element
    - IDs must be unique per page

```html
#main-header {
    background-color: black;
}

- “.” for a class
    - Can apply to many elements
    - Reusable, composable.

```html
.highlight {
    color: yellow;
}
```

```html
<p class="highlight"> Hello</p>
<span class="highlight">World</span>
```

{% enddetails %}

{% details Attribute selectors %}
- Select elements based on the presence or value of attributes.

```html
input[type="text"] {
  border: 1px solid gray;
}
```

- Other common forms:

```html
a[target] { }                 /* has attribute */
a[target="_blank"] { }        /* exact match */
img[src^="https"] { }         /* starts with */
img[src$=".png"] { }          /* ends with */
img[src*="logo"] { }          /* contains */
```

- Help styling elements semantically without extra classes
- Especially useful in forms and accessibility-aware design.

{% enddetails %}

{% details Universal selector (*) %}
- Selects everything.

```html
* {
  box-sizing: border-box;
}
```

- Common use:
    - CSS resets
     -Global defaults
- This selector is computationally expensive if overused.

{% enddetails %}

{% details Grouping selectors %}

- Apply the same rules to multiple selectors.

```html
h1, h2, h3 {
  font-family: sans-serif;
}
```

{% enddetails %}


### The CSS Cascade Precedence

For conflicting rules, the order of cascade precendence is:

- Style sheet creators
- Style sheet methods
- Style sheet selectors
- Specificity

In other words, when two rules conflict, the browser ask the questions in the following order to determine priority (from high to low)

- Who wrote this? (creator)
- Is it inline, internal, or external? (method)
- How specific is the selector?
- Does one have higher specificity?
- If still tied, who came last?


### Elements Positioning

- CSS positioning answers one question:
    - *Relative to what is this element being placed?*

{% details Relative Positioning %}

```html
.box {
  position: relative;
  top: 10px;
  left: 20px;
}
```

- What it means:
    - The element is positioned relative to its normal position in the document flow.
    - The space it originally occupied is still reserved.
- Key properties:
    - Stays in the normal flow
    - Can be nudged with top, left, right, bottom
    - Often used as a reference point for absolutely positioned children

{% enddetails %}

{% details Absolute Positioning %}

```html
.box {
  position: absolute;
  top: 10px;
  left: 20px;
}
```

- What it means:
    - The element is removed from the normal document flow.
    - It is positioned relative to:
        - The nearest positioned ancestor (relative, absolute, fixed)
        - The document body if no nearest relative exists. 
- Key properties:
    - Does not reserve space
    - Other elements behave as if it doesn’t exist
    - Common for overlays, tooltips, dropdowns

{% enddetails %}

{% details Fixed Positioning %}

```html
.box {
  position: fixed;
  bottom: 0;
  right: 0;
}
```

- What it means
    - The element is positioned relative to the **viewport**, the are of the browser that is visible to users. 
    - It does not move when the page scrolls
- Key properties:
    - Removed from document flow
    - Always stays in the same screen position
    - Used for nav bars, chat buttons, cookie notices

{% enddetails %}

### The Box Model and Layout

Every HTML element is a box. CSS just makes that box negotiable.


```
The Box Model Layers (Inside → Outside)
+-----------------------+
|       Margin          |
|  +-----------------+  |
|  |     Border      |  |
|  |  +-----------+  |  |
|  |  | Padding   |  |  |
|  |  | +-------+ |  |  |
|  |  | |Content| |  |  |
|  |  | +-------+ |  |  |
|  |  +-----------+  |  |
|  +-----------------+  |
+-----------------------+
```

{% details Content %}

- The actual text, image, or element content
- Controlled by width and height (by default)

{% enddetails %}

{% details Padding %}

```html
padding: 10px;
```

- What it does:
    - Space inside the element, between content and border
    - Background color extends into padding

{% enddetails %}

{% details Border %}

```html
border: 1px solid black;
```

- What it does:
    - Wraps padding and content
    - Visually separates the element from others
- Borders count toward the element’s total size unless box-sizing is changed.

{% enddetails %}

{% details Margin %}

```html
margin: 20px;
```

- What it does:
    - Space outside the element
    - Controls distance between elements
    - Margins can collapse vertically

{% enddetails %}

## 6. Quiz Information

Open book open note!

- Quiz 1: 
    - Available on Dec 16, 2025
    - Due/End on Dec 21, 2025
- Quiz 2: 
    - Available on Jan 05, 2026
    - Due/End on Jan 11, 2026
- Quiz 3: 
    - Available on Jan 13, 2026
    - Due/End on Jan 18, 2026    
    
    