/*
 * Python bindings for Jsonic library.
 *
 * https://github.com/rohanrhu/python-jsonic
 * https://oguzhaneroglu.com/projects/python-jsonic/
 *
 * Licensed under MIT
 * Copyright (C) 2019, Oğuzhan Eroğlu (https://oguzhaneroglu.com/) <rohanrhu2@gmail.com>
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#ifndef _MSC_VER
#include <unistd.h>
#else
#include <io.h>
#endif
#include <stdlib.h>

#include "python-jsonic.h"
#include "lib/jsonic/jsonic.h"

static PyObject*
PyJsonic_from_file(PyObject *self, PyObject* args) {
    char* file_name;
    if (!PyArg_ParseTuple(args, "s", &file_name)) {
        return NULL;
    }
    
#ifdef _MSC_VER
    FILE* fd;
    if (fd = fopen(file_name, "r")) {
        fclose(fd);
#else
    if (access(file_name, F_OK) != -1) {
#endif
        char* json = jsonic_from_file(file_name);
    
        return PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(si)", json, 1)
        );
    } else {
        Py_RETURN_FALSE;
    }
}

static void
PyJsonic_JsonicType_dealloc(
    PyJsonic_JsonicObject *self
) {
    jsonic_free_addr(self->node);
    jsonic_free_addr(self->from);
    Py_CLEAR(self->json);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

int
PyJsonic_JsonicType_init(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    int is_root = 1;
    if (!PyArg_ParseTuple(args, "U|i", &self->json, &is_root)) {
        return NULL;
    }

    Py_INCREF(self->json);
    self->json_ascii = PyBytes_AS_STRING(PyUnicode_AsEncodedString(self->json, "utf-8", NULL));

    if (is_root) {
        self->node = jsonic_get_root(self->json_ascii);
        self->from = NULL;
        self->json_type = self->node->type;
    } else {
        self->node = NULL;
        self->from = NULL;
        self->json_type = 0;
    }

    return 0;
}

static PyObject*
PyJsonic_JsonicType_root(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    if (self->node == NULL) {
        Py_RETURN_NONE;
    }

    PyObject* pyNode;

    if (self->node->type == JSONIC_OBJECT) {
        Py_RETURN_NONE;
    } else if (self->node->type == JSONIC_ARRAY) {
        Py_RETURN_NONE;
    } else if (self->node->type == JSONIC_STRING) {
        return PyUnicode_FromString(self->node->val);
    } else if (self->node->type == JSONIC_NUMBER) {
        return PyFloat_FromDouble(atof(self->node->val));
    } else if (self->node->type == JSONIC_BOOLEAN) {
        return PyBool_FromLong(self->node->val[0] == '1');
    } else if (self->node->type == JSONIC_NULL) {
        return PyObject_CallObject((PyObject *) &PyJsonic_NullType, NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
PyJsonic_JsonicType_key(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    char* key;
    if (!PyArg_ParseTuple(args, "s", &key)) {
        return NULL;
    }
    
    jsonic_node_t* node = jsonic_object_get(
        self->json_ascii,
        self->node,
        key
    );

    if (node == NULL) {
        Py_RETURN_NONE;
    }

    PyObject* pyNode;

    if (node->type == JSONIC_OBJECT) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_ARRAY) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_STRING) {
        return PyUnicode_FromString(node->val);
    } else if (node->type == JSONIC_NUMBER) {
        return PyFloat_FromDouble(atof(node->val));
    } else if (node->type == JSONIC_BOOLEAN) {
        return PyBool_FromLong(node->val[0] == '1');
    } else if (node->type == JSONIC_NULL) {
        return PyObject_CallObject((PyObject *) &PyJsonic_NullType, NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
PyJsonic_JsonicType_item(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    unsigned int index;
    if (!PyArg_ParseTuple(args, "I", &index)) {
        return NULL;
    }
    
    jsonic_node_t* node = jsonic_array_get(
        self->json_ascii,
        self->node,
        index
    );

    if (node == NULL) {
        Py_RETURN_NONE;
    }

    PyObject* pyNode;

    if (node->type == JSONIC_OBJECT) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_ARRAY) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_STRING) {
        return PyUnicode_FromString(node->val);
    } else if (node->type == JSONIC_NUMBER) {
        return PyFloat_FromDouble(atof(node->val));
    } else if (node->type == JSONIC_BOOLEAN) {
        return PyBool_FromLong(node->val[0] == '1');
    } else if (node->type == JSONIC_NULL) {
        return PyObject_CallObject((PyObject *) &PyJsonic_NullType, NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
PyJsonic_JsonicType_len(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    unsigned int length = jsonic_array_length(
        self->json_ascii,
        self->node
    );

    return PyLong_FromLong(length);
}

static PyObject*
PyJsonic_JsonicType_iterItem(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    unsigned int index = 0;
    if (!PyArg_ParseTuple(args, "|I", &index)) {
        return NULL;
    }
    
    jsonic_node_t* node = jsonic_array_iter(
        self->json_ascii,
        self->node,
        self->from,
        index
    );

    if (node == NULL) {
        Py_RETURN_NONE;
    }

    self->from = malloc(sizeof(jsonic_node_t));
    memcpy(self->from, node, sizeof(jsonic_node_t));

    PyObject* pyNode;

    if (node->type == JSONIC_OBJECT) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_ARRAY) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_STRING) {
        return PyUnicode_FromString(node->val);
    } else if (node->type == JSONIC_NUMBER) {
        return PyFloat_FromDouble(atof(node->val));
    } else if (node->type == JSONIC_BOOLEAN) {
        return PyBool_FromLong(node->val[0] == '1');
    } else if (node->type == JSONIC_NULL) {
        return PyObject_CallObject((PyObject *) &PyJsonic_NullType, NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
PyJsonic_JsonicType_iterKey(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    char* key;
    if (!PyArg_ParseTuple(args, "s", &key)) {
        return NULL;
    }
    
    jsonic_node_t* node = jsonic_object_iter(
        self->json_ascii,
        self->node,
        self->from,
        key
    );

    if (node == NULL) {
        Py_RETURN_NONE;
    }

    self->from = malloc(sizeof(jsonic_node_t));
    memcpy(self->from, node, sizeof(jsonic_node_t));

    PyObject* pyNode;

    if (node->type == JSONIC_OBJECT) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_ARRAY) {
        pyNode = PyObject_CallObject(
            (PyObject *) &PyJsonic_JsonicType,
            Py_BuildValue("(Oi)", self->json, 0)
        );

        ((PyJsonic_JsonicObject *) pyNode)->node = node;
        ((PyJsonic_JsonicObject *) pyNode)->json_type = node->type;

        return pyNode;
    } else if (node->type == JSONIC_STRING) {
        return PyUnicode_FromString(node->val);
    } else if (node->type == JSONIC_NUMBER) {
        return PyFloat_FromDouble(atof(node->val));
    } else if (node->type == JSONIC_BOOLEAN) {
        return PyBool_FromLong(node->val[0] == '1');
    } else if (node->type == JSONIC_NULL) {
        return PyObject_CallObject((PyObject *) &PyJsonic_NullType, NULL);
    }

    Py_RETURN_NONE;
}

static PyObject*
PyJsonic_JsonicType_reset(
    PyJsonic_JsonicObject *self,
    PyObject *args,
    PyObject *kwds
) {
    self->from = malloc(sizeof(jsonic_node_t));
    memcpy(self->from, jsonic_get_root(self->json_ascii), sizeof(jsonic_node_t));

    Py_RETURN_NONE;
}

PyMODINIT_FUNC
PyInit_jsonic(void) {
    PyObject* module  = PyModule_Create(&PyJsonicModule);

    if (PyType_Ready(&PyJsonic_JsonicType) < 0) {
        return NULL;
    }
    PyModule_AddObject(module, "Jsonic", (PyObject *)&PyJsonic_JsonicType);

    if (PyType_Ready(&PyJsonic_NullType) < 0) {
        return NULL;
    }
    PyModule_AddObject(module, "Null", (PyObject *)&PyJsonic_NullType);
    PyModule_AddStringConstant(module, "version", PYJSONIC_VERSION);
    PyModule_AddIntConstant(module, "TYPE_OBJECT", JSONIC_OBJECT);
    PyModule_AddIntConstant(module, "TYPE_ARRAY", JSONIC_ARRAY);

    return module;
}