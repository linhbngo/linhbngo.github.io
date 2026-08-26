---
layout: lecture
pretty_table: true
collection: csc112
order: 10
title: "Statistical Functions and Copilot as a Checked Assistant"
description: "Describe a distribution honestly, then let Copilot draft formulas you can still verify."
mermaid:
  enabled: true
  zoomable: true

toc:
  - name: This week
  - name: Objectives
  - name: A distribution is more than a mean
  - name: Statistical functions in Excel
  - name: What Copilot is and is not
  - name: Draft, explain, verify
  - name: Academic integrity
  - name: Try this in Microsoft 365
  - name: Takeaways
---

## This week

Week 11 · Excel Ch. 8 · Excel Projects 12–13. Next: Python as automation (lecture 10).

## Objectives

{% details After this lecture you should be able to %}

- Explain why mean, median, and spread can disagree
- Compute `AVERAGE`, `MEDIAN`, `STDEV` / `STDEV.S`, and a simple percentile on a Table column
- Use Copilot (or an equivalent assistant) to *draft* or *explain* a formula
- Verify against a hand-checked example, a boundary, and a type trap
- Distinguish allowed assistance from submitting unreviewed generated work

{% enddetails %}

## A distribution is more than a mean

{% details The mean is one sentence about a list %}

- `AVERAGE` of `{10, 10, 10, 100}` is pulled by 100 (lecture 4)
- **Median**: the middle after sorting — often closer to "a typical row"
- **Spread**: standard deviation, IQR, min/max — "how much do rows disagree?"
- A PivotTable of averages by group can hide that one group is tiny (lecture 7)

{% enddetails %}

{% details Science, not vibes %}

- GE Goal 3: a number is a measurement with a method
- Report: "median attendance 42 (n = 18); mean 61 because of one festival"
- A chart from lecture 5 (histogram or sorted column) is the picture of the same claim
- Dropping the festival without saying so is not "cleaning"; it is a different dataset

{% enddetails %}

## Statistical functions in Excel

{% details A starter set (Ch. 8) %}

| Question | Function | Note |
| --- | --- | --- |
| Typical value | `AVERAGE`, `MEDIAN` | Blanks vs zeros (lecture 4) |
| Spread | `STDEV.S` (sample), `STDEV.P` (whole population) | For a class of *these* students, sample vs population is a judgment |
| Position | `MIN`, `MAX`, `QUARTILE.INC` / `PERCENTILE.INC` | Know inclusive vs exclusive if the textbook distinguishes them |
| Count in a band | `COUNTIFS` | "How many between 0.7 and 0.8?" |
| Rank | `RANK.EQ` | Ties |

{% enddetails %}

{% details STDEV.S vs STDEV.P %}

- Sample (`S`): you have some of the rows, infer spread
- Population (`P`): this list *is* the whole set you care about
- For a single course roster, instructors often treat the roster as the population — say which you used
- Copilot may pick `.P` or `.S` at random; you choose from the question

{% enddetails %}

{% details Check a tiny list by hand %}

- Data: `2, 4, 4, 4, 5, 5, 7, 9`
- Median, mean, and a rough sense of spread on paper
- Then Excel — if they disagree, your range includes a header or a total row

{% enddetails %}

## What Copilot is and is not

{% details A practical definition %}

- Copilot in Microsoft 365 is a language model wired into Excel, Word, PowerPoint, and Outlook
- It predicts useful text and formulas from your prompt and (sometimes) the file context
- It does **not** know whether `STDEV.S` matches your scientific claim
- It does **not** replace SLO5: you determine correctness

{% enddetails %}

{% details Strengths %}

- Remembering syntax (`PERCENTILE.INC` vs older `PERCENTILE`)
- Explaining a formula you do not yet read fluently
- Drafting a caption or data-dictionary stub in Word
- Suggesting a PivotTable layout from a stated question

{% enddetails %}

{% details Failure modes you should expect %}

- Invents a column that is not in the sheet
- Mixes up relative and absolute references
- Treats IDs as numbers, dates as text, or percents as already-multiplied values
- Sounds confident while being wrong (fluency ≠ accuracy)
- Picks `STDEV.P` when you meant a sample — or the reverse

{% enddetails %}

## Draft, explain, verify

{% details The same loop as every Excel week %}

```mermaid
flowchart LR
  Q[Your question] --> P[Prompt]
  P --> D[Draft formula or text]
  D --> E[Explain it back in your words]
  E --> V[Verify on known rows]
  V --> K[Keep, fix, or discard]
```

- If you cannot explain the draft, you do not understand the solution yet
- If it fails the known list (`2,4,4,4,5,5,7,9`), it is not done

{% enddetails %}

{% details Verify like a lab %}

- Keep a **known example**: tiny list or one student computed by hand
- Test a **boundary**: exact 70%, blank, zero
- Test a **type trap**: ID with a leading zero
- Change one input; confirm the output moves in the direction you expect

{% enddetails %}

{% details Prompts that help %}

1. **Question**: median lab score for on-time rows, or `STDEV.S` of `Weighted`
2. **Shape**: Table name, column headers, types
3. **Success**: "Match the paper median of the Checks list; ignore the Totals row"

- Weak: "Do stats on this sheet"
- Stronger: "Table `Scores`, column `Weighted` (numbers 0–1). `MEDIAN` and `STDEV.S` of that column only, not the Totals row. Explain sample vs population in one sentence."

{% enddetails %}

{% details Copilot in Word and PowerPoint %}

- Word: turn the stats into a methods + results paragraph; you still own the numbers
- PowerPoint: three slides (question, distribution, caveat) — no invented statistics
- Ask Copilot to *outline*; you paste values from Excel yourself

{% enddetails %}

## Academic integrity

{% details Allowed in this course (unless an exam says otherwise) %}

- Using Copilot to learn syntax and to draft formulas you then test
- Pasting a generated formula *after* you can explain it and after it matches your checks
- Citing assistance in a brief note when the assignment asks how you worked

{% enddetails %}

{% details Not allowed %}

- Submitting a workbook you cannot explain in office hours
- Generating an entire project and turning it in unreviewed
- Using Copilot during a closed-resource Excel exam
- Presenting Copilot's prose as your reflection without revision (GE Goal 1a)

{% enddetails %}

## Try this in Microsoft 365

{% details Lab 12 — Describe a distribution %}

1. On `Scores[Weighted]`, compute `n` (`COUNTA` or `COUNT`), `AVERAGE`, `MEDIAN`, `MIN`, `MAX`, `STDEV.S`
2. Hand-check median on a **copy** of 7 values in `Checks`
3. One-sentence result + caveat in Word (outlier? missing zeros?)
4. Optional: quartile box or a simple column chart of sorted totals (lecture 5)

{% enddetails %}

{% details Lab 13 — Audit a generated formula %}

1. Ask Copilot for nested `IF` letter grades from `Weighted` **or** for a `COUNTIFS` band
2. Paste into a **new** column, not over working formulas
3. Hand-compute two students and the tiny `Checks` list
4. Find at least one bug or ambiguity (boundaries, rounding, Totals row, `.P` vs `.S`)
5. Fix it yourself; comment: what Copilot got wrong
6. Close the assistant; write the explanation of the *fixed* formula from memory

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- If Copilot and your hand calculation disagree, which do you trust first?
- How is this different from asking a classmate to "just send the file"?

{% enddetails %}

## Takeaways

{% details Carry these into Python %}

- Mean, median, and spread are different claims; say which you computed
- Copilot is a productivity tool inside the question → check loop
- Fluency is not correctness; known rows and boundaries are
- Next: when the same Excel steps must run every week, Python repeats a *verified* analysis

{% enddetails %}

{% details Placeholder notes for expansion %}

- Histogram / `FREQUENCY` if the textbook covers it
- Screenshots of Excel Copilot vs formula bar
- Department AI-use statement, if updated

{% enddetails %}