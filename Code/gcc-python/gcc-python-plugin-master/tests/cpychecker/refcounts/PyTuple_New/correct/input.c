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

#include <Python.h>

/*
  Test of correct reference-handling in a call to PyTuple_New
*/

extern void __cpychecker_dump(Py_ssize_t s);

PyObject *
test(PyObject *self, PyObject *args)
{
    PyObject *tuple;
    tuple = PyTuple_New(0);
    if (!tuple) {
        return NULL;
    }

    __cpychecker_dump(PyTuple_Size(tuple));

    /* "tuple" should now have an ob_refcnt of 1 */
    return tuple;
}
static PyMethodDef test_methods[] = {
    {"test_method",  test, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

/*
  PEP-7
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/
