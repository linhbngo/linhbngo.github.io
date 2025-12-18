---
layout: lecture
pretty_table: true
order: 4
title: "Project 1: Dynamic Data and Form Handling"
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

We will develop a website for a company with tabs including `Home`, `Users`, 
and `Add Contacts`. There are two parts for this project: 

- (1) Displaying dynamic data, 
- (2) Form Handling with in-memory data. 

CSC418 students are required to complete the `form` operations which allow a 
user to add a new contact and display the new list of users. CSC587 students 
need to display the form, add a new user, and delete a user.

## 1. Displaying Date and Time at the Server Side

In the first part of the project, you will begin with a simple Node & 
Express project. What you need to do is to set up the Main App, the Route 
to display the index page with any name you like using your preferred View 
Engine in addition to HTML. The main requirement is to be able to show 
the current time and date dynamically. If you refresh the webpage, the date and 
time should change. Following is an example:

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_1/project_1_1.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

You need to show the screen shots of the IDE, e.g., Visual Studio Code, 
and the Browser. The layout.ejs provides the format of all webpages with `Top Navigation`, `Navigation`, `Body`, and the `Footer` divisions.

The layout.ejs provides the format of all webpages with `Top Navigation`, `Navigation`, 
`Body`, and the `Footer` divisions.


## 2. Form Handling

In the second part of the project, you will allow a user to enter the name 
and the gender via a form. Then, the newly entered name and gender will be 
added to the in-memory data reservoir. If you click the `Users` tab, you 
should see the new user. If you restart the browser, the newly added user 
may be lost. It is due to the nature of in-memory data reservoir.

You need to show:

- the form page, 

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_1/project_1_2.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- the before,

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_1/project_1_3.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

- and the after page.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_1/project_1_4.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

On the after page, you will see an added user. For showing the deletion of a user, you 
show the `before`, the execution of the delete form, and the `after`.

You need to show the screenshot of the IDE with the main routing statements shown in the
editing area, and the process of adding a user is displayed in the Terminal area.

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/project_1/project_1_5.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

## 3. Submissions:

1. Delete node_modules from your part I project; and compress all files; store all files with
the name `<ABCD_project1-Part1>.zip`.
2. Delete node_modules from part II and compress all files with the name
`<ABCD_project1-part2>.zip`.
3. Submit a Word document with screen shots using the name `<ABCD_project1>.docx`.
Here ABCD is the first four letters of your last name. If I submit my project, I will call it
`Ngo_project1-Part1.zip`, `Ngo_project2-Part2.zip`, and `Ngo_project1.docx`.

## 4. Grading Rubric:

1. **30% MVC architecture** - must separate model, view, and controller. You cannot merge
model/view/controller in any way. If you use one folder to keep any two in MVC together, it is a
violation of this rule. If you use one file to combine any two or more of the MVC parts, it is
worse.
2. **30% Soundness** - Your project must be executable and provide required functions. When
implementing the database, you must use the model/schema operations to
complete the functions.
3. **30% Front-End Implementation** - You must use JavaScript with EJS to implement the front-
end. You are not allowed to use HTML/CSS with jQuery, PHP, etc., to implement the project.
4. **10% Submission Rules and documentation** - Two files are required: 
    - a Word document with screenshots to demonstrate that your code works; and 
    - a .zip file that contains the code. 
    
- **Do not** use special compressing format such that special software is needed. If so, you will need
to describe the procedure to unzip your file in the Word document. 
- The Word document must include the instructions to execute your code, if needed. 
- The Word document must not be compressed with the code in the second file. 
- The second file must not include nide_modules.
- The naming convention for the folder containing the code must follow the naming convention BEFORE or AFTER the compressed file is unzipped.