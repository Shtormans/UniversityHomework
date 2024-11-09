namespace Lab_3;

internal class Person : IDateAndCopy
{
    protected string _name;
    protected string _surname;
    protected DateTime _birthday;

    public Person() : this("Default Name", "Default Surname", DateTime.UtcNow)
    {

    }

    public Person(string name, string surname, DateTime birthday)
    {
        Name = name;
        Surname = surname;
        Birthday = birthday;
    }

    public DateTime Date { get; set; }
    public string Name { get => _name; set => _name = value; }
    public string Surname { get => _surname; set => _surname = value; }
    public DateTime Birthday { get => _birthday; set => _birthday = value; }

    public int BirthdayYear
    {
        get => Birthday.Year;
        set => Birthday = new(value, Birthday.Month, Birthday.Day);
    }

    public override string ToString()
    {
        return $"{nameof(Name)}: {Name},\n{nameof(Surname)}: {Surname},\n{nameof(Birthday)}: {Birthday:d}";
    }

    public virtual string ToShortString()
    {
        return $"{nameof(Name)}: {Name},\n{nameof(Surname)}: {Surname}";
    }

    public virtual object DeepCopy()
    {
        return new Person(Name, Surname, Birthday);
    }

    public override bool Equals(object? obj)
    {
        if (obj is not Person person)
        {
            return false;
        }

        return person == this;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Name, Surname, Birthday);
    }

    public static bool operator==(Person left, Person right)
    {
        return left is not null 
            && right is not null 
            && left.GetHashCode() == right.GetHashCode();
    }

    public static bool operator !=(Person left, Person right)
    {
        return !(left == right);
    }
}
