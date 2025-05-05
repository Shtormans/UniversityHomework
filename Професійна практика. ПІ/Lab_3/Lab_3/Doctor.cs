using Newtonsoft.Json;
using System.Text;
namespace Lab_3;

internal class Doctor
{
    private int _experienceYears;
    private List<Diploma> _diplomas;

    public Doctor()
    {
        Specialty = string.Empty;
        Category = Category.First;
        _experienceYears = 0;
        _diplomas = [];
    }

    public Doctor(string specialty, Category category, int experienceYears, List<Diploma> diplomas)
    {
        Specialty = specialty;
        Category = category;
        _experienceYears = experienceYears;
        _diplomas = diplomas;
    }

    public string Specialty { get; set; }

    public Category Category { get; set; }

    public int ExperienceYears
    {
        get => _experienceYears;
        set
        {
            if (value < 0 || value > 100)
            {
                throw new ArgumentOutOfRangeException("Experience years can't be less less than 0 and more than 100");
            }

            _experienceYears = value;
        }
    }

    public IReadOnlyList<Diploma> Diplomas => _diplomas;

    public override string ToString()
    {
        StringBuilder builder = new();

        builder.Append($"Specialty: {Specialty}\n");
        builder.Append($"Category: {Category}\n");
        builder.Append($"Experience years: {ExperienceYears}\n");
        builder.Append($"Diplomas:\n{string.Join("\n", Diplomas)}\n");

        return builder.ToString();
    }

    public Doctor DeepCopy()
    {
        return Deserialize(Serialize());
    }

    public bool Save(string fileName)
    {
        try
        {
            string json = Serialize();
            File.WriteAllText(fileName, json);

        }
        catch (Exception)
        {
            return false;
        }

        return true;
    }

    public bool Load(string fileName)
    {
        string json;
        try
        {
            json = File.ReadAllText(fileName);
            Doctor copy = Deserialize(json);

            _experienceYears = copy.ExperienceYears;
            Specialty = copy.Specialty;
            Category = copy.Category;
            _diplomas = copy._diplomas;
        }
        catch (Exception)
        {
            return false;
        }


        return true;
    }

    public bool AddFromConsole()
    {
        Console.Write("Enter diploma in format (organization, qualification, issueDate(dd.mm.yyyy)): ");
        string text = Console.ReadLine()!;

        try
        {
            string[] splitText = text.Split(", ");

            string organization = splitText[0];
            string qualification = splitText[1];
            DateTime issueDate = DateTime.Parse(splitText[2]);

            Diploma diploma = new(organization, qualification, issueDate);
            _diplomas.Add(diploma);
        }
        catch (Exception)
        {
            Console.WriteLine("Input was wrong!");
            return false;
        }


        return true;
    }

    public static bool Save(string fileName, Doctor doctor)
    {
        return doctor.Save(fileName);
    }

    public static bool Load(string fileName, Doctor doctor)
    {
        return doctor.Load(fileName);
    }

    private string Serialize()
    {
        return JsonConvert.SerializeObject(this);
    }

    private Doctor Deserialize(string json)
    {
        return JsonConvert.DeserializeObject<Doctor>(json)!;
    }
}
