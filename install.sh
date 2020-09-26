#!/usr/bin/env bash
(cd src && make clean && echo $'\n   Gimme some sugar baby!' && ./configure -s && echo "   It's time to kick ass and chew bubblegum..." && make -s && echo "   Damn! Whadda we got here?" && make install && sugar -v && echo $'   Ha! Fluff you, you fluffin\' fluff\n' && make clean)
