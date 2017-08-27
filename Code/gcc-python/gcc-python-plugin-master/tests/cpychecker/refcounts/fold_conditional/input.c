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

PyObject *
fold_conditional(PyObject *self, PyObject *args)
{
    PyObject *list;
    list = PyList_New(5);
    if (!list) {
        return NULL;
    }

    /*
       Try a useless conditional to verify that the analyser knows it's
       false:
    */
    if (PyList_GET_SIZE(list) != 5) {
        /* The analyser should figure out that we can never get here: */
        return list;
    }

    /*
      Try another useless conditional, to verify that the analyser knows
      it's false:
    */
    if (Py_TYPE(list) != &PyList_Type) {
        /*
	  Likewise, the analyser should figure out that we can never get
	  here:
	*/
        return list;
    }

    return list;
}
static PyMethodDef test_methods[] = {
    {"test_method",  fold_conditional, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL} /* Sentinel */
};
