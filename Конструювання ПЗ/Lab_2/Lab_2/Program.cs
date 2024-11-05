using Lab_2;

internal class Program
{
    private static void Main(string[] args)
    {
        {
            Doctor doctor = new();
            Console.WriteLine(doctor);

            doctor.Person = new("Nick", "Nnick", new(2010, 10, 10));
            doctor.Specialty = new("Surgeon");
            doctor.Category = Category.Second;
            doctor.ExperienceYears = 10;

            Console.WriteLine();
            Console.WriteLine(doctor.ToShortString());
        }

        {
            Doctor doctor = new(new("Mike", "Mmike", new(2009, 9, 9)), "Otolaryngologist", Category.First, 2);

            Console.WriteLine();
            Console.WriteLine(doctor.ToString());

            doctor.AddDiplomas(new Diploma("St Cath Hospital", "Surgeon", new(2014, 5, 5)), new Diploma("Oxford", "Otolaryngologist", new(2013, 5, 5)));

            Console.WriteLine();
            Console.WriteLine(doctor.ToString());

            Console.WriteLine();
            Console.WriteLine(doctor.Diploma);
        }
    }
}