namespace Lab_4;

internal class DoctorCollection
{
    private const int DefaultDoctorsCount = 3;
    private List<Doctor> _doctors = new();

    public delegate void DoctorListHandler(object source, DoctorListHandlerEventArgs args);

    public event DoctorListHandler DoctorAdded;
    public event DoctorListHandler DoctorReplaced;
    
    public DoctorCollection(string collectionName)
    {
        CollectionName = collectionName;
    }

    public string CollectionName { get; private set; }

    public bool Replace(int index, Doctor doctor)
    {
        if (index < 0 || index >= _doctors.Count)
        {
            return false;
        }
        
        _doctors[index] = doctor;
        
        DoctorReplaced?.Invoke(this, new DoctorListHandlerEventArgs(CollectionName, "Replaced doctor", index));
        
        return true;
    }
    
    public void AddDefaults()
    {
        _doctors = Enumerable
            .Range(0, DefaultDoctorsCount)
            .Select(TestCollections.CreateSimpleInstance)
            .ToList();
        
        DoctorAdded?.Invoke(this, new DoctorListHandlerEventArgs(CollectionName, "Added doctors", _doctors.Count));
    }

    public void AddDoctors(params Doctor[] doctors)
    {
        _doctors.AddRange(doctors);
        
        DoctorAdded?.Invoke(this, new DoctorListHandlerEventArgs(CollectionName, "Added doctors", _doctors.Count));
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
    
    public Doctor this[int index]
    {
        get => _doctors[index];
        set => Replace(index, value);
    }
}
