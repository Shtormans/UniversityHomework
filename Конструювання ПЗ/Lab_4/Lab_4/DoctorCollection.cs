namespace Lab_4;

internal class DoctorCollection
{
    private List<Doctor> _doctors = new();

    public void AddDefaults()
    {
        
    }

    public void AddDoctors(params Doctor[] doctors)
    {
        _doctors.AddRange(doctors);
    }

    public void SortBySurname()
    {
        _doctors.Sort();
    }

    public void SortByBirthday()
    {
        _doctors.Sort(new Person());
    }

    public void SortByExperience()
    {
        _doctors.Sort(new DoctorComparer());
    }

    public override string ToString()
    {
        return string.Join("\n", _doctors);
    }

    public string ToShortString()
    {
        return string.Join("\n", _doctors.Select(doctor => doctor.ToShortString()));
    }
}
