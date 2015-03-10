genoServ
========

<a name="tableOfContents"></a>
## Table of contents

  * <a href="#introduction">Introduction</a>
  * <a href="#howToUse">How to use</a>
  * <a href="#contributing">Contributing</a>
  * <a href="#license">License</a>

<a name="introduction"></a>
### Introduction

**genoServ** aims to be a generic, easy-to-use, fast, modulable, scalable and highly configurable server, specifically designed to run JSONesque user-defined protocols.

It is remotely administrable via [genoConsole](https://github.com/teh-cmc/genoConsole), its standard terminal UI client.

Written in SSJS, powered by [nodeJS](https://github.com/joyent/node).

*Currently in development. Nothing in here is frozen, quite the opposite actually.*

<a name="howToUse"></a>
### How to use

- Clone this repository, then initialize and update submodules:

```
$ git submodule init
$ git submodule update
```

- Build nodejs (take a look at nodejs/README.md for more details):

```
$ cd nodejs
$ ./configure
$ make
```

- Install node-levelUP and node-levelDOWN

```
$ cd ..
$ ./node npm-cli.js install levelup leveldown
```

- Run it:

```
$ ./node run.js
```

<a name="contributing"></a>
### Contributing

1. [Fork](https://github.com/teh-cmc/genoServ/fork) genoServ's repository
2. Create your branch (`git checkout -b my-branch-where-I-did-smth`)
3. Code and commit your changes (and add your name @copyrights)
4. Push to your branch (`git push origin my-branch-where-I-did-smth`)
5. Create your new Pull Request

Please use the [issues tracker](issues) to report any bug or just share your thoughts/feedback.

<a name="license"></a>
### License

genoServ is available under the [GNU General Public License, version 3](COPYING).
