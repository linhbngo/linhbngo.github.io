---
layout: lecture
pretty_table: true
order: 7
title: "Project 2: JSON and MongoDB"
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

We will develop a website for a company with tabs including `Home`, `Users`, and `Add
Contacts`. This project is a continuation of the previous project. In Project#1, you used an in-
memory data reservoir to store the user data. You will convert the in-memory data reservoir to
a MongoDB/Mongoose database with one collection of users. CSC587 students are required to
allow a user to complete `CRUD` operations for the database accessing; CSC418 students only
need to complete `Create` and `Read` operations. For CSC587, you may use an additional tab
for Edit, Delete.

## 1. Create a MongoDB/Mongoose Database

In the first part of the project, you will begin with creating a MongoDB database using
command line commands. You don’t need to write any code to complete this part once you
install the MongoDB database management system.

## 2. Access MongoDB Database via JavaScript Code

In the second part of the project, you will allow a user to enter the name and the gender via a
form. Then, the newly entered name and gender will be added to the database. If you click the
`Users` tab, you should see the new user. If you restart the browser, the newly added user may
not be lost. You will be able to access the database and list all users, if needed.
You need to show the form page, the before, and the after page. On the after page, you will see
an added user.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_1.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_2.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_3.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

You need to show the screenshot of the IDE with the main routing statements shown in the
editing area, and the process of adding a user is displayed in the Terminal area.
Of course, we cannot tell if this was indeed retrieved from a database without checking the
code in the homecontroller.js. So please show the screenshot of part of the homecontroller.js
and the code. You may use any IDE to show the code. 

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_4.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_5.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_6.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

We can tell that the Routing of `/users` and the actual code for accessing the MongoDB
database. You also need to submit the compressed files including main.js, the homecontroller.js
files.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_7.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_2/project_2_8.png" class="img-fluid z-depth-1" zoomable=true %}
</div>


## 3. Submissions: Use all lower case for the name of all projects.

1. You may include the screen shot of a Robo 3T or MongoDB Compass to show that you
have created a database. You can include this screen shot in your Word document.

2. Delete node_modules from part II and compress all files with the name
<abcd_project2>.zip. You should call your project folder the same as the compressed
file after it is uncompressed.

3. Submit a Word document with screen shots using the name <abcd_project2>.docx to
show the `Before, action, and after` in this document for Add and for Delete,
respectively.
Here abcd is the first four letters of your last name. If I submit my project, I will call it
yang_project2.zip, and yang_project2.docx. Be sure to check if the project name is changed
after uncompressing. If so, you will receive a penalty.

## 4. Grading Rubric:

1. 30% MVC architecture - must separate model, view, and controller. You cannot merge
model/view/controller in any way. If you use one folder to keep any two in MVC together, it is a
violation of this rule. If you use one file to combine any two or more of the MVC parts, it is
worse.

2. 30% Soundness - Your project must be executable and provide required functions. When
implementing the database, you must use the model/schema/mongoose operations to
complete the functions.

3. 30% Front-End Implementation - You must use JavaScript with EJS to implement the front-
end. You are not allowed to use HTML/CSS with jQuery, PHP, etc., to implement the project.

4. 10% Submission Rules and documentation - Two files are required: a Word document with
screenshots to demonstrate that your code works; and a .zip file that contains the code. Please
do not use special compressing format such that special software is needed. If so, you will need
to describe the procedure to unzip your file in the Word document. The Word document must
include the instructions to execute your code, if needed. The Word document must not be
compressed with the code in the second file. The second file must not include nide_modules.
The naming convention for the folder containing the code must follow the naming convention
BEFORE or AFTER the compressed file is unzipped.