using System.Collections;
using System.Collections.Generic;

namespace Lab_4;

internal class Doctor : Person, IEnumerable<Diploma>
{
    private string _specialty;
    private Category _category;
    private int _experienceYears;
    private List<Diploma> _diplomas;
    private List<Patient> _patients;

    public Doctor() : this(new(), "Default Specialty", default, 1)
    {

    }

    public Doctor(Person person, string specialty, Category category, int experienceYears)
    {
        Name = person.Name;
        Surname = person.Surname;
        Birthday = person.Birthday;

        _specialty = specialty;
        _category = category;
        _experienceYears = experienceYears;

        _diplomas = [];
        _patients = [];
    }

    public Person Person => (Person)base.DeepCopy();

    public string Specialty
    {
        get => _specialty;
        set => _specialty = value;
    }

    public Category Category
    {
        get => _category;
        set => _category = value;
    }

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

    public List<Diploma> Diplomas
    {
        get => _diplomas;
        set => _diplomas = value;
    }

    public List<Patient> Patients
    {
        get => _patients;
        set => _patients = value;
    }

    public Diploma Diploma => _diplomas.MinBy(diploma => diploma.IssueDate)!;

    public void AddDiplomas(params Diploma[] diplomas)
    {
        _diplomas = _diplomas.Concat(diplomas).ToList();
    }

    public override string ToString()
    {
        return $"{nameof(Person)}:\n{Person},\n{nameof(Specialty)}: {Specialty},\n{nameof(Category)}: {Category},\n{nameof(ExperienceYears)}: {ExperienceYears},\n{nameof(Diplomas)}:\n{string.Join(";\n", Diplomas)}\n{nameof(Patients)}:\n{string.Join(";\n", Patients)}";
    }

    public override string ToShortString()
    {
        return $"{nameof(Person)}: {Person},\n{nameof(Specialty)}: {Specialty},\n{nameof(Category)}: {Category},\n{nameof(ExperienceYears)}: {ExperienceYears},\n{nameof(Diplomas)}: {_diplomas.Count}\n{nameof(Patients)}: {_patients.Count}";
    }

    public override object DeepCopy()
    {
        Doctor copy = new(Person, Specialty, Category, ExperienceYears);
        copy._diplomas = _diplomas.Select(diploma => diploma.Clone()).ToList();
        copy._patients = _patients.Select(patient => patient.Clone()).ToList();

        return copy;
    }

    public IEnumerable<Patient> GetPatients()
    {
        foreach (Patient patient in _patients)
        {
            yield return patient;
        }
    }

    public IEnumerable<Patient> GetPatients(string diagnosis)
    {
        foreach (Patient patient in _patients)
        {
            if (patient.Diagnosis != diagnosis)
            {
                continue;
            }

            yield return patient;
        }
    }

    public IEnumerable<Patient> GetPatientsLessThanMonth()
    {
        DateTime comparingDate = DateTime.UtcNow.AddMonths(-1).Date;

        foreach (Patient patient in _patients)
        {
            if (patient.AdmissionDate.Date >= comparingDate)
            {
                continue;
            }

            yield return patient;
        }
    }

    public IEnumerator<Diploma> GetEnumerator()
    {
        return new DoctorEnumerator(_diplomas);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return new DoctorEnumerator(_diplomas);
    }

    private class DoctorEnumerator : IEnumerator<Diploma>
    {
        private IEnumerator<Diploma> _enumerator;

        public DoctorEnumerator(List<Diploma> diplomas)
        {
            _enumerator = diplomas.GetEnumerator();
            _enumerator = diplomas.Where(diploma => diploma.IssueDate.Year < 2000).GetEnumerator();
        }

        public Diploma Current => _enumerator.Current;
        object IEnumerator.Current => _enumerator.Current;

        public void Dispose()
        {
            _enumerator.Dispose();
        }

        public bool MoveNext()
        {
            return _enumerator.MoveNext();
        }

        public void Reset()
        {
            _enumerator.Reset();
        }
    }
}
