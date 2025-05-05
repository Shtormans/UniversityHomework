namespace Lab_2;

internal class Program
{
    private static void Main(string[] args)
    {
        DoctorCollection<string> collection1 = new(CalculateDoctorKey);
        DoctorCollection<string> collection2 = new(CalculateDoctorKey);

        collection1.CollectionName = "Collection 1";
        collection2.CollectionName = "Collection 2";

        Listener listener = new();

        collection1.DoctorsChanged += listener.OnDoctorsChanged;
        collection2.DoctorsChanged += listener.OnDoctorsChanged;

        Doctor testDoctor1 = new Doctor(new Person("Test person 1", "Test p", DateTime.Now), "Random specialty 1", Category.Second, 2);
        Doctor testDoctor2 = new Doctor(new Person("Test person 2", "Test p", DateTime.Now), "Random specialty 1", Category.Second, 2);

        collection1.AddDoctor(testDoctor1);
        testDoctor1.Category = Category.First;
        collection1.Replace(testDoctor1, testDoctor2);

        testDoctor1.ExperienceYears = 1;
        collection2.AddDoctor(testDoctor2);

        collection1.AddDoctor(testDoctor1);

        Console.WriteLine(listener);
        Console.WriteLine();

        Console.WriteLine($"Max experience points in collection 1: {collection1.MaxExperienceYears}");
        Console.WriteLine();
        Console.WriteLine(string.Join("\n", collection1.CategoryForm(Category.Second).Select(pair => pair.Value.ToShortString())));
        Console.WriteLine();
        Console.WriteLine(string.Join("\n", collection1.GrouppedDoctors.Select(pair => $"{pair.Key}\n{string.Join("\n", pair.Select(doctor => doctor.Value.ToShortString()))}\n")));
        Console.WriteLine();
        Console.WriteLine(string.Join("\n", collection1.GetListBySpecialty("Random specialty 1").Select(doctor => doctor.ToShortString())));
    }

    private static string CalculateDoctorKey(Doctor doctor)
    {
        return $"{doctor.Name}_{doctor.Birthday.Ticks}";
    }
}