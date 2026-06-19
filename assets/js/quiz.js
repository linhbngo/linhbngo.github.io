function _quizBlock(id) {
  return document.getElementById("quiz-" + id);
}

function _quizChoiceButtons(id) {
  var block = _quizBlock(id);
  if (!block) return [];
  return Array.from(block.querySelectorAll(".quiz-choice"));
}

function _quizCorrectIndex(id) {
  return ((window.__quizAnswers || {})[id] ?? -1);
}

function _setFeedback(id, isCorrect, message) {
  var block = _quizBlock(id);
  if (!block) return;
  var feedback = block.querySelector(".quiz-feedback");
  if (!feedback) return;
  feedback.removeAttribute("hidden");
  feedback.querySelector(".quiz-feedback-icon").textContent = isCorrect ? "✅" : "❌";
  feedback.querySelector(".quiz-feedback-text").textContent = message || "";
}

function _showExplanation(id) {
  var el = document.getElementById("quiz-explanation-" + id);
  if (el) el.removeAttribute("hidden");
}

function _lockChoices(id) {
  _quizChoiceButtons(id).forEach(function (btn) {
    btn.disabled = true;
  });
}

function quizHandleChoice(btn) {
  var id = btn.dataset.quizId;
  var buttons = _quizChoiceButtons(id);
  if (buttons.some(function (b) { return b.disabled; })) return;

  var isCorrect = btn.dataset.correct === "true";
  if (isCorrect) {
    btn.classList.add("quiz-correct");
    _setFeedback(id, true, "Correct!");
    _showExplanation(id);
    _lockChoices(id);
  } else {
    btn.classList.add("quiz-wrong");
    _setFeedback(id, false, "Not quite — try again.");
    setTimeout(function () {
      btn.classList.remove("quiz-wrong");
      var block = _quizBlock(id);
      if (block) {
        var feedback = block.querySelector(".quiz-feedback");
        if (feedback) feedback.setAttribute("hidden", "");
      }
    }, 1000);
  }
}

function quizReveal(id) {
  var idx = _quizCorrectIndex(id);
  var buttons = _quizChoiceButtons(id);
  if (idx >= 0 && idx < buttons.length) {
    buttons[idx].classList.add("quiz-revealed");
  }
  _setFeedback(id, true, "The correct answer has been revealed.");
  _showExplanation(id);
  _lockChoices(id);
}

function quizToggleHint(id) {
  var el = document.getElementById("quiz-hint-" + id);
  if (!el) return;
  if (el.hasAttribute("hidden")) {
    el.removeAttribute("hidden");
  } else {
    el.setAttribute("hidden", "");
  }
}

function quizReset(id) {
  var buttons = _quizChoiceButtons(id);
  buttons.forEach(function (btn) {
    btn.classList.remove("quiz-correct", "quiz-wrong", "quiz-revealed");
    btn.disabled = false;
  });

  var block = _quizBlock(id);
  if (!block) return;

  var feedback = block.querySelector(".quiz-feedback");
  if (feedback) {
    feedback.setAttribute("hidden", "");
    feedback.querySelector(".quiz-feedback-icon").textContent = "";
    feedback.querySelector(".quiz-feedback-text").textContent = "";
  }

  var explanation = document.getElementById("quiz-explanation-" + id);
  if (explanation) explanation.setAttribute("hidden", "");

  var hint = document.getElementById("quiz-hint-" + id);
  if (hint) hint.setAttribute("hidden", "");
}
