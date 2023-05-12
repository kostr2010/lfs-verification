# LFS VERIFICATION TASK

this repo consists of two parts: `src` and `verification`.

## SRC

`src` contains c++ inpementation of lock free stack and tests for it. tests dump trace that can be used later for verification

## VERIFICATION

`verification` contains tla model for the algrithm and script that checks trace against LTL formula using spot framework
