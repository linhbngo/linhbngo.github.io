---
layout: lecture
pretty_table: true
collection: csc112
order: 6
title: "Charts as Arguments"
description: "A chart makes one claim. Choose a type, title the claim, and keep it linked to the data."
mermaid:
  enabled: true
  zoomable: true
chart:
  chartjs: true

toc:
  - name: This week
  - name: Objectives
  - name: A chart is a sentence
  - name: Choosing a chart type
  - name: Design that does not lie
  - name: Charts in Word and PowerPoint
  - name: Try this in Excel
  - name: Takeaways
---

## This week

Week 5 · Excel Ch. 3 · Excel Project 5. Next: datasets and Tables (lecture 6).

## Objectives

{% details After this lecture you should be able to %}

- State the one claim a chart is supposed to support
- Match that claim to a chart type (column, bar, line, scatter — and when *not* pie)
- Title axes and the chart with words a reader can check against the sheet
- Paste into Word or PowerPoint as a linked object when the story should update

{% enddetails %}

## A chart is a sentence

{% details Not decoration %}

- Bad title: `Chart 1`, `Attendance`, `Sheet1`
- Better title: `Club events: film nights drew more attendees than workshops in September`
- If you cannot finish that sentence, you are not ready to Insert → Chart
- The data rectangle from lecture 2 is the evidence; the chart is the argument (GE Goal 1c / 1d)

{% enddetails %}

{% details Question → series → chart %}

```mermaid
flowchart LR
  Q[Question] --> R[Summary range or Table]
  R --> C[Chart]
  C --> S[One sentence under the chart]
```

- Often you chart a **summary** (`COUNTIF` of `Review` vs `OK`), not every student ID
- A column of 40 names is a table, not a chart
- Last week's `Status` column is a good source for a two-bar comparison

{% enddetails %}

## Choosing a chart type

{% details Start from the comparison %}

| You want to show | Usually use | Avoid |
| --- | --- | --- |
| Categories vs a number | Column or bar | 3-D column |
| Change over time | Line (time on x) | Category axis that is not in order |
| Relationship of two numbers | Scatter | Line connecting unordered IDs |
| Parts of **one** whole, few slices | Pie, maybe | Pie for many categories or for comparing two years |
| Distribution | Histogram / box (if available) | A pie of bins you made by hand without saying so |

{% enddetails %}

{% details Pie charts are a special case %}

- They encode parts of a single total
- Humans compare angles poorly; a bar chart is usually clearer
- Never: pie of "sales by month" (not a part-whole of one moment)
- If you use one: few slices, labeled with values, no 3-D explosion

{% enddetails %}

{% details Combo charts and two axes %}

- Two vertical axes can make a small series look huge
- If you use a secondary axis, say so in the caption
- Default instinct: two charts, or index both series to a common scale

{% enddetails %}

## Design that does not lie

{% details Honest defaults %}

- Start column/bar axes at zero unless you have a written reason not to
- Time goes left → right; sort the Table first
- One color story: data vs highlight, not a rainbow of categories
- Gridlines light; data labels only when they do not collide
- Excel Ch. 3: chart styles and layouts are costumes — they do not fix a wrong type

{% enddetails %}

{% details Sparklines %}

- Mini line/column inside a cell: trend per row
- Good for "each section's weekly attendance" next to the name
- Still need a full chart when the claim is the point of a slide

{% enddetails %}

{% details Source and refresh %}

- Click the chart: which range is highlighted?
- If you add rows, a **Table** as the source (next lecture) expands; a static `A1:B6` does not
- Moving a chart to a `Charts` sheet is fine; keep the data on `Data`

{% enddetails %}

## Charts in Word and PowerPoint

{% details Linked vs picture %}

- **Linked** (Paste Special → keep source formatting / link): updates when the workbook changes
- **Picture**: a frozen snapshot — use when you email a deck without the `.xlsx`
- Say in a footnote which one you used
- Never type a number on a slide that is not in the workbook

{% enddetails %}

{% details Caption in Word %}

- One sentence: claim + caveat ("September only; waitlist not counted")
- That caption is the analysis; the figure is evidence
- Same habit as a lab report (GE Goal 3)

{% enddetails %}

## Try this in Excel

{% details Lab 5 — Chart one claim %}

1. From the gradebook or event Table, build a two-column summary (`Status` | `Count`) with `COUNTIF`
2. Insert a **clustered column** chart (not 3-D, not pie)
3. Chart title = the claim in words
4. Vertical axis title = `Number of students` (or events)
5. Move the chart to a `Charts` sheet; leave the summary next to the data or on `Summary`
6. Paste the chart into a blank PowerPoint slide as a **link**; change one source count; refresh and confirm the slide intent
7. In Word, write the caption sentence including one limitation

{% enddetails %}

{% details Lab 5b — A chart that should not exist %}

- Chart every student ID vs weighted total as a pie
- Write three reasons this fails (part-whole? too many slices? IDs are not a composition?)
- Replace it with a column of counts or a histogram-style bin chart if you have bins

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- When is a table clearer than a chart?
- If Copilot "makes a chart," what do you inspect first: type, source range, or title?

{% enddetails %}

## Takeaways

{% details Carry these into Tables week %}

- One claim per chart; title the claim
- Type follows the comparison; pie is rarely the answer
- Link to Word/PowerPoint when the numbers still live in Excel
- Next lecture: Tables so charts, filters, and formulas keep up when rows are added

{% enddetails %}

{% details Placeholder notes for expansion %}

- Screenshot: Select Data dialog
- Histogram / Pareto if the Excel 365 version includes them
- Accessibility: don't rely on color alone

{% enddetails %}