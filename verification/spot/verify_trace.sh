#!/bin/bash

set -Eeu -o pipefail -o posix
shopt -s nullglob inherit_errexit

PWD=$(dirname "$(realpath "${0}")")
OUT_DIR="${PWD}/out"

clear_file() {
    true >"${1:?}"
}

clear_dir() {
    mkdir -p "${1:?}"
    rm -rf "${1:?}"/*
    rm -rf "${1:?}"/.[a-zA-Z0-9]*
}

generate_automata() {
    local LTL_FORMULA="G(push -> F(pop))"
    local OUT_FILE="${OUT_DIR}/automata.hoa"

    ltl2tgba -UC --formula="${LTL_FORMULA}" >"${OUT_FILE}"

    echo "${OUT_FILE}"
}

verify_trace() {
    local TRACE="${1:?}"

    local OUT_FILE
    OUT_FILE=$(generate_automata)

    python3 "${PWD}/verify_trace.py" "${TRACE}" "${OUT_FILE}"

    echo "TRACE CHECKED SUCCESSFULLY"
}

clear_dir "${OUT_DIR}"
verify_trace "${@:?}"
