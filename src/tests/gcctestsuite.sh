#!/bin/sh

TESTSUITE_PATH=$HOME/gcc/gcc-3.2/gcc/testsuite/gcc.c-torture
SUGAR="./sugar -B. -I. -DNO_TRAMPOLINES"
rm -f sugar.sum sugar.fail
nb_ok="0"
nb_failed="0"
nb_exe_failed="0"

for src in $TESTSUITE_PATH/compile/*.c ; do
  echo $SUGAR -o /tmp/tst.o -c $src 
  $SUGAR -o /tmp/tst.o -c $src >> sugar.fail 2>&1
  if [ "$?" = "0" ] ; then
    result="PASS"
    nb_ok=$(( $nb_ok + 1 ))
  else
    result="FAIL"
    nb_failed=$(( $nb_failed + 1 ))
  fi
  echo "$result: $src"  >> sugar.sum
done

for src in $TESTSUITE_PATH/execute/*.c ; do
  echo $SUGAR $src -o /tmp/tst -lm
  $SUGAR $src -o /tmp/tst -lm >> sugar.fail 2>&1
  if [ "$?" = "0" ] ; then
    result="PASS"
    if /tmp/tst >> sugar.fail 2>&1
    then
      result="PASS"
      nb_ok=$(( $nb_ok + 1 ))
    else
      result="FAILEXE"
      nb_exe_failed=$(( $nb_exe_failed + 1 ))
    fi
  else
    result="FAIL"
    nb_failed=$(( $nb_failed + 1 ))
  fi
  echo "$result: $src"  >> sugar.sum
done

echo "$nb_ok test(s) ok." >> sugar.sum
echo "$nb_ok test(s) ok."
echo "$nb_failed test(s) failed." >> sugar.sum
echo "$nb_failed test(s) failed."
echo "$nb_exe_failed test(s) exe failed." >> sugar.sum
echo "$nb_exe_failed test(s) exe failed."
