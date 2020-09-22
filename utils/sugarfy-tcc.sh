#!/usr/bin/env bash

# Bash script by Antonio Prates, 2020

# this is a utility to help patching
# Sugar C based on Tiny C repo

# this script assumes you have already
# a working version of Sugar C
# properly set up on your system
# if not, please run `install.sh` first

# you will need `rename` to run this script
# if on mac you can `brew install rename`

# get the path as argument
tccpath="$1"

# prevent running the script with no defined path or on a path that does not contain tcc.c
[[ -z "$tccpath" ]] && echo "Hey, this won't work! The base directory parameter is missing..." && echo "Please, provide full path to tcc folder (without final slash), like:" && echo "./sugarfy_tinc.sh ~/tcc" && exit 1

[[ -f "$tccpath/tcc.c" ]] || echo "Hey, this does not seem to be the right directory: no tcc found!"
[[ -f "$tccpath/tcc.c" ]] || exit 1

# do the hard work
function sugarfy() {
  for item in $1/*; do
    if [[ -d "$item" ]]; then # it's a directory
      echo "   Directory found: sugarfying recursively..."
      echo "-> Now starting at: $item"
      (sugarfy $item)
      echo "<- Continuing with: $1"
    else # it's a file
      (./sugarfy-tcc.c $item)
    fi
  done
  echo ""
  (cd $1 && rename -v 's/tcc/sugar/' *)
}

# some explanatory notes...
echo ""
echo "Let's make it sweet:"
echo "tcc ======> sugar"
echo "TCC ======> SUGAR"
echo "TINYC ====> SUGARC"
echo "tinycc ===> sugarc"
echo "TinyCC ===> SugarC"
echo "Tiny C ===> Sugar C"
echo ""

# LET'S DO THIS!
echo "-> Starting at: $tccpath"
sugarfy $tccpath

# reorganize and houskeeping on the project structure
echo "Doing some more renames..."
(cd $tccpath && mkdir ../src && mv * ../src/ && mv ../src/ "$tccpath/src")

# copy out to root some files
mv "$tccpath/src/examples/" "$tccpath/examples"
mv "$tccpath/src/Changelog" "$tccpath/ChangeLog"
mv "$tccpath/src/COPYING" "$tccpath/COPYING"
mv "$tccpath/src/TODO" "$tccpath/TODO"

# rename some other files
mv "$tccpath/src/README" "$tccpath/src/TINYC-README"
mv "$tccpath/src/RELICENSING" "$tccpath/src/TINYC-RELICENSING"
mv "$tccpath/src/USES" "$tccpath/src/TINYC-USES"
mv "$tccpath/src/VERSION" "$tccpath/src/TINYC-VERSION"

echo "<- Done!"
echo ""
echo "==== Tiny C ===> it's Sugar baby!!"
echo "fluff you, you fluffin' fluff"
echo ""
exit 0
