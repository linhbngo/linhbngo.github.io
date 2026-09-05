---
layout: lecture
pretty_table: true
collection: csc496
title: "Swift MVC"
toc:
  - name: MVC
  - name: Hands-on MVC Array
---
# Swift MVC

## MVC:

{% details Motivational project %}

Create an app that list all GitHub public repository, given a GitHub ID. 
For example, for user `linhbngo`, the API link 
is: `https://api.github.com/users/linhbngo/repos?page=1&per_page=200"

{% enddetails %}
{% details MVC: Model-View-Control %}

The Model-View-Controller (MVC) design pattern assigns objects in 
an application one of three roles: 

    - Model, 
    - View, or 
    - Controller. 

The pattern defines:

    - the roles objects play in the application, 
    - the way objects communicate with each other. 

The types are separated from the others by abstract 
boundaries and communicates with objects of the other 
types across those boundaries. 

The collection of objects of a certain MVC type is 
sometimes referred to as a layer—for example, model layer.

{% enddetails %}
{% details Model Objects %}


- Encapsulate the data specific to an application 
- Define the logic and computation that manipulate and process that data. 

For example, a model object might represent a character in a game or a contact in an address book. A model object can have to-one and to-many relationships with other model objects, and so sometimes the model layer of an application effectively is one or more object graphs. Much of the data that is part of the persistent state of the application (whether that persistent state is stored in files or databases) should reside in the model objects after the data is loaded into the application. Because model objects represent knowledge and expertise related to a specific problem domain, they can be reused in similar problem domains. Ideally, a model object should have no explicit connection to the view objects that present its data and allow users to edit that data—it should not be concerned with user-interface and presentation issues.

Communication: User actions in the view layer that create or modify data are communicated through a controller object and result in the creation or updating of a model object. When a model object changes (for example, new data is received over a network connection), it notifies a controller object, which updates the appropriate view objects.

{% enddetails %}
{% details View Objects %}

A view object is an object in an application that users can see. A view object knows how to draw itself and can respond to user actions. A major purpose of view objects is to display data from the application’s model objects and to enable the editing of that data. Despite this, view objects are typically decoupled from model objects in an MVC application.

Because you typically reuse and reconfigure them, view objects provide consistency between applications. Both the UIKit and AppKit frameworks provide collections of view classes, and Interface Builder offers dozens of view objects in its Library.

Communication: View objects learn about changes in model data through the application’s controller objects and communicate user-initiated changes—for example, text entered in a text field—through controller objects to an application’s model objects.

{% enddetails %}
{% details Controller Objects %}

A controller object acts as an intermediary between one or more of an application’s view objects and one or more of its model objects. Controller objects are thus a conduit through which view objects learn about changes in model objects and vice versa. Controller objects can also perform setup and coordinating tasks for an application and manage the life cycles of other objects.

Communication: A controller object interprets user actions made in view objects and communicates new or changed data to the model layer. When model objects change, a controller object communicates that new model data to the view objects so that they can display it.

{% enddetails %}
## Hands-on: MVC Array

{% details Project creation %}


- Create a project named `repo_list`
- Update the files with the follow source codes

{% details info repo_listApp %}

```swift
--8<-- "docs/csc496/lectures/codes/03-mvc/repo_listApp.swift"
```

{% enddetails %}
{% details info ContenView.swift %}

```swift
--8<-- "docs/csc496/lectures/codes/03-mvc/ContentView.swift"
```

{% enddetails %}
{% details info repos.swift %}

```swift
--8<-- "docs/csc496/lectures/codes/03-mvc/repos.swift"
```

{% enddetails %}
{% details info repos_api.swift %}

```swift
--8<-- "docs/csc496/lectures/codes/03-mvc/repos_api.swift"
```

{% enddetails %}
{% enddetails %}
{% details Code designs %}


{% include figure.liquid path="assets/img/courses/csc496/03-mvc/repos_mvc.png" max-width="50%" zoomable=true %}

{% enddetails %}
{% details Challenge 1 %}

- Replace the URL with your own GitHUB username and check that the script can play with different names.

{% enddetails %}
{% details Array activities %}

- Open Playground
{% enddetails %}
