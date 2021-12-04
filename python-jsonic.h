/*
 * Python bindings for Jsonic library.
 *
 * https://github.com/rohanrhu/python-jsonic
 * https://oguzhaneroglu.com/projects/python-jsonic/
 *
 * Licensed under MIT
 * Copyright (C) 2019, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
 */

#ifndef __PYTHON_JSONIC_H__
#define __PYTHON_JSONIC_H__

#include <Python.h>
#include "structmember.h"

#include "lib/jsonic/jsonic.h"

#define PYJSONIC_VERSION "1.10"

typedef struct {
    PyObject_HEAD
} PyJsonic_NullObject;

typedef struct {
    PyObject_HEAD
    jsonic_node_t* node;
    jsonic_node_t* from;
    PyObject* json;
    char* json_ascii;
    int json_type;
} PyJsonic_JsonicObject;

int
PyJsonic_JsonicType_init(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_root(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static void
PyJsonic_JsonicType_dealloc(
    PyJsonic_JsonicObject *self
);

static PyObject*
PyJsonic_JsonicType_key(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_item(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_len(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_iterItem(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_iterKey(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_JsonicType_reset(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
);

static PyObject*
PyJsonic_from_file(PyObject *self, PyObject* args);

static PyMethodDef
PyJsonicModule_methods[] = {
    {
        "from_file",
        PyJsonic_from_file,
        METH_VARARGS,
        "Read and return json from file."
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef
PyJsonicModule = {
    PyModuleDef_HEAD_INIT,
    "jsonic",
    NULL,
    -1,
    PyJsonicModule_methods
};

static PyMemberDef
PyJsonic_JsonicType_members[] = {
   {"json", T_OBJECT, offsetof(PyJsonic_JsonicObject, json), 0, "JSON String"},
   {"type", T_INT, offsetof(PyJsonic_JsonicObject, json_type), 0, "JSON Type"},
   {NULL, 0, 0, 0, NULL}
};

static PyMethodDef
PyJsonic_JsonicType_methods[] = {
   {"root", PyJsonic_JsonicType_root, METH_VARARGS, "Get value of root Jsonic object."},
   {"key", PyJsonic_JsonicType_key, METH_VARARGS, "Get value of a key."},
   {"item", PyJsonic_JsonicType_item, METH_VARARGS, "Get item of an array index."},
   {"len", PyJsonic_JsonicType_len, METH_VARARGS, "Get length of an array."},
   {"iterItem", PyJsonic_JsonicType_iterItem, METH_VARARGS, "Iterate array."},
   {"iterKey", PyJsonic_JsonicType_iterKey, METH_VARARGS, "Iterate object."},
   {"reset", PyJsonic_JsonicType_reset, METH_VARARGS, "Reset iteration current."},
   {NULL, NULL, 0, NULL}
};

static PyTypeObject PyJsonic_JsonicType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "jsonic.Jsonic",
    .tp_basicsize = sizeof(PyJsonic_JsonicObject),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor) PyJsonic_JsonicType_dealloc,
    .tp_vectorcall_offset = 0,
    .tp_getattr = 0,
    .tp_setattr = 0,
    .tp_as_async = 0,
    .tp_repr = 0,
    .tp_as_number = 0,
    .tp_as_sequence = 0,
    .tp_as_mapping = 0,
    .tp_hash  = 0,
    .tp_call = 0,
    .tp_str = 0,
    .tp_getattro = 0,
    .tp_setattro = 0,
    .tp_as_buffer = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Jsonic Object",
    .tp_traverse = 0,
    .tp_clear = 0,
    .tp_richcompare = 0,
    .tp_weaklistoffset = 0,
    .tp_iter = 0,
    .tp_iternext = 0,
    .tp_methods = PyJsonic_JsonicType_methods,
    .tp_members = PyJsonic_JsonicType_members,
    .tp_getset = 0,
    .tp_base = 0,
    .tp_dict = 0,
    .tp_descr_get = 0,
    .tp_descr_set = 0,
    .tp_dictoffset = 0,
    .tp_init = PyJsonic_JsonicType_init,
    .tp_alloc = 0,
    .tp_new = PyType_GenericNew,
    .tp_free = 0,
    .tp_is_gc = 0,
    .tp_bases = 0,
    .tp_mro = 0,
    .tp_cache = 0,
    .tp_subclasses = 0,
    .tp_weaklist = 0,
    .tp_del = 0,
    .tp_version_tag = 0,
    .tp_finalize = 0
};

static PyTypeObject PyJsonic_NullType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "jsonic.Null",
    .tp_basicsize = sizeof(PyJsonic_NullObject),
    .tp_itemsize = 0,
    .tp_dealloc = 0,
    .tp_vectorcall_offset = 0,
    .tp_getattr = 0,
    .tp_setattr = 0,
    .tp_as_async = 0,
    .tp_repr = 0,
    .tp_as_number = 0,
    .tp_as_sequence = 0,
    .tp_as_mapping = 0,
    .tp_hash  = 0,
    .tp_call = 0,
    .tp_str = 0,
    .tp_getattro = 0,
    .tp_setattro = 0,
    .tp_as_buffer = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "Jsonic NULL Object",
    .tp_traverse = 0,
    .tp_clear = 0,
    .tp_richcompare = 0,
    .tp_weaklistoffset = 0,
    .tp_iter = 0,
    .tp_iternext = 0,
    .tp_methods = 0,
    .tp_members = 0,
    .tp_getset = 0,
    .tp_base = 0,
    .tp_dict = 0,
    .tp_descr_get = 0,
    .tp_descr_set = 0,
    .tp_dictoffset = 0,
    .tp_init = 0,
    .tp_alloc = 0,
    .tp_new = PyType_GenericNew,
    .tp_free = 0,
    .tp_is_gc = 0,
    .tp_bases = 0,
    .tp_mro = 0,
    .tp_cache = 0,
    .tp_subclasses = 0,
    .tp_weaklist = 0,
    .tp_del = 0,
    .tp_version_tag = 0,
    .tp_finalize = 0
};

#endif