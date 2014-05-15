using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;
using System.Reflection;
using Microsoft.Win32;
using System.Windows.Forms;

#region Structures

public struct PROCESS_INFORMATION
{
    public IntPtr hProcess;
    public IntPtr hThread;
    public uint dwProcessId;
    public uint dwThreadId;
}

public struct STARTUPINFO
{
    public uint cb;
    public string lpReserved;
    public string lpDesktop;
    public string lpTitle;
    public uint dwX;
    public uint dwY;
    public uint dwXSize;
    public uint dwYSize;
    public uint dwXCountChars;
    public uint dwYCountChars;
    public uint dwFillAttribute;
    public uint dwFlags;
    public short wShowWindow;
    public short cbReserved2;
    public IntPtr lpReserved2;
    public IntPtr hStdInput;
    public IntPtr hStdOutput;
    public IntPtr hStdError;
}

public struct SECURITY_ATTRIBUTES
{
    public int length;
    public IntPtr lpSecurityDescriptor;
    public bool bInheritHandle;
}

#endregion

namespace A_cool_launcher.Methods
{
    class Configuration
    {
        #region Imports

        [DllImport("kernel32.dll")]
        static extern bool CreateProcess(string lpApplicationName, string lpCommandLine, IntPtr lpProcessAttributes, IntPtr lpThreadAttributes, bool bInheritHandles, uint dwCreationFlags, IntPtr lpEnvironment, string lpCurrentDirectory, ref STARTUPINFO lpStartupInfo, out PROCESS_INFORMATION lpProcessInformation);

        [DllImport("kernel32.dll")]
        static extern uint ResumeThread(IntPtr hThread);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool TerminateProcess(IntPtr hProcess, uint uExitCode);

        #endregion

        #region Variables

        static RegistryKey MSkey = Registry.LocalMachine.OpenSubKey("SOFTWARE\\Wizet\\").OpenSubKey("MapleStory");

        static string MSpath;

        static string DIRname = Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData) + "\\" + "MSB" + "\\";

        static string DLLname;

        static STARTUPINFO StartupInfo;

        static PROCESS_INFORMATION ProcessInfo;

        #endregion

        public static bool RetrievePath()
        {
            try
            {
                if (MessageBox.Show("Would you like to automatically launch MapleStory?", "Launch", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (File.Exists(MSkey.GetValue("ExecPath").ToString() + @"\MapleStory.exe"))
                    {
                        MSpath = MSkey.GetValue("ExecPath").ToString() + @"\MapleStory.exe";

                        MSkey.Close();

                        return true;
                    }
                    else
                    {
                        if (File.Exists(MSkey.GetValue("Executable").ToString()))
                        {
                            MSpath = MSkey.GetValue("Executable").ToString();

                            MSkey.Close();

                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    OpenFileDialog dialog = new OpenFileDialog();

                    if (dialog.ShowDialog() == DialogResult.OK)
                    {
                        MSpath = dialog.FileName;

                        MSkey.Close();

                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool CreateProcess()
        {
            try
            {
                StartupInfo = new STARTUPINFO();

                ProcessInfo = new PROCESS_INFORMATION();

                if (CreateProcess(MSpath, " WebStart", IntPtr.Zero, IntPtr.Zero, false, 4, IntPtr.Zero, null, ref StartupInfo, out ProcessInfo))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool CreateFile()
        {
            try
            {
                if (!Settings.Default.destroy)
                {
                    if (Directory.Exists(DIRname))
                    {
                        Directory.Delete(DIRname, true);

                        Settings.Default.destroy = true;
                        Settings.Default.Save();
                    }
                }

                if (!Directory.Exists(DIRname))
                {
                    Directory.CreateDirectory(DIRname);
                }

                if (File.Exists(Settings.Default.path))
                {
                    File.Delete(Settings.Default.path);
                }

                DLLname = DIRname + ProcessInfo.dwProcessId.ToString();

                File.WriteAllBytes(DLLname + ".dll", Resource.A_cool_trainer);

                Settings.Default.path = DLLname + ".dll";
                Settings.Default.Save();

                return true;
            }
            catch
            {
                TerminateProcess(ProcessInfo.hProcess, 0);

                return false;
            }
        }

        public static bool InjectDll()
        {
            try
            {
                int ProcessID = Convert.ToInt32(ProcessInfo.dwProcessId);

                IntPtr hProcess = (IntPtr)Methods.Inject.OpenProcess(0x1F0FFF, 1, ProcessID);

                if (hProcess != null)
                {
                    Methods.Inject.InjectDLL(hProcess, DLLname);

                    ResumeThread(ProcessInfo.hThread);
                    
                    return true;
                }
                else
                {
                    TerminateProcess(ProcessInfo.hProcess, 0);

                    return false;
                }
            }
            catch
            {
                TerminateProcess(ProcessInfo.hProcess, 0);

                return false;
            }
        }
    }
}