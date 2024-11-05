namespace Lab_2;

public class Person
{
    private string _name;
    private string _surname;
    private DateTime _birthday;

    public Person() : this("Default Name", "Default Surname", DateTime.UtcNow)
    {
        
    }

    public Person(string name, string surname, DateTime birthday)
    {
        _name = name;
        _surname = surname;
        _birthday = birthday;
    }

    public string Name => _name;
    public string Surname => _surname;
    public DateTime Birthday => _birthday;

    public int BirthdayYear
    {
        get => _birthday.Year;
        set => _birthday = new(value, _birthday.Month, _birthday.Day);
    }

    public override string ToString()
    {
        return $"{nameof(Name)}: {_name},\n{nameof(Surname)}: {_surname},\n{nameof(Birthday)}: {Birthday:d}";
    }

    public string ToShortString()
    {
        return $"{nameof(Name)}: {_name},\n{nameof(Surname)}: {_surname}";
    }
}
