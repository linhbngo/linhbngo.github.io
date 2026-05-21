#!/usr/bin/env bash
# One-time (or repeat) setup: install Ruby gems into the active conda env prefix.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

if [[ "$ROOT" == /mnt/* ]]; then
  echo "WARNING: Repo is on the Windows drive ($ROOT)."
  echo "         drvfs mounts often block writes (e.g. Gemfile.lock). Prefer ~/linhbngogithubio — see INSTALL_LOCAL.md."
fi

if [[ -f Gemfile.lock && ! -w Gemfile.lock ]]; then
  echo "ERROR: Gemfile.lock is not writable:" >&2
  ls -l Gemfile.lock >&2
  echo >&2
  echo "On /mnt/* (Windows drive), sudo chown usually does NOT fix drvfs permissions." >&2
  echo "Recommended — clone into WSL home, then re-run setup:" >&2
  echo "  git clone \"$ROOT\" ~/linhbngogithubio && cd ~/linhbngogithubio && bash bin/setup-conda-env.sh" >&2
  echo "See INSTALL_LOCAL.md for Windows takeown/icacls or WSL metadata options." >&2
  exit 1
fi

ENV_NAME="${CONDA_JEKYLL_ENV:-linhbngo-jekyll}"
CONDA_BASE="$(conda info --base)"
# shellcheck disable=SC1091
source "${CONDA_BASE}/etc/profile.d/conda.sh"

if ! conda env list | grep -qE "^${ENV_NAME}[[:space:]]"; then
  echo "Creating conda env '${ENV_NAME}' from environment.yml ..."
  conda env create -f environment.yml
fi

conda activate "${ENV_NAME}"

if [[ -z "${CONDA_PREFIX:-}" ]]; then
  echo "Failed to activate conda env '${ENV_NAME}'." >&2
  exit 1
fi

GEM_HOME="${CONDA_PREFIX}/share/rubygems"
BUNDLE_PATH="${CONDA_PREFIX}/share/bundle"
ACTIVATE_DIR="${CONDA_PREFIX}/etc/conda/activate.d"
DEACTIVATE_DIR="${CONDA_PREFIX}/etc/conda/deactivate.d"

mkdir -p "${GEM_HOME}" "${BUNDLE_PATH}" "${ACTIVATE_DIR}" "${DEACTIVATE_DIR}"

cat > "${ACTIVATE_DIR}/jekyll-conda.sh" <<EOF
# Auto-configured by bin/setup-conda-env.sh — keeps gems inside this conda env.
export _CONDA_JEKYLL_OLD_GEM_HOME="\${GEM_HOME-}"
export _CONDA_JEKYLL_OLD_GEM_PATH="\${GEM_PATH-}"
export _CONDA_JEKYLL_OLD_PATH="\${PATH}"

export GEM_HOME="${GEM_HOME}"
export GEM_PATH="${GEM_HOME}"
export BUNDLE_PATH="${BUNDLE_PATH}"
export PATH="${GEM_HOME}/bin:${CONDA_PREFIX}/bin:\${PATH}"
EOF

cat > "${DEACTIVATE_DIR}/jekyll-conda.sh" <<'EOF'
if [ -n "${_CONDA_JEKYLL_OLD_GEM_HOME+x}" ]; then
  export GEM_HOME="${_CONDA_JEKYLL_OLD_GEM_HOME}"
  unset _CONDA_JEKYLL_OLD_GEM_HOME
else
  unset GEM_HOME
fi
if [ -n "${_CONDA_JEKYLL_OLD_GEM_PATH+x}" ]; then
  export GEM_PATH="${_CONDA_JEKYLL_OLD_GEM_PATH}"
  unset _CONDA_JEKYLL_OLD_GEM_PATH
else
  unset GEM_PATH
fi
unset BUNDLE_PATH
if [ -n "${_CONDA_JEKYLL_OLD_PATH+x}" ]; then
  export PATH="${_CONDA_JEKYLL_OLD_PATH}"
  unset _CONDA_JEKYLL_OLD_PATH
fi
EOF

# Re-apply activate hooks for the current shell.
# shellcheck disable=SC1091
source "${ACTIVATE_DIR}/jekyll-conda.sh"

bundle config set --local path "${BUNDLE_PATH}"
bundle config set --local bin "${CONDA_PREFIX}/bin"

echo "Installing bundler (lockfile: BUNDLED WITH 4.0.4) ..."
gem install bundler -v 4.0.4 --no-document

echo "Installing Gemfile dependencies into \${CONDA_PREFIX} ..."
bundle install

cat <<EOF

Conda Jekyll env is ready.

  conda activate ${ENV_NAME}
  bundle exec jekyll serve --livereload

Gems live under:
  ${BUNDLE_PATH}
  ${GEM_HOME}

To clone or move this env on another machine:
  conda env export -n ${ENV_NAME} > environment.lock.yml
  # on target: conda env create -f environment.lock.yml && bash bin/setup-conda-env.sh

Or pack the whole prefix (includes gems after bundle install):
  conda install -n ${ENV_NAME} -c conda-forge conda-pack
  conda pack -n ${ENV_NAME} -o ${ENV_NAME}.tar.gz

EOF
