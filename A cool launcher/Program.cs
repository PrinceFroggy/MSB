using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace A_cool_launcher
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            if (!Methods.Security.Version())
                if (!Methods.Security.Running())
                    if (Methods.Configuration.RetrievePath())
                        if (Methods.Configuration.CreateProcess())
                            if (Methods.Configuration.CreateFile())
                                if (Methods.Configuration.InjectDll())
                                    return;
        }
    }
}