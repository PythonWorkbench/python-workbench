#include <iostream>
#include <string>
#include <Python.h>

int main(int argc, char* argv[]) {
    // 1. Initialize the Python interpreter
    Py_Initialize();

    if (!Py_IsInitialized()) {
        std::cerr << "Error initializing Python interpreter\n";
        return 1;
    }

    // Add current directory to Python path to find modules in the same directory as the executable.
    PyRun_SimpleString("import sys; sys.path.append('.')");

    // 2. Run Python code directly (as a string)
    std::cout << "\nExecuting Python code directly:\n";
    PyRun_SimpleString("print('Hello from embedded Python!')");
    PyRun_SimpleString("result = 5 + 3");
    PyRun_SimpleString("print(f'Result: {result}')");

    // 3. Execute a Python file
    std::cout << "\nExecuting a Python file (script.py):\n";
    FILE* fp = fopen("script.py", "r"); // Make sure "script.py" exists
    if (fp) {
        PyRun_SimpleFile(fp, "script.py");
        fclose(fp);
    } else {
        std::cerr << "Error opening script.py\n";
    }

    // 4. Use Python objects (more advanced)
    std::cout << "\nUsing Python objects:\n";
    PyObject* pModule = PyImport_AddModule("__main__"); // Get the main module
    PyObject* pDict = PyModule_GetDict(pModule);        // Get the module's dictionary

    // Set a variable in the Python namespace
    PyObject* pValue = PyLong_FromLong(42);
    PyDict_SetItemString(pDict, "my_cpp_variable", pValue);
    Py_DECREF(pValue); // Important: Decrement reference count

    // Execute some Python code that uses the variable
    PyRun_SimpleString("print(f'My C++ variable in Python: {my_cpp_variable}')");
    PyRun_SimpleString("my_python_variable = my_cpp_variable * 2");

    // Get a variable back from Python
    PyObject* pResult = PyDict_GetItemString(pDict, "my_python_variable");
    if (pResult && PyLong_Check(pResult)) {
        long result = PyLong_AsLong(pResult);
        std::cout << "My Python variable back in C++: " << result << "\n";
    }
    Py_XDECREF(pResult); // Decrement if not NULL

    // 5. Calling Python functions
    std::cout << "\nCalling Python functions:\n";
    PyObject* pFunc = PyDict_GetItemString(pDict, "my_python_function"); // Function defined in script.py

    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject* pArgs = PyTuple_New(1); // Create argument tuple
        PyObject* pArg = PyLong_FromLong(10);
        PyTuple_SetItem(pArgs, 0, pArg);
        Py_DECREF(pArg);

        PyObject* pReturnValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);

        if (pReturnValue) {
            if(PyLong_Check(pReturnValue)){
                long ret = PyLong_AsLong(pReturnValue);
                std::cout << "Python function returned: " << ret << "\n";
            }
            Py_DECREF(pReturnValue);
        } else {
            PyErr_Print(); // Print Python errors
        }
    } else {
        std::cerr << "Error: Could not find function 'my_python_function'\n";
    }


    // 6. Finalize the Python interpreter (important!)
    Py_FinalizeEx();
    return 0;
}