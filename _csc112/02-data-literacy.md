---
layout: lecture
pretty_table: true
collection: csc112
order: 3
title: "Data Literacy Before Excel"

mermaid:
  enabled: true
  zoomable: true

toc:
  - name: A spreadsheet is a model of the world
  - name: Rows, columns, and a question
  - name: Messy data is the default
  - name: What gets counted
  - name: Try this in Excel
  - name: Takeaways
---

## A spreadsheet is a model of the world

{% details Excel is not a poster %}

- A spreadsheet is useful because it turns part of the world into a **rectangle of observations and variables**
- Analysis works best with one header row, one observation per row, and one variable per column
- A sheet can look clean and still contain ambiguous, missing, or incorrect data
- Formatting can make data easier to read; it cannot make bad measurements correct

{% enddetails %}

{% details Our running dataset: Open Food Facts %}

- For this lecture we will use an extract from **Open Food Facts**, a community-contributed database of food products.
  - `4,535,554` rows from raw text data. 
  - a csv file containing `10,000` random samples (and a smaller portions of columns) was created. 
- [Typical fields](https://github.com/openfoodfacts/api-documentation/issues/64) in the extract include things such as:
  - a product identifier such as `code` / barcode
  - `product_name`
  - `brands`
  - `quantity` or serving information
  - product/category text
  - nutrition measurements such as calories, fat, sugar, or protein per 100 g

This is useful precisely because it is **real data entered and maintained by people**. Some fields are complete and standardized; others may be missing, inconsistent, or questionable.

{% enddetails %}

{% details Before writing a formula %}

- What is one row?
- Is a barcode a number or an identifier?
- Is sugar measured per serving, per package, or per 100 g?
- What does a blank sugar value mean?
- Are all products equally well documented?

The spreadsheet cannot answer a question until we understand what its cells represent.

{% enddetails %}

## Rows, columns, and a question

{% details Vocabulary using the food data %}

- **Observation / record**: one row representing one product record
- **Variable / field**: one column, such as product name, barcode, quantity, or sugar per 100 g
- **Value**: the contents of one cell for one product and one variable
- **Identifier**: a value used to distinguish records; it may contain only digits without being a quantity
- **Missing**: a value that was not recorded or is not available

Important:

> A blank cell is not automatically zero.

{% enddetails %}

{% details What exactly is one row? %}

At first glance, one row may look like "one food."

A better description is:

> **One row is one product record identified by a product code/barcode.**


- Two package sizes of a similar product may have different barcodes
- Similar products from different brands are different records
- A product record is not the same thing as a unique type of food

When we later count rows, we are counting **records**, not necessarily distinct foods in the everyday sense.

{% enddetails %}

{% details A barcode looks numeric — but is it a number? %}

A barcode may contain only digits.

But ask what arithmetic would mean:

- barcode + barcode?
- average barcode?
- twice a barcode?

Those calculations make no sense.

So a barcode is better treated as **Text / an identifier**, even if every character is a digit.

This is the same reason ZIP codes and student IDs should usually not be treated as measurements.

{% enddetails %}

{% details Units and definitions %}

Compare these possible fields:

| Field | Looks like | What it really means |
| --- | --- | --- |
| `code` | digits | identifier |
| `product_name` | text | product label/name |
| `quantity` | `340 g`, `12 oz`, etc. | amount **plus a unit** |
| sugar per 100 g | number | standardized measurement |
| serving size | number/text | amount whose meaning depends on the unit |

The number alone is not enough. **Units are part of the data.**

A value of `12` could mean 12 g, 12 oz, 12 servings, or something else entirely.

{% enddetails %}

{% details Write the question before the formula %}

Good:

> "For products with a reported sugar-per-100-g value, how much sugar would a 30 g portion contain?"

Less useful:

> "Do something with this spreadsheet."

The first question tells us:

- which column matters
- what unit we need
- what calculation we expect
- which rows may not be answerable because data are missing

SLO1: comprehend the problem before designing the solution.

{% enddetails %}

## Messy data is the default

{% details Real-world mess is often inside the cells %}

This dataset may already look like a clean rectangle. That does **not** mean the data are clean.

Look for problems such as:

- missing product names or nutrition values
- inconsistent capitalization or spelling in text fields
- multiple ideas stored inside one text field
- quantities that combine a number and a unit
- products using different serving sizes
- values that look numeric but are actually identifiers
- suspicious or impossible-looking nutrition values caused by entry errors

The hard part is often not fixing the spreadsheet layout. It is deciding what the values mean.

{% enddetails %}

{% details Missing does not mean zero %}

Suppose `sugars_100g` is blank for a product.

Possible meanings include:

- nobody entered the value
- the nutrition label was unavailable
- the contributor skipped that field
- the product record is incomplete

It does **not** necessarily mean the food contains zero sugar.

This becomes important when Excel performs arithmetic: a formula can produce a perfectly valid-looking number from an invalid assumption.

{% enddetails %}

{% details Standardized fields are easier to compare %}

A field measured **per 100 g** gives us a common denominator.

That means two products with different package sizes can still be compared using the same unit.

By contrast:

- `quantity = 12 oz`
- `quantity = 340 g`

cannot be compared directly without interpreting and converting the units.

Standardization is part of the model, not merely formatting.

{% enddetails %}

{% details Community-contributed data can contain errors %}

Open Food Facts is useful because it reflects how real datasets are created:

- people contribute records
- some products receive more attention than others
- contributors can interpret labels differently
- fields can be left blank
- data-entry mistakes can occur

A value being present in a spreadsheet does not guarantee that it is correct.

`Does this value make sense in the real world?`

{% enddetails %}

{% details Raw data versus presentation %}

Keep different jobs separate when possible.

| Sheet role | Purpose |
| --- | --- |
| `Raw` | Preserve the original downloaded data |
| `Work` | Make formatting changes and add calculations |
| `Notes` | Record the question, definitions, assumptions, and observations |

The `Raw` sheet is evidence of where you started.

Do not "clean" the only copy and then forget what was changed.

{% enddetails %}

## What gets counted

{% details This is not a random sample of every food people eat %}

A community-contributed product database reflects what has been entered into it.

Ask:

- Which products are included?
- Which products are missing?
- Are popular brands more completely documented?
- Are some countries, stores, or categories represented more heavily than others?
- Are products with missing nutrition information systematically different from products with complete information?

A large dataset can still be an incomplete picture of the world.

{% enddetails %}

{% details Records are not necessarily foods, purchases, or people %}

If the dataset contains 10,000 rows, we can safely say:

> "This extract contains 10,000 product records."

We should **not** automatically say:

- "These are the 10,000 most common foods"
- "These represent what 10,000 people eat"
- "These are 10,000 unique kinds of food"

Those claims require information the rows do not provide.

{% enddetails %}


## Try this in Excel

{% details Guided exercise — Inspect before calculating %}

Work with the provided Open Food Facts workbook.

1. Rename the original worksheet `Raw`.
2. Make a copy of it and rename the copy `Work`.
3. Add a third worksheet named `Notes`.
4. In `Notes!A1`, write:
   - **Question:** `For products with a reported sugar-per-100-g value, how much sugar would a 30 g portion contain?` 
5. In the `Work` sheet, identify:
   - the product identifier column
   - the product-name column
   - one text field
   - one numeric nutrition field
   - at least one column containing missing values
6. Adjust column widths and use **Wrap Text** where needed so the records are readable.
7. Format the product identifier/barcode column as **Text**.
8. Format nutrition measurements as **Number** with a sensible number of decimal places.

Do not delete rows simply because they look inconvenient.

{% enddetails %}

{% details Guided formula — Normalize to a 30 g portion %}

Suppose a product reports sugar as grams per 100 g.

Insert a new column named something like:

`Sugar_in_30g`

For the first product row with a valid sugar value, create a formula equivalent to:

```text
=sugar_per_100g_cell*30/100
```

Then use the **fill handle** to copy the formula down the column.

This uses only:

- cell references
- multiplication
- division
- copied formulas

Now inspect the results carefully.

{% enddetails %}

{% details The important failure case %}

Find a row where the original sugar-per-100-g value is blank.

Ask:

- What result did the copied formula produce?
- Does that result mean the product contains zero sugar?
- Is the formula wrong, or is our assumption wrong?

This is the key lesson:

> **A spreadsheet can calculate correctly from data that do not support the conclusion.**

We will learn more sophisticated formula techniques later. For now, recognizing the problem is the important skill.

{% enddetails %}

{% details Build a small presentation sheet %}

Create a worksheet named `Example`.

1. Copy the headers and about 5–10 interesting product rows from `Work`.
2. Include the original sugar-per-100-g value and your calculated 30 g value.
3. Add a descriptive title above the copied range.
4. Adjust widths, alignment, number formats, borders, and font emphasis so the result is easy to read.

Compare the jobs:

- `Raw` preserves the source
- `Work` supports calculation
- `Example` communicates a small result to a human reader

{% enddetails %}

{% details Notes sheet — What can and cannot be concluded? %}

In the `Notes` sheet, write two sentences:

**Can answer:**

> "For records with valid sugar-per-100-g data, we can calculate the sugar content of a standardized 30 g portion."

**Cannot answer from this dataset alone:**

> "Which product is healthiest?"

Why not?

"Healthiest" requires a definition and possibly variables that are not represented by one sugar calculation.

{% enddetails %}
