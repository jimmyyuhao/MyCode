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
  Test of incorrect call to PyString_AsString
*/
PyObject *
test(PyObject *self, PyObject *args)
{
    PyObject *repr_args = NULL;
    PyObject *result = NULL;

    repr_args = PyObject_Repr(args);
    /*
       This code fails to check that the call to PyObject_Repr succeeded;
       the checker ought to detect that a NULL ptr deref can happen inside
       PyString_AsString:
     */

    result = PyString_FromFormat("test(args=%s)",
                                 PyString_AsString(repr_args));
    Py_DECREF(repr_args);
    return result;
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
