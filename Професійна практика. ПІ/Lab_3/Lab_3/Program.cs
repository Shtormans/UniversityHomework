using Bogus;
using Lab_3;
using System.Runtime.CompilerServices;

internal class Program
{
    private static void Test(int tes, [CallerArgumentExpression(nameof(tes))] string? paramName = null)
    {
        Console.WriteLine(paramName);
    }

    private static void Main(string[] args)
    {
        int a = 2;
        Test(2);

        Diploma diploma = new Diploma("Test organization", "Test qualification", DateTime.Now);
        Doctor doctor = new("Specialty 1", Category.Second, 3, [diploma]);

        Doctor doctorCopy = doctor.DeepCopy();

        Console.WriteLine("Original");
        Console.WriteLine(doctor);
        Console.WriteLine("Copy");
        Console.WriteLine(doctorCopy);

        Console.WriteLine();
        Console.Write("Input file name: ");



        string fileName = Console.ReadLine()!;

        if (!File.Exists(fileName))
        {
            Console.WriteLine("There is no such file. Creating one.");
            doctor.Save(fileName);
        }

        Doctor doctorFromFile = new();
        Doctor.Load(fileName, doctorFromFile);

        Console.WriteLine("Doctor from file");
        Console.WriteLine(doctorFromFile);

        doctorFromFile.AddFromConsole();
        doctorFromFile.Save(fileName);

        Console.WriteLine();
        Console.WriteLine("Updated doctor from file");
        Console.WriteLine(doctorFromFile);

        Doctor.Load(fileName, doctorFromFile);
        doctorFromFile.AddFromConsole();
        Doctor.Save(fileName, doctorFromFile);

        Console.WriteLine();
        Console.WriteLine("Updated doctor from file");
        Console.WriteLine(doctorFromFile);

        new Faker<Doctor>().RuleFor(x => x.Specialty, faker => faker.Person.FirstName).Generate(100);
    }
}