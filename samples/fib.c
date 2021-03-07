#if 0
  /usr/local/bin/sugar `basename $0` $@ && exit;
  // above is a shebang hack, so you can run: ./fib.c <number>
#endif

#include <sugar.h>

// from original tcc examples (sweetened)

number fib(n) {
  if (n <= 2)
    return 1;
  else
    return fib(n - 1) + fib(n - 2);
}

app({
  if (argc < 2) {
    println("usage: fib n");
    println("Compute nth Fibonacci number");
    return EXIT_FAILURE;
  }

  number n = ofString(argv[1]);
  println(join4s("fib(", argv[1], ") = ", ofNumber(fib(n, 2))));
})
