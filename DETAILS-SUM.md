# Distill `details` variants

Lecture, Distill, and other pages support collapsible blocks through the Liquid tag `{% details %}`. The first word of the tag is an optional **variant**. If it is not a known variant name, the whole string is used as the caption and the block is styled as `default`.

Markup is implemented in `_plugins/details.rb`. Colors come from `--global-details-*` tokens in `_sass/_themes.scss`. Shared chrome lives in `_sass/_details.scss` (global, not Distill-only). Distill/lecture articles only add `grid-column: text` in `_sass/_distill.scss`.

```liquid
{% details VARIANT Caption text %}
Body markdown goes here.
{% enddetails %}
```

The renderer emits (non-default variants include a visible label so the type is not color-only):

```html
<details class="details details--VARIANT" data-variant="VARIANT">
  <summary><span class="details-label">Label</span>Caption text</summary>
  …converted body…
</details>
```

Known variant names: `default`, `note`, `tip`, `warning`, `info`, `success`, `danger`, `comm`, `critical`, `career`, `tech`.

Palettes below are the **live** values as of 21 August 2026. They meet WCAG 2.2 AA for summary and body text in both themes (`python3 scripts/check_contrast.py`). See `ACCESSIBILITY.md` §7.

---

## Shared structure

Every variant uses the same chrome:

- Rounded panel, 8px / 12px padding, 6px radius
- 4px left border
- `<summary>` is the colored label; body text uses `--global-text-color` (`#000000` light, `#e8e8e8` dark)
- `:focus-visible` outline on `<summary>` in the theme accent
- Non-default variants prefix the caption with an uppercase `.details-label` (Warning, Communication, …)

Body contrast against every listed fill is ≥ 10:1 (AAA).

---

## Semantic variants

### `default`

Neutral collapsible. Used when the tag has no variant word, or when the variant is `default`. No `.details-label` is injected.

```liquid
{% details What happens when a program runs? %}
The process fetches, decodes, and executes instructions.
{% enddetails %}
```

| Theme | Summary | Background | Left border |
|---|---|---|---|
| Light | `#7a0676` | `#f4f4f4` | `#b509ac` |
| Dark | `#4ec3e0` | `#2c3237` | `#4ec3e0` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 9.03:1 | AAA |
| Light body | 19.09:1 | AAA |
| Dark summary | 6.31:1 | AA |
| Dark body | 10.59:1 | AAA |

---

### `note`

Annotation or aside that is not a tip, warning, or info callout. Distinct slate panel (not the default grey + purple edge).

```liquid
{% details note List comprehensions %}
…
{% enddetails %}
```

Label: **Note**. Hue: **slate**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#1f2937` | `#f3f4f6` | `#4b5563` |
| Dark | `#d1d5db` | `#25262b` | `#9ca3af` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 13.34:1 | AAA |
| Dark summary | 10.25:1 | AAA |

---

### `tip`

Optional extra help, a mnemonic, or a key point.

```liquid
{% details tip Key points %}
- Prefer measuring before optimizing.
{% enddetails %}
```

Label: **Tip**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#006f7c` | `#e0f7fa` | `#007a88` |
| Dark | `#99f6e4` | `#152e30` | `#5eead4` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 5.29:1 | AA |
| Dark summary | 11.37:1 | AAA |

---

### `warning`

Caution, a pitfall, or a prerequisite.

```liquid
{% details warning Episode prerequisites %}
Complete the slicing lab before this section.
{% enddetails %}
```

Label: **Warning**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#6b5900` | `#fff8d8` | `#8a7000` |
| Dark | `#fde68a` | `#2a2408` | `#fbbf24` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 6.44:1 | AA |
| Dark summary | 12.45:1 | AAA |

---

### `info`

Reference material, definitions, or “more detail.”

```liquid
{% details info uvmalloc %}
User-space allocation path in xv6.
{% enddetails %}
```

Label: **Info**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#1f5fbf` | `#eaf2ff` | `#1558c0` |
| Dark | `#8ab4ff` | `#1e2634` | `#8ab4ff` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 5.41:1 | AA |
| Dark summary | 7.27:1 | AAA |

---

### `success`

A solution, a completed check, or an acknowledgement.

```liquid
{% details success Solution %}
`ls -r` lists in reverse chronological order.
{% enddetails %}
```

Label: **Success**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#006b30` | `#e0f8ea` | `#007a33` |
| Dark | `#a7f3d0` | `#143326` | `#6ee7b7` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 5.97:1 | AA |
| Dark summary | 10.69:1 | AAA |

---

### `danger`

A serious error, unsafe operation, or destructive outcome.

```liquid
{% details danger Do not run rm -rf on / %}
This will destroy the workspace.
{% enddetails %}
```

Label: **Danger**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#990000` | `#ffe0e0` | `#cc0000` |
| Dark | `#fecaca` | `#3b1515` | `#fca5a5` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 7.22:1 | AAA |
| Dark summary | 11.13:1 | AAA |

---

## NACE competency variants

These four map to [NACE Career Readiness](https://www.naceweb.org/career-readiness/competencies/career-readiness-defined) competencies. Palettes stay on distinct axes from the semantic set (indigo, umber, wine, slate — not warning-yellow, info-blue, success-green, danger-red, or tip-cyan).

They are not a substitute for `warning` / `info` / `success`. Use them when the block is about that competency.

### `comm` — Communication

Written, oral, or visual communication: explaining a design, presenting, writing a report, giving feedback.

```liquid
{% details comm Explain the trade-off to a non-expert %}
State the constraint, the options, and the recommendation in three sentences.
{% enddetails %}
```

Label: **Communication**. Hue: **indigo**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#3730a3` | `#eef2ff` | `#4338ca` |
| Dark | `#c7d2fe` | `#1c2038` | `#a5b4fc` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 8.88:1 | AAA |
| Dark summary | 10.72:1 | AAA |

---

### `critical` — Critical thinking

Analysis, evaluation of evidence, debugging reasoning, comparing approaches.

```liquid
{% details critical Why is this schedule unsafe? %}
Identify the race, then name one ordering that breaks the invariant.
{% enddetails %}
```

Label: **Critical thinking**. Hue: **umber**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#7c2d12` | `#fff7ed` | `#9a3412` |
| Dark | `#fed7aa` | `#2a1d14` | `#fdba74` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 8.83:1 | AAA |
| Dark summary | 12.08:1 | AAA |

---

### `career` — Career and self-development

Professional growth, portfolios, internships, identity as a practitioner, reflecting on skills.

```liquid
{% details career What to put in a project write-up %}
Problem, your role, one technical decision, and evidence it worked.
{% enddetails %}
```

Label: **Career**. Hue: **wine / rose**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#831843` | `#fdf2f8` | `#9d174d` |
| Dark | `#fbcfe8` | `#2a1522` | `#f9a8d4` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 8.84:1 | AAA |
| Dark summary | 12.36:1 | AAA |

---

### `tech` — Technology

Tools, platforms, APIs, environments, and technical fluency (what to install, which library, how the stack is wired).

```liquid
{% details tech TensorFlow Lite conversion %}
Export SavedModel, convert with the TFLite converter, then validate on-device.
{% enddetails %}
```

Label: **Technology**. Hue: **slate**.

| Theme | Summary | Background | Border |
|---|---|---|---|
| Light | `#1e293b` | `#f1f5f9` | `#334155` |
| Dark | `#cbd5e1` | `#222830` | `#94a3b8` |

| Pair | Ratio | WCAG |
|---|---|---|
| Light summary | 13.35:1 | AAA |
| Dark summary | 10.00:1 | AAA |

---

## Quick reference

| Variant | Label | Light summary | Light fill | Dark summary | Dark fill | Caption contrast |
|---|---|---|---|---|---|---|
| `default` | (none) | `#7a0676` | `#f4f4f4` | `#4ec3e0` | `#2c3237` | AAA / AA |
| `note` | Note | `#1f2937` | `#f3f4f6` | `#d1d5db` | `#25262b` | AAA |
| `tip` | Tip | `#006f7c` | `#e0f7fa` | `#99f6e4` | `#152e30` | AA / AAA |
| `warning` | Warning | `#6b5900` | `#fff8d8` | `#fde68a` | `#2a2408` | AA / AAA |
| `info` | Info | `#1f5fbf` | `#eaf2ff` | `#8ab4ff` | `#1e2634` | AA / AAA |
| `success` | Success | `#006b30` | `#e0f8ea` | `#a7f3d0` | `#143326` | AA / AAA |
| `danger` | Danger | `#990000` | `#ffe0e0` | `#fecaca` | `#3b1515` | AAA |
| `comm` | Communication | `#3730a3` | `#eef2ff` | `#c7d2fe` | `#1c2038` | AAA |
| `critical` | Critical thinking | `#7c2d12` | `#fff7ed` | `#fed7aa` | `#2a1d14` | AAA |
| `career` | Career | `#831843` | `#fdf2f8` | `#fbcfe8` | `#2a1522` | AAA |
| `tech` | Technology | `#1e293b` | `#f1f5f9` | `#cbd5e1` | `#222830` | AAA |

---

## Authoring notes

1. The variant word must be the **first token** and must match the list above exactly (lowercase). `{% details Communication ... %}` is not `comm`; it becomes a default block whose caption starts with “Communication”.
2. The plugin already prefixes a text label. You do not need to repeat “Warning:” in the caption unless you want it in the title twice.
3. Nested `details` are allowed. There is no `question` or `example` variant; those names currently render as `default`.
4. Styles apply site-wide via `_details.scss`. Distill articles additionally place the block on the text grid column.
5. After changing a hex in `_themes.scss`, run `python3 scripts/check_contrast.py`.
