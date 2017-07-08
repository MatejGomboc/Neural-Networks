using System;
using System.Runtime.InteropServices;

namespace neural_networks_test_project
{
    class DLLImport
    {
        // TODO: set the DLL location !!!
        #if DEBUG
        [DllImport(@"..\..\..\neural_networks_dll_project\bin\Debug\neural_networks.dll")]
        #else
        [DllImport(@"..\..\..\neural_networks_dll_project\bin\Release\neural_networks.dll")]
        #endif
        public static extern int fnneural_networks_dll_project();
    }
}
