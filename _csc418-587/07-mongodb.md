---
layout: lecture
pretty_table: true
order: 5
title: MongoDB
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
  - name: "Lesson 13: Setting up a MongoDB"
  - name: "Lesson 14: Connect a NodeJS to MongoDB"
  - name: "Lesson 15: Further customization"
  
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

{% details Recording: MongoDB on Docker Desktop %}

<iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=dc99ba52-f1de-4243-9dd3-b254001e53fb&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="mongodb" ></iframe>

{% enddetails %}


## Overview

This is an introductory lecture on MongoDB. We follow the structure of the book:

- Lesson 13 introduces MongoDB with CLI interaction. 
- Lesson 14 shows how to connect the MongoDB database to a NodeJS application. 
- Lesson 15 discusses the types of query commands that can be used with the MongoDB database from within the Node.js application. 

{% details Why MongoDB/NoSQL? %}

Between MongoDB and PostgreSQL/MySQL/..., one will have to make a choice. For JavaScript/NodeJS, 
online resources and documentations have indicated that MongoDB is the popular tool of choice. 
It is important that we understand some of the characteristics of MongoDB that makes it 
*attractive* for certain *designs*. These are the followings:

- Schema flexibility (a.k.a. “move fast, ask forgiveness”)
    - MongoDB stores data as documents (JSON/BSON): Fields can be added whenever is necessary. 
    - This is advantageous for:
        - Frequent changing product requirements
        - APIs prototyping
- Natural fit for application objects
    - NodeJS/JavaScript speaks JSON natively.
    - It is not limited by object-relational impedance mismatch. 
- Easy scaling for early-stage development. 

In the long run, it is critically important to keep track of performance of your 
database performance. 

{% enddetails %}

## Lesson 13: Setting up a MongoDB

Instructions for installing MongoDB directly on Windows or Linux-based environments can be found in [MongoDB Documentation](https://www.mongodb.com/docs/manual/administration/install-community/?operating-system=linux&linux-distribution=red-hat&linux-package=default&search-linux=with-search-linux). However, MongoDB's rolling versions can be problematic for production setup, as technical issues shown in previous versions of class lectures. 

In our case, we will freeze all versions of NodeJS and MongoDB through containerization. 

- Launch Docker Desktop and click on the csc418env container to show the two individual containers:
    - `webapp`
    - `webdb`

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/mongodb/mongodb-webdb.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- Click the three dots of `webdb` and select `Open in terminal`:

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/mongodb/mongodb-webdb-terminal.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- Run `mongosh` from the terminal. 
    - The container has everything built in for MongoDB set up. 
    - Follow the [Digital Ocean's tutorial](https://www.digitalocean.com/community/tutorials/how-to-use-the-mongodb-shell) to practice. 

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/mongodb/mongodb-mongosh.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


Go through `Unit 3`, `Lesson 13` of the textbook. One important thing to keep in mind is that this 
book uses the local MongoDB installation, hence `dbRURL = "mongodb://localhost:27017". 

For this class, with the container structure, we are assuming a remote MongoDB server located on 
node `webdb`. You will need to change the `dbURL` value accordingly:

```js
dbURL = "mongodb://webdb:27017",
```

## Lesson 14: Connect a NodeJS to MongoDB

[Mongoose](https://mongoosejs.com/) is an Object Data Modeling (ODM) library that sits 
between your JavaScript/Node.js code and MongoDB.

Mongoose allows developers to define schemas for NodeJS. 


## Lesson 15: Further customization
