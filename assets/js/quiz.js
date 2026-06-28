function _quizBlock(id) {
  return document.getElementById("quiz-" + id);
}

function _quizSelect(id) {
  return document.getElementById("quiz-select-" + id);
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
  var sel = _quizSelect(id);
  if (sel) sel.disabled = true;
}

function quizHandleSelect(selectEl, id) {
  if (selectEl.disabled) return;
  var chosenIndex = parseInt(selectEl.value, 10);
  var correctIndex = _quizCorrectIndex(id);
  var isCorrect = (chosenIndex === correctIndex);

  if (isCorrect) {
    selectEl.classList.add("quiz-correct");
    _setFeedback(id, true, "Correct!");
    _showExplanation(id);
    _lockChoices(id);
  } else {
    selectEl.classList.add("quiz-wrong");
    _setFeedback(id, false, "Not quite — try again.");
    setTimeout(function () {
      selectEl.classList.remove("quiz-wrong");
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
  var sel = _quizSelect(id);
  if (sel && idx >= 0) {
    sel.value = String(idx);
    sel.classList.add("quiz-revealed");
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
  var sel = _quizSelect(id);
  if (sel) {
    sel.value = "";
    sel.classList.remove("quiz-correct", "quiz-wrong", "quiz-revealed");
    sel.disabled = false;
  }

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
