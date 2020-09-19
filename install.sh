#!/usr/bin/env bash
make clean && echo "Gimme some sugar" && ./configure -s && echo "Baking ingredients..." && make -s && echo "Let's see what we got:" && make install && echo "" && sugar -v && cat sugarc.art
