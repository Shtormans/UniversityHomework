using System.ComponentModel;

namespace Lab_2;

internal class DoctorCollection<TKey>
{
    private readonly KeySelector<TKey> _calculateKey;
    private readonly Dictionary<TKey, Doctor> _doctors = [];

    public event DoctorsChangedHandler<TKey> DoctorsChanged;

    public DoctorCollection(KeySelector<TKey> calculateKey)
    {
        _calculateKey = calculateKey;
    }

    public string CollectionName { get; set; }
    public int MaxExperienceYears => _doctors.Max(pair => pair.Value.ExperienceYears);
    public IEnumerable<IGrouping<Category, KeyValuePair<TKey, Doctor>>> GrouppedDoctors => _doctors.GroupBy(pair => pair.Value.Category);

    public void AddDefaults()
    {
        for (int i = 0; i < 5; i++)
        {
            Doctor doctor = new(new($"TestPerson {i + 1}", "TT", DateTime.Now), $"TestSpecialty {i + 1}", Category.High, i + 4);
            AddDoctor(doctor);
        }
    }

    public void AddDoctor(params Doctor[] doctors)
    {
        foreach (Doctor doctor in doctors)
        {
            TKey key = _calculateKey(doctor);
            _doctors[key] = doctor;

            doctor.PropertyChanged += NotifyPropertyUpdate;

            NotifyDoctorAddition(doctor);
        }
    }

    public bool Replace(Doctor doctorOld, Doctor doctorNew)
    {
        TKey key = _calculateKey(doctorOld);

        if (!_doctors.TryGetValue(key, out var _))
        {
            return false;
        }

        _doctors[key].PropertyChanged -= NotifyPropertyUpdate;
        _doctors.Remove(key);

        key = _calculateKey(doctorNew);
        _doctors[key] = doctorNew;
        doctorNew.PropertyChanged += NotifyPropertyUpdate;

        NotifyDoctorReplacement(doctorNew);

        return true;
    }

    public IEnumerable<KeyValuePair<TKey, Doctor>> CategoryForm(Category value)
    {
        return _doctors.Where(pair => pair.Value.Category == value);
    }

    public List<Doctor> GetListBySpecialty(string specialty)
    {
        return _doctors.CreateDoctorList(specialty);
    }

    public string ToShortString()
    {
        return string.Join("\n", _doctors.Values.Select(doctor => doctor.ToShortString()));
    }

    public override string ToString()
    {
        return string.Join("\n", _doctors.Values);
    }

    private void NotifyDoctorAddition(Doctor doctor)
    {
        TKey key = _calculateKey(doctor);
        DoctorsChangedEventArgs<TKey> args = new(CollectionName, DoctorUpdateType.Add, string.Empty, key);

        DoctorsChanged?.Invoke(this, args);
    }

    private void NotifyDoctorReplacement(Doctor doctor)
    {
        TKey key = _calculateKey(doctor);
        DoctorsChangedEventArgs<TKey> args = new(CollectionName, DoctorUpdateType.Replace, string.Empty, key);

        DoctorsChanged?.Invoke(this, args);
    }

    private void NotifyPropertyUpdate(object? sender, PropertyChangedEventArgs e)
    {
        TKey key = _calculateKey((sender as Doctor)!);
        DoctorsChangedEventArgs<TKey> args = new(CollectionName, DoctorUpdateType.Property, e.PropertyName!, key);

        DoctorsChanged?.Invoke(this, args);
    }
}
