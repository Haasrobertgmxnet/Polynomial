using System;
//using Polynomial.Dll.CLI;

namespace Polynomial.Wpf
{
    class Process
    {
        string inString = string.Empty;
        string outString = string.Empty;
        readonly double[] vals = new double[10];

        public Process()
        {
            var rand = new Random();

            for (int j = 0; j < 10; j++)
            {
                vals[j] = 5.0 * (2.0 * rand.NextDouble() - 1.0);
            }

            InString = "Gleichung vierten Grades\n";
            InString += "gegeben als A*Z^4 + B*Z^3 + C*Z^2 + D*Z + E = 0\n";
            InString += "Die komplexen Zahlen A, B, C, D und E kommen aus dem\n";
            InString += "Pseudozufallszahlengenerator\n\n";

            for (var j = 0; j < 10; j += 2)
            {
                char character = (char)(65 + j / 2);
                InString += character.ToString() + ": " + vals[j].ToString() + "+" + vals[j + 1].ToString() + "i\n";
            }
        }

        public void Do()
        {
            using (var wrapper = new Polynomial.Dll.CLI.Polynomial(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5], vals[6], vals[7], vals[8], vals[9]))
            // Using block is here to make sure we release native memory right away
            {
                wrapper.FindRoots();
                wrapper.ValidateRoots();
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
