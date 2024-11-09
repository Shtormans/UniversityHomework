using Lab_3;

internal class Program
{
    private static void Main(string[] args)
    {
        Person person1 = new("Nick", "Nnick", new(1999, 12, 12));
        Person person2 = new("Nick", "Nnick", new(1999, 12, 12));

        Console.WriteLine(person1 == person2);
        Console.WriteLine();

        Doctor doctor = new(person1, "Surgery", Category.High, 20);
        
        doctor.AddDiplomas([
            new Diploma("Organization1", "Qualification1", DateTime.UtcNow.AddYears(-25)), 
            new Diploma("Organization2", "Qualification2", DateTime.UtcNow.AddYears(-12)),
            new Diploma("Organization3", "Qualification3", DateTime.UtcNow.AddYears(-32)),
            new Diploma("Organization4", "Qualification4", DateTime.UtcNow.AddYears(-40)),
            new Diploma("Organization5", "Qualification5", DateTime.UtcNow.AddYears(-16))
        ]);

        doctor.Patients = 
        [
            new Patient(new Person("Name1", "Surname1", DateTime.UtcNow.AddYears(-20)), "Diagnosis1", DateTime.UtcNow),
            new Patient(new Person("Name2", "Surname2", DateTime.UtcNow.AddYears(-25)), "Diagnosis2", DateTime.UtcNow),
            new Patient(new Person("Name3", "Surname3", DateTime.UtcNow.AddYears(-30)), "Diagnosis1", DateTime.UtcNow.AddDays(-28)),
            new Patient(new Person("Name4", "Surname4", DateTime.UtcNow.AddYears(-15)), "Diagnosis2", DateTime.UtcNow.AddDays(-40)),
            new Patient(new Person("Name5", "Surname5", DateTime.UtcNow.AddYears(-23)), "Diagnosis1", DateTime.UtcNow.AddDays(-45)),
            new Patient(new Person("Name6", "Surname6", DateTime.UtcNow.AddYears(-24)), "Diagnosis2", DateTime.UtcNow.AddDays(-50))
        ];

        Console.WriteLine(doctor.Person.ToString());
        Console.WriteLine();

        Doctor doctorCopy = (Doctor)doctor.DeepCopy();
        doctorCopy.Patients[0].Name = "Name0";
        doctorCopy.Patients[0].Diagnosis = "Diagnosis0";

        Console.WriteLine("Original:");
        Console.WriteLine(doctor);
        Console.WriteLine();
        Console.WriteLine("Copy");
        Console.WriteLine(doctorCopy);
        Console.WriteLine();

        try
        {
            doctor.ExperienceYears = 102;
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine();

        foreach (Patient patient in doctor.GetPatients().Where(patient => patient.AdmissionDate.Date == DateTime.UtcNow.Date))
        {
            Console.WriteLine(patient.ToString());
        }

        Console.WriteLine();

        foreach (Patient patient in doctor.GetPatients("Diagnosis1"))
        {
            Console.WriteLine(patient.ToString());
        }

        Console.WriteLine();

        foreach (Diploma diploma in doctor)
        {
            Console.WriteLine(diploma.ToString());
        }

        Console.WriteLine();

        foreach (Patient patient in doctor.GetPatientsLessThanMonth())
        {
            Console.WriteLine(patient.ToString());
        }
    }
}