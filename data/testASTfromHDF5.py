#!/usr/bin/env python3

import ast
import h5py

code= ast.parse("print('Hello World!')")
print(code)

exec(compile(code, filename='', mode='exec'))
