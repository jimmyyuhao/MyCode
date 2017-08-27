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
  Verify that the checker can cope with various incorrect actions on an
  uninitialized pointer
*/

PyObject *
test(int len)
{
    PyObject *result = NULL;
    PyObject *item; /* never initialized */
    int i;
    
    result = PyList_New(len);
    if (!result) {
	goto error;
    }

    for (i = 0; i < len; i++) {
        /* Erroneous comparison against uninitialized data: */
	if (!item) {
	    goto error;
	}
        /* Erroneous call using uninitialized data: */
	PyList_SetItem(result, i, item);
    }

    return result;

 error:
    Py_XDECREF(result);
    return NULL;
}

/*
  PEP-7
Local variables:
c-basic-offset: 4
indent-tabs-mode: nil
End:
*/
