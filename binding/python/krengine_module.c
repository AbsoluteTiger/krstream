#include "kr_engine.h"
#include "Python.h"


static PyObject *
pykrengine_startup(PyObject *self, PyObject *args)
{
    T_KREngine *krengine;
    char *dsn, *user, *pass;
    char *logpath, *logname;
    int loglevel;
    char *krdbname;
    char *krdbmodule, *datamodule, *rulemodule;
    int shmkey, hdicachesize, threadcnt, hwm;

    if (!PyArg_ParseTuple(args, "sssssiissssiii", &dsn, &user, &pass, 
                &logpath, &logname, &loglevel, &shmkey, &krdbname, 
                &krdbmodule, &datamodule, &rulemodule,
                &hdicachesize, &threadcnt, &hwm))
        return NULL;
    krengine = kr_engine_startup(dsn, user, pass, 
            logpath, logname, loglevel, shmkey, krdbname, 
            krdbmodule, datamodule, rulemodule, 
            hdicachesize, threadcnt, hwm, NULL);
    return Py_BuildValue("l", krengine);
}

static PyObject *
pykrengine_run(PyObject *self, PyObject *args)
{
    T_KREngine *krengine;
    int oprcode, datasrc;
    char *msgbuf;
    PyObject *extra;
    int ret;
    
    if (!PyArg_ParseTuple(args, "liisO", &krengine, 
                &oprcode, &datasrc, &msgbuf, &extra))
        return NULL;
    ret=kr_engine_run(krengine, oprcode, datasrc, msgbuf, extra);
    return Py_BuildValue("i", ret);
}

static PyObject *
pykrengine_shutdown(PyObject *self, PyObject *args)
{
    T_KREngine *krengine;

    if (!PyArg_ParseTuple(args, "l", &krengine))
        return NULL;

    kr_engine_shutdown(krengine);
    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject *
pykrengine_info(PyObject *self, PyObject *args)
{
    T_KREngine *krengine;
    char *krinfo;
    
    if (!PyArg_ParseTuple(args, "l", &krengine))
        return NULL;
    krinfo=kr_engine_info(krengine);
    PyObject *info=PyString_FromString(krinfo);
    return info;
}


static PyMethodDef KREngineMethods[] = {
    {"startup",  pykrengine_startup, METH_VARARGS,""},
    {"run",  pykrengine_run, METH_VARARGS,""},
    {"shutdown",  pykrengine_shutdown, METH_VARARGS,""},
    {"info",  pykrengine_info, METH_VARARGS,""},
    {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC
init_krengine(void)
{
    (void) Py_InitModule("_krengine", KREngineMethods);
}

