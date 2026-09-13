module.exports = {
  content: ["_site/**/*.html", "_site/**/*.js"],
  css: ["_site/assets/css/*.css"],
  output: "_site/assets/css/",
  skippedContentGlobs: ["_site/assets/**/*.html"],
  // Keep every details variant even when no lecture uses it yet.
  // Without this, challenge/solution/NACE rules are stripped and
  // those blocks fall back to the default grey/purple chrome.
  safelist: {
    standard: ["details", "details-label", /^details--/, /^data-variant/],
    greedy: [/^details/, /data-variant/],
  },
};
