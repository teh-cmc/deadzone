## Otogonf

[![GoDoc](https://godoc.org/github.com/teh-cmc/otogonf?status.png)](https://godoc.org/github.com/teh-cmc/otogonf) [![Build Status](https://travis-ci.org/teh-cmc/otogonf.svg?branch=master)](https://travis-ci.org/teh-cmc/otogonf)

Otogonf is a toolset allowing you to manage your configuration files locally as well as remotely, composed of:
- [Otolib](https://github.com/teh-cmc/otogonf/tree/master/otolib): a Go library allowing you to load your config files and to automatically generate REST APIs to handle them remotely
- [Otocli](https://github.com/teh-cmc/otogonf/tree/master/otocli): a command-line client to use these APIs and a daemon to use otogonf in a language agnostic way

### Install

This project assumes you are using [Godep](https://github.com/tools/godep) to manage vendored dependencies, as endorsed by the [Go project](https://code.google.com/p/go-wiki/wiki/PackageManagementTools)

#### Otocli

    $ godep get github.com/teh-cmc/otocli/otocli

#### Otolib

    $ godep get github.com/teh-cmc/otogonf/otolib

### License

```text
The MIT License (MIT)

Copyright (c) 2013 Clement Rey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
