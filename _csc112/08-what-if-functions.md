---
layout: lecture
pretty_table: true
collection: csc112
order: 9
title: "What-If Analysis and Specialized Functions"
description: "Treat weights and rates as parameters. Look up descriptions; Goal Seek and scenarios record experiments."
mermaid:
  enabled: true
  zoomable: true

toc:
  - name: This week
  - name: Objectives
  - name: Models have parameters
  - name: Goal Seek, Data Tables, Scenarios, Solver
  - name: Lookup functions
  - name: Other specialized functions
  - name: Try this in Excel
  - name: Takeaways
---

## This week

Weeks 9–10 · Excel Ch. 6–7 · Excel Projects 9–11. Next: statistics and Copilot (lecture 9).

## Objectives

{% details After this lecture you should be able to %}

- Separate **inputs you change** (parameters) from **outputs you watch**
- Use Goal Seek or a one-variable data table to answer "what input gives this result?"
- Record named scenarios instead of overwriting the only model
- Join a code to a description with `XLOOKUP` (and know what `VLOOKUP` still does)

{% enddetails %}

## Models have parameters

{% details Scientific method, spreadsheet edition %}

- Hypothesis: "If the exam weight rises to 40%, more students fall below 70%"
- Parameter cells: weights, tax rate, price, capacity — **absolute references** (lecture 3)
- Formulas and `IF`s depend on those cells, not on typed copies of the rate
- Output: count of `Review`, total cost, break-even units
- Record what you changed; do not save over the only copy of the model (`File → Save As` or a `Scenarios` sheet)

{% enddetails %}

{% details Layout %}

| Sheet | Contains |
| --- | --- |
| `Data` | Table of observations |
| `Model` | Parameter cells + formulas that read the Table |
| `Checks` | Hand-computed rows |
| `Scenarios` | Notes: date, what changed, what happened |

- Yellow (or a named style) for parameter cells is a convention, not magic
- Protect the sheet later if others will type only in yellow cells

{% enddetails %}

## Goal Seek, Data Tables, Scenarios, Solver

{% details Goal Seek %}

- Question: "What exam score makes weighted total = 0.70?"
- Data → What-If → Goal Seek: set cell (output) to value, by changing (parameter)
- Works on **one** input; the relationship should be something Excel can nudge
- Always sanity-check: is that exam score possible (`0`–`1` or `0`–`100`)?

{% enddetails %}

{% details Data Tables %}

- One-variable: a column of trial tax rates, a row (or column) of resulting totals
- Two-variable: grid of two parameters (use sparingly; it is easy to misread)
- Data Table is *not* an Excel Table (lecture 6) — unfortunate name
- Must sit on the same sheet as the formula in older workbooks; follow the textbook's layout

{% enddetails %}

{% details Scenario Manager %}

- Named bundles of parameter values: `Base`, `HeavyExam`, `QuizHeavy`
- Switch and compare; add a scenario summary sheet
- Better than "I think I undo'd back to the original weights"

{% enddetails %}

{% details Solver (preview) %}

- Several inputs, constraints ("weights sum to 1", "hours ≥ 0")
- Overkill for this course's first pass; know it exists for optimization-style questions
- Placeholder: one demo if time (maximize average without any weight > 0.5)

{% enddetails %}

## Lookup functions

{% details Join a code to a description %}

- Data: `section` is `A`, `B`, `C`
- Table `Sections`: code | room | meeting time
- `XLOOKUP([@section], Sections[code], Sections[room])`
- This is a **join**, the same idea as matching IDs — do not retype rooms by hand

{% enddetails %}

{% details XLOOKUP vs VLOOKUP %}

| | `XLOOKUP` | `VLOOKUP` |
| --- | --- | --- |
| Lookup column | Any | Leftmost of the range |
| Insert columns | Safer | Breaks if you insert inside the range |
| Not found | Custom if_not_found | `#N/A` unless wrapped |
| Approximate match | Explicit | Easy to leave TRUE by accident |

- Textbook may still teach `VLOOKUP`; if you use it, **FALSE** (exact match) is the default you want for IDs
- `INDEX`+`MATCH` is the older flexible pair; optional

{% enddetails %}

{% details Lookup failures %}

- Extra spaces: `A` vs `A `
- Number vs text IDs (lecture 1 types)
- Duplicate keys: lookup returns the first match — is that the rule you wanted?
- Approximate match on unsorted data: silent wrong room

{% enddetails %}

## Other specialized functions

{% details Text and dates (you will need a few) %}

- `LEFT` / `RIGHT` / `TRIM` / `TEXTSPLIT` — when two variables were stuffed in one column (lecture 2)
- `YEAR` / `MONTH` / `EOMONTH` / `NETWORKDAYS` — only on real date serials
- `TEXT` to display a date; the stored value should stay a date
- Do not parse dates as text if Excel already stores them as dates

{% enddetails %}

{% details Logical lookups %}

- `IFNA` / `IFERROR` around a lookup: show `Missing section` instead of `#N/A`
- Teach `IFERROR` after you have seen the error — it can hide type bugs

{% enddetails %}

## Try this in Excel

{% details Lab 9 — Goal Seek and scenarios on the gradebook %}

1. Parameters: three weights that `SUM` to 1
2. Output: `COUNTIF` of `Review`
3. Scenario Manager: `Base` (0.3/0.3/0.4), `ExamHeavy` (0.2/0.2/0.6)
4. Switch; record both Review counts on `Scenarios`
5. Goal Seek: set one student's weighted total to 0.70 by changing **their** exam cell (not the class weight)
6. Write in Word: which parameter you would not Goal Seek in real life (ethics / fairness)

{% enddetails %}

{% details Lab 10 — XLOOKUP %}

1. Small `Sections` Table: code, room, seats
2. On `Scores`, `Room = XLOOKUP([@section], …)`
3. Break it: a typo section code; handle with `if_not_found`
4. Optional: Copilot drafts the `XLOOKUP`; you explain each argument in a comment

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- How is Goal Seek different from "I typed numbers until it looked right"?
- If a lookup is `#N/A`, is that a formula error or a data-quality finding?

{% enddetails %}

## Takeaways

{% details Carry these into stats and Copilot week %}

- Parameters live in cells; experiments get names
- Goal Seek / data tables / scenarios beat random typing
- Lookups join tables; exact match and types matter
- Next: describe a distribution (`MEDIAN`, `STDEV`) and use Copilot only inside the check loop

{% enddetails %}

{% details Placeholder notes for expansion %}

- Two-variable data table screenshot from the textbook
- Solver one-pager
- `XLOOKUP` with two criteria (optional)

{% enddetails %}