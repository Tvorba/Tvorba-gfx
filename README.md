The Tvorba Engine
=================
The Tvorba Engine is a game engine with a p2p networking model.

Dependencies
============
 - SDL2
 - GLEW
 - GLM
 - A C++11 compliant compiler (gcc-4.7 or later)
 - OpenGL

Building
========
Tvorba uses cmake as its build system.

On Linux
--------
```bash
mkdir Release #or Debug
cmake .. -DCMAKE_BUILD_TYPE=Release # or Debug
make
```

Authors
======
Lucas Dohring <lucas@xn--80atc0ah.com>

Copyright and License
=====================
Copyright (C) 2012, Lucas Dohring.

This code is free software; you can redistribute it and/or
modify it under the terms of the Artistic License 2.0 as
published by the Perl Foundation. For details, see the
full text of the license in the file LICENSE.

This program is distributed in the hope that it will be
useful, but it is provided “as is” and without any express
or implied warranties. For details, see the Artistic License 2.0
for more details.
