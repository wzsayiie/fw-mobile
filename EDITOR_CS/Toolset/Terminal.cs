using System;

class Terminal
{
    private int LeftEndlines { get; set; }

    private void Write(int wantedEndlines, string format, params object[] args)
    {
        //1 add wanted endlines.
        if (LeftEndlines < wantedEndlines)
        {
            for (int it = LeftEndlines; it < wantedEndlines; ++it)
            {
                Console.Write("\n");
            }
            LeftEndlines = wantedEndlines;
        }

        //2 write this output.
        string message = "";
        try
        {
            message = string.Format(format, args);
            Console.Write(message);
        }
        catch (Exception)
        {
            Console.Write("");
        }

        //3 count endlines from this output.
        int count = 0;
        for (int it = message.Length - 1; it >= 0; --it)
        {
            if (message[it] == '\n')
            {
                count++;
            }
            else
            {
                break;
            }
        }

        if (count == message.Length)
        {
            //all characters are '\n'
            LeftEndlines += count;
        }
        else
        {
            LeftEndlines = count;
        }
    }

    // example:
    //
    //  Terminal.WriteLine(""); //start a new line and write new text.
    //  Terminal.Spac(N).W(""); //interval N blank lines from the last output and write new text.
    //  Terminal.WriteText(""); //write new text close to the last output text.
    //

    private static readonly Terminal SharedObject = new Terminal();

    public static void WriteLine(string format, params object[] args)
    {
        SharedObject.Write(1, format, args);
    }

    public static void WriteText(string format, params object[] args)
    {
        SharedObject.Write(0, format, args);
    }

    public static Terminal Spac(int wantedEndline)
    {
        SharedObject.Write(wantedEndline + 1, null);
        return SharedObject;
    }
    public void W(string format, params object[] args)
    {
        SharedObject.Write(0, format, args);
    }
}
