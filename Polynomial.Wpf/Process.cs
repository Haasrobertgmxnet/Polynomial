using System;
using System.Collections.Generic;
using System.Numerics;

namespace Polynomial.Wpf
{
    class Process
    {
        string inString = string.Empty;
        string outString = string.Empty;

        public Dictionary<string, double> Coefficients = new Dictionary<string, double>()
        {
            {"coefficientARe",0.0 },{"coefficientAIm",0.0 },
            {"coefficientBRe",0.0 },{"coefficientBIm",0.0 },
            {"coefficientCRe",0.0 },{"coefficientCIm",0.0 },
            {"coefficientDRe",0.0 },{"coefficientDIm",0.0 },
            {"coefficientERe",0.0 },{"coefficientEIm",0.0 }
        };

        public Process()
        {
            var rand = new Random((int)DateTime.Now.Ticks);

            List<string> keys = new List<string>(Coefficients.Keys);
            foreach (string key in keys)
            {
                Coefficients[key] = 5.0 * (2.0 * rand.NextDouble() - 1.0);
            }
        }

        public void Do()
        {
            using (var wrapper = new Polynomial.Dll.CLI.Polynomial(
                Coefficients["coefficientARe"], Coefficients["coefficientAIm"],
            Coefficients["coefficientBRe"], Coefficients["coefficientBIm"],
            Coefficients["coefficientCRe"], Coefficients["coefficientCIm"],
            Coefficients["coefficientDRe"], Coefficients["coefficientDIm"],
            Coefficients["coefficientERe"], Coefficients["coefficientEIm"]))
            // Using block is here to make sure we release native memory right away
            {
                wrapper.FindRoots();
                wrapper.ValidateRoots();

                InString = "Gleichung vierten Grades\n";
                InString += "gegeben als A*Z^4 + B*Z^3 + C*Z^2 + D*Z + E = 0\n";

                foreach (var elem in Coefficients)
                {
                    string s;
                    elem.Key.Substring(11, 1);
                    if (elem.Key.Substring(12, 2) == "Re")
                    {
                        InString += elem.Key.Substring(11, 1) + ": " + elem.Value;
                    }
                    if (elem.Key.Substring(12, 2) == "Im")
                    {
                        InString += "+" + elem.Value + "i\n";
                    }
                }
                OutString = "\nDie Lösungen:\n";
                for (uint j = 0; j < 4; j++)
                {
                    OutString += "Lösung " + (j + 1).ToString() + ": " + wrapper.GetRoot(j, 0) + "+" + wrapper.GetRoot(j, 1) + "i\n";
                }
                OutString += "Fehler: " + wrapper.GetResultError();
            }
        }

        public string InString { get => inString; set => inString = value; }
        public string OutString { get => outString; set => outString = value; }
    }
}
