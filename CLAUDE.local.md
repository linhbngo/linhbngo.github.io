# Quiz Component — Claude Code Task

This file instructs Claude Code to generate an interactive multiple-choice quiz
component for the al-folio Jekyll site at this repository root.

## Context

This is a Jekyll site using the al-folio theme. The quiz component lets a
lecturer embed self-check multiple-choice questions inside any markdown file
using a single Liquid `{% include %}` tag.

## Your Task

Generate the following **three files** from scratch, then print the two manual
wiring steps the user must do afterward. Do not modify any existing files.

---

## File 1 — `_includes/quiz.liquid`

A Liquid HTML template that renders one quiz question. It must:

- Accept these include parameters:
  - `include.id` (required) — unique string ID, used to namespace DOM element IDs
  - `include.question` (required) — question text (plain text or inline HTML)
  - `include.choices` (required) — pipe-separated answer choices, e.g. `"Paris|London|Berlin"`
  - `include.answer` (required) — 0-based index of the correct choice as a string, e.g. `"0"`
  - `include.hint` (optional) — short hint text
  - `include.explanation` (optional) — explanation shown after correct answer or reveal

- Split `include.choices` on `"|"` using `| split: "|"`.
- Use `{% assign _quiz_letters = "A,B,C,D,E,F,G,H" | split: "," %}` to label choices.
- Render each choice as a `<button>` with:
  - `class="quiz-choice"`
  - `data-quiz-id="{{ include.id }}"`
  - `data-choice-index="{{ forloop.index0 }}"`
  - `data-correct="true"` or `data-correct="false"` depending on whether the index matches `include.answer | plus: 0`
  - `onclick="quizHandleChoice(this)"`
- Wrap everything in `<div class="quiz-block" id="quiz-{{ include.id }}">`.
- Include a `.quiz-actions` div with buttons for Hint (if `include.hint` present), Show Answer, and Reset.
- Include a hidden `.quiz-hint` div (if `include.hint` present).
- Include a hidden `.quiz-feedback` div with child spans for icon and text.
- Include a hidden `.quiz-explanation` div (if `include.explanation` present).
- Include an inline `<script>` block that registers the correct answer index:
  ```html
  <script>
  (function () {
    window.__quizAnswers = window.__quizAnswers || {};
    window.__quizAnswers["{{ include.id }}"] = {{ _quiz_correct }};
  })();
  </script>
  ```
- Add a Liquid comment block at the top showing the full usage syntax.

---

## File 2 — `_sass/_quiz.scss`

A SCSS partial that styles the quiz component. It must:

- Use only al-folio CSS custom properties for colours — no hardcoded hex except
  for green/red correct/wrong states. Key variables available:
  - `--global-bg-color`, `--global-text-color`, `--global-text-color-light`
  - `--global-theme-color`, `--global-hover-text-color`
  - `--global-divider-color`, `--global-code-bg-color`, `--global-details-bg-color`
  - `--global-warning-block`, `--global-warning-block-bg`, `--global-warning-block-text`
- Style `.quiz-block` with a left border using `--global-theme-color`.
- Style `.quiz-choice` buttons with hover state and three state classes:
  - `.quiz-correct` — green border + background
  - `.quiz-wrong` — red border + background
  - `.quiz-revealed` — same as correct
- Style `.quiz-choice-letter` as a small circular badge.
- Style `.quiz-actions` as a flex row of small buttons.
- Style `.quiz-hint` using warning block variables.
- Style `.quiz-explanation` with a left border accent.
- Include a `html[data-theme="dark"]` block that overrides correct/wrong colours
  to use semi-transparent backgrounds so they work on dark backgrounds.

---

## File 3 — `assets/js/quiz.js`

A plain vanilla JavaScript file (no external dependencies) that must define
these global functions:

- `quizHandleChoice(btn)` — called on choice click:
  - Reads `btn.dataset.quizId` and `btn.dataset.correct`
  - If correct: adds `.quiz-correct`, calls `_setFeedback`, `_showExplanation`, `_lockChoices`
  - If wrong: adds `.quiz-wrong`, calls `_setFeedback` with retry message, then removes `.quiz-wrong` after 1000 ms
  - Does nothing if any choice button in this quiz is already disabled (already answered)

- `quizReveal(id)` — called by Show Answer button:
  - Reads correct index from `window.__quizAnswers[id]`
  - Adds `.quiz-revealed` to the correct choice button
  - Calls `_setFeedback` and `_showExplanation`, then `_lockChoices`

- `quizToggleHint(id)` — toggles `hidden` on `#quiz-hint-{id}`

- `quizReset(id)` — removes all state classes, re-enables all buttons, hides
  feedback, explanation, and hint

- Private helpers (prefixed `_quiz`):
  - `_quizBlock(id)` — returns `document.getElementById("quiz-" + id)`
  - `_quizChoiceButtons(id)` — returns array of `.quiz-choice` buttons in the block
  - `_quizCorrectIndex(id)` — returns `(window.__quizAnswers || {})[id] ?? -1`
  - `_setFeedback(id, isCorrect, message)` — shows the feedback div with icon (✅/❌) and message
  - `_showExplanation(id)` — unhides `#quiz-explanation-{id}`
  - `_lockChoices(id)` — sets `disabled = true` on all choice buttons

---

## After Creating the Files

Print the following instructions for the user:

```
=== Manual wiring required (2 steps) ===

1. In assets/css/main.scss, add "quiz" to the @import block, e.g. after "tabs":

   @import
     ...
     "tabs",
     "quiz",    ← add this
     ...
   ;

2. In _includes/head_custom.liquid (create it if it doesn't exist), add:

   <script defer src="{{ '/assets/js/quiz.js' | relative_url }}"></script>

=== Usage in any markdown lecture file ===

{% include quiz.liquid
   id="q1"
   question="Your question here?"
   choices="Choice A|Choice B|Choice C|Choice D"
   answer="0"
   hint="Optional hint text."
   explanation="Optional explanation shown after correct answer."
%}

answer= is 0-based: "0" = A, "1" = B, "2" = C, etc.
```
