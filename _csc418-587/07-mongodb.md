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


???tip "Recording: MongoDB on Docker Desktop"
    <iframe src="https://wcupa.hosted.panopto.com/Panopto/Pages/Embed.aspx?id=dc99ba52-f1de-4243-9dd3-b254001e53fb&autoplay=false&offerviewer=true&showtitle=true&showbrand=true&captions=true&interactivity=all" height="405" width="720" style="border: 1px solid #464646;" allowfullscreen allow="autoplay" aria-label="Panopto Embedded Video Player" aria-description="mongodb" ></iframe>



## Overview

This is an introductory lecture on MongoDB. We follow the structure of the book:

- Lesson 13 introduces MongoDB with CLI interaction. 
- Lesson 14 shows how to connect the MongoDB database to a NodeJS application. 
- Lesson 15 discusses the types of query commands that can be used with the MongoDB database from within the Node.js application. 

## Lesson 13: Setting up a MongoDB

Instructions for installing MongoDB directly on Windows or Linux-based environments can be found in [MongoDB Documation](https://www.mongodb.com/docs/manual/administration/install-community/?operating-system=linux&linux-distribution=red-hat&linux-package=default&search-linux=with-search-linux). However, MongoDB's rolling versions can be problematic for production setup, as technical issues shown in previous versions of class lectures. 

In our case, we will freeze all versions of NodeJS and MongoDB through containerization. 

## Lesson 14: Connect a NodeJS to MongoDB



## Lesson 15: Further customization
