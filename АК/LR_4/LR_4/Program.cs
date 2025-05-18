using System.IO;

internal class Program
{
    private static void Main(string[] args)
    {
        if (args.Length == 1 && (args[0] == "/h" || args[0] == "-h" || args[0] == "--help"))
        {
            DisplayHelpScreen();
            return;
        }

        var (folderArgs, patterns) = ParseParameters(args);

        foreach (string directory in folderArgs)
        {
            CheckDirectory(directory, patterns);
        }
    }

    private static void CheckDirectory(string directory, List<string> patterns)
    {
        if (!Directory.Exists(directory))
        {
            Console.WriteLine($"Папки '{directory}' немає!");
            return;
        }

        patterns.ForEach(pattern =>
        {
            foreach (string file in Directory.GetFiles(directory, pattern, SearchOption.AllDirectories))
            {
                FileAttributes attr = File.GetAttributes(file);
                if ((attr & FileAttributes.ReadOnly) == FileAttributes.ReadOnly)
                {
                    Console.WriteLine($"Read-only file, can't delete: {file}");
                    return;
                }
                if ((attr & FileAttributes.Hidden) == FileAttributes.Hidden)
                {
                    Console.WriteLine($"Deleting hidden file: {file}");
                }
                if ((attr & FileAttributes.Archive) == FileAttributes.Archive)
                {
                    Console.WriteLine($"Deleting archived file: {file}");
                }
                else
                {
                    Console.WriteLine($"Deleting {Path.GetFullPath(file)}");
                }

                File.Delete(file);
            }
        });
    }

    private static (List<string>, List<string>) ParseParameters(string[] args)
    {
        List<string> folderArgs = [];
        List<string> patterns = [];

        if (args.Length == 0)
        {
            return ([Directory.GetCurrentDirectory()], ["*"]);
        }

        foreach (string arg in args)
        {
            if (arg.Contains('*') || arg.Contains('?'))
            {
                patterns.Add(arg);
            }
            else
            {
                folderArgs.Add(arg);
            }
        }

        if (folderArgs.Count == 0)
        {
            folderArgs.Add(Directory.GetCurrentDirectory());
        }
        
        if (patterns.Count == 0)
        {
            patterns.Add("*");
        }

        return (folderArgs, patterns);
    }

    static void DisplayHelpScreen()
    {
        Console.WriteLine("Викорситання:");
        Console.WriteLine("/h                                Допомога");
        Console.WriteLine("[каталог_1] [каталог_2] [...]     Видалити файли з папок");
        Console.WriteLine("[каталог_1] <патерн_1> [...]      Видалити файли з патернами");
    }
}
