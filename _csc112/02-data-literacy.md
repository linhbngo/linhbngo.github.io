---
layout: lecture
pretty_table: true
collection: csc112
order: 3
title: "Data Literacy Before Excel"
description: "Ask a question, name the rows and columns, and clean types before you SUM anything."
mermaid:
  enabled: true
  zoomable: true

toc:
  - name: A spreadsheet is a model of the world
  - name: Rows, columns, and a question
  - name: Messy data is the default
  - name: Ethics and what gets counted
  - name: Try this in Excel
  - name: Takeaways
---

## A spreadsheet is a model of the world

{% details Excel is not a poster %}

- Color, clip art, and merged title cells can make a sheet look finished
- Analysis needs a **rectangle of data**: one header row, one observation per row, one variable per column
- If the sheet is laid out for printing, it is often a poor layout for formulas, charts, and PivotTables

{% enddetails %}

{% details Two sheets, two jobs %}

| Sheet role | Looks like | Good for |
| --- | --- | --- |
| Data | Plain table, no merged cells | Formulas, sorts, pivots, Python later |
| Presentation | Titles, colors, charts, Word/PowerPoint paste | Humans reading a story |

- Keep them separate when you can
- This is the same idea as "content vs slide design" in PowerPoint

{% enddetails %}

{% details A running example %}

Question: *Among these campus events, which category had the highest attendance in September?*

You cannot answer that until you know:

- What is one row? (one event? one ticket? one day?)
- What does `Attendance` include? (students only? no-shows?)
- What timezone or calendar is `Date` using?

{% enddetails %}

## Rows, columns, and a question

{% details Vocabulary %}

- **Observation / record**: one row (one student, one sale, one sensor reading)
- **Variable / field**: one column (id, date, amount, section)
- **Value**: the typed contents of one cell
- **Missing**: blank is not the same as zero, and not the same as `"N/A"`

{% enddetails %}

{% details Write the question in a cell %}

- Put the question in `A1` of a `Notes` sheet, in a Word outline, or in the assignment header
- Good: "What is the average lab score for students who submitted on time?"
- Vague: "Do something with this spreadsheet"
- SLO1 starts here: comprehend the problem before designing the solution

{% enddetails %}

{% details Units and definitions %}

- `Time` in minutes or hours?
- `Cost` with or without tax?
- `Grade` as percent or letter?
- If two people use different definitions, both can "calculate correctly" and still disagree

{% enddetails %}

## Messy data is the default

{% details Classic spreadsheet problems %}

- Header in row 1 *and* a title in row 1 of a merged range
- Blank rows used as visual spacing
- Numbers stored as text (`'15` or a leading apostrophe)
- Dates typed as `Fall 26` (text) instead of a real date
- Two variables in one column (`"MW 3:00 UNA 161"`)
- Totals mixed into the data (`SUM` rows in the middle of a list)

{% enddetails %}

{% details Why this is a science issue, not just a software issue %}

- GE Goal 3: quantitative methods only work if the measurements mean what you think they mean
- A tidy table is closer to a lab notebook than to a flyer
- Garbage in, formatted-nicely garbage out

{% enddetails %}

{% details CSV is a lowest-common-denominator file %}

- CSV = comma-separated values: plain text, not an Excel workbook
- Opening a CSV in Notepad/TextEdit shows the raw observations
- Opening it in Excel *interprets* types (and can mangle ZIP codes and dates)
- Later, Python will read the same CSV with different default guesses
- Always check a few rows after import

{% enddetails %}

## Ethics and what gets counted

{% details Data literacy includes what is missing %}

- Who is not in the dataset?
- Was participation voluntary?
- Can a person be identified from a "anonymous" sheet (name + section + rare major)?
- Course work: do not publish real student identifiers; use sample or de-identified files

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- If a club spreadsheet omits events with zero attendance, what happens to the average?
- When is it honest to drop a row, and when is it cooking the data?

{% enddetails %}

## Try this in Excel

{% details Lab 2 — From messy grid to Table %}

1. Download (or type) a small messy list: extra title row, mixed date formats, a blank row, a total row
2. Delete the decorative title from the data rectangle (move it to a `Notes` sheet)
3. Remove blank rows and the total row from the data
4. Make sure each column has a short, unique header (`date`, `category`, `attendance`)
5. Select the rectangle → **Insert → Table** (or `Ctrl/Cmd + T`)
6. Set column types: Date, Number, Text
7. Sort by date; filter one category
8. On a `Notes` sheet, write one sentence: the question this table could answer, and one it cannot

{% enddetails %}

{% details Lab 2b — Import a CSV without trusting Auto %}

- Data → From Text/CSV
- Check the preview: did Excel turn IDs into numbers?
- If needed, set the ID column to Text before loading
- Save as `.xlsx` so you keep Table formatting; keep the original CSV as the raw source

{% enddetails %}

{% details Optional Word companion %}

- In Word, write a 5-line **data dictionary**: column name, type, allowed values, missing-value code
- That document is the specification your Excel (and later Python) work should obey

{% enddetails %}

## Takeaways

{% details Carry these into formulas week %}

- Question first, table second, formula third, chart last
- One observation per row; one variable per column; no totals inside the data
- Types and missing values are part of the science, not housekeeping
- Next lecture: formulas as reusable thinking (relative vs absolute references)

{% enddetails %}

{% details Placeholder notes for expansion %}

- Screenshot set: bad "report layout" vs good Table
- One historical cautionary tale (spreadsheet error) as a reading
- Power Query mention only as a "later, if we have time" cleaner

{% enddetails %}
