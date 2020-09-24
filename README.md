# Sugar C

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

A different flavour of Tiny C, it's sugar!

This fork of tcc intends to adds some syntactic sweetness to C-like scripts. Also reviewing the basic interface that is offered to the user from the command line, defaulting the compiler to run code on the fly, instead of building a binary.

## Table of Contents

- [Install](#install)
- [Usage](#usage)

## Install

You need to make-install Sugar C to get it properly working on your system. Hopefully this will be straight forward, so keep fingers crossed.

For `linux` and `osx` should be as simple as pasting this line into your terminal:

```sh
$ git clone https://github.com/antonioprates/sugar.git && cd sugar && ./install.sh
```

If you get permission issues, you can try to `sudo` the install script also:

```sh
$ sudo ./install.sh
```

If you don't need the source code, you can remove the folder afterwards:

```sh
$ cd .. && rm -rf sugar
```

For `windows` you can clone the repo and give it a try to the win32/build-sugar.bat (ugh!), never tried. Maybe send me a message, I will be happy to know it still works, or if needs any fixes.

## Usage

The implicit '-run' directive together with the <sugar.h> library, makes c-scripting easier. You can try and inspect the samples like:

```sh
$ sugar hello.c
```

Or if given the right permission to the file, and assuming `/usr/local/bin/sugar` to be sugar install path on your system:

```sh
$ ./hello.c
```
