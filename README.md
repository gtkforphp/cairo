Cairo for PHP 7
=============

Cairo is a 2D graphics library with support for multiple output devices. Output
targets include the X Window System (via both Xlib and XCB), Quartz, Win32,
image buffers, PostScript, PDF, and SVG files.

This extension provides access to Cairo functionality in PHP7 in the Cairo namespace

Status
=============
This is a work in progress rewrite of the original cairo extension
There are plans to add appveyor and travis builds for testing

Requirements
=============
 * PHP 7.0.0-alpha1+
 * Cairo 1.12.0+
 * [Eos\DataStructures](http://github.com/eos-org/datastructures) 0.1.0-dev

Additional features are supported up to Cairo version 1.14.2

Features are enabled at compile time based on the library version they are compiled against.

Documentation and information about the underlying library can be found at [cairographics.org](http://cairographics.org/manual/)

Installation
=============
There are plans to make this available via [pecl](http://pecl.php.net) and [pickle](https://github.com/FriendsOfPHP/pickle)
But this is currently the unstable PHP7 version

Until then, please compile and install the both the datastructures and the cairo extensions and enable them in your php.ini file

```
extension=eos_datastructures.so
extension=cairo.so
```

Compile
=============

This extension can be compiled and tested using phpize

First you need to make and install the Eos\DataStructures extension, which provides Enum support

The cairo extension also requires cairo development files.  You can build the package
manually or use your system's package manager.  For example on ubuntu use

```
apt-get install libcairo-dev
```

Then you can use phpize to install the extension against your current PHP install

```
phpize
./configure
make && make test && make install
```

If you want to use a non-standard location for your PHP use

```
/path/to/phpize
./configure --with-php-config=/path/to/php-config
make && make test && make install
```

`make install` copies `cairo.so` to the right location, but you still need to enable the module
in your php.ini file.  Although the extension can be used with a webserver, that is not recommended.

Examples
====
The examples directory holds samples of all currently working utilities for the extension

Community
=====
You can find us on [freenode](http://freenode.org) on #gtkforphp

The main website is [Gtk For PHP](http://gtkforphp.net)

You can view commits and released on [twitter](http://twitter.com/gtkforphp)

You can send comments, patches, questions [here on github](https://github.com/gtkforphp/glib/issues)

See Contributing.md for information on how to get involved

Authors
====
Elizabeth M Smith

License
=====
PHP extension binding code released under the [MIT license](http://opensource.org/licenses/MIT)
See [LICENSE](LICENSE)

The Cairo Graphics library is is released under the [LGPL](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html)

Documentation
=====
What little documentation we currently have is in code comments and the docs directory

We'd like to use some kind of markdown or rst format for docs, a decision isn't final yet
