/*
   Copyright 2011 David Malcolm <dmalcolm@redhat.com>
   Copyright 2011 Red Hat, Inc.

   This is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see
   <http://www.gnu.org/licenses/>.
*/

/*
  Verify that the checker emits a warning for code "s" with a non-const
  char*

  Code "s" writes a pointer back to the insides of an object's representation,
  so it really should be a (const char*), not just a (char*)
*/
#include <Python.h>

PyObject *
test(PyObject *self, PyObject *args)
{
    char *str;

    if (!PyArg_ParseTuple(args, "s",
                          &str)) {
        return NULL;
    }

    Py_RETURN_NONE;
}

/*
  PEP-7
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/
