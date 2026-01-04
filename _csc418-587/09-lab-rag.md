---
layout: lecture
pretty_table: true
order: 6
title: "Lab: Mini RAG"
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
  - name: "Part 0: Ollama Setup"
  - name: "Part 1: Create the project structure"
  - name: "Part 2: Install Dependencies"
  - name: "Part 3: Environment Configuration"
  - name: "Part 4: Database Connection"
  - name: "Part 5: Define the Model"
  - name: "Part 6: Controllers"
  - name: "Part 7: Ollama Service"
  - name: "Part 8: Routes"
  - name: "Part 9: Views (EJS)"
  - name: "Part 10: The final puzzle piece"
  - name: "Part 11: Run and Test"
  - name: "Part 12: Customization"
---

## Overview

For this lab, we will build a small Express.js web application 
using MVC. This includes:

- Define and use Mongoose models with MongoDB
- Implement server-side retrieval using MongoDB text search
- Integrate a local LLM (Ollama) from a Node.js backend

{% details What is a RAG %}

Retrieval-Augmented Generation (RAG) is an AI technique that 
enhances Large Language Models (LLMs) by connecting them to 
external, authoritative data sources to provide more accurate, 
up-to-date, and specific answers, rather than relying solely 
on their static training data. 

{% enddetails %}

## Part 0: Ollama Setup

For this lab, you will use Ollama installed directly on the Desktop. 
- Download and install Ollama from [the website](https://ollama.com/). 
- Start Ollama and pull a model:

```bash
ollama serve
ollama pull llama3.1:8b
ollama ls
```

## Part 1: Create the project structure

First, we will start with creating the main folder 
for the lab application. 

```bash
cd /apps
mkdir mini-rag
cd mini-rag
```

Second, we initialize the Node project inside the 
directory structure. 

```bash
npm init -y
```

Next, we create the remaining directory structures

```bash
mkdir config controllers models routes services views public
```

## Part 2: Install Dependencies

```bash
npm install express mongoose ejs dotenv
npm install --save-dev nodemon
```

Add the following content to `package.json`:

{% details package.json %}

```json
{
  "name": "mini-rag",
  "version": "1.0.0",
  "description": "Simple MVC RAG with MongoDB, Mongoose, and Ollama",
  "main": "app.js",
  "scripts": {
    "dev": "nodemon app.js",
    "start": "node app.js"
  },
  "dependencies": {
    "dotenv": "^16.4.5",
    "ejs": "^3.1.10",
    "express": "^4.19.2",
    "mongoose": "^8.6.1"
  },
  "devDependencies": {
    "nodemon": "^3.1.4"
  }
}
```
{% enddetails %}

## Part 3: Environment Configuration

- First, create the file called `.env` with the 
following contents:

{% details .env %}

```bash
PORT=3000
MONGODB_URI=mongodb://webdb:27017/mini_rag
OLLAMA_URL=http://host.docker.internal:11434
OLLAMA_MODEL=llama3.1:8b
TOP_K=4
```

{% enddetails %}

- Using `.env` is a convenient way to separate configuration from deployment. In 
this case, these are environment parameters that will be used inside the NodeJS 
app later on. 
- Since we are using a Docker-based deployment, the app will be running inside 
the Docker environment. Assuming the Ollama service is being run directly on host, 
the `OLLAMA_URL` is a way to allow containers inside Docker to communicate with 
the Ollama service on host. 

## Part 4: Database Connection

- Create the file `config/db.js` with the following contents:

{% details db.js %}
```js
"use strict";

const mongoose = require("mongoose");

module.exports = async function connectDb() {
  const uri = process.env.MONGODB_URI;
  if (!uri) {
    console.error("Missing MONGODB_URI in environment.");
    process.exit(1);
  }

  try {
    await mongoose.connect(uri);
    console.log("Connected to MongoDB");
  } catch (err) {
    console.error("MongoDB connection failed:", err.message);
    process.exit(1);
  }
};
```

{% enddetails %}

This code will do the followings:

- Import mongoose
- Connect using `process.env.MONGODB_URI`
    - This is the `MONGODB_URI` specified in `.env`
- Exit the process on failure

## Part 5: Define the Model

We will create a document model with the following 
fields:

- `title (String, required)`
- `content (String, required)`
- `tags (array of Strings)`
- `timestamps` enabled

We will create the following contents in `models/Document.js`

{% details Document.js %}

```js
"use strict";

const mongoose = require("mongoose");

const DocumentSchema = new mongoose.Schema(
  {
    title: { type: String, required: true, trim: true, maxlength: 120 },
    content: { type: String, required: true, trim: true, maxlength: 20000 },
    tags: [{ type: String, trim: true }]
  },
  { timestamps: true }
);

// Simple retrieval: Mongo text search
DocumentSchema.index({ title: "text", content: "text" });

module.exports = mongoose.model("Document", DocumentSchema);
```
{% enddetails %}

## Part 6: Controllers 

{% details Document controller %}

Create `controllers/docController.js` with the following 
contents:

```js
"use strict";

const Document = require("../models/Document");

exports.index = async (req, res, next) => {
  try {
    const docs = await Document.find().sort({ createdAt: -1 }).limit(50);
    res.render("docs", { title: "Docs", docs, error: null });
  } catch (err) {
    next(err);
  }
};

exports.create = async (req, res, next) => {
  try {
    const title = (req.body.title || "").trim();
    const content = (req.body.content || "").trim();
    const tagsRaw = (req.body.tags || "").trim();

    if (!title || !content) {
      const docs = await Document.find().sort({ createdAt: -1 }).limit(50);
      return res.status(400).render("docs", {
        title: "Docs",
        docs,
        error: "Title and content are required."
      });
    }

    const tags = tagsRaw
      ? tagsRaw.split(",").map(t => t.trim()).filter(Boolean).slice(0, 10)
      : [];

    await Document.create({ title, content, tags });
    res.redirect("/docs");
  } catch (err) {
    next(err);
  }
};
```

{% enddetails %}


{% details RAG Controller %}

Create `controllers/ragController.js` with the following 
contents:


```js
"use strict";

const Document = require("../models/Document");
const { generateWithOllama } = require("../services/ollamaService");

function buildPrompt({ question, docs }) {
  // Keep it strict. Less “creative writing,” more “grounded answer.”
  const system = [
    "You are a helpful assistant.",
    "Use ONLY the provided CONTEXT to answer.",
    "If the answer is not in the context, say: “I don’t know from the provided notes.”",
    "When you use a note, cite it like [Doc:TITLE]."
  ].join(" ");

  const context = docs.length
    ? docs
        .map((d, idx) => {
          // Trim context to avoid huge prompts
          const snippet = d.content.length > 1200 ? d.content.slice(0, 1200) + "..." : d.content;
          return `Doc ${idx + 1}\nTITLE: ${d.title}\nCONTENT:\n${snippet}\n`;
        })
        .join("\n")
    : "No notes found.";

  return `${system}\n\nCONTEXT:\n${context}\n\nQUESTION:\n${question}\n\nANSWER:`;
}

exports.askPage = (req, res) => {
  res.render("index", {
    title: "MiniRAG",
    question: "",
    answer: null,
    citations: [],
    error: null
  });
};

exports.answer = async (req, res, next) => {
  try {
    const question = (req.body.question || "").trim();
    const topK = Math.max(1, Math.min(parseInt(process.env.TOP_K || "4", 10), 8));

    if (!question) {
      return res.status(400).render("index", {
        title: "MiniRAG",
        question: "",
        answer: null,
        citations: [],
        error: "Please enter a question."
      });
    }

    // Retrieval: MongoDB text search
    // If empty DB or no text index, this will simply return empty results.
    const docs = await Document.find(
      { $text: { $search: question } },
      { score: { $meta: "textScore" }, title: 1, content: 1 }
    )
      .sort({ score: { $meta: "textScore" } })
      .limit(topK);

    const prompt = buildPrompt({ question, docs });

    let answerText;
    try {
      answerText = await generateWithOllama({ prompt });
    } catch (ollamaErr) {
      // Make this a teaching moment: graceful degradation.
      return res.status(502).render("index", {
        title: "MiniRAG",
        question,
        answer: null,
        citations: docs.map(d => d.title),
        error:
          "Could not reach Ollama. Is it running? (Try: `ollama serve`) " +
          `Details: ${ollamaErr.message}`
      });
    }

    res.render("index", {
      title: "MiniRAG",
      question,
      answer: answerText,
      citations: docs.map(d => d.title),
      error: null
    });
  } catch (err) {
    next(err);
  }
};
```

- This controller will do the followings:
    - Accept a question
    - Retrieve top-K documents using MongoDB $text search
    - Build a strict prompt
    - Call Ollama
    - Render the answer and citations

{% enddetails %}


## Part 7: Ollama Service

{% details Accessing Ollama API %}

Create `services/ollamaService.js` with the following 
contents:

```js
"use strict";

/**
 * Calls Ollama's /api/generate endpoint.
 * Uses fetch (Node 18+ has global fetch).
 */
async function generateWithOllama({ prompt }) {
  const baseUrl = process.env.OLLAMA_URL || "http://localhost:11434";
  const model = process.env.OLLAMA_MODEL || "llama3.1:8b";

  const res = await fetch(`${baseUrl}/api/generate`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({
      model,
      prompt,
      stream: false
    })
  });

  if (!res.ok) {
    const text = await res.text().catch(() => "");
    throw new Error(`Ollama error (${res.status}): ${text}`);
  }

  const data = await res.json();
  return data.response || "";
}

module.exports = { generateWithOllama };
```

{% enddetails %}

## Part 8: Routes

{% details Docs routes %}

Create `routes/docRoutes.js` with the following 
contents:

```js
"use strict";

const express = require("express");
const router = express.Router();
const docController = require("../controllers/docController");

router.get("/", docController.index);
router.post("/", docController.create);

module.exports = router;
```

{% enddetails %}

{% details RAG routes %}

Create `routes/ragRoutes.js` with the following 
contents:

```js
"use strict";

const express = require("express");
const router = express.Router();
const ragController = require("../controllers/ragController");

router.get("/", ragController.askPage);
router.post("/ask", ragController.answer);

module.exports = router;
```

{% enddetails %}

## Part 9: Views (EJS)

Create the following view EJS files inside `views` directory

{% details layout.ejs %}

```js
<!doctype html>
<html>
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title><%= title %></title>
  <link rel="stylesheet" href="/styles.css" />
</head>
<body>
  <header class="topbar">
    <div class="brand">
      <a href="/">MiniRAG</a>
      <span class="sep">|</span>
      <a href="/docs">Docs</a>
    </div>
  </header>

  <main class="container">
    <%- body %>
  </main>

  <footer class="footer">
    <small>Lab RAG</small>
  </footer>
</body>
</html>
```
{% enddetails %}

{% details index.ejs %}

```js
<%
  const body = `
    <h1>MiniRAG</h1>
    <p class="muted">Ask a question. The server retrieves matching notes and asks the local model to answer using only that context.</p>

    ${error ? `<div class="alert">${error}</div>` : ""}

    <form method="POST" action="/ask" class="card">
      <label>Question</label>
      <input name="question" value="${(question || "").replace(/"/g, "&quot;")}" placeholder="e.g., What is Mongoose used for?" />
      <button type="submit">Ask</button>
    </form>

    ${answer ? `
      <section class="card">
        <h2>Answer</h2>
        <pre class="answer">${answer}</pre>

        <h3>Citations (retrieved notes)</h3>
        ${citations && citations.length
          ? `<ul>${citations.map(t => `<li>${t}</li>`).join("")}</ul>`
          : `<p class="muted">No notes matched your question.</p>`
        }
      </section>
    ` : ""}

    <p class="muted">Tip: add some notes first in <a href="/docs">Docs</a>.</p>
  `;
%>
<%- include("layout", { title, body }) %>
```
{% enddetails %}

{% details docs.ejs %}

```js
<%
  const body = `
    <h1>Docs</h1>
    <p class="muted">Add notes to your knowledge base. Retrieval uses MongoDB text search.</p>

    ${error ? `<div class="alert">${error}</div>` : ""}

    <form method="POST" action="/docs" class="card">
      <label>Title</label>
      <input name="title" placeholder="e.g., Express middleware basics" />

      <label>Content</label>
      <textarea name="content" rows="8" placeholder="Write your note here..."></textarea>

      <label>Tags (comma-separated)</label>
      <input name="tags" placeholder="express, mvc, mongodb" />

      <button type="submit">Save Note</button>
    </form>

    <section class="card">
      <h2>Saved Notes</h2>
      ${docs.length ? `
        <ul class="doclist">
          ${docs.map(d => `
            <li>
              <div class="doctitle">${d.title}</div>
              <div class="muted">${new Date(d.createdAt).toLocaleString()}</div>
              <div class="snippet">${(d.content || "").slice(0, 180)}${d.content.length > 180 ? "..." : ""}</div>
            </li>
          `).join("")}
        </ul>
      ` : `<p class="muted">No notes yet. Add one above.</p>`}
    </section>
  `;
%>
<%- include("layout", { title, body }) %>
```
{% enddetails %}


## Part 10: The final puzzle piece

The `app.js` should:
- Load environment variables
- Connect to MongoDB
- Register middleware
- Register routes
- Handle 404 and 500 errors

{% details app.js %}

```js
"use strict";

require("dotenv").config();

const path = require("path");
const express = require("express");
const connectDb = require("./config/db");

const ragRoutes = require("./routes/ragRoutes");
const docRoutes = require("./routes/docRoutes");

const app = express();
const port = process.env.PORT || 3000;

// DB
connectDb();

// View engine
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views"));

// Middleware
app.use(express.urlencoded({ extended: false }));
app.use(express.json());
app.use(express.static(path.join(__dirname, "public")));

// Tiny request logger (helps students “see” the pipeline)
app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);
  next();
});

// Routes
app.use("/", ragRoutes);
app.use("/docs", docRoutes);

// 404
app.use((req, res) => {
  res.status(404).render("layout", {
    title: "Not Found",
    body: `<h2>404</h2><p>That route doesn't exist.</p><p><a href="/">Go home</a></p>`
  });
});

// Error handler
app.use((err, req, res, next) => {
  console.error("ERROR:", err);
  res.status(500).render("layout", {
    title: "Server Error",
    body: `<h2>500</h2><p>Something broke on the server.</p>`
  });
});

app.listen(port, () => console.log(`MiniRAG running at http://localhost:${port}`));
```
{% enddetails %}

## Part 11: Run and Test

```bash
npm run dev
```

{% details First launch %}

This is where you can ask the RAG bot the question. You need to 
update your document first. 

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/labrag/mainrag.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

{% enddetails %}

{% details Document interface %}

<div class="row mt-3">
    {% include figure.liquid loading="eager" path="assets/img/courses/csc418/labrag/docrag.png" class="img-fluid z-depth-1" zoomable=true %}
</div>

{% enddetails %}

## Part 11: Customization

Attempt to perform the following add-ons to your app

- Modify the prompt template inside `ragController.js` and see how that 
impact the answer. 
- There might be cases where there is no relevant document yet. Add a new 
service that provides an alternative non-RAG answer. 