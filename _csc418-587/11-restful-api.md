---
layout: lecture
pretty_table: true
order: 8
title: Building a REST API
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
  - name: What is a Web Service?
    # if a section has subsections, you can add them as follows:
    # subsections:
    #   - name: Example Child Subsection 1
    #   - name: Example Child Subsection 2
  - name: Types of Web Services
  - name: What is a REST API?
  - name: Developing a REST API
  - name: Accessing the API 
---

This lecture provides an overview for RESTful clients and how to build RESTful API for web services. 

## What is a Web Service?

- A web service is a generic term for an interoperable machine-to-machine software 
function that is hosted at a network addressable location.
- A web service has an interface, which hides the implementation details so that it 
can be used independently of the hardware or software platform on which it is implemented, 
and independently of the programming language in which it is written. 
- This independence encourages web service-based applications to be loosely coupled, 
component-oriented, cross-technology implementations. 
- Web services can be used alone or with other web services to
carry out a complex aggregation or a business transaction.

## Types of Web Services

{% details SOAP-based %} 

- Traditional web services are implemented with a complicated architecture
when the messages being passed is XML-based (eXtensible Markup Language). 
- It uses a Simple Object Accessing Protocol (SOAP) to
provide the API for sending and receiving messages in the payload of an 
HTTP message.

{% enddetails %}

{% details JSON-based %} 

- The modern Web Services are using JavaScript Object Notation 
(JSON)format to structure the messages. 
- A JSON message stores the Get-Put-Update-Delete methods in the HTTP header in 
a request message; and a set of property-value pairs of data in the reply message. 
- It simplifies the protocol and the message structure for representational state 
(REST) web services.

{% enddetails %}

## What is a REST API?

{% details REST %}

- Representational State Transfer. 
- Is an architectural style for building distributed systems 
(especially on the web), defined by a set of constraints tha tend to 
produce systems that are scalable, performant, and evolvable. 

{% enddetails %}

{% details Key Idea %}

Data and functionality are modeled as `resources`. Each resource is identified by a URI (often a URL on the web). 
Clients interact with resources by exchanging representations of those resources (commonly JSON today, but not required). 

{% enddetails %}


{% details Core REST constraints %}

- Client–server separation:  Separate UI concerns vs. data concerns
- Stateless requests:  Each request contains what the server needs to understand it and the server doesn’t rely on stored `conversation state`.
- Cacheable responses (when appropriate)
- Uniform interface: A consistent way to interact with resources
- Layered system: proxies, gateways, load balancers can sit in-between

{% enddetails %}


{% details Uniform interface %}

- Resource identification via URI
- Manipulating resources through representations
- Self-descriptive messages (e.g., Content-Type, caching headers, auth context, etc.)
- Hypermedia-driven navigation (clients discover valid next actions via links in responses) 

{% enddetails %}

{% details HTTP methods in modern practice %}

HTTP methods have standardized semantics that REST APIs typically lean on:

- GET: retrieve a representation (should be read-only; “safe”) 
- PUT: create or replace the representation at a known URI
- DELETE: remove a resource
- POST: submit data to a resource (often to create a subordinate resource or trigger processing); 
- PATCH (commonly used today): partial update 

{% enddetails %}

{% details Additional notes %}

- REST’s stateless constraint still allows for authentication via cookies, bearer tokens, etc. as long as each request carries the needed context. 
- Many production `REST APIs` are really HTTP+JSON APIs.

{% enddetails %}

## Developing a REST API

When we develop a REST API, we need to do the following:

1. Develop a RESTful web service server (an endpoint),
2. Develop RESTful web services API functions to implement the CRUD operations,
3. Complete routers.
4. Develop an API for a client to consume a web service. We need to develop EJS views to
display the data received from the Endpoint.

The textbook's lesson 26 will provide details on how to develop a Web Service Server. 

## Accessing the API 

- In lesson 10, the textbook describes EJS for client-side scripting. 
- In lesson 26, the textbook shows examples of using jQuary to access a 
Document Object Model(DOM) object. EJS, bootstrap, jQuary are all 
considered technologies for the front-end development.

- Lesson 27 of the textbook describe how the API endpoints can be 
accessed. The example codes will show the following:
    - Creating an API namespace
    - Building a UI model to fetch data asynchronously
    - Connecting models with MongoDB methods.

- For the authentication step of Lessons 26.3 and 27, you will need to setup the `bcrypt` module as follows:

```bash
npm install bcrypt@latest
```
