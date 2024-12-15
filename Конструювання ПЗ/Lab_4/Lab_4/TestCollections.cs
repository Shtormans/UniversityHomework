using System.Diagnostics;

namespace Lab_4;

internal class TestCollections
{
    private List<Person> _genericList;
    private List<string> _stringList;
    private Dictionary<Person, Doctor> _genericDictionary;
    private Dictionary<string, Doctor> _stringDictionary;

    public TestCollections(int length)
    {
        _genericList = new(length);
        _stringList = new(length);
        _genericDictionary = new(length);
        _stringDictionary = new(length);

        for (int i = 0; i < length; i++)
        {
            Doctor doctor = CreateSimpleInstance(i + 1);

            _genericList.Add(doctor);
            _stringList.Add(doctor.Surname);
            _genericDictionary[doctor.Person] = doctor;
            _stringDictionary[doctor.Surname] = doctor;
        }
    }

    public TimeSpan CalculateGenericListTimestamp(Person toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _genericList.FirstOrDefault(person => person == toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public TimeSpan CalculateStringListTimestamp(string toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _stringList.FirstOrDefault(surname => surname == toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public TimeSpan CalculateGenericDictionaryKeyTimestamp(Person toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _genericDictionary.GetValueOrDefault(toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public TimeSpan CalculateStringDictionaryKeyTimestamp(string toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _stringDictionary.GetValueOrDefault(toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public TimeSpan CalculateGenericDictionaryValueTimestamp(Doctor toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _genericDictionary.Values.FirstOrDefault(doctor => doctor == toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public TimeSpan CalculateStringDictionaryValueTimestamp(Doctor toFind)
    {
        long startTime = Stopwatch.GetTimestamp();

        _stringDictionary.Values.FirstOrDefault(doctor => doctor == toFind);

        return Stopwatch.GetElapsedTime(startTime);
    }

    public static Doctor CreateSimpleInstance(int extraArg)
    {
        Person person = new($"Name {extraArg}", $"Surname {extraArg}", DateTime.UtcNow.AddYears(-(extraArg > 2020 ? 1900 : extraArg)));

        return new(person, $"Specialty {extraArg}", Category.Second, extraArg);
    }
}
