---
layout: lecture
pretty_table: true
collection: csc112
order: 5
title: "Functions and Logical Expressions"
description: "Functions are named algorithms. IF is a decision you can test at the boundary."
mermaid:
  enabled: true
  zoomable: true

toc:
  - name: This week
  - name: Objectives
  - name: Functions are named algorithms
  - name: Counting and aggregating
  - name: Decisions with IF
  - name: Combining conditions
  - name: Try this in Excel
  - name: Takeaways
---

## This week

Week 4 · Excel Ch. 2 (functions) · Excel Project 4. Next: charts (lecture 5).

## Objectives

{% details After this lecture you should be able to %}

- Match a question to a function family (`SUM` vs `AVERAGE` vs `COUNT`)
- Write an `IF` (or `IFS`) you can explain, including the boundary
- Use `AND` / `OR` without guessing what Excel treats as TRUE
- Prefer a helper column you can check over an unreadable nested formula

{% enddetails %}

## Functions are named algorithms

{% details A function takes arguments and returns a value %}

- `SUM(B2:B20)` means: *add the numbers in this range*
- You do not open the box; you do need to know what the box assumes (types, blanks)
- Last week you wrote the algorithm yourself; this week you call a named one
- Syntax: `=NAME(argument1, argument2, …)` — the `=` is still "this is an instruction"

{% enddetails %}

{% details You do not memorize the catalog %}

- Learn to name the *question*, then look up the function
- Formula bar autocomplete and Formulas → Insert Function are legitimate tools
- Copilot can remind you of names; you still test the result (lecture 9)
- Lookups (`XLOOKUP`) wait until lecture 8; stats (`MEDIAN`, `STDEV`) wait until lecture 9

{% enddetails %}

## Counting and aggregating

{% details Which question are you asking? %}

| Question | Function | Watch out |
| --- | --- | --- |
| Total of a quantity | `SUM` | Text "numbers" are skipped or error |
| Typical value | `AVERAGE` | Blanks vs zeros change the story |
| Smallest / largest | `MIN` / `MAX` | Dates and numbers mixed = nonsense |
| How many numeric scores? | `COUNT` | Ignores text labels |
| How many filled cells? | `COUNTA` | Counts `"N/A"` as present |
| How many empty? | `COUNTBLANK` | Spaces are not blank |
| Total if a condition holds | `SUMIF` / `SUMIFS` | Criteria types (`">=10"` vs a cell) |

{% enddetails %}

{% details AVERAGE is a scientific claim %}

- Mean of `{10, 10, 10, 100}` is pulled by the 100
- Zeros that mean "missing" drag the mean down; they should perhaps be blank
- Lecture 2: if the club omitted zero-attendance events, `AVERAGE` is already biased
- Next week a chart of the raw values will often show what the mean hides

{% enddetails %}

## Decisions with IF

{% details Logic is still an algorithm %}

- Words: "If attendance is at least 10, label `Viable`, else `Too small`"
- Excel: `=IF(B2>=10,"Viable","Too small")`
- Structure: `IF(condition, value_if_true, value_if_false)`
- The condition is a Boolean (lecture 1): `TRUE` / `FALSE`, not the text `"TRUE"`

{% enddetails %}

{% details Test the boundary %}

- For `>=10`, the rows that matter are `9`, `10`, and blank
- Write those three cases on a `Checks` sheet *before* filling the column
- Off-by-one here is how people "fail" with a 69.9 when the rule was 70
- Rounding: `=IF(ROUND(B2,2)>=0.70,…)` if the rule is two decimal places

{% enddetails %}

{% details Nested IF vs IFS vs a table %}

- Nested `IF`s get hard to audit after three levels
- `IFS(test1, result1, test2, result2, …)` is flatter, still needs a final catch-all
- A small grade-band table plus a lookup (lecture 8) is often clearer than six `IF`s
- Helper column: compute `pass` as `TRUE`/`FALSE`, then a second column for the label — easier to check

{% enddetails %}

## Combining conditions

{% details AND, OR, NOT %}

- `AND(A2>=0.7,B2>=0.7)` — both must hold
- `OR(A2="Review",B2="Missing")` — either holds
- `NOT(ISBLANK(C2))` — sometimes clearer than double negatives
- Empty cell in a comparison: Excel often treats blank as `0`, which can make `B2>=10` unexpectedly `FALSE` or `TRUE`

{% enddetails %}

{% details Common traps %}

- `=IF(A2=70 or A2=80, …)` is not Excel syntax; use `OR(A2=70,A2=80)`
- `"TRUE"` (text) is not `TRUE` (Boolean) — `IF` may not branch how you think
- `IF` returning `""` looks blank but `COUNTA` still counts it — know which you want

{% enddetails %}

## Try this in Excel

{% details Lab 4 — Status column on last week's weighted total %}

1. Reopen the weighted-total workbook
2. `Status = IF([@Weighted]<0.7,"Review","OK")` (or ordinary cell refs if you are not in a Table yet)
3. Checks sheet: one student clearly below, one exactly `0.70`, one blank weighted cell
4. Add `Flag = AND([@Quiz]<0.6,[@Exam]<0.6)` — "weak on both"
5. Use `COUNTIF` to count `Review` — compare to a filter you can see
6. Optional: nested `IF` or `IFS` for letter bands; write the bands in words first

{% enddetails %}

{% details Lab 4b — Read the function, then hide it %}

- Pick `AVERAGE` of a column that includes one blank and one zero
- In Word: one sentence on whether blank and zero *should* mean the same thing in this dataset
- That sentence is the analysis; the function is just arithmetic

{% enddetails %}

{% details Discussion %}

- Designate a note-taker
- Should a student at exactly 70% be `OK` or `Review`? Who decides — the formula or the syllabus rule?
- When is a nested `IF` a smell that you wanted a lookup table?

{% enddetails %}

## Takeaways

{% details Carry these into charts week %}

- Name the question, then pick the function
- `IF` is a decision; boundaries and blanks are part of the test plan
- Helper columns you can see beat clever one-liners you cannot check
- Next lecture: a chart should argue one claim, not dump every column

{% enddetails %}

{% details Placeholder notes for expansion %}

- `SUMIF`/`COUNTIF` mini-lab as a bridge to PivotTables
- Error-aware `IFERROR` — teach last, so it does not hide type bugs
- Grade-band table preview of `XLOOKUP`

{% enddetails %}