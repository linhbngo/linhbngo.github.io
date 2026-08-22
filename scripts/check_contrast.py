#!/usr/bin/env python3
"""WCAG 2.2 contrast check for theme tokens.

Run from the repository root:

    python3 scripts/check_contrast.py

Exit status is 1 if any *text* pair is below 4.5:1 (AA normal text) or any
*ui* pair is below 3:1 (AA non-text contrast).
"""

from __future__ import annotations

import sys

AA_TEXT = 4.5
AA_UI = 3.0
AAA_TEXT = 7.0


def hex_to_rgb(value: str) -> tuple[float, float, float]:
    value = value.lstrip("#")
    if len(value) == 3:
        value = "".join(c * 2 for c in value)
    return tuple(int(value[i : i + 2], 16) for i in (0, 2, 4))


def _linear(channel: float) -> float:
    channel = channel / 255.0
    if channel <= 0.04045:
        return channel / 12.92
    return ((channel + 0.055) / 1.055) ** 2.4


def luminance(value: str) -> float:
    r, g, b = hex_to_rgb(value)
    return 0.2126 * _linear(r) + 0.7152 * _linear(g) + 0.0722 * _linear(b)


def contrast(fg: str, bg: str) -> float:
    lighter, darker = sorted((luminance(fg), luminance(bg)), reverse=True)
    return (lighter + 0.05) / (darker + 0.05)


def grade(ratio: float) -> str:
    if ratio >= AAA_TEXT:
        return "AAA"
    if ratio >= AA_TEXT:
        return "AA"
    if ratio >= AA_UI:
        return "AA-large/UI"
    return "FAIL"


# (kind, name, fg, bg)  kind is "text" or "ui"
PAIRS = [
    # Light chrome
    ("text", "light body", "#000000", "#ffffff"),
    ("text", "light muted", "#595959", "#ffffff"),
    ("text", "light links", "#b509ac", "#ffffff"),
    ("text", "light text on theme fill", "#ffffff", "#b509ac"),
    ("text", "light code", "#b509ac", "#f4f4f4"),
    ("text", "light default details summary", "#7a0676", "#f4f4f4"),
    ("text", "light default details body", "#000000", "#f4f4f4"),
    ("ui", "light default details border", "#b509ac", "#ffffff"),
    ("text", "light footer hover", "#e8a0e4", "#1c1c1d"),
    ("text", "light back-to-top", "#ffffff", "#5c5c5c"),
    ("text", "light search highlight", "#ffffff", "#8e0788"),
    # Dark chrome
    ("text", "dark body", "#e8e8e8", "#1c1c1d"),
    ("text", "dark muted", "#a3a3a3", "#1c1c1d"),
    ("text", "dark links", "#2698ba", "#1c1c1d"),
    ("text", "dark text on theme-on fill", "#ffffff", "#1a7a96"),
    ("text", "dark code / default summary", "#4ec3e0", "#2c3237"),
    ("text", "dark default details body", "#e8e8e8", "#2c3237"),
    ("text", "dark footer hover", "#155e75", "#e8e8e8"),
    ("text", "dark search highlight", "#1c1c1d", "#4ec3e0"),
    ("ui", "dark divider", "#6e6e75", "#1c1c1d"),
    # Light callouts
    ("text", "light tip title/body", "#215d42", "#e2f5ec"),
    ("ui", "light tip border", "#1d6b4a", "#ffffff"),
    ("text", "light warning title/body", "#6b5900", "#fff8d8"),
    ("ui", "light warning border", "#8a7000", "#ffffff"),
    ("text", "light danger title", "#990000", "#ffe0e0"),
    ("text", "light danger body", "#660000", "#ffe0e0"),
    # Dark callouts
    ("text", "dark tip title", "#99f6e4", "#152e30"),
    ("text", "dark warning title", "#fde68a", "#2a2408"),
    ("text", "dark danger title", "#fecaca", "#3b1515"),
    ("text", "dark callout body", "#e8e8e8", "#152e30"),
    # Light details
    ("text", "light note summary", "#1f2937", "#f3f4f6"),
    ("text", "light tip summary", "#006f7c", "#e0f7fa"),
    ("text", "light warning summary", "#6b5900", "#fff8d8"),
    ("text", "light info summary", "#1f5fbf", "#eaf2ff"),
    ("text", "light success summary", "#006b30", "#e0f8ea"),
    ("text", "light danger summary", "#990000", "#ffe0e0"),
    ("text", "light comm summary", "#3730a3", "#eef2ff"),
    ("text", "light critical summary", "#7c2d12", "#fff7ed"),
    ("text", "light career summary", "#831843", "#fdf2f8"),
    ("text", "light tech summary", "#1e293b", "#f1f5f9"),
    # Dark details
    ("text", "dark note summary", "#d1d5db", "#25262b"),
    ("text", "dark tip summary", "#99f6e4", "#152e30"),
    ("text", "dark warning summary", "#fde68a", "#2a2408"),
    ("text", "dark info summary", "#8ab4ff", "#1e2634"),
    ("text", "dark success summary", "#a7f3d0", "#143326"),
    ("text", "dark danger summary", "#fecaca", "#3b1515"),
    ("text", "dark comm summary", "#c7d2fe", "#1c2038"),
    ("text", "dark critical summary", "#fed7aa", "#2a1d14"),
    ("text", "dark career summary", "#fbcfe8", "#2a1522"),
    ("text", "dark tech summary", "#cbd5e1", "#222830"),
    # Quiz + badges
    ("text", "quiz correct light", "#1b5e20", "#e8f5e9"),
    ("text", "quiz wrong light", "#b71c1c", "#ffebee"),
    ("text", "quiz correct dark", "#a5d6a7", "#203422"),
    ("text", "quiz wrong dark", "#ef9a9a", "#461f20"),
    ("text", "badge queued", "#23212d", "#c4a3d6"),
    ("text", "badge reread", "#23212d", "#d9a3bc"),
]


def main() -> int:
    failed = 0
    print(f"{'pair':42} {'ratio':>8}  grade")
    print("-" * 60)
    for kind, name, fg, bg in PAIRS:
        ratio = contrast(fg, bg)
        label = grade(ratio)
        threshold = AA_TEXT if kind == "text" else AA_UI
        ok = ratio >= threshold
        if not ok:
            failed += 1
            label += "  <-- below AA"
        print(f"{name:42} {ratio:7.2f}:1  {label}")
    print("-" * 60)
    if failed:
        print(f"{failed} pair(s) below WCAG 2.2 AA")
        return 1
    print("All pairs meet WCAG 2.2 AA")
    return 0


if __name__ == "__main__":
    sys.exit(main())
