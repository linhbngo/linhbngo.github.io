---
layout: lecture
pretty_table: true
collection: csc112
order: 7
title: "Datasets and Tables"
description: "A Table is a living rectangle: structured references, sort, filter, and formatting that follows the data."
mermaid:
  enabled: true
  zoomable: true

toc:
  - name: This week
  - name: Objectives
  - name: From range to Table
  - name: Structured references
  - name: Sort, filter, and views
  - name: Conditional formatting
  - name: Try this in Excel
  - name: Takeaways
---

## This week

Week 6 · Excel Ch. 4 · Excel Project 6. Next: PivotTables (lecture 7). Exam 1 is after that block.

## Objectives

{% details After this lecture you should be able to %}

- Convert a clean rectangle into an Excel Table and name it
- Write a formula with structured references (`[@column]`)
- Sort and filter without destroying the source order (or keep a `source_order` column)
- Apply conditional formatting as a *finding tool*, not as decoration

{% enddetails %}

## From range to Table

{% details Why Tables exist %}

- Lecture 2 asked for a rectangle: one header, one observation per row
- **Insert → Table** (`Ctrl/Cmd + T`) tells Excel: this rectangle is a dataset
- New rows inherit formulas, formatting, and chart source (if the chart is based on the Table)
- Totals row is optional and stays *outside* the observations — unlike a `SUM` row mixed into the list

{% enddetails %}

{% details Table hygiene %}

- Unique, short headers: `date`, `category`, `attendance` — not `Attendance (see notes!!!)`
- No merged cells, no blank header cells
- One Table per data region; do not stack two datasets in one Table
- Name the Table (`Table Design → Table Name`): `Events`, `Scores` — you will thank yourself in PivotTables

{% enddetails %}

{% details Freeze and print are not the data model %}

- Freeze header row so the variables stay visible
- Print titles (Page Layout) for paper; that is presentation, not analysis
- Keep a `Notes` sheet for the question and data dictionary

{% enddetails %}

## Structured references

{% details Formulas that name columns %}

- Old: `=B2*$F$1+C2*$G$1`
- Table: `=[@Quiz]*W_Quiz+[@Project]*W_Project+[@Exam]*W_Exam`
- `[@Quiz]` means "this row's Quiz"
- `Scores[Quiz]` means "the whole Quiz column"
- `SUM(Scores[Quiz])` does not break when you add a student

{% enddetails %}

{% details Fill-down becomes automatic %}

- Enter the formula in one Table column; Excel fills the column
- If it does not, check that you are actually in a Table (filter buttons on the header)
- Still hand-check **one row** (lecture 3) — Tables do not make the algorithm correct

{% enddetails %}

## Sort, filter, and views

{% details Filter is a question %}

- Filter `category = Film` is "only these observations"
- `AVERAGE` of a filtered column may still include hidden rows depending on the function (`SUBTOTAL` vs `AVERAGE`)
- `SUBTOTAL` / `AGGREGATE` respect filters; plain `SUM` often does not — know which you clicked
- Clear filters before you declare a class-wide total

{% enddetails %}

{% details Sort is a view %}

- Sort by date, then by attendance
- Custom sort for categories that are not alphabetical (`Freshman`, `Sophomore`, …)
- If you need the original order back, keep an `id` or `source_row` column
- Sorting does not replace a PivotTable when you want grouped totals (next lecture)

{% enddetails %}

{% details Slicers %}

- Visual filters for Tables (and later PivotTables)
- Good for a dashboard sheet; still a filter — say what is sliced in the caption

{% enddetails %}

## Conditional formatting

{% details Highlight to discover, then write the finding %}

- Color scales on `Weighted` show spread
- Highlight cells `< 0.7` to find `Review` candidates — then confirm with the `IF` column
- Data bars are a tiny chart in the cell
- Do not color the whole sheet "for professionalism"; it hides the data rectangle

{% enddetails %}

{% details Rules are formulas too %}

- A rule "cell value < `$F$1`" uses the same `$` thinking as lecture 3
- Applies to a range: if you insert rows in a Table, rules often expand
- Duplicate values rule: catch double-submitted IDs

{% enddetails %}

## Try this in Excel

{% details Lab 6 — Table-ize the gradebook %}

1. Convert the score rectangle to a Table named `Scores`
2. Rewrite the weighted total with structured references (absolute names or `$` for weights still OK)
3. Add a Totals row: `AVERAGE` of `Weighted` — compare to a hand `AVERAGE` of the visible column
4. Filter to one section (or one `Status`); compare `SUM` vs `SUBTOTAL` of `Weighted`
5. Conditional formatting: highlight `Weighted < 0.7`
6. Sort by `Weighted` ascending; confirm `id` is still unique
7. Re-point last week's chart at the Table summary (or a second summary Table)

{% enddetails %}

{% details Lab 6b — Word data dictionary, updated %}

- For each Table column: name, type, missing-value rule
- One line: "Filters change what `SUBTOTAL` sees; they do not change the stored rows"

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- When would you duplicate a sheet as `Scores_archive` before a destructive sort?
- How is a Table different from "I put filter buttons on a random range"?

{% enddetails %}

## Takeaways

{% details Carry these into Pivot week %}

- A Table is the dataset Excel can grow with
- Structured references name columns; you still check a row
- Filter/sort are views; `SUBTOTAL` vs `SUM` matters
- Next: PivotTables ask grouped questions without destroying the Table

{% enddetails %}

{% details Placeholder notes for expansion %}

- Remove Duplicates vs conditional-format duplicates
- Power Query as "Table from CSV with a refreshable recipe"
- Screenshot: Table Design ribbon

{% enddetails %}