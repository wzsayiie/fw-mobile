using System;

class L
{
    private static L SharedObject = new L();

    private int NCountAtLast;
    private int NCountRequired;

    public void Write(string format, params object[] args)
    {
        //1 add required line-ending
        if (NCountAtLast < NCountRequired)
        {
            for (int it = NCountAtLast; it < NCountRequired; ++it)
            {
                Console.Write("\n");
            }
            NCountAtLast = NCountRequired;
        }

        //2 print this output
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

        int nCount = 0;
        for (int it = message.Length - 1; it >= 0; --it)
        {
            if (message[it] == '\n')
            {
                nCount++;
            }
            else
            {
                break;
            }
        }

        //3 record
        if (nCount == message.Length)
        {
            //all chars are '\n'
            NCountAtLast += nCount;
        }
        else
        {
            NCountAtLast = nCount;
        }
    }

    public static L StartNewLine
    {
        get
        {
            SharedObject.NCountRequired = 1;
            return SharedObject;
        }
    }

    public static L ContinueLast
    {
        get
        {
            SharedObject.NCountRequired = 0;
            return SharedObject;
        }
    }

    public static L SpaceLine(int n)
    {
        SharedObject.NCountRequired = n + 1;
        SharedObject.Write("");

        SharedObject.NCountRequired = 0;
        return SharedObject;
    }
}
