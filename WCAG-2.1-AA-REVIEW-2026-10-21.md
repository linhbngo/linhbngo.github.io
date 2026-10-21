# WCAG 2.1 AA review

21 October 2026

Built site, 337 pages. This is a technical gap review of the Jekyll output, not a legal certification. A public university’s ADA web requirement is met by conforming to WCAG 2.1 Level AA.

## Verdict

The site is not at WCAG 2.1 Level AA yet. The color system is. The pages are not.

The August 2026 color-token work holds: body text, links, callouts, quizzes, and badges meet AA contrast, and links are underlined. The pages still fail AA. Every page lacks a skip link. The lecture layout, which is 192 of 337 pages, also omits the page language and a main landmark. Two-thirds of images have no alt text, and syntax-highlight comments fall below 4.5:1 on both themes.

| Measure | Result |
| --- | --- |
| Pages missing `lang` and a main landmark | 192 of 337 |
| Pages with a skip link | 0 of 337 |
| Images with no alt text | 531 of 815 |
| Theme contrast script | Pass |

Source: `_site/index.html` across 337 routes, plus `scripts/check_contrast.py` against the live tokens in `_sass/_themes.scss`. Image and landmark counts are from the built HTML, not from a screen reader.

## Success criteria that decide AA

A page conforms only when every applicable Level A and AA criterion passes. These are the criteria this pass could measure from templates, built HTML, and the contrast script.

| Criterion | Name | Result | Where | Evidence |
| --- | --- | --- | --- | --- |
| 1.1.1 | Non-text content | Fail | 531 of 815 images | Built pages: 531 `img` elements have no `alt` attribute. `figure.liquid` writes alt only when the include passes one, so lecture figures of diagrams, terminals, and code screenshots are unnamed. |
| 1.3.1 | Info and relationships | Fail | 192 of 337 pages | Lecture and Distill layouts have no main landmark. The same 192 pages are the ones missing a language attribute. Ninety-six of those pages also repeat the lecture title as two identical `h1` elements. |
| 1.4.3 | Contrast (minimum) | Partial | Chrome passes; code comments fail | `scripts/check_contrast.py`: every theme text pair is at least 4.5:1 and every UI pair is at least 3:1. Pygments comments are not in that script. GitHub theme comments `#999988` on the code background `#f4f4f4` are 2.63:1. Native dark comments `#999999` on `#404040` are 3.64:1. |
| 1.4.5 | Images of text | Fail | Course figures that are the only copy of the text | Many lecture figures are screenshots of terminals, slides, or code. Where the same words now exist as real text, the image can be marked decorative. Where the screenshot is the only copy, it is an image of text. |
| 2.4.1 | Bypass blocks | Fail | All 337 pages | No skip link in any layout or include. Repeated navigation is present on every page. Lecture pages also lack a main landmark, so there is no programmatic bypass. |
| 2.4.2 | Page titled | Pass | All 337 pages | Every built `index.html` has a non-empty `title` element. |
| 3.1.1 | Language of page | Fail | 192 of 337 pages | `default.liquid` sets `lang` from `site.lang` (`en`). `lecture.liquid` and `distill.liquid` open with a bare `<html>` tag. The lock lecture page is one of those 192. |
| 4.1.2 | Name, role, value | Partial | Icon controls on every page | The theme button is an icon with `title="Change theme"` and no accessible name in the button text. The search control’s visible name is “ctrl k”; “Search” lives only in the title attribute. The scroll progress element has no label. The nav toggle does expose `aria-expanded`, `aria-controls`, and `aria-label`. |

## What already holds

### Color and text

Body, muted text, links, filled buttons, inline code, details summaries, tip and warning callouts, quiz feedback, book badges, search highlight, and the back-to-top control all meet 4.5:1 for text or 3:1 for UI. Light links are `#b509ac` at 5.83:1 and are underlined. Dark links are `#2698ba` at 5.09:1 and are underlined.

### Page chrome

Default-layout pages set `lang="en"` and `role="main"`. Every built page has a title. The header is a navigation landmark and the footer is `contentinfo`. The navbar toggle exposes its expanded state. Focus-visible rings exist on links, details, and quizzes. Font Awesome honors `prefers-reduced-motion`.

## Distance to AA

The structural failures are a few template edits. The volume is in figure alt text and in replacing screenshots that are the only copy of the words.

| Order | Change | Criteria it clears |
| --- | --- | --- |
| 1 | Add a skip link to the shared header, pointing at a main landmark on every layout. | 2.4.1 |
| 2 | Set `lang` on `lecture.liquid` and `distill.liquid` the same way `default.liquid` already does. | 3.1.1 |
| 3 | Wrap lecture and Distill article content in `main`, and stop Distill from emitting a second copy of the title as `h1`. | 1.3.1 |
| 4 | Give the theme and search buttons an accessible name, and label the scroll progress bar. | 4.1.2 |
| 5 | Darken Pygments comment colors on the GitHub and native themes until comments reach 4.5:1 on the code background. | 1.4.3 |
| 6 | Require `alt` on `figure.liquid`. Use a real description for diagrams. Use empty alt only when the same information is already in text next to the image. | 1.1.1, 1.4.5 |

## Not measured this pass

Full keyboard traversal, 200% text resize and reflow, a screen reader pass, captions on any embedded media, PDF accessibility, and a deuteranopia check of the magenta accent. Jupyter and Grade3 stylesheets were left out of the August contrast fix and were not re-measured here. The newsletter form has an unlabeled email field, and that form is disabled in `_config.yml`, so it is not on the live pages.
