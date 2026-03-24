#!/bin/bash

# GitHubからMELEW3_pkgsに必要パッケージをclone
mkdir ../MELEW3_pkgs
cd ../MELEW3_pkgs

# qpOASES
git clone git@github.com:kuka-isir/qpOASES.git

# (pkg_name)
# git clone git@github.com: ... .git