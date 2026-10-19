# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

The public website for **Kódkupa**, a Hungarian national team programming competition for
high-school students (served at kodkupa.hu, see `CNAME`). It is a 100% static site — plain HTML,
CSS and vanilla JS — published directly via GitHub Pages from this repo. There is no build step,
no package manager, no templating engine, and no server-side code. All content (including UI text)
is in Hungarian.

The site is based on the "Alpha" template by HTML5 UP (see `README.txt` / `LICENSE.txt` for
attribution/license).

## Running / previewing locally

There is no build or dev server. To preview, just open the HTML files directly in a browser, or
serve the directory statically, e.g.:

```
python3 -m http.server 8000
```

There is no linting or test suite in this repo.

## Site structure

Top-level pages (real, linked-to content — these share one header/footer/nav layout):
- `index.html` — landing page: competition overview, rounds/schedule, categories, prizes, sponsors.
- `tasks.html` — per-round task lists (statements + sample C++/Python solutions) for the **current**
  season.
- `results.html` — per-round leaderboard tables for the **current** season.
- `archive.html` — links out to past seasons' frozen `tasks.html`/`results.html`/versenykiírás under
  `archive/<year>/`.
- `contact.html`, `generic.html`, `elements.html` — unused leftover template boilerplate from
  HTML5 UP ("Alpha" demo pages). Not linked from the live nav; don't treat them as real content to
  keep in sync.

Supporting content:
- `tasks/<year>/<round>/<taskname>.{pdf,cpp,py}` — task statement PDFs and sample solutions, one
  subdirectory per round per season (e.g. `tasks/2026/round3/`, plus a `*_pp` sibling per round for
  the "ProgramPohár" novice category, e.g. `round3_pp`). Not every task has a Python solution.
  Some round folders also contain an `editorial.pdf`.
  Filenames (without extension) are the task's internal/njudge identifier; `tasks.html` maps each
  one to its Hungarian display name manually.
- `archive/<year>/` — a frozen snapshot of a past season's `tasks.html`, `results.html`, and
  versenykiírás PDF. `archive.html` links to these.
- `assets/` — the HTML5 UP template's CSS (`assets/css/main.css`, built from `assets/sass/`), JS
  (jQuery + plugins in `assets/js/`), and webfonts. Treat as vendored template code; prefer not to
  hand-edit `main.css` — edit `assets/sass/` and recompile if a style changes (no compile tooling is
  checked in, so this is effectively frozen/manual).
- `images/`, `icons/` — static assets (sponsor/partner logos, favicons, site banner, etc.).
- Root-level PDFs (`kodkupa_versenykiiras.pdf`, `tajekoztato_versenyzoknek.pdf`,
  `adatkezelesi_tajekoztato.pdf`, `cpp_python_tanacsok.pdf`) — competition rules, contestant info,
  privacy notice, and C++/Python tips, linked from the pages above.

## Editing conventions

- Every real page repeats the same header/nav/footer markup (see `index.html` /
  `tasks.html` / `results.html`) — there is no shared include mechanism, so navigation changes must
  be copy-pasted into each page by hand. Internal links in `tasks.html`/`results.html`/`archive.html`
  use absolute root paths (`/tasks.html`, `/images/...`); `index.html` and `contact.html` use
  relative paths. Match whichever style the page you're editing already uses.
- `tasks.html` and `results.html` grow every season: a new `<div class="box">...<details>` block is
  prepended for each new round (most recent round first), containing an `<ol>` of tasks with links
  into the matching `tasks/<year>/<round>/` directory. Follow the existing per-round block as a
  template when adding a new round.
- `results.html` leaderboard tables use `<td class="rank">`, `<b class="teamname">`, team member
  names joined with `&nbsp;` between first/last name, and `<td class="school">` /
  `<td class="totalscore">` columns — match this structure exactly when adding results so the
  existing `assets/css/main.css` styling (`.results` table rules) applies correctly.
- At the end of a season: move that season's `tasks.html`/`results.html`/versenykiírás PDF into a
  new `archive/<year>/` folder, add a link block in `archive.html`, and reset `tasks.html` /
  `results.html` for the new season (see commits like "Updates for 2025-26 and archive last year"
  for the pattern).
- This repo has two competition categories per round: the main competition and "ProgramPohár"
  (`_pp` suffix on task folders and filenames) — a parallel, easier track for younger/novice
  contestants. When adding a round's tasks, check whether a `_pp` variant is also needed.
