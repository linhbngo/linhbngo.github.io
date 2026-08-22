# Color Accessibility Report

**Scope:** Color tokens and color-using components in this site theme (`_sass/`, selected `assets/css/`, Distill lecture styles).  
**Standard:** [WCAG 2.2](https://www.w3.org/TR/WCAG22/) Level AA is the compliance target. Level AAA is noted where it is already met or is a low-cost improvement.  
**Audit date:** 21 August 2026  
**Implementation date:** 21 August 2026  
**Status of this document:** The recommendations in §5–§6 (Scheme A plus the design list) were **implemented on 21 August 2026**. Sections 2–3 describe the **pre-change** inventory and measurements. Current tokens and post-change ratios are in §7 and in `DETAILS-SUM.md`. Verify new hex values with `python3 scripts/check_contrast.py`.

Contrast ratios were computed from the WCAG relative-luminance formula (sRGB, 2.2 gamma). Composite colors (for example `rgba(241, 196, 15, 0.12)` over `#ffffff` or `#1c1c1d`) were flattened before measurement.

| Criterion | Normal text | Large text (18pt / 14pt bold) | UI / graphics (WCAG 1.4.11) |
|---|---|---|---|
| AA | 4.5:1 | 3:1 | 3:1 |
| AAA | 7:1 | 4.5:1 | — |

`<summary>` text in Distill `details` is not large text, so **4.5:1** is required for those labels.

---

## 1. Executive summary

**This section is the 21 August 2026 audit (before the token work).** Issues listed here were addressed the same day; see §4 and §7.

Primary body text in both themes meets **AAA**. Brand accents, muted text, callout titles, Distill `details` summaries, and several interactive states **did not consistently meet AA**.

The highest-impact problems:

1. **Dark theme reuses light-theme callout tokens.** Tip, warning, and danger blockquotes stay pastel in dark mode. Distill `details` variants use the same light `rgba()` fills, so summary colors that work on a cream background fail on the darkened composite.
2. **Muted text `#828282` fails AA** on both white (3.84:1) and near-black (4.43:1). It is used for post metadata, tags, Distill appendix copy, tab labels, and “light” body text.
3. **Links rely on color without a persistent underline.** Light-theme purple vs black is 3.60:1 (the 3:1 link-vs-body bar is met); dark-theme cyan vs body text is **2.73:1** (WCAG 1.4.1 failure unless links are underlined or otherwise marked in a non-color way).
4. **Yellow / lime / bright green** (`#efcc00`, `#f1c40f`, `#e7c000`, `#00c853`, `#b7d12a`, `#11d68b`) cannot meet 4.5:1 (or often even 3:1) on white. They are used as borders and titles, so they fail non-text contrast as well.
5. **Several interactive states invert or wash out contrast:** quiz button hover in light mode (white on white), search-term highlight, Distill TOC headings hardcoded to `rgba(0,0,0,0.8)`, footer link hover, back-to-top control, dark-theme pagination.

The site is an academic / lecture site with long-form reading. The 21 August 2026 implementation moved tokens into `_sass/_variables.scss` and `_sass/_themes.scss` and pointed Distill `details` and quiz states at those tokens.

---

## 2. Color inventory

### 2.1 Palette (`_sass/_variables.scss`)

| Token | Hex | Notes |
|---|---|---|
| `$red-color` | `#ff3636` | 3.60:1 on white (large/UI only) |
| `$red-color-dark` | `#b71c1c` | 6.57:1 on white (AA). Used as `--global-highlight-color` in light theme |
| `$orange-color` | `#f29105` | 2.38:1 on white (fail) |
| `$blue-color` | `#0076df` | 4.51:1 on white (AA, barely) |
| `$blue-color-dark` | `#00369f` | Sufficient on white |
| `$cyan-color` | `#2698ba` | 3.34:1 on white; 5.09:1 on `#1c1c1d` (dark theme accent) |
| `$green-color` | `#00ab37` | 3.05:1 on white (large/UI only). Tints default `details` background |
| `$green-color-lime` | `#b7d12a` | 1.73:1 on white (fail) |
| `$green-color-dark` | `#009f06` | 3.52:1 on white (large/UI only) |
| `$green-color-bright` | `#11d68b` | 1.91:1 on white (fail) |
| `$green-color-light` | `#ddffdd` | Background only |
| `$purple-color` | `#b509ac` | Light-theme accent / links. 5.83:1 on white (AA, not AAA) |
| `$pink-color` | `#f92080` | 3.79:1 on white (large/UI only) |
| `$yellow-color` | `#efcc00` | 1.58:1 on white (fail) |
| `$grey-color` | `#828282` | Muted text. Fails AA on both theme backgrounds |
| `$grey-color-light` | `#e8e8e8` | Sass `adjust($grey-color, $lightness: 40%)`. Dark-theme body text |
| `$grey-color-dark` | `#1c1c1d` | Dark-theme page background; light-theme footer |
| `$grey-900` | `#212529` | Dark-theme card background |
| `$white-color` / `$black-color` | `#ffffff` / `#000000` | 21:1 together |

Derived surfaces:

| Token | Composition | Flattened (on white) |
|---|---|---|
| `$details-bg-color-light` | `rgba(#00ab37, 0.3)` | `#b2e6c3` |
| `$code-bg-color-light` | `rgba(#e8e8e8, 0.5)` | `#f4f4f4` |
| `$details-bg-color-dark` / `$code-bg-color-dark` | `#2c3237` | solid |

### 2.2 Theme CSS variables (`_sass/_themes.scss`)

**Light (`:root`)**

| Variable | Value | Role |
|---|---|---|
| `--global-bg-color` | `#ffffff` | Page |
| `--global-text-color` | `#000000` | Body |
| `--global-text-color-light` | `#828282` | Muted |
| `--global-theme-color` / `--global-hover-color` | `#b509ac` | Links, accents |
| `--global-hover-text-color` | `#ffffff` | Text on accent |
| `--global-footer-bg-color` | `#1c1c1d` | Footer |
| `--global-footer-text-color` | `#e8e8e8` | Footer copy |
| `--global-footer-link-color` | `#ffffff` | Footer links |
| `--global-distill-app-color` | `#828282` | Distill appendix |
| `--global-highlight-color` | `#b71c1c` | Award / emphasis |
| `--global-details-bg-color` | green 30% tint | Default `details` |
| `--global-code-bg-color` | grey 50% tint | Code |

**Dark (`html[data-theme="dark"]`)**

| Variable | Value | Role |
|---|---|---|
| `--global-bg-color` | `#1c1c1d` | Page |
| `--global-text-color` | `#e8e8e8` | Body |
| `--global-text-color-light` | `#828282` | Muted |
| `--global-theme-color` / `--global-hover-color` | `#2698ba` | Links, accents |
| `--global-footer-bg-color` | `#e8e8e8` | Inverted footer |
| `--global-footer-text-color` | `#1c1c1d` | Footer copy |
| `--global-footer-link-color` | `#000000` | Footer links |
| `--global-card-bg-color` | `#212529` | Cards |
| `--global-details-bg-color` / `--global-code-bg-color` | `#2c3237` | Panels |

Callout tokens (`--global-tip-block*`, `--global-warning-block*`, `--global-danger-block*`) are **copied unchanged** into the dark theme. That is the root cause of light boxes on a dark page.

### 2.3 Other color sources

| Location | What it colors |
|---|---|
| `_sass/_distill.scss` | Distill `details` variants (hard-coded hex, not theme tokens) |
| `_sass/_quiz.scss` | Correct / wrong / revealed states (hard-coded; dark overrides exist) |
| `_sass/_base.scss` | Book-cover status badges, search highlight, newsletter, pagination hover |
| `_sass/_cv.scss`, `_sass/_tabs.scss`, `_sass/_layout.scss` | Theme variables only |
| `assets/css/jupyter.css`, `jupyter-grade3.css`, Rouge / Pygments sheets | Notebook and syntax highlighting (third-party; sampled below) |

---

## 3. Findings by component

Ratios are rounded to two decimals. **Fail** means below AA for that role (normal text unless noted).

### 3.1 Page chrome — light theme

| Pair | Foreground | Background | Ratio | AA |
|---|---|---|---|---|
| Body text | `#000000` | `#ffffff` | 21.00 | AAA |
| Muted text, Distill appendix, tabs, post meta | `#828282` | `#ffffff` | 3.84 | **Fail** (large only) |
| Links / theme | `#b509ac` | `#ffffff` | 5.83 | AA |
| Link vs surrounding body (1.4.1, no underline) | `#b509ac` vs `#000000` | — | 3.60 | Passes 3:1 bar |
| Text on theme (newsletter button, active page, CV badge) | `#ffffff` | `#b509ac` | 5.83 | AA |
| Highlight | `#b71c1c` | `#ffffff` | 6.57 | AA |
| Inline code | `#b509ac` | `#f4f4f4` | 5.28 | AA |
| Footer copy | `#e8e8e8` | `#1c1c1d` | 13.90 | AAA |
| Footer links | `#ffffff` | `#1c1c1d` | 17.03 | AAA |
| Footer link hover | `#b509ac` | `#1c1c1d` | 2.92 | **Fail** |
| Back-to-top | `#ffffff` | `rgba(0,0,0,0.4)` → `#999999` | 2.85 | **Fail** |
| Search highlight (`::highlight(search)`) | `#000000` | `#b509ac` | 3.60 | **Fail** (normal text) |

### 3.2 Page chrome — dark theme

| Pair | Foreground | Background | Ratio | AA |
|---|---|---|---|---|
| Body text | `#e8e8e8` | `#1c1c1d` | 13.90 | AAA |
| Muted text | `#828282` | `#1c1c1d` | 4.43 | **Fail** (large only) |
| Links / theme | `#2698ba` | `#1c1c1d` | 5.09 | AA |
| Link vs surrounding body (1.4.1, no underline) | `#2698ba` vs `#e8e8e8` | — | 2.73 | **Fail** |
| White text on cyan (active pagination) | `#ffffff` | `#2698ba` | 3.34 | **Fail** (normal); large/UI only |
| Inline code / default `details` summary | `#2698ba` | `#2c3237` | 3.88 | **Fail** (summary is normal text) |
| Default `details` body | `#e8e8e8` | `#2c3237` | 10.59 | AAA |
| Card body | `#e8e8e8` | `#212529` | 12.59 | AAA |
| Footer hover | `#2698ba` | `#e8e8e8` | 2.73 | **Fail** |
| Divider vs page (1.4.11) | `#424246` | `#1c1c1d` | 1.70 | **Fail** (if the line is the only cue) |
| Search highlight | `#e8e8e8` | `#2698ba` | 2.73 | **Fail** |
| Newsletter button | `#1c1c1d` | `#2698ba` | 5.09 | AA |

### 3.3 Blockquotes: tip / warning / danger (`_base.scss` + `_themes.scss`)

These tokens are identical in light and dark themes.

| Role | Color | On | Ratio | AA |
|---|---|---|---|---|
| Tip body | `#215d42` | `#e2f5ec` | 6.83 | AA |
| Tip title | `#359469` | `#e2f5ec` | 3.31 | **Fail** |
| Tip border vs page | `#42b983` | `#ffffff` | 2.47 | **Fail** (1.4.11) |
| Warning body | `#6b5900` | `#fff8d8` | 6.44 | AA |
| Warning title | `#b29400` | `#fff8d8` | 2.76 | **Fail** |
| Warning border vs page | `#e7c000` | `#ffffff` | 1.76 | **Fail** (1.4.11) |
| Danger body | `#660000` | `#ffe0e0` | 10.86 | AAA |
| Danger title | `#cc0000` | `#ffe0e0` | 4.76 | AA |
| Danger border vs page | `#cc0000` | `#ffffff` | 5.89 | AA |

In dark mode the pastel surfaces remain readable internally (dark text on light fill), but they flash as light “holes” in the page and do not follow `color-scheme`. That is a theme-coherence issue and a problem for readers who chose dark mode specifically to reduce luminance.

### 3.4 Distill `details` (existing variants)

Body text uses `--global-text-color` (`!important` on `d-article p`). Variant CSS only restyles the left border, fill, and `<summary>`.

Fills are `rgba(accent, 0.10–0.12)`, so the measured background depends on the page.

**Light (over `#ffffff`)**

| Variant | Summary | Fill | Summary ratio | Body (black) | Border vs page |
|---|---|---|---|---|---|
| default | `#b509ac` | `#b2e6c3` | 4.16 **Fail** | 14.99 AAA | green 3.05 UI-only |
| warning | `#b07d00` | `#fdf8e2` | 3.41 **Fail** | 19.71 AAA | `#f1c40f` 1.66 **Fail** |
| info | `#1f5fbf` | `#eaf2ff` | 5.40 AA | 18.62 AAA | `#2b7cff` 3.87 UI-only |
| success | `#008b3d` | `#e0f8ea` | 3.96 **Fail** | 18.85 AAA | `#00c853` 2.24 **Fail** |
| danger | `#b52b27` | `#faeaea` | 5.41 AA | 18.08 AAA | `#d9534f` 3.96 UI-only |
| tip | `#008fa1` | `#e0f7fa` | 3.46 **Fail** | 18.86 AAA | `#00bcd4` 2.30 **Fail** |

**Dark (over `#1c1c1d`)**

| Variant | Summary | Fill | Summary ratio | Body (`#e8e8e8`) |
|---|---|---|---|---|
| default | `#2698ba` | `#2c3237` | 3.88 **Fail** | 10.59 AAA |
| warning | `#b07d00` | `#36301b` | 3.62 **Fail** | 10.74 AAA |
| info | `#1f5fbf` | `#1e2634` | 2.51 **Fail** | 12.47 AAA |
| success | `#008b3d` | `#193123` | 3.18 **Fail** | 11.44 AAA |
| danger | `#b52b27` | `#332323` | 2.39 **Fail** | 12.25 AAA |
| tip | `#008fa1` | `#192f33` | 3.63 **Fail** | 11.44 AAA |

Default `details` in light mode is a **green panel with a purple summary**, so it reads as “success” even when it is semantically neutral.

`note` is accepted by `_plugins/details.rb` but has **no distinct CSS**; it renders as `default`.

### 3.5 Distill `details` (NACE variants — implemented, compliant)

These four variants were added with dedicated light and dark colors. All summary, body, and border pairs below meet **AA**; most meet **AAA**. See `DETAILS-SUM.md` for usage.

| Variant | Theme | Summary | Fill | Summary ratio | Body ratio | Border vs page |
|---|---|---|---|---|---|---|
| comm | light | `#3730a3` | `#eef2ff` | 8.88 AAA | 18.78 AAA | 7.90 AAA |
| comm | dark | `#c7d2fe` | `#1c2038` | 10.72 AAA | 13.05 AAA | 8.54 AAA |
| critical | light | `#7c2d12` | `#fff7ed` | 8.83 AAA | 19.78 AAA | 7.31 AAA |
| critical | dark | `#fed7aa` | `#2a1d14` | 12.08 AAA | 13.35 AAA | 10.10 AAA |
| career | light | `#831843` | `#fdf2f8` | 8.84 AAA | 19.23 AAA | 7.88 AAA |
| career | dark | `#fbcfe8` | `#2a1522` | 12.36 AAA | 13.95 AAA | 9.39 AAA |
| tech | light | `#1e293b` | `#f1f5f9` | 13.35 AAA | 19.17 AAA | 10.35 AAA |
| tech | dark | `#cbd5e1` | `#222830` | 10.00 AAA | 12.12 AAA | 6.64 AA |

Hues were chosen so the set stays separable under common color-vision deficiencies (indigo, umber, wine, slate) and does not collide with existing warning-yellow, info-blue, success-green, danger-red, or tip-cyan.

### 3.6 Quiz (`_sass/_quiz.scss`)

| State | Pair | Ratio | AA |
|---|---|---|---|
| Correct / revealed (light) | `#1b5e20` on `#e8f5e9` | 7.00 | AA (exactly AAA threshold) |
| Wrong (light) | `#b71c1c` on `#ffebee` | 5.75 | AA |
| Correct (dark) | `#a5d6a7` on `#203422` | 8.11 | AAA |
| Wrong (dark) | `#ef9a9a` on `#461f20` | 6.61 | AA |
| Hint | warning-block tokens | same as §3.3 | title/border issues |
| **Button hover (light)** | `--global-hover-text-color` (`#ffffff`) on `--global-bg-color` (`#ffffff`) | **1.00** | **Fail** |

The hover rule changes text to white and does not change the button fill. In light mode the label disappears.

### 3.7 Distill table of contents

`d-article d-contents nav div` is hardcoded to `color: rgba(0, 0, 0, 0.8)` in `_sass/_distill.scss`.

| Theme | Effective pair | Ratio | AA |
|---|---|---|---|
| Light | `#333333` on `#ffffff` | 12.63 | AAA |
| Dark | `#333333` on `#1c1c1d` | 1.35 | **Fail** |

### 3.8 Book-cover status badges (`_sass/_base.scss`)

Text is always `#23212d`.

| Status | Background | Ratio | AA |
|---|---|---|---|
| abandoned | `#ee5f5b` | 4.84 | AA |
| finished / watched | `#62c462` | 7.23 | AAA |
| interested | `#7691db` | 5.16 | AA |
| paused | `#bdac7e` | 7.06 | AAA |
| queued | `#9e76b5` | 4.31 | **Fail** |
| reading / watching | `#f89406` | 6.96 | AA |
| reread / rewatch | `#a6517d` | 3.09 | **Fail** |
| uncategorized | `#b0abb3` | 7.03 | AAA |

### 3.9 Notebook / syntax CSS (sample)

Not site-brand tokens, but they appear in lecture pages that embed notebooks.

| Sample | Pair | Ratio | AA |
|---|---|---|---|
| Jupyter keyword (light) | `#008000` on `#ffffff` | 5.14 | AA |
| Jupyter `def` (light) | `#0000ff` on `#ffffff` | 8.59 | AAA |
| Jupyter UI font 38% black | `#9e9e9e` on `#ffffff` | 2.68 | **Fail** |
| grade3 orange headings | `#ff7823` on `#ffffff` | 2.64 | **Fail** |
| grade3 green | `#009e07` on `#ffffff` | 3.56 | **Fail** (normal text) |

### 3.10 Use of color alone (WCAG 1.4.1)

Meaning that is currently color-only:

- `details` variant (warning vs info vs success, and the four NACE types)
- Quiz correct vs wrong vs revealed
- Book-cover reading status
- Tip / warning / danger blockquotes (if the heading text does not name the severity)

The disclosure triangle on `details` shows open/closed state, but **not** which variant it is. Captions that already say “Warning” or “Communication” are fine; captions that are only a topic title are not.

---

## 4. Issue register

| ID | Severity | WCAG | Issue | Status (21 Aug 2026) |
|---|---|---|---|---|
| A1 | Critical | 1.4.3 | Quiz `.quiz-btn:hover` is white-on-white in light theme | **Fixed** — hover uses `--global-theme-on-color` fill with white text |
| A2 | Critical | 1.4.3 | Distill TOC headings `rgba(0,0,0,0.8)` in dark theme (1.35:1) | **Fixed** — `var(--global-text-color)` |
| A3 | High | 1.4.3 | `#828282` muted text fails AA in both themes | **Fixed** — `#595959` light / `#a3a3a3` dark |
| A4 | High | 1.4.3 | Five of six existing Distill `details` summaries fail AA | **Fixed** — solid per-theme tokens; all summaries ≥ 4.5:1 |
| A5 | High | 1.4.3 / 1.4.11 | Warning and tip titles and borders fail | **Fixed** — darker titles/borders; dark-theme callout tokens |
| A6 | High | 1.4.1 | Dark-theme links are not 3:1 from body text and are not underlined | **Fixed** — body/Distill links underlined |
| A7 | High | 1.4.3 | Dark theme: white (or light) text on cyan | **Fixed** — `--global-theme-on-color` (`#1a7a96`) for filled controls |
| A8 | Medium | 1.4.3 | Default `details` summary fails AA; green fill implies “success” | **Fixed** — neutral `#f4f4f4` / `#2c3237` with `#7a0676` / `#4ec3e0` summary |
| A9 | Medium | 1.4.3 | Footer link hover fails in both themes | **Fixed** — `--global-footer-hover-color` |
| A10 | Medium | 1.4.3 | Back-to-top (light) 2.85:1 | **Fixed** — fill `#5c5c5c` (6.69:1) |
| A11 | Medium | 1.4.11 | Dark divider `#424246` on `#1c1c1d` is 1.70:1 | **Fixed** — `#6e6e75` (3.37:1) |
| A12 | Medium | 1.4.3 | Book badges `queued` and `reread` fail AA | **Fixed** — `#c4a3d6` / `#d9a3bc` |
| A13 | Medium | 1.4.3 | Callout and `details` tokens are not dark-theme-aware | **Fixed** — separate light/dark values in `_themes.scss` |
| A14 | Low | 1.4.1 | Variant type is color-only unless the caption states it | **Fixed** — plugin injects a `.details-label` prefix except on `default` |
| A15 | Low | 1.4.3 | Bright palette leftovers unsafe as text | **Noted** — comment in `_variables.scss`; not used as text |

**Deferred (optional in the original §5.5):** vendor Jupyter / Grade3 / Pygments sheets. Those remain third-party samples and were not restyled.

---

## 5. Alternative color schemes (implemented 21 August 2026)

Scheme A (keep brand hues, fix failing pairs) was applied. Scheme B (AAA-darkened purple `#8e0788` as the main light accent) was **not** adopted as the site-wide theme color, so the light-theme purple `#b509ac` remains for links (5.83:1 AA on white, with underlines). Darkened purple is used where a filled control or search highlight needs extra contrast (`#8e0788` search fill; `#7a0676` default `details` summary).

The replacement tables in the original §5.3–§5.4 are now the live values in `_sass/_themes.scss`. NACE hues were kept on distinct axes (indigo, umber, wine, slate).

---

## 6. Design recommendations (implemented 21 August 2026)

| # | Recommendation | What changed |
|---|---|---|
| 1 | Semantic CSS variables per `details` variant | `_sass/_themes.scss` (`--global-details-*`) |
| 2 | Replace hard-coded hex in Distill and quiz | `_sass/_details.scss`, `_sass/_quiz.scss` |
| 3 | `--global-theme-on-color` vs `--global-theme-color` | Light `#b509ac`; dark fill `#1a7a96` |
| 4 | Stop copying light callout tokens into dark | Dark tip/warning/danger tokens added |
| 5 | Muted text `#595959` / `#a3a3a3` | `--global-text-color-light` |
| 6 | Underline body/Distill links | `_base.scss`, `_distill.scss` |
| 7 | Non-color hover/focus; `:focus-visible` | `details` summary, quiz, pagination, newsletter, Distill links |
| 8 | White-on-cyan controls use darker fill | Pagination, badges, newsletter, dropdowns, quiz hover |
| 9 | Neutral default `details` | Grey fill, theme-colored left border |
| 10 | §5.3 palettes for warning/info/success/danger/tip | Applied to both `details` and blockquotes |
| 11 | Visible non-color variant label | `_plugins/details.rb` `.details-label` |
| 12 | Distinct `note` style | Slate grey panel + “Note” label |
| 13 | Global `details` styles | `_sass/_details.scss` (not only `d-article`) |
| 14 | Quiz button hover fill + text together | `_sass/_quiz.scss` |
| 15 | Distill TOC uses theme text color | `_sass/_distill.scss` |
| 16 | Search highlight high-contrast pair | `--global-highlight-search-*` |
| 17 | Back-to-top fill | `#5c5c5c` in light |
| 18 | Pagination active uses theme-on-color | `_base.scss` |
| 19 | Quiz meaning not color-only | Unchanged text: “Correct!” / “Not quite — try again.” |
| 20 | Keep NACE hue axes | Unchanged |
| 21 | Do not use yellow/lime/bright green/orange as text | Comment in `_variables.scss` |
| 22 | Contrast check on theme changes | `scripts/check_contrast.py` |
| 23 | Manual light/dark/deuteranopia pass | Author follow-up; tokens chosen to stay separable under deuteranopia |
| 24 | Keyboard: `summary` focus ring | `:focus-visible` on `summary` |

---

## 7. Implementation changelog — 21 August 2026

Applied Scheme A and the §6 list. Files touched:

| File | Change |
|---|---|
| `_sass/_variables.scss` | Muted greys, theme-on, code, footer-hover tokens; default `details` fill is `#f4f4f4`; comment on unsafe bright hues |
| `_sass/_themes.scss` | Light/dark CSS variables for chrome, callouts, every `details` variant, quiz states, search highlight |
| `_sass/_details.scss` | **New.** Global variant styles driven by those variables |
| `_sass/_distill.scss` | Grid-only `details` placement; TOC color; Distill link underlines |
| `_sass/_base.scss` | Links, footer hover, pagination, code color, search highlight, badges, newsletter, dropdown fills, focus rings |
| `_sass/_quiz.scss` | Tokenized states; hover fill+text; `:focus-visible`; explanation uses body text color |
| `_sass/_cv.scss` | TOC badge uses theme-on fill |
| `_plugins/details.rb` | Visible labels for non-default variants |
| `assets/css/main.scss` | Imports `_details.scss` |
| `scripts/check_contrast.py` | **New.** AA regression check (`python3 scripts/check_contrast.py`) |
| `DETAILS-SUM.md` | Updated to the live palettes and labels |

### Live chrome (post-change)

| Pair | Light | Dark |
|---|---|---|
| Muted text | `#595959` on white 7.00 AAA | `#a3a3a3` on `#1c1c1d` 6.75 AA |
| Links | `#b509ac` 5.83 AA + underline | `#2698ba` 5.09 AA + underline |
| Filled controls | white on `#b509ac` 5.83 AA | white on `#1a7a96` 4.92 AA |
| Inline code | `#b509ac` on `#f4f4f4` 5.30 AA | `#4ec3e0` on `#2c3237` 6.31 AA |
| Footer link hover | `#e8a0e4` on `#1c1c1d` 8.58 AAA | `#155e75` on `#e8e8e8` 5.93 AA |
| Search highlight | white on `#8e0788` 8.28 AAA | `#1c1c1d` on `#4ec3e0` 8.28 AAA |

### Still out of scope

- Jupyter / Grade3 / Rouge vendor styles (original §5.5)
- Scheme B as the site-wide light accent (`#8e0788` everywhere)
- A visual deuteranopia pass in a browser (tokens were chosen for hue separation; please confirm on a lecture page with `details` and quizzes)
