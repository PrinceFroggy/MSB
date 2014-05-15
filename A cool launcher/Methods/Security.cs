using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Net;
using System.Windows.Forms;

namespace A_cool_launcher.Methods
{
    class Security
    {
        public static bool Version()
        {
            try
            {
                WebRequest request = WebRequest.Create("http://download.m-84.com/version/");
                
                WebResponse response = request.GetResponse();
                
                System.IO.StreamReader reader = new System.IO.StreamReader(response.GetResponseStream());

                string versionNumber = reader.ReadToEnd();

                if (versionNumber == "6\n")
                {
                    return false;
                }
                else
                {
                    MessageBox.Show("Update available at: download.m-84.com", "Update", MessageBoxButtons.OK);
                    
                    return true;
                }
            }
            catch
            {
                return false;
            }
        }

        public static bool Running()
        {
            try
            {
                foreach (Process clsProcess in Process.GetProcesses())
                {
                    if (clsProcess.ProcessName.Contains("MapleStory"))
                    {
                        return true;
                    }
                }
                return false;
            }
            catch
            {
                return false;
            }
        }
    }
}
